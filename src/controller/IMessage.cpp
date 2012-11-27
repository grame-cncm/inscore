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
#include "rational.h"

#ifndef NO_OSCSTREAM
#include "ITLError.h"
#endif

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
// IMessage implementation
//--------------------------------------------------------------------------
IMessage::IMessage(const IMessage& msg)
{
	*this = msg;
}

//--------------------------------------------------------------------------
IMessage::IMessage(const std::string& address, const argslist& args, const TUrl& url)
				: fAddress(address), fHasMessage(true), fUrl(url.fHostname.c_str(), url.fPort)
{
	fArguments = args;
	fHasMessage = fArguments.size() && fArguments[0]->isType<string>();
}

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
	const char *ptr = str.c_str();
	while (*ptr) {
		char c = *ptr++;
		if ((c == ' ') || (c == '\t') || (c == 0x0a) || (c == 0x0d))
			return true;
	}
	return false;
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
SIMessage IMessage::watchMsg2Msg(int& index)
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
SIMessageList IMessage::watchMsg2Msgs(int startIndex)
{
	SIMessageList list = IMessageList::create();
	int n = size();
	while (startIndex < n) {
		SIMessage msg = watchMsg2Msg (startIndex);
		if (!msg) break;
		else list->list().push_back(msg);
	}
	return list;
}

//--------------------------------------------------------------------------
SIMessage IMessage::buildWatchMsg(int startIndex)
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
// print a single parameter
//--------------------------------------------------------------------------
void IMessage::print(std::ostream& out, int i, int nested) const
{
	string str; int val; float fval; SIMessageList msgs; TJavaScript js; TLuaScript lua;

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

	if (fUrl.fPort) out << fUrl.fHostname << ':' << fUrl.fPort;
	out << address() << " ";
	if (*msg) out << message();
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

//--------------------------------------------------------------------------
bool IMessage::operator == (const IMessage& other) const
{
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
