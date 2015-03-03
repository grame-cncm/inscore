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
#include "IScene.h"

namespace inscore
{

Thread::Thread(int port, int frequency, VObjectView *exportedView, QObject * parent) :
	QThread(parent),
	fExportedView(exportedView),
	fPort(port),
	fFrequency(frequency)
{
}

Thread::~Thread()
{
	delete fServer;
}

void Thread::run() {
	// Create a webscocket server and wait for event.
	fServer = new QtWebSocketServer(fPort, fFrequency, fExportedView);
	connect(this, &Thread::signalPort, fServer, &QtWebSocketServer::changePort);
	exec();
}

bool Thread::changePort(int port)
{
	// Use a signal to restart the websocket server in his thread.
	emit signalPort(port);
	return true;
}

void Thread::changeFrequency(int frequency)
{
	fServer->changeFrequency(frequency);
}

QtWebSocketController::QtWebSocketController(const std::string &name, IObject *parent) :
	QObject(0), IWebSocket(name, parent)
{
	fThreadServer = 0;
}

QtWebSocketController::~QtWebSocketController()
{
	// Wait for end of thread.
	fThreadServer->quit();
	fThreadServer->wait();
}

bool QtWebSocketController::init(int port, int frequency)
{
	if(fThreadServer) {
		if(frequency != fFrequency) {
			fFrequency = frequency;
			fThreadServer->changeFrequency(frequency);
		}
		if(port != fPort) {
			fPort = port;
			return fThreadServer->changePort(port);
		}
		return true;
	}
	// Create and start a new thread
	fPort = port;
	fFrequency = frequency;
	fThreadServer = new Thread(fPort, fFrequency, this->getScene()->getView(), this);
	fThreadServer->start();
	return true;
}

}
