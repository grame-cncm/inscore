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

#include "TILoader.h"
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
MsgHandler::msgStatus TILoader::load(const IMessage* msg, IObject* client, const std::string& rootpath)
{
	if (msg->size() == 1) {
		string srcfile; 
		if (!msg->param(0, srcfile)) return MsgHandler::kBadParameters;
		if (srcfile.size()) {

			if (Tools::isurl(rootpath) && !Tools::isurl(srcfile))
				srcfile = makeAbsolutePath(rootpath, srcfile);

			if(srcfile.size()<11 || srcfile.substr(srcfile.size()-11,11) != ".inscorezip"){
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
				ITLparser p (stream, 0, getJSEngine(), getLUAEngine());
				SIMessageList msgs = p.parse();
				bool error = false;
				if (msgs)
					error = !process (msgs, client->getRoot(), client->getOSCAddress());
				if(error) ITLErr << "while parsing file" << srcfile << ITLEndl;

				if(msgs) return MsgHandler::kProcessed;
			}else{

				qarchive::SQArchive a;
				QFileDownloader * downloader = new QFileDownloader();
				qarchive::QArchiveError error;
				if (Tools::isurl(srcfile)) {
					if (!downloader) return MsgHandler::kCreateFailure;
					if (downloader->get (srcfile.c_str()) && downloader->dataSize()) {
						a = qarchive::QArchive::readArchiveFromData(& (downloader->byteArray()), error);
					}
					else return MsgHandler::kBadParameters;
				}
				else {
					a = qarchive::QArchive::readArchiveFromFile(makeAbsolutePath(rootpath, srcfile).c_str(), error);
				}

				if(!error){
					size_t id = srcfile.rfind("/");
					if(id==string::npos)
						id=0;
					else
						id++;
					std::string bundleName =  srcfile.substr(id, srcfile.size()-id-11);
					QString bundleRootPath = QDir::temp().absolutePath()+QDir::separator()+"INScore"+QDir::separator();
					bundleRootPath += QString("bundle")+QDir::separator()+QString::fromStdString(bundleName);
					error = a->extract(bundleRootPath, true);
					if(!error){
						INScore::postMessage("/ITL", "rootPath",bundleRootPath.toStdString().c_str());
						INScore::postMessage("/ITL/scene", "rootPath",bundleRootPath.toStdString().c_str());
						INScore::postMessage("/ITL", "load", "main.inscore");
					}
				}

				a = (qarchive::QArchive*)0;
				delete downloader;
				if(!error)
					return MsgHandler::kProcessed;
				else if(error==qarchive::FILE_NOT_FOUND)
					ITLErr<<"The file \""<<srcfile<<"\" is not reachable."<<ITLEndl;
				else if(error==qarchive::FILE_CORRUPTED)
					ITLErr<<"The bundle \""<<srcfile<<"\" is corrupted."<<ITLEndl;
				else if(error==qarchive::WRONG_PERMISSIONS)
					ITLErr<<"Impossible to write in the temporary folder."<<ITLEndl;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

} // end namespace

