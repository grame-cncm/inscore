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

#include "QtWebSocketController.h"
#include "IWebSocket.h"
#include "IAppl.h"
#include "ITLError.h"

using namespace std;
namespace inscore
{

//-------------------------------------------------------------------------------
QtWebSocketController::QtWebSocketController(IWebSocket* infos)
	: fInfos(infos), fServer (0)
{}

QtWebSocketController::~QtWebSocketController()		{ stop(); delete fServer; }

//-------------------------------------------------------------------------------
bool QtWebSocketController::start (int /*port*/)
{
	stop();
	QThread::start();
	wait (100);				// wait 100 ms for potential thread exit
	if (running())			// check if the server is running
		return true;
	stop();
	return false;
}

//-------------------------------------------------------------------------------
bool QtWebSocketController::running() const				{ return fServer ? fServer->isListening() : false; }

//-------------------------------------------------------------------------------
void QtWebSocketController::stop()
{
	if (isRunning()) {			// check if the thread is running
		quit();
		wait(100);
		delete fServer;
		fServer = 0;
	}
}

//-------------------------------------------------------------------------------
int QtWebSocketController::clients() const
{
	return fServer ? fServer->getClients() : 0;
}

//-------------------------------------------------------------------------------
void QtWebSocketController::run()
{
	WebApi api(fInfos->getView(), fInfos->getAppl());
	fServer = new QtWebSocketServer (fInfos->getFrequency(), &api);
	if (fServer) {
		if (fServer->start(fInfos->getPort()))
			exec();
		else {
			ITLErr << "Can't start websocket server on port" << fInfos->getPort() << ITLEndl;
			exit(-1);
		}
		// Stop server in the thread where it was created to avoid problem on timer destruction.
		fServer->stop();
	}
}

}
