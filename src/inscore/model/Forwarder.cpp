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

#include <string>
#include <QUrl>
#include <QWebSocket>
#include <QTcpServer>

#include "Forwarder.h"
#include "HttpForwarder.h"
#include "IApplVNodes.h"
#include "IFilterForward.h"
#include "Tools.h"
#include "IAppl.h"

#include "json_object.h"
#include "json_element.h"
#include "json_parser.h"
#include "json_stream.h"

using namespace std;
using namespace json;

namespace inscore
{

//--------------------------------------------------------------------------
class OSCForwarder : public ForwardEndPoint
{
	public:
				 OSCForwarder (const IMessage::TUrl& url) : ForwardEndPoint(url) {}
		virtual ~OSCForwarder () {}
		
		void send (const IMessage * imsg) {
			OSCStream::sendEvent (imsg, dest().fHostname, dest().fPort);
		}
};

//--------------------------------------------------------------------------
// Web Socket Forwarder
//--------------------------------------------------------------------------
class WSForwarder : public ForwardEndPoint
{
	int			fID = 1;
	QWebSocket	fWSocket;
	QString IMessage2String (const IMessage * imsg) {
		string msgstr = imsg->toString();
		json_object *json = new json_object;
		json->add (new json_element("id", new json_int_value(fID++)));
		json->add (new json_element("method", new json_string_value("post")));
		json->add (new json_element("data", new json_string_value(msgstr.c_str())));
		std::ostringstream jstream;
		json->print(jstream);
		QString out (jstream.str().c_str());
		return out;
	}

	public:
				 WSForwarder (const IMessage::TUrl& url) : ForwardEndPoint(url), fWSocket("INScore") {
					QString tmp ("ws://");
					tmp += url.fHostname.c_str();
					QUrl dest (tmp);
					dest.setPort(url.fPort);
					fWSocket.open (dest);
				 }
		virtual ~WSForwarder () { fWSocket.close(); }

		void send (const IMessage * imsg) {
			qint64 n = fWSocket.sendTextMessage (IMessage2String(imsg));
		}
};

//--------------------------------------------------------------------------
// Http Forwarder
//--------------------------------------------------------------------------
string HTTPForwarder::IMessage2String (const IMessage * imsg) {
		string str = imsg->toString();
		string msgstr;
		for (const char* ptr = str.c_str(); *ptr; ptr++) {
			if (*ptr == '\n') msgstr += ' ';		// remove CR
			else if (*ptr == '\t') msgstr += ' ';	// remove tabs
			else msgstr	+= *ptr;
		}
		json_object *json = new json_object;
		json->add (new json_element("id", new json_int_value(fID++)));
		json->add (new json_element("method", new json_string_value("post")));
		json->add (new json_element("data", new json_string_value(msgstr.c_str())));
		std::ostringstream jstream;
		json->print(jstream);
		return jstream.str();
}

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
	string msgStr = IMessage2String (imsg);
	QString qstr (msgStr.c_str());
	QString b64 = qstr.toUtf8().toBase64();
	for (auto socket: fClients) {
		send (socket, b64.toStdString().c_str());
	}
}

//--------------------------------------------------------------------------
void Forwarder::forward(const IMessage * imsg)
{
	// Forward if have host in foward list and if no filter or filter is not bloking the message.
	if (fForwardList.size() && (!fFilter || !fFilter->applyFilter(imsg))) {
        for (unsigned int i = 0; i < fForwardList.size(); i++) {
            ForwardEndPoint* endpoint = fForwardList[i];
            const IMessage::TUrl& url = endpoint->dest();
            // Forward message only if the destination is not the source of the message.
            if ((url.fProtocol!=IMessage::TUrl::kOSCProtocol) || (Tools::ip2string(imsg->src()) != url.fHostname))
                endpoint->send (imsg);
        }
    }
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus Forwarder::processForwardMsg(const IMessage* msg)
{
	clear();								// clear the forward list first
	if (msg->size() == 0)					// no other param
		return MsgHandler::kProcessed;		// that's done

    for (int i=0; i<msg->size(); i++) {
        std::string address;
        if (msg->param(i, address)) {
            IMessage::TUrl url;
            if (!url.parse (address)) return MsgHandler::kBadParameters;
            // Transform hostname in Ip in string format
            url.fHostname = Tools::ip2string(Tools::getIP(url.fHostname));
			if (!url.fPort) url.fPort = IAppl::kUPDPort;
			// Add in host list.
			switch (url.fProtocol) {
				case IMessage::TUrl::kWSProtocol:
					fForwardList.push_back(new WSForwarder(url));
					break;
				case IMessage::TUrl::kHTTPProtocol:
					fForwardList.push_back(new HTTPForwarder(url, fLog));
					break;
				default:
					fForwardList.push_back(new OSCForwarder(url));
			}
        }
        else return MsgHandler::kBadParameters;
    }
    return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
const vector<IMessage::TUrl> Forwarder::getForwardList() const {
	vector<IMessage::TUrl> list;
	for (auto e: fForwardList) list.push_back(e->dest());
	return list;
}

//--------------------------------------------------------------------------
void Forwarder::clear()
{
	for (auto a: fForwardList) delete a;
	fForwardList.clear();
}

}
