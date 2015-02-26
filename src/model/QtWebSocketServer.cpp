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
}
#include <iostream>
bool QtWebSocketServer::start()
{
	fWebSocketServer = new QWebSocketServer(QStringLiteral("WebSocketServer"), QWebSocketServer::NonSecureMode, this);

	fWebSocketServer->moveToThread(this->thread());
	fWebSocketServer->setParent(this);
	std::cout << "parent" << fWebSocketServer->parent() << std::endl;
	// Start the web socket server.
	if (fWebSocketServer->listen(QHostAddress::Any, fPort)) {
		connect(fWebSocketServer, &QWebSocketServer::newConnection, this, &QtWebSocketServer::onNewConnection);
		connect(fWebSocketServer, &QWebSocketServer::closed, this, &QtWebSocketServer::closed);

		// Fired a possible notification in each end of the timer.
		fTimer = new QTimer(this);
		connect(fTimer, SIGNAL(timeout()),this, SLOT(sendNotification()));
		fTimer->start(fFrequency);
		return true;
	}
	return false;
}

QtWebSocketServer::~QtWebSocketServer()
{
	fWebSocketServer->close();
	qDeleteAll(fClients.begin(), fClients.end());
	//delete fTimer;
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
	// The screen have been updated
	if(fExportedView->isNewVersion(fScreenVersion)) {
		// Send to all clients
		QList<QWebSocket *>::iterator i;
		for (i = fClients.begin(); i != fClients.end(); ++i)  {
			(*i)->sendTextMessage("Screen updated");
		}
	}
}
#include <iostream>
void QtWebSocketServer::processTextMessage(QString message)
{
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		if(message == IWebSocket::GET_IMAGE) {
			AbstractData data = fExportedView->getImage("PNG");
			std::cout << "data.size=" << data.size << std::endl;
			QByteArray bArray = QByteArray::fromRawData(data.data, data.size);
			pClient->sendBinaryMessage(bArray);
		} else {
			pClient->sendTextMessage("Error : unknown request.");
		}
	}
}

}
