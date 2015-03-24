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
#include "ITLparser.h"
#include "IGlue.h"
#include "IMessage.h"
#include "IObject.h"

#include "OSCAddress.h"
#include "QFileDownloader.h"

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
void TILoader::process (const SIMessageList& msgs, IObject* root, const string& baseaddress)
{
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
	}
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus TILoader::load(const IMessage* msg, IObject* client, const std::string& rootpath)
{
	if (msg->size() == 1) {
		string srcfile; 
		if (!msg->param(0, srcfile)) return MsgHandler::kBadParameters;

		if (srcfile.size()) {
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
			if (msgs) {
				process (msgs, client->getRoot(), client->getOSCAddress());
				return MsgHandler::kProcessed;
			}
			else ITLErr << "while parsing file" << srcfile << ITLEndl;
		}
	}
	return MsgHandler::kBadParameters;
}

} // end namespoace

