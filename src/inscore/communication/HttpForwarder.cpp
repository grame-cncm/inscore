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

#include <string>

#include "Modules.h"

#if HASHTTPSupport
#include "HttpForwarder.h"
#endif

#include "Forwarder.h"
#include "IApplVNodes.h"

#include "json_object.h"
#include "json_element.h"
#include "json_parser.h"
#include "json_stream.h"

using namespace std;
using namespace json;

namespace inscore
{

#if HASHTTPSupport

HTTPForwarder::HTTPForwarder (const IMessage::TUrl& url, IApplLog* log) : fLog(log), ForwardEndPoint(url)
{
	connect(this, &QTcpServer::newConnection, this, &HTTPForwarder::accept);
	listen(QHostAddress::Any, url.fPort);
}

HTTPForwarder::~HTTPForwarder ()		{ close(); }

void HTTPForwarder::log  (const char * msg) {
	if (fLog) fLog->print (msg);
}

void HTTPForwarder::accept () {
	QTcpSocket* socket = nextPendingConnection();
	if (!socket) return;

	stringstream sstr;
	sstr << "New HTTP connection from " << socket->peerAddress().toString().toStdString() << " on port " << dest().fPort;
	log (sstr.str().c_str());
	connect(socket, &QTcpSocket::disconnected, this, &HTTPForwarder::disconnect);
	fClients.push_back(socket);		// add the client to the clients list
	socket->flush();
	send (socket, "INScore");
}

void HTTPForwarder::disconnect () {
	QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
	if (socket) {
		stringstream sstr;
		sstr  << "HTTP client " << socket->peerAddress().toString().toStdString() << ":" << dest().fPort << " disconnected.";
		log (sstr.str().c_str());
		// Remove the client from the list
		fClients.erase(std::remove(fClients.begin(), fClients.end(), socket), fClients.end());
	}
}

void HTTPForwarder::send (QTcpSocket *socket, const char * msg) {
	const char* nl = "\n";
	stringstream netmsg;
	netmsg << "HTTP/1.1 200 OK" << nl
		<< "Content-Type: text/event-stream" << nl
		<< "Access-Control-Allow-Origin: *" << nl
		<< "Connection: keep-alive" << nl
		<< "Cache-Control: no-cache" << nl << nl
		<< "data: " << msg << nl << nl;
	qint64 n = socket->write(netmsg.str().c_str());
	socket->flush();
}

void HTTPForwarder::send (const IMessage * imsg) {
	string msgStr = IMessage2String (imsg, fID++);
	QString qstr (msgStr.c_str());
	QString b64 = qstr.toUtf8().toBase64();
	for (auto socket: fClients) {
		send (socket, b64.toStdString().c_str());
	}
}
#endif

}
