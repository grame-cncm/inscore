/*

  INScore Project

  Copyright (C) 2020  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include "Connect.h"
#include "IAppl.h"

#ifdef EMCC
#include <emscripten.h>
static void connect (const char* url, bool first) {
	EM_ASM( { TConnections.connect(Module.UTF8ToString($0), $1); }, url, first);
}
#else
static void connect (const char* url, bool first) {}
#endif

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
MsgHandler::msgStatus Connect::processConnectMsg(const IMessage* msg)
{
	clear();								// clear the forward list first
	if (msg->size() == 0)					// no other param
		return MsgHandler::kProcessed;		// that's done

    for (int i=0; i<msg->size(); i++) {
        std::string address;
        if (msg->param(i, address)) {
            IMessage::TUrl url;
            if (!url.parse (address)) return MsgHandler::kBadParameters;
			if (!url.fPort) url.fPort = IAppl::kUPDPort;
			// Add in host list.
			switch (url.fProtocol) {
				case IMessage::TUrl::kWSProtocol:
				case IMessage::TUrl::kHTTPProtocol:
					connect (string(url).c_str(), i==0);
					fCnxList.push_back(url);
					break;
				default:
					ITLErr << "only ws and http protocols are supported" << ITLEndl;
					return MsgHandler::kBadParameters;
			}
        }
        else return MsgHandler::kBadParameters;
    }
    return MsgHandler::kProcessed;
}

}
