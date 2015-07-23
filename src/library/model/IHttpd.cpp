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

#include "IHttpd.h"
#include "WebApi.h"
#if defined(__LINUX__) || defined(TARGET_OS_MAC)
#include "HTTPServer.h"
#include "IScene.h"
#include "ITLError.h"
#endif
using namespace std;

namespace inscore
{
const string IHttpd::kIHttpdType("httpd");
#if defined(__LINUX__) || defined(TARGET_OS_MAC)
//--------------------------------------------------------------------------
IHttpd::IHttpd(const std::string& name, IObject * parent ) : IObject (name, parent)
{
	fTypeString = kIHttpdType;
	fHttpdServer = 0;
	fHttpPort = -1;

	fGetMsgHandlerMap[kstatus_GetMethod]	= TGetParamMethodHandler<IHttpd, string (IHttpd::*)() const>::create(this, &IHttpd::status);
}

IHttpd::~IHttpd()
{
	stop();
}

//--------------------------------------------------------------------------
void IHttpd::stop()
{
	if(fHttpdServer) {
		fHttpdServer->stop();
		delete fHttpdServer;
		delete fApi;
		fHttpdServer = 0;
	}
}

//--------------------------------------------------------------------------
void IHttpd::del()
{
	stop();
	IObject::del();
}

//--------------------------------------------------------------------------
SIMessageList IHttpd::getSetMsg () const
{
	SIMessageList outmsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	*msg << kIHttpdType << fHttpPort;
	outmsgs->list().push_back (msg);
	return outmsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IHttpd::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	int n = msg->size();
	if (n == 2) {
		int port;
		if (!msg->param(1, port)) {
			return MsgHandler::kBadParameters;
		}
		// Initialize Http server
		if(init(port))
			return MsgHandler::kProcessed;
		else {
			ITLErr << "Cannot create http server on port " << fHttpPort << ITLEndl;
			return MsgHandler::kCreateFailure;
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
bool IHttpd::init (int port)
{
	if(!fHttpdServer) {
		// Create a new server
		fApi = new WebApi(getScene()->getView(), getScene()->getJSEngine(), getScene()->getLUAEngine());
		fHttpdServer = new HTTPDServer(fApi, 0, 0);
	} else {
		// It's the same port, do nothing
		if(port == fHttpPort)
			return true;
		// Stop the server and start it on the new port.
		fHttpdServer->stop();
	}
	fHttpPort = port;
	return fHttpdServer->start(fHttpPort);
}

//--------------------------------------------------------------------------
string IHttpd::status () const
{
	return fHttpdServer->status() ? "started": "stopped";
}
#endif // __LINUX__ || TARGET_OS_MAC
}

