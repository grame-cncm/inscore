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
#include <iostream>


using namespace std;

namespace inscore
{
const string IHttpd::kIHttpdType("httpd");

IHttpd::IHttpd(const std::string& name, IObject * parent ) : IObject (name, parent)
{
	fTypeString = kIHttpdType;
	fHttpServer = 0;
	cout << "constructor IHttpd" << endl;
}

IHttpd::~IHttpd()
{
	if(fHttpServer) {
		fHttpServer->stop();
		delete fHttpServer;
	}
}

SIMessageList IHttpd::getSetMsg () const
{
	cout << "getSetMsg IHttpd" << endl;
	SIMessageList list = IObject::getSetMsg();
	return list;
}

MsgHandler::msgStatus IHttpd::set (const IMessage* msg)
{
	cout << "set IHttpd" << endl;
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	int n = msg->size();
	if (n == 2) {
		if (!msg->param(1, fHttpPort)) {
			return MsgHandler::kBadParameters;
		}
		// Initialize Http server
		if(init())
			return MsgHandler::kProcessed;
		else return MsgHandler::kCreateFailure;
	}
	return MsgHandler::kBadParameters;
}

bool IHttpd::init ()
{
	cout << "IHttpd::init" << endl;
	fHttpServer = new THttpdPlugin;
	fHttpServer->start(fHttpPort);
	return true;
}

}
