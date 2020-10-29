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

#include <vector>
#include <QTcpServer>
#include <QTcpSocket>

#include "Forwarder.h"
#include "IMessage.h"

namespace inscore
{

//--------------------------------------------------------------------------
class HTTPForwarder : public QTcpServer, public ForwardEndPoint
{
	Q_OBJECT

	int			fID = 1;
	std::vector<QTcpSocket*>	fClients;

	std::string 	IMessage2String (const IMessage * imsg);
	void 	clear ();

	public:
				 HTTPForwarder (const IMessage::TUrl& url);
		virtual ~HTTPForwarder ();

		void send (const IMessage * imsg);

	private Q_SLOTS:
		void accept ();
		void disconnect ();
};

} //
