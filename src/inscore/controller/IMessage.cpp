/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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

#include <iostream>
#include <sstream>

#include "Modules.h"
#include "IMessage.h"
#include "IMessageStream.h"
#include "IMessageStack.h"
#include "IExpression.h"
#include "Methods.h"
#include "Tools.h"
#include "rational.h"
#include "TWallClock.h"
#include "TSorter.h"
#include "ITLError.h"

#if HASOSCStream
#include "OSCStream.h"
#endif

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
// some static tools
//--------------------------------------------------------------------------
static string escape (const string& str)
{
	string out;
	const char *ptr = str.c_str();
	while (*ptr) {
		char c = *ptr++;
		if (c == '"')
			out += "\\\"";
		else out += c;
	}
	return out;
}

//--------------------------------------------------------------------------
static bool needQuotes (const string& str)
{
	bool ret = false;
	const char *ptr = str.c_str();
	if (*ptr == '$') return true;
	while (*ptr) {
		int c = *ptr++;
		if (!isdigit(c) && !isalpha(c)					// number and letters
			&& (c != '-') && (c != '_')					// identifiers chars
			&& (c != '+') && (c != '*') && (c != '?'))	// regexp chars (note that class description needs quotes)
			ret = true;
	}
	return ret;
}

//--------------------------------------------------------------------------
// IMessage implementation
//--------------------------------------------------------------------------
IMessage::IMessage(const IMessage& msg): smartable()
{
	*this = msg;
}

//--------------------------------------------------------------------------
IMessage::IMessage(const std::string& address, const std::string& msg)
				: fSrcIP(kLocalHost), fAddress(address)
{
	fArguments.push_back (new IMsgParam<string>(msg));
	fHasMessage = true;
}

//--------------------------------------------------------------------------
IMessage::IMessage(const std::string& address, const argslist& args, const TUrl& url)
				: fSrcIP(kLocalHost), fAddress(address), fHasMessage(false), fUrl(url.fHostname.c_str(), url.fPort)
{
	fArguments = args;
	if (fArguments.size()) {
		string method = fArguments[0]->value<string>("");
		fHasMessage = method.size(); // && !needQuotes(method);
	}
}

//--------------------------------------------------------------------------
void IMessage::setMessage(const string& msg)
{
	argPtr p = new IMsgParam<string>(msg);
	if (fHasMessage)
		fArguments[0] = p;
	else
		fArguments.insert (fArguments.begin(), p);
	fHasMessage = true;
}

//--------------------------------------------------------------------------
string IMessage::message() const
{
	if (!fHasMessage) return "";
	return fArguments[0]->value<string>("");
}

//--------------------------------------------------------------------------
void IMessage::add( const argslist& params )
{ 
	for (unsigned int i=0; i<params.size(); i++) {
		fArguments.push_back( params[i] );
	}
}

//--------------------------------------------------------------------------
bool IMessage::cast_param(int i, float& val) const
{
	if (param(i)->isType<float>()) {
		val = param(i)->value<float>(0);
		return true;
	}
	if (param(i)->isType<int>()) {
		int nval = param(i)->value<int>(0);
		val = float(nval);
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IMessage::cast_param(int i, int& val) const
{
	if (param(i)->isType<int>()) {
		val = param(i)->value<int>(0);
		return true;
	}
	if (param(i)->isType<float>()) {
		val = int(param(i)->value<float>(0));
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool IMessage::param(int i, rational& val) const
{ 
	if (size() < (i+2)) return false;
	int num, denum;
	if (!param(i, num))		return false;
	if (!param(i+1, denum)) return false;
	val = rational(num, denum);
	return true;
}

//----------------------------------------------------------------------
bool IMessage::param(int i, SIExpression& val) const
{
	val = param(i)->value<SIExpression>(val);
	return param(i)->isType<SIExpression>();
}

//----------------------------------------------------------------------
bool IMessage::TUrl::parse (const std::string& address)
{
	string ws = "ws://";
	string osc = "osc://";
	string http = "http://";
	string https = "https://";
	string tail = address;
	if (address.compare (0, ws.length(), ws) == 0) {
		fProtocol = kWSProtocol;
		tail = address.substr(ws.length());
	}
	else if (address.compare (0, osc.length(), osc) == 0) {
		fProtocol = kOSCProtocol;
		tail = address.substr(osc.length());
	}
	else if (address.compare (0, http.length(), http) == 0) {
		fProtocol = kHTTPProtocol;
		tail = address.substr(http.length());
	}
	else if (address.compare (0, https.length(), https) == 0) {
		fProtocol = kHTTPSProtocol;
		tail = address.substr(https.length());
	}
	else if (address.find_first_of('/') != string::npos) {
		ITLErr << address << ": incorrect url or unsupported protocol." << ITLEndl;
		return false;
	}
	size_t startPort = tail.find_first_of(':');
	if (startPort != string::npos) {
		fHostname = tail.substr (0, startPort);
		string portStr = tail.substr (startPort+1);
		fPort = atoi(portStr.c_str());
	}
	else {
		fHostname = address;
		fPort = 7000;
	}
	return true;
}

//----------------------------------------------------------------------
string IMessage::relative2absoluteAddress(const std::string& prefix) const
{
	return prefix + fAddress.substr(1);
}

//----------------------------------------------------------------------
bool IMessage::decodeAddress (const std::string& address, std::string& oscAddress, IMessage::TUrl& url)
{
	size_t startOsc = address.find_first_of('/');
	if (startOsc == string::npos) return false;		// incorrect osc address (no '/')
	// check addresses that start with a dot to support relative addresses
	oscAddress = address.substr ((address[0] == '.') ? 0 : startOsc);	// stores the osc address

	url.fPort = 0;									// first disable address extension
	if (startOsc > 0) {								// and check for the extension
		size_t startPort = address.find_first_of(':');
		if ((startPort != string::npos) && (startPort < startOsc)) {
			url.fHostname = address.substr (0, startPort);
			string portStr = address.substr (startPort+1, startOsc-1);
			url.fPort = atoi(portStr.c_str());
		}
	}
	return true;
}

//--------------------------------------------------------------------------
SIMessage IMessage::buildWatchMsg(int startIndex) const
{
	SIMessageList msgs = watchMsg2Msgs (startIndex);
	if (!msgs) return 0;

	SIMessage msg = IMessage::create();
	msg->setSrcIP( src() );
	msg->setAddress( address());
	msg->setMessage( message());
	msg->setUrl( url());
	for (int i=0; i < startIndex; i++)		// add the first args of the watch message
		msg->add(param(i));
	msg->add(msgs);							// next add the messages
	return msg;
}

//--------------------------------------------------------------------------
SIMessage IMessage::watchMsg2Msg(int& index) const
{
	string address, oscaddress; TUrl url;
	if (!param(index++, address) || !decodeAddress (address, oscaddress, url)) {
		ITLErr << "incorrect address " << address << " in watch message" << ITLEndl;
		return 0;
	}
	
	argslist args;
	int n = size();
	while (index < n) {
		string str;
		if (param(index, str)) {
			// first look for the messages separator ( ',' or ':') or end list marker
			if ((str == ",") || (str == ":") || (str == ")")) {
				break;
			}
			else if (str == "(") {			// enclosed messages list
				args.push_back(new IMsgParam<SIMessageList>(_watchMsg2Msgs (++index)));
				break;
			}
		}
		args.push_back(param(index++));
	}
	return IMessage::create (oscaddress, args, url);
}

//--------------------------------------------------------------------------
SIMessageList IMessage::watchMsg2Msgs(int startIndex) const
{
	SIMessageList list;
	if (param(startIndex, list))	{		// message has already the correct format (parsed message)
		return list;
	}

	string listMarker;
	if (param (startIndex, listMarker) && (listMarker == "(" ))		// look for opening parenthesis first
		startIndex++;
	return _watchMsg2Msgs (startIndex);
}

//--------------------------------------------------------------------------
SIMessageList IMessage::_watchMsg2Msgs(int& startIndex) const
{
	SIMessageList list = IMessageList::create();
	int n = size();
	while (startIndex < n) {
		string str;
		if (param(startIndex, str) && (str == ")")) {
			startIndex++;			// list end marker found
			return list;			// return the list
		}
		else {
			if ((str != ",") && (str != ":")) {	
				SIMessage msg = watchMsg2Msg (startIndex);
				if (msg) list->list().push_back(msg);
			}
			else startIndex++;		// skip messages separators
		}
	}
	return list;
}

//--------------------------------------------------------------------------
// sending messages
//--------------------------------------------------------------------------
#ifndef PARSERTEST
void IMessage::send(const bool& delay) const
#else
void IMessage::send(const bool& ) const
#endif
{
	if (extendedAddress()) {
#if HASOSCStream
		OSCStream::sendEvent (this, url().fHostname, url().fPort);
#endif
	}
	else {
#ifndef PARSERTEST
		SIMessage copy = IMessage::create(*this);
		if (copy){
			if(!delay)
				gMsgStack->push(new SIMessage(copy));
			else
				gDelayStack->push(new SIMessage(copy));
		}
#endif
	}
}

//--------------------------------------------------------------------------
void IMessageList::send(const bool& delay) const
{
#ifndef IBUNDLE
	double time = TWallClock::time();
	for (auto msg: list()) {
		if (msg->delay()) inscore2::TSorter::schedule (msg, time);
		else msg->send(delay);
	}
#endif
//	for (unsigned int i=0; i < list().size(); i++) {
//		const IMessage * msg = list()[i];
//		if (msg) msg->send(delay);
//	}
}

//--------------------------------------------------------------------------
void IMessageList::sendWebMsg() const
{
	for (unsigned int i=0; i < list().size(); i++) {
		const IMessage * msg = list()[i];
		SIMessage copy = IMessage::create(*msg);
#ifndef PARSERTEST
		gWebMsgStack->push(new SIMessage(copy));
#endif
	}
}

//--------------------------------------------------------------------------
// print a single parameter
//--------------------------------------------------------------------------
string IMessage::toString() const
{
	stringstream sstr;
	print (sstr);
	return sstr.str();
}

//--------------------------------------------------------------------------
// print a single parameter
//--------------------------------------------------------------------------
void IMessage::print(std::ostream& out, int i, int nested, const char* sep) const
{
    string str; int val; float fval;
	SIMessageList msgs; TJavaScript js; SIExpression expr;

	if (param(i, str)) {
		const char * q = needQuotes (str) ? "\"" : "";
		out << q << escape(str) << q;
	}
	else if (param(i, val))
		out << val;
	else if (param(i, fval))
		out << Tools::ensurefloat (fval);
	else if (param(i, msgs)) {
		string prefix, suffix;
		int n  = nested;
		while (n--) { prefix += "	"; }
		suffix = "";
		out << (sep ? "( " : "(\n");
		for (size_t j = 0 ; j < msgs->list().size(); j++) {
			SIMessage msg = msgs->list()[j];
			out << suffix;
			out << prefix;
			msg->print(out, nested, sep);
			suffix = sep ? sep : ",\n";
		}
		out << " )";
	}
	else if (param(i, js))
		out << "<? javascript " << js << " ?>";
    else if(param(i, expr))
        out << expr;
}

//--------------------------------------------------------------------------
void IMessage::print(std::ostream& out, int nested, const char* sep) const
{
	nested++;
	if (delay()) out << delay() << " ";
	if (extendedAddress()) out << string(fUrl);
	out << address() << " ";
	const string method = message();
	if (method.size()) {
		const char * q = needQuotes (method) ? "\"" : "";
		out << q << escape(method) << q;
	}
	if (size()) {
		out << " ";
		for (int i=0; i< size()-1; i++) {
			print (out, i, nested, sep);
			out << " ";
		}
		print (out, size()-1, nested, sep);
	}
	if (nested == 1) out << ";";
	nested--;
}

IMessage::TUrl::operator string() const
{
	stringstream str;
	switch (fProtocol) {
		case kWSProtocol:		str << "ws://"; break;
		case kHTTPProtocol:		str << "http://"; break;
		case kHTTPSProtocol:	str << "https://"; break;
		default:
			cerr << "IMessage::TUrl:: operator string: unknown protocol " << fProtocol << endl;
	}
	str << fHostname;
	if (fPort) str << ':' << fPort;
	return str.str();
}

#if HASOSCStream
//--------------------------------------------------------------------------
void IMessage::linearize(OSCStream& osc) const
{
	string addr = extendedAddress() ? (string(fUrl) + address()) : address();
	osc << addr.c_str();
	if (message().size()) osc << message();
	printArgs(osc);
}

//--------------------------------------------------------------------------
void IMessage::print(OSCStream& osc) const
{
	bool start = (osc.state() == OSCStream::kIdle);
	if (start) osc << OSCStart(address().c_str());
	else osc << address().c_str();
	if (message().size()) osc << message();
	printArgs(osc);
	if (start) osc << OSCEnd();
}

//--------------------------------------------------------------------------
void IMessage::print(OSCErrorStream& osc) const
{
	bool start = (osc.state() == OSCStream::kIdle);
	if (start) osc << OSCStart(address().c_str());
	else osc << address().c_str();
	if (message().size()) osc << message();
	printArgs(osc);
	if (start) osc << OSCEnd();
}
	
//--------------------------------------------------------------------------
void IMessage::printArgs(OSCStream& osc) const
{
	for (int i=0; i < size(); i++) {
		std::string str; float fv; int iv; SIExpression expr;
		SIMessageList msgs;
		if (param(i, fv))			osc << fv;		// param is a float value
		else if (param(i, iv))		osc << iv;		// param is an int32 value
		else if (param(i, str))		osc << str;		// param is a string
        else if (param(i, expr))		osc << expr;// param is an expression
		else if (param(i, msgs)) {					// param is a list of messages
			size_t n = msgs->list().size();
			if (n == 0) continue;					// empty message list
			else n -= 1;
			osc << "(";
			for (size_t i=0; i < n; i++) {
				const IMessage* msg = msgs->list()[i];
				msg->linearize(osc);
				osc << ":";
			}
			msgs->list()[n]->linearize(osc);
			osc << ")";
		}
		else ITLErr << "IMessage::printArgs to OSC: unknown message parameter type" << ITLEndl;
	}
}
#endif

//--------------------------------------------------------------------------
bool IMessage::operator == (const IMessage& other) const
{
	if ( url() != other.url() )
		return false;
	if ( address() != other.address() )
		return false;
	if ( message() != other.message() )
		return false;
	if ( size() != other.size() )
		return false;
	for ( int i = 0 ; i < size() ; i++ )
	{
		if (param(i) != other.param(i))
			return false;
	}
	return true;
}

//--------------------------------------------------------------------------
template <>	IMessage& operator <<(IMessage& msg, TSize<double> val)
{
	msg << float(val.width()) << float(val.height());
	return msg;
}

//--------------------------------------------------------------------------
IMessage& operator << (IMessage& out, const rational& val)
{
	out.add(int(val.getNumerator()));
	out.add(int(val.getDenominator()));
	return out;
}

//--------------------------------------------------------------------------
IMessage& operator <<(IMessage& msg, const TFloatPoint& val)
{
	msg.add(float(val.x()));
	msg.add(float(val.y()));
	return msg; 
}

//--------------------------------------------------------------------------
IMessage& operator <<(IMessage& msg, const TIntSize& val)
{
	msg.add(val.width());
	msg.add(val.height()); 
	return msg; 
}

//--------------------------------------------------------------------------
IMessage& operator <<(IMessage& msg, const std::string& val)
{ 
	msg.add(val);
	return msg; 
}

//--------------------------------------------------------------------------
IMessage& operator <<(IMessage& msg, const char* val)
{ 
	msg.add(string(val));
	return msg; 
}

//--------------------------------------------------------------------------
IMessage& operator << (IMessage& out, const IMessage* m)
{
//	string addr = m->extendedAddress() ? (string(m->url()) + m->address()) : m->address();
//	out << addr << m->message();
	out << m->address() << m->message();
	for (int i = 0; i < m->size(); i++) {
        string strv; int iv; float fv;
		if (m->param(i, iv))	out << iv;
		else if (m->param(i, fv))	out << fv;
        else if (m->param(i, strv))	out << strv;
	}
	return out;
}

//--------------------------------------------------------------------------
std::ostream& operator << (std::ostream& out, const IMessage* m)
{
	m->print(out);
	return out;
}

} // end namespoace
