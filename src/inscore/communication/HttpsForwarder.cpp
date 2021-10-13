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

#if HASSSLSUPPORT
#include <QSslCertificate>
#include <QSslKey>
#include <QSslConfiguration>
#include <QSslSocket>
#endif

#include "IAppl.h"
#include "HttpsForwarder.h"

using namespace std;

namespace inscore
{

#if HASSSLSUPPORT
//----------------------------------------------------------------------------
HTTPSForwarder::HTTPSForwarder (const IMessage::TUrl& url, IAppl* appl)
	: HTTPForwarder(url, appl->getLogWindow())
{
	initialize(appl);
}

//----------------------------------------------------------------------------
bool HTTPSForwarder::initialize(const IAppl* appl)
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
		QSslSocket* socket = new QSslSocket(this);
		QSslConfiguration config = socket->sslConfiguration();
		config.addCaCertificate (*fSsl.cacert);
		config.setLocalCertificate (*fSsl.cert);
		config.setPrivateKey(*fSsl.key);
		config.setPeerVerifyMode(QSslSocket::VerifyNone);
		config.setSslOption(QSsl::SslOptionDisableServerNameIndication, true);
		config.setSslOption(QSsl::SslOptionDisableLegacyRenegotiation, true);
		
		socket->setSslConfiguration(config);
		socket->setSocketOption(QAbstractSocket::KeepAliveOption, true );
		if (socket->setSocketDescriptor(socketDescriptor)) {
			socket->startServerEncryption();
			return socket;
		}
		else {
			ITLErr << protocol() << " failed to create socket: " << errorString().toStdString() << ITLEndl;
			socket->close();
		}
     }
	else {
		ITLErr << protocol() << " connection request failed to create socket: missing certificates" << ITLEndl;
	}
    return nullptr;
}

//----------------------------------------------------------------------------
void HTTPSForwarder::incomingConnection(qintptr socketDescriptor)
{
	QSslSocket* socket = newConnection(socketDescriptor);
	if (!socket) return;
	addPendingConnection(socket);
}

#else

//----------------------------------------------------------------------------
HTTPSForwarder::HTTPSForwarder (const IMessage::TUrl& url, IAppl* appl)
	: HTTPForwarder(url, appl->getLogWindow())
{
	ITLErr << "HTTPS server failed to start: no SSL support." << ITLEndl;
}

#endif

}
