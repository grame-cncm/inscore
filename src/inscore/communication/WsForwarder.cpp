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
WSForwarder::WSForwarder (const IMessage::TUrl& url) : ForwardEndPoint(url), fWSocket("INScore")
{
	QString tmp ("ws://");
	tmp += url.fHostname.c_str();
	QUrl dest (tmp);
	dest.setPort(url.fPort);
cerr << "new WSForwarder " << tmp.toStdString() << endl;
	fWSocket.open (dest);
}

WSForwarder::~WSForwarder ()
{
	fWSocket.close();
}

void WSForwarder::send (const IMessage * imsg) {
cerr << "WSForwarder::send " << imsg << endl;
	std::string json = IMessage2String(imsg, fID++);
	qint64 n = fWSocket.sendTextMessage (QString(json.c_str()));
}


} //
#endif
