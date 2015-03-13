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
#include "WebSocketController.h"

using namespace std;

namespace inscore
{

const string IWebSocket::kIWebSocketType("websocket");
const char * IWebSocket::kGetImgMsg = "getImage";

//-------------------------------------------------------------------------------
IWebSocket::IWebSocket(const std::string &name, IObject *parent)
	: IObject (name, parent), fWebServer(0), fPort(0), fFrequency(0)
{
	fTypeString = kIWebSocketType;
	fGetMsgHandlerMap[kstatus_GetMethod]	= TGetParamMethodHandler<IWebSocket, string (IWebSocket::*)() const>::create(this, &IWebSocket::status);
}

IWebSocket::~IWebSocket()
{
	delete fWebServer;
}

//-------------------------------------------------------------------------------
VObjectView* IWebSocket::getView() const
{
	const IObject* obj = (const IObject*)getScene();
	return obj ? obj->getView() : 0;
}

//-------------------------------------------------------------------------------
void IWebSocket::setFrequency (int freq)
{
	fFrequency = freq;
	fWebServer->setFrequency(freq);
}

//-------------------------------------------------------------------------------
bool IWebSocket::running () const		{ return fWebServer->running(); }
string IWebSocket::status () const		{ return running() ? "running" : "stopped"; }
bool IWebSocket::start (int port)		{ return fWebServer->start(port); }

//-------------------------------------------------------------------------------
MsgHandler::msgStatus IWebSocket::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	// Two parameters are mandatory : port and notification time.
	if (msg->size() != 3) return MsgHandler::kBadParameters;

	int port, frequency;
	if (!msg->param(1, port) || !msg->param(2, frequency))
		return MsgHandler::kBadParameters;
	if (!port || !frequency)
		return MsgHandler::kBadParameters;

	if (frequency != fFrequency)
		setFrequency(frequency);

	if (port != fPort) {
		setPort(port);
		if ( !start(port) ) {
			ITLErr << "Cannot create web socket server on port " << fPort << ITLEndl;
			return MsgHandler::kCreateFailure;
		}
	}
	return MsgHandler::kProcessed;
}

SIMessageList IWebSocket::getSetMsg () const
{
	SIMessageList outmsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	*msg << kIWebSocketType << fPort << fFrequency;
	outmsgs->list().push_back (msg);
	return outmsgs;
}

//--------------------------------------------------------------------------
SIMessageList IWebSocket::getMsgs(const IMessage* msg) const
{
	SIMessageList outMsgs = IMessageList::create();
	for ( int i = 0 ; i < msg->size() ; i++ )
	{
		string param = "-";
		msg->param(i, param);

		if ( param == "clients" )
		{
			SIMessage msg = IMessage::create(getOSCAddress(), param);
			*msg << fWebServer->clients();
			outMsgs->list().push_back (msg);
		}
	}
	outMsgs->list().push_back (IObject::getMsgs(msg)->list());
	return outMsgs;
}

}
