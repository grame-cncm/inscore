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

#include <QWebSocket>
#include <string>
#include <iostream>

#include "QtWebSocketServer.h"
#include "IWebSocket.h"
#include "VObjectView.h"
#include "abstractdata.h"

using namespace std;

namespace inscore {

//-------------------------------------------------------------------------------
QtWebSocketServer::QtWebSocketServer(int frequency, VObjectView *view) :
	QWebSocketServer(QStringLiteral("WebSocketServer"), QWebSocketServer::NonSecureMode),
	fScreenVersion(0), fView (view), fFrequency(frequency)
{
	connect(&fTimer, SIGNAL(timeout()),this, SLOT(timeTask()));
}

//-------------------------------------------------------------------------------
QtWebSocketServer::~QtWebSocketServer()
{
	stop();
}

//-------------------------------------------------------------------------------
bool QtWebSocketServer::start(int port)
{
	stop();										// stop the server, in case it's already running

	if (listen(QHostAddress::Any, port)) {		// and start listening in port 'port'
		connect(this, &QWebSocketServer::newConnection, this, &QtWebSocketServer::onNewConnection);
		connect(this, &QWebSocketServer::closed, this, &QtWebSocketServer::closed);
		fTimer.start(fFrequency);
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::stop()
{
	fTimer.stop ();
	close();										// close the server
	qDeleteAll(fClients.begin(), fClients.end());	// and delete all the clients.
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::onNewConnection()
{
	QWebSocket *pSocket = nextPendingConnection();
	// Connect client to action.
	connect(pSocket, &QWebSocket::disconnected, this, &QtWebSocketServer::socketDisconnected);
	connect(pSocket, &QWebSocket::textMessageReceived, this, &QtWebSocketServer::processTextMessage);
	fClients << pSocket;		// add the client to the clients list
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::setFrequency(int frequency)
{
cout << "QtWebSocketServer::setFrequency " << frequency << endl;
	fFrequency = frequency;
	fTimer.stop();
	fTimer.start(fFrequency);
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::socketDisconnected()
{
	// Retrieve the client
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		// Remove the client in the list
		fClients.removeAll(pClient);
		pClient->deleteLater();
	}
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::timeTask()
{
	if(fView->isNewVersion(fScreenVersion)) {		// check for view updates

		// The screen have been updated, send notifications to all the clients
		QList<QWebSocket *>::iterator i;
		for (i = fClients.begin(); i != fClients.end(); ++i)  {
			(*i)->sendTextMessage("Screen updated");
		}
	}
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::processTextMessage(QString message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		// Verify message and get back image and send it
		if(message == IWebSocket::kGetImgMsg) {
			AbstractData data = fView->getImage("PNG");
			QByteArray bArray = QByteArray::fromRawData(data.data, data.size);
			pClient->sendBinaryMessage(bArray);
		} else {
			pClient->sendTextMessage("Error : unknown request.");
		}
	}
}

}
