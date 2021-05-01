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

#if HASWSSupport
#include "WsForwarder.h"
#endif
#if HASHTTPSupport
#include "HttpForwarder.h"
#include "HttpsForwarder.h"
#endif

#include "Forwarder.h"
#include "IApplVNodes.h"
#include "IFilterForward.h"
#include "Tools.h"
#include "IAppl.h"
#include "OSCStream.h"

#include "json_object.h"
#include "json_element.h"
#include "json_parser.h"
#include "json_stream.h"

using namespace std;
using namespace json;

namespace inscore
{

string ForwardEndPoint::IMessage2String (const IMessage * imsg, int id) {
	string str = imsg->toString();
	string msgstr;
	for (const char* ptr = str.c_str(); *ptr; ptr++) {
		if (*ptr == '\n') msgstr += ' ';		// remove CR
		else if (*ptr == '\t') msgstr += ' ';	// remove tabs
		else msgstr	+= *ptr;
	}
	json_object *json = new json_object;
	json->add (new json_element("id", new json_int_value(id)));
	json->add (new json_element("method", new json_string_value("post")));
	json->add (new json_element("data", new json_string_value(msgstr.c_str())));
	std::ostringstream jstream;
	json->print(jstream);
	delete json;
	return jstream.str();
}

void ForwardEndPoint::log  (const char * msg) {
	if (fLog) fLog->print (msg);
}

//--------------------------------------------------------------------------
class OSCForwarder : public ForwardEndPoint
{
	public:
				 OSCForwarder (const IMessage::TUrl& url) : ForwardEndPoint(url, 0) {}
		virtual ~OSCForwarder () {}
		
		void send (const IMessage * imsg) {
			OSCStream::sendEvent (imsg, dest().fHostname, dest().fPort);
		}
		size_t 	getClients () const 	{ return 0; }
};

//--------------------------------------------------------------------------
void Forwarder::forward(const IMessage * imsg)
{
//#if HASOSCStream
	// Forward if have host in foward list and if no filter or filter is not bloking the message.
	if (fForwardList.size() && (!fFilter || !fFilter->applyFilter(imsg))) {
		for (auto endpoint: fForwardList) {
            const IMessage::TUrl& url = endpoint->dest();
            // Forward message only if the destination is not the source of the message.
            if ((url.fProtocol!=IMessage::TUrl::kOSCProtocol) || (Tools::ip2string(imsg->src()) != url.fHostname))
                endpoint->send (imsg);
		}
    }
//#endif
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus Forwarder::processForwardMsg(const IMessage* msg)
{
	// clear the forward list first
	for (auto endpoint: fForwardList)
		delete endpoint;
	fForwardList.clear();

#if HASOSCStream
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
#if HASWSSupport
				case IMessage::TUrl::kWSProtocol:
					fForwardList.push_back(new WSForwarder(url, fLog));
					break;
#endif
#if HASHTTPSupport
				case IMessage::TUrl::kHTTPProtocol:
					fForwardList.push_back(new HTTPForwarder(url, fLog));
					break;
				case IMessage::TUrl::kHTTPSProtocol:
					fForwardList.push_back(new HTTPSForwarder(url, fLog->getAppl()));
					break;
#endif
				case IMessage::TUrl::kOSCProtocol:
					fForwardList.push_back(new OSCForwarder(url));
			}
        }
        else return MsgHandler::kBadParameters;
    }
#endif
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

//--------------------------------------------------------------------------
SIMessage Forwarder::makeCount (const char* address, const char* proto, size_t count) const
{
	SIMessage msg = IMessage::create(address, kclients_GeMethod);
	msg->add (proto);
	msg->add (int(count));
	return msg;
}

//--------------------------------------------------------------------------
SIMessageList Forwarder::getClients() const
{
	SIMessageList out = IMessageList::create();
	size_t http = 0;
	size_t https = 0;
	size_t ws = 0;
	size_t wss = 0;
	for (auto endpoint: fForwardList) {
		int proto = endpoint->protocol();
		size_t clients = endpoint->getClients();
		switch (proto) {
			case IMessage::TUrl::kWSProtocol:		ws 		+= clients; break;
			case IMessage::TUrl::kHTTPProtocol:		http	+= clients; break;
			case IMessage::TUrl::kHTTPSProtocol:	https	+= clients; break;
		}
	}

	size_t total = http + https + ws + wss;
	const char* dest = "/ITL";
	if (total) {
		if (http)
			out->list().push_back( makeCount(dest, "http", http) );
		if (https)
			out->list().push_back( makeCount(dest, "https", https) );
		if (ws)
			out->list().push_back( makeCount(dest, "ws", ws) );
		if (out->list().size() > 1)
			out->list().push_back( makeCount(dest, "total", total) );
	}
	else {
		SIMessage msg = IMessage::create(dest, kclients_GeMethod);
		msg->add (0);
        out->list().push_back(msg);
	}
	return out;
}


}
