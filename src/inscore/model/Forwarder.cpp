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

#include "Forwarder.h"
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
void Forwarder::forward(const IMessage * imsg)
{
	// Forward if have host in foward list and if no filter or filter is not bloking the message.
	if (fForwardList.size() && (!fFilter || !fFilter->applyFilter(imsg))) {
        for (unsigned int i = 0; i < fForwardList.size(); i++) {
            ForwardEndPoint* endpoint = fForwardList[i];
            const IMessage::TUrl& url = endpoint->dest();
            // Forward message only if the destination is not the source of the message.
            if(Tools::ip2string(imsg->src()) != url.fHostname)
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
            url.parse (address);
            // Transform hostname in Ip in string format
            url.fHostname = Tools::ip2string(Tools::getIP(url.fHostname));
			if (!url.fPort) url.fPort = IAppl::kUPDPort;
			// Add in host list.
			switch (url.fProtocol) {
				case IMessage::TUrl::kWSProtocol:
					fForwardList.push_back(new WSForwarder(url));
					break;
				case IMessage::TUrl::kWSSProtocol:
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
