/*
  Copyright (c) Grame 2015

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 11, cours Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#include "HTTPServer.h"
#include "INScoreServer.h"

using namespace inscorehttpd;

void * initialize(callbackGetData callbackFct, void * object)
{
	return new HTTPDServer(callbackFct, object);
}

void destroy(void * server)
{
	HTTPDServer *aServer  = static_cast<HTTPDServer *>(server);
	delete aServer;
}

bool start(void * server, int port)
{
	HTTPDServer *aServer  = static_cast<HTTPDServer *>(server);
	if(aServer) {
		return aServer->start(port);
	}
	return false;
}

bool stop(void * server)
{
	HTTPDServer *aServer  = static_cast<HTTPDServer *>(server);
	if(aServer) {
		aServer->stop();
		return true;
	}
	return false;
}

int status(void * server)
{
	HTTPDServer *aServer  = static_cast<HTTPDServer *>(server);
	if(aServer) {
		return aServer->status();
	}
	return false;
}
