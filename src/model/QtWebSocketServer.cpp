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

#include "QtWebSocketServer.h"
#include "IWebSocket.h"
#include "VObjectView.h"
#include "abstractdata.h"

#include <QWebSocketServer>
#include <QWebSocket>

#include <string>

using namespace std;

namespace inscore {

QtWebSocketServer::QtWebSocketServer(int port, int frequency, VObjectView *exportedView, QObject *parent) : QObject(parent),
	fClients(),
	fExportedView(exportedView),
	fPort(port),
	fFrequency(frequency)
{
	fScreenVersion = 0;
	fWebSocketServer = new QWebSocketServer(QStringLiteral("WebSocketServer"), QWebSocketServer::NonSecureMode, this);
	// Start the web socket server.
	if (fWebSocketServer->listen(QHostAddress::Any, fPort)) {
		connect(fWebSocketServer, &QWebSocketServer::newConnection, this, &QtWebSocketServer::onNewConnection);
		connect(fWebSocketServer, &QWebSocketServer::closed, this, &QtWebSocketServer::closed);

		// Fire a possible notification in each end of the timer.
		fTimer = new QTimer(this);
		connect(fTimer, SIGNAL(timeout()),this, SLOT(sendNotification()));
		fTimer->start(fFrequency);
	}
}

QtWebSocketServer::~QtWebSocketServer()
{
	// Close server and delete all client.
	fWebSocketServer->close();
	qDeleteAll(fClients.begin(), fClients.end());
}


void QtWebSocketServer::onNewConnection()
{
	QWebSocket *pSocket = fWebSocketServer->nextPendingConnection();
	// Connect client to action.
	connect(pSocket, &QWebSocket::disconnected, this, &QtWebSocketServer::socketDisconnected);
	connect(pSocket, &QWebSocket::textMessageReceived, this, &QtWebSocketServer::processTextMessage);
	// Add client in list
	fClients << pSocket;
}

void QtWebSocketServer::changeFrequency(int frequency)
{
	// Change timer frequency
	fTimer->stop();
	fFrequency = frequency;
	fTimer->start(fFrequency);
}

bool QtWebSocketServer::changePort(int port)
{
	// Close server and recreate a new
	fWebSocketServer->close();
	fPort = port;
	return fWebSocketServer->listen(QHostAddress::Any, fPort);
}

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


void QtWebSocketServer::sendNotification() {
	// Verify and update screen version
	if(fExportedView->isNewVersion(fScreenVersion)) {
		// The screen have been updated, send to all clients
		QList<QWebSocket *>::iterator i;
		for (i = fClients.begin(); i != fClients.end(); ++i)  {
			(*i)->sendTextMessage("Screen updated");
		}
	}
}

void QtWebSocketServer::processTextMessage(QString message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		// Verify message and get back image and send it
		if(message == IWebSocket::GET_IMAGE) {
			AbstractData data = fExportedView->getImage("PNG");
			QByteArray bArray = QByteArray::fromRawData(data.data, data.size);
			pClient->sendBinaryMessage(bArray);
		} else {
			pClient->sendTextMessage("Error : unknown request.");
		}
	}
}

}
