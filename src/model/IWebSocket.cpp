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

#include "IWebSocket.h"

using namespace std;

namespace inscore
{
const string IWebSocket::kIWebSocketType("websocket");

const char * IWebSocket::GET_IMAGE = "getImage";

IWebSocket::IWebSocket(const std::string &name, IObject *parent) : IObject (name, parent)
{
	fTypeString = kIWebSocketType;
	fGetMsgHandlerMap[kstatus_GetMethod]	= TGetParamMethodHandler<IWebSocket, string (IWebSocket::*)() const>::create(this, &IWebSocket::status);
}

IWebSocket::~IWebSocket()
{
}

MsgHandler::msgStatus IWebSocket::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	// Two parameters are mandatory : port and notification time.
	int n = msg->size();
	if (n == 3) {
		int port;
		if (!msg->param(1, port)) {
			return MsgHandler::kBadParameters;
		}
		int frequency;
		if (!msg->param(2, frequency)) {
			return MsgHandler::kBadParameters;
		}
		// Initialize Http server
		if(init(port, frequency))
			return MsgHandler::kProcessed;
		else {
			ITLErr << "Cannot create server on port " << fPort << ITLEndl;
			return MsgHandler::kCreateFailure;
		}
	}
	return MsgHandler::kBadParameters;
}

SIMessageList IWebSocket::getSetMsg () const
{
	SIMessageList outmsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	*msg << kIWebSocketType << fPort << fFrequency;
	outmsgs->list().push_back (msg);
	return outmsgs;
}

}
