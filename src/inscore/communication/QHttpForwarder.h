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

#include <string>
#include <vector>

#include <QTcpServer>
class QTcpSocket;

#include "Forwarder.h"
#include "IMessage.h"

namespace inscore
{

class IAppl;
class IApplLog;

//--------------------------------------------------------------------------
class HTTPForwarder : public QTcpServer, public ForwardEndPoint
{
	Q_OBJECT

	int	fID = 1;	// a monotonic id used for inscore messages

	protected:
		std::vector<QTcpSocket*>	fClients;
				void clear ();
				void send (QTcpSocket *s, const char * msg);
		virtual bool initialize (const IAppl* appl)	{ return true; }
		virtual std::string protocol () const	{ return "HTTP"; }

	public:
				 HTTPForwarder (const IMessage::TUrl& url, IApplLog* log);
		virtual ~HTTPForwarder ();

		void 	send  (const IMessage * imsg);
		size_t  getClients () const 	{ return fClients.size(); }

	private Q_SLOTS:
		void accept ();
		void disconnect ();
};

} //
