/*

  INScore Project

  Copyright (C) 2015  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#include <fstream>
#include <sstream>
#include <QStandardPaths>

#include "TILoader.h"
#include "IAppl.h"
#include "INScore.h"
#include "ITLparser.h"
#include "IGlue.h"
#include "IMessage.h"
#include "IObject.h"

#include "OSCAddress.h"
#include "QFileDownloader.h"
#include "../QArchive/QArchive.h"

using namespace std;

namespace inscore
{


//--------------------------------------------------------------------------
std::string TILoader::makeAbsolutePath( const std::string& path, const std::string& file )
{
	char ending = path[path.length()-1];
#ifdef WIN32
		const char* sep = (ending == '/') || (ending == '\\') ? "" : "/";
		return ( file[1] != ':') ? ( path + sep + file ) : file ;
#else
		const char* sep = (ending == '/') ? "" : "/";
		return ( file[0] != '/' ) ? ( path + sep + file ) : file ;
#endif
}


//--------------------------------------------------------------------------
bool TILoader::process (const SIMessageList& msgs, IObject* root, const string& baseaddress)
{
	bool error = false;
	for (IMessageList::TMessageList::const_iterator i = msgs->list().begin(); i != msgs->list().end(); i++) {
		IMessage * msg = *i;
		string address;
		if (msg->relativeAddress())
			address = msg->relative2absoluteAddress (baseaddress);
		else
			address = msg->address();
		string beg  = OSCAddress::addressFirst(address);
		string tail = OSCAddress::addressTail(address);
		int ret = root->processMsg(beg, tail, *i);
		IGlue::trace(*i, ret);
		error |= ret==MsgHandler::kBadAddress||ret==MsgHandler::kBadParameters;
	}
	return !error;
}

//--------------------------------------------------------------------------
bool TILoader::isBundle(const std::string& file)
{
	const string bundleExtension = ".ibundle";
	size_t len = bundleExtension.size();
	return (file.size() > len) && (file.substr(file.size()-len) == bundleExtension);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus TILoader::loadBundle(const std::string& srcfile, const std::string& rootpath)
{
	// ---- Load a bundle ----
	qarchive::QArchive* a = 0;
	QFileDownloader downloader;
	qarchive::QArchiveError error;

	if (Tools::isurl(srcfile)) {
		if (downloader.get (srcfile.c_str()) && downloader.dataSize()) {
#ifdef __MOBILE__
			//On mobile devices bundle should be stored
			QString path = QStandardPaths::standardLocations(QStandardPaths::DownloadLocation).last();
			path += QString("/bundles") + srcfile.substr(srcfile.find_last_of('/')).c_str();
			QFile f(path);
			if(f.open(QIODevice::WriteOnly)){
				f.write(downloader->byteArray());
				f.close();
			}
#endif
			a = qarchive::QArchive::readArchiveFromData(& (downloader.byteArray()), error);
		}
		else return MsgHandler::kBadParameters;
	}
	else {
		a = qarchive::QArchive::readArchiveFromFile(makeAbsolutePath(rootpath, srcfile).c_str(), error);
	}

	if(!error){
		float itlBundleVersion;
		if(a->header().readNbrProperty(0,itlBundleVersion) && itlBundleVersion>INScore::version())
			ITLErr << srcfile << "has been bundled for INScore " << itlBundleVersion << ": error might happened with version " << INScore::version() << ITLEndl;

		size_t id = srcfile.rfind("/");
		if(id==string::npos)
			id=0;
		else
			id++;
		std::string bundleName =  srcfile.substr(id, srcfile.size()-id-11);
		QString bundleRootPath = QDir::temp().absolutePath() + QDir::separator() + "INScore" + QDir::separator();
		bundleRootPath += QString("bundle") + QDir::separator() + QString::fromStdString(bundleName);
		error = a->extract(bundleRootPath, true);
		if(!error){
			INScore::postMessage("/ITL", "rootPath", bundleRootPath.toStdString().c_str());
			INScore::postMessage("/ITL/scene", "rootPath", bundleRootPath.toStdString().c_str());
			INScore::postMessage("/ITL", "load", "main.inscore");
		}
	}

	if(a){
		delete a;
		a=0;
	}

	switch (error) {
		case 0:
			return MsgHandler::kProcessed;
		case qarchive::FILE_NOT_FOUND:
			ITLErr << "The file \"" << srcfile<<"\" is not reachable." << ITLEndl;
			break;
		case qarchive::FILE_CORRUPTED:
			ITLErr << "The bundle \"" << srcfile<<"\" is corrupted." << ITLEndl;
			break;
		case qarchive::WRONG_PERMISSIONS:
			ITLErr << "Impossible to write in the temporary folder." << ITLEndl;
			break;
		default:
			ITLErr << "Unknown error" << error << ITLEndl;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
bool TILoader::loadString(const std::string& str, IObject* client)
{
	stringstream sstr (str);
	ITLparser p (&sstr, 0, client->getAppl());
	return p.parse();
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus TILoader::load(const IMessage* msg, IObject* client, const std::string& rootpath)
{
	if (msg->size() == 1) {
		string srcfile;
		if (!msg->param(0, srcfile)) return MsgHandler::kBadParameters;
		if (srcfile.size()) {

			if (Tools::isurl(rootpath) && !Tools::isurl(srcfile))
				srcfile = makeAbsolutePath(rootpath, srcfile);

			if(isBundle (srcfile))
				return loadBundle(srcfile, rootpath);			// load a bundle
			
			// not a bundle : load a script
			stringstream buff;
			ifstream file;
			if (Tools::isurl(srcfile)) {
				QFileDownloader * downloader = new QFileDownloader();
				if (!downloader) return MsgHandler::kCreateFailure;
				if (downloader->get (srcfile.c_str()) && downloader->dataSize()) {
					buff.write (downloader->data(), downloader->dataSize());
				}
				else return MsgHandler::kBadParameters;
				delete downloader;
			}
			else {
				file.open(makeAbsolutePath(rootpath, srcfile).c_str(), fstream::in);
			}

			istream * stream;
			if (file.is_open()) stream = &file;
			else stream = &buff;

			ITLparser p (stream, 0, client->getAppl());
			if (!p.parse()) {
				ITLErr << "while parsing file" << srcfile << ITLEndl;
			}
			else return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;
}

} // end namespace

