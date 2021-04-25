/*

  INScore Project

  Copyright (C) 2020  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#pragma once

#include <QTcpServer>
#include <QSslSocket>
#include <QTcpSocket>

#include "Forwarder.h"
#include "IApplVNodes.h"
#include "IMessage.h"

class QSslKey;
class QSslCertificate;

namespace inscore
{

class IAppl;
//--------------------------------------------------------------------------
class HTTPSForwarder : public QTcpServer, public ForwardEndPoint
{
	Q_OBJECT

	int			fID = 1;
	std::vector<QSslSocket*>	fClients;
//	std::vector<QTcpSocket*>	fClients;
//	QSslSocket					fServerSocket;

	void clear ();
//	void send (QTcpSocket *s, const char * msg);
	void send (QSslSocket *s, const char * msg);
	QSslSocket* newConnection (qintptr socketDescriptor);

	protected:
		virtual void	incomingConnection(qintptr socketDescriptor);

	public:
				 HTTPSForwarder (const IMessage::TUrl& url, IAppl* appl);
		virtual ~HTTPSForwarder ();

		void send (const IMessage * imsg);

	private:
		IApplSsl::Ssl		fSsl;
//		const QSslKey* 		 	fKey  = nullptr;
//		const QSslCertificate*	fCert = nullptr;
//		const QSslCertificate*	fCA = nullptr;

		bool 			 initialize (IAppl* appl) ;
//		QSslKey* 		 getKey (const std::string & name) const;
//		QSslCertificate* getCert (const std::string & name) const;
		
	private Q_SLOTS:
		void disconnect ();
};

} //
