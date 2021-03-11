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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include "Modules.h"

#if HASWSSupport
#include <vector>

#include <QUrl>
#include <QWebSocket>

#include "Forwarder.h"
#include "IMessage.h"
#include "WsForwarder.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
// Web Socket Forwarder
//--------------------------------------------------------------------------
WSForwarder::WSForwarder (const IMessage::TUrl& url, IApplLog* log) :
	QWebSocketServer(QStringLiteral("INScore"), QWebSocketServer::NonSecureMode),
	ForwardEndPoint(url, log)
{
	connect(this, &QWebSocketServer::newConnection, this, &WSForwarder::accept);
	listen(QHostAddress::Any, url.fPort);
}

WSForwarder::~WSForwarder ()	{ close(); }

void WSForwarder::send (QWebSocket* socket, const QString& msg) {
//cerr << "WSForwarder::send " << imsg << endl;
	qint64 n = socket->sendTextMessage (msg);
}

void WSForwarder::send (const IMessage * imsg)
{
	string msgStr = IMessage2String (imsg, fID++);
	QString qstr (msgStr.c_str());
	QString b64 = qstr.toUtf8().toBase64();
	for (auto socket: fClients) {
		send (socket, b64);
	}
}

void WSForwarder::accept () {
	QWebSocket* socket = nextPendingConnection();
	if (!socket) return;

	stringstream sstr;
	sstr << "New WebSocket connection from " << socket->peerAddress().toString().toStdString() << " on port " << dest().fPort;
	log (sstr.str().c_str());
	connect(socket, &QWebSocket::disconnected, this, &WSForwarder::disconnect);
	fClients.push_back(socket);		// add the client to the clients list
	socket->flush();
	send (socket, "INScore");
}

void WSForwarder::disconnect () {
	QWebSocket *socket = qobject_cast<QWebSocket *>(sender());
	if (socket) {
		stringstream sstr;
		sstr  << "WebSocket client " << socket->peerAddress().toString().toStdString() << ":" << dest().fPort << " disconnected.";
		log (sstr.str().c_str());
		// Remove the client from the list
		fClients.erase(std::remove(fClients.begin(), fClients.end(), socket), fClients.end());
	}
}


} //
#endif
