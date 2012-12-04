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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>
#include <sstream>

#include "IMessage.h"
#include "IMessageStream.h"
#include "IMessageStack.h"
#include "rational.h"

#ifndef NO_OSCSTREAM
#include "OSCStream.h"
#include "ITLError.h"
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
IMessage::IMessage(const IMessage& msg)
{
	*this = msg;
}

//--------------------------------------------------------------------------
IMessage::IMessage(const std::string& address, const std::string& msg)
				: fAddress(address)
{
	fArguments.push_back (new IMsgParam<string>(msg));
	fHasMessage = true;
}

//--------------------------------------------------------------------------
IMessage::IMessage(const std::string& address, const argslist& args, const TUrl& url)
				: fAddress(address), fHasMessage(false), fUrl(url.fHostname.c_str(), url.fPort)
{
	fArguments = args;
	if (fArguments.size()) {
		string method = fArguments[0]->value<string>("");
		fHasMessage = method.size() && !needQuotes(method);
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
static bool decodeAddress (const std::string& address, std::string& oscAddress, IMessage::TUrl& url)
{
	size_t startOsc = address.find_first_of('/');
	if (startOsc == string::npos) return false;		// incorrect osc address (no '/')
	oscAddress = address.substr (startOsc);			// stores the osc address

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
SIMessage IMessage::watchMsg2Msg(int& index) const
{
	string address, oscaddress; TUrl url;
	if (!param(index++, address) || !decodeAddress (address, oscaddress, url)) {
		ITLErr << "incorrect address in watch message" << ITLEndl;
		return 0;
	}
	
	argslist args;
	int n = size();
	while (index < n) {
		// first look for the messages separator ( ',' or ':')
		string str;
		if (param(index, str) && ((str == ",") || (str == ":")) ) {
			index++;
			break;
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
	list = IMessageList::create();
	int n = size();
	while (startIndex < n) {
		SIMessage msg = watchMsg2Msg (startIndex);
		if (!msg) break;
		else list->list().push_back(msg);
	}
	return list;
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
// sending messages
//--------------------------------------------------------------------------
void IMessage::send() const
{
	if (extendedAddress()) {
#ifndef NO_OSCSTREAM
		OSCStream::sendEvent (this, url().fHostname, url().fPort);
#endif
	}
	else {
#ifndef PARSERTEST
		SIMessage copy = IMessage::create(*this);
		if (copy) gMsgStack->push(new SIMessage(copy));
#endif
	}
}

//--------------------------------------------------------------------------
void IMessageList::send() const
{
	for (unsigned int i=0; i < list().size(); i++) {
		const IMessage * msg = list()[i];
		if (msg) msg->send();
	}
}

//--------------------------------------------------------------------------
// print a single parameter
//--------------------------------------------------------------------------
void IMessage::print(std::ostream& out, int i, int nested) const
{
	string str; int val; float fval;
	SIMessageList msgs; TJavaScript js; TLuaScript lua;

	if (param(i, str)) {
		const char * q = needQuotes (str) ? "\"" : "";
		out << q << escape(str) << q;
	}
	else if (param(i, val))
		out << val;
	else if (param(i, fval))
		out << fval;
	else if (param(i, msgs)) {
		string prefix;
		while (nested--) { prefix += "	"; }
		msgs->list().set(prefix.c_str(), ",\n");
		out << "(\n" << msgs->list() << " )";
	}
	else if (param(i, js))
		out << "<? javascript " << js << " ?>";
	else if (param(i, lua))
		out << "<? lua " << js << " ?>";
}

//--------------------------------------------------------------------------
void IMessage::print(std::ostream& out) const
{
	static int nested = 0;
	nested++;
	ios::fmtflags f = out.flags ( ios::showpoint );
	const char * msg = message().c_str();

	if (extendedAddress()) out << string(fUrl);
	out << address() << " ";
	if (*msg) {
		const string method = message();
		const char * q = needQuotes (method) ? "\"" : "";
		out << q << escape(method) << q;
	}
	if (size()) {
		out << " ";
		for (int i=0; i< size()-1; i++) {
			print (out, i, nested);
			out << " ";
		}
		print (out, size()-1, nested);
	}
	if (nested == 1) out << ";";
	nested--;
	out.flags ( f );
}

IMessage::TUrl::operator string() const
{
	stringstream str;
	str << fHostname << ':' << fPort;
	return str.str();
}

#ifndef NO_OSCSTREAM
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
	osc << OSCStart(address().c_str());
	if (message().size()) osc << message();
	printArgs(osc);
	osc << OSCEnd();
}
	
//--------------------------------------------------------------------------
void IMessage::printArgs(OSCStream& osc) const
{
	for (int i=0; i < size(); i++) {
		std::string str; float fv; int iv;
		SIMessageList msgs;
		if (param(i, fv))			osc << fv;
		else if (param(i, iv))		osc << iv;
		else if (param(i, str))		osc << str;
		else if (param(i, msgs)) {
			int n = msgs->list().size() - 1;
			for (int i=0; i < n; i++) {
				const IMessage* msg = msgs->list()[i];
				msg->linearize(osc);
				osc << ":";
			}
			if (n >= 0) msgs->list()[n]->linearize(osc);
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
IMessage& operator << (IMessage& out, const rational& val)
{
	out.add(int(val.getNumerator()));
	out.add(int(val.getDenominator()));
	return out;
}

//--------------------------------------------------------------------------
IMessage& operator <<(IMessage& msg, const TFloatPoint& val)
{
	msg.add(val.x());
	msg.add(val.y());
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
	const char *ptr = val.c_str();
	bool quote = false;
	while (*ptr) {
		if (*ptr == ' ') {
			quote = true;
			break;
		}
		ptr++;
	}
	msg.add(val);
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
