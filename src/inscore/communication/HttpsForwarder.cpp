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
#include "IAppl.h"
//#include "IApplVNodes.h"

#if HASHTTPSupport
#include <QSslCertificate>
#include <QSslKey>
#include <QSslConfiguration>

#include "HttpsForwarder.h"
#endif

using namespace std;

namespace inscore
{

#if HASHTTPSupport

//----------------------------------------------------------------------------
HTTPSForwarder::HTTPSForwarder (const IMessage::TUrl& url, IAppl* appl)
	: ForwardEndPoint(url, appl->getLogWindow()) //, fServerSocket (this)
{
	if (initialize(appl)) {
		if (!listen(QHostAddress::Any, url.fPort)) {
			ITLErr << "HTTPS server failed to start" << errorString().toStdString() << ITLEndl;
		}
	}
}

//----------------------------------------------------------------------------
HTTPSForwarder::~HTTPSForwarder ()
{
	close();
}

//----------------------------------------------------------------------------
bool HTTPSForwarder::initialize(IAppl* appl)
{
	const IApplSsl* ssl = appl->getSsl();
	fSsl = ssl->getSslInfos();
	if (!fSsl.cert || !fSsl.key || !fSsl.cacert) {
		ITLErr << "HTTPS server failed to start: INScore certificates are missing." << ITLEndl;
		return false;
	}
	return true;
}

//----------------------------------------------------------------------------
QSslSocket* HTTPSForwarder::newConnection (qintptr socketDescriptor)
{
	if (fSsl.cert || fSsl.key || fSsl.cacert) {
		QSslConfiguration config;
		config.addCaCertificate (*fSsl.cacert);
		config.setLocalCertificate (*fSsl.cert);
		config.setPrivateKey(*fSsl.key);
		config.setPeerVerifyMode(QSslSocket::VerifyPeer);
		
		QSslSocket* socket = new QSslSocket(this);
		socket->setSslConfiguration(config);
		socket->setSocketOption(QAbstractSocket::KeepAliveOption, true );
		if (socket->setSocketDescriptor(socketDescriptor)) {
			addPendingConnection(socket);
			socket->startServerEncryption();
			return socket;
		}
		else socket->close();
     }
     return nullptr;
}

//----------------------------------------------------------------------------
void HTTPSForwarder::incomingConnection(qintptr socketDescriptor)
{
	QSslSocket* socket = newConnection(socketDescriptor);
	if (!socket) return;

	stringstream sstr;
	sstr << "New HTTPS connection from " << socket->peerAddress().toString().toStdString() << " on port " << dest().fPort << " - client #" << fClients.size() + 1;
	log (sstr.str().c_str());
	connect(socket, &QTcpSocket::disconnected, this, &HTTPSForwarder::disconnect);
	fClients.push_back(socket);		// add the client to the clients list
	socket->flush();
	send (socket, "INScore");
}


void HTTPSForwarder::disconnect () {
	QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());
	if (socket) {
		stringstream sstr;
		sstr  << "HTTP client " << socket->peerAddress().toString().toStdString() << ":" << dest().fPort << " disconnected.";
		log (sstr.str().c_str());
		// Remove the client from the list
		fClients.erase(std::remove(fClients.begin(), fClients.end(), socket), fClients.end());
	}
}

void HTTPSForwarder::send (QSslSocket *socket, const char * msg) {
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

void HTTPSForwarder::send (const IMessage * imsg) {
	string msgStr = IMessage2String (imsg, fID++);
	QString qstr (msgStr.c_str());
	QString b64 = qstr.toUtf8().toBase64();
	for (auto socket: fClients) {
		send (socket, b64.toStdString().c_str());
	}
}
#endif

}
