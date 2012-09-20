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

#include <stdlib.h>
#include <sstream>

#include "EventMessage.h"
#include "IMessage.h"
#include "IMessageStack.h"
#include "IMessageStream.h"
#include "IObject.h"
#include "OSCStream.h"
#include "deelx.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

extern SIMessageStack gMsgStack;

const char* kXVar		= "$x";
const char* kYVar		= "$y";
const char* kSceneXVar	= "$sx";
const char* kSceneYVar	= "$sy";
const char* kAbsXVar	= "$absx";
const char* kAbsYVar	= "$absy";
const char* kDateVar	= "$date";
const char* kRelativeDateVar = "$rdate";
const char* kSelfVar	= "$self";
const char* kNameVar	= "$name";
const char* kAddressVar	= "$address";


//----------------------------------------------------------------------
EventMessage::EventMessage (const string& objname, const std::string& scene, const IMessage* msg, int startindex) 
	: fMessage(0), fPort(kDefaultUPDPort)
{
	decodeMessage (objname, scene, msg, startindex);
}

//----------------------------------------------------------------------
EventMessage::~EventMessage () { delete fMessage; }

//----------------------------------------------------------------------
string EventMessage::checkVariableAddress (const string& address, const string& objname, const string& scene) const
{
	CRegexpT<char> regexp1("\\$self", EXTENDED);
	char* tmp1 = regexp1.Replace (address.c_str(), objname.c_str());

	CRegexpT<char> regexp2("\\$scene", EXTENDED);
	char* tmp2 = regexp2.Replace (tmp1, scene.c_str());

	string outAddress = tmp2;
	regexp1.ReleaseString (tmp1);
	regexp2.ReleaseString (tmp2);
	return outAddress;
}

//----------------------------------------------------------------------
string EventMessage::address () const
{
	if (fDest.empty())	return fMessage->address();
	else {
		stringstream address;
		address << fDest << ':' << fPort << fMessage->address();
		return address.str();
	}
}

//----------------------------------------------------------------------
void EventMessage::decodeAddress (const std::string& address, std::string& oscAddress, std::string& host, int& port) const
{
	size_t startOsc = address.find_first_of('/');
	if (startOsc != string::npos) {
		port = kDefaultUPDPort;
		oscAddress = address.substr (startOsc);
		if (startOsc > 0) {
			size_t startPort = address.find_first_of(':');
			if ((startPort != string::npos) && (startPort < startOsc)) {
				host = address.substr (0, startPort);
				string portStr = address.substr (startPort+1, startOsc-1);
				port = atoi(portStr.c_str());
			}
			else host = address.substr (0, startOsc);
		}
		else host.clear();
	}
}

//----------------------------------------------------------------------
void EventMessage::splitMsg (const char * msg, vector<string>& list)
{
	string word;
	while (*msg) {
		if ((*msg ==' ') || (*msg=='	')) {
			if (word.size()) {
				list.push_back (word);
				word.clear();
			}
		}
		else word += *msg;
		msg++;
	}
	if (word.size()) list.push_back (word);
}

//----------------------------------------------------------------------
// check if the param is a message based variable
void EventMessage::checkVariableMsg (const string& param, int index)
{
	if ((param.substr (0,2) == "$(") && (param[param.size()-1] == ')')) {
		vector<string> parts;
		splitMsg (param.substr(2, param.size()-3).c_str(), parts);
		int n = parts.size();
		if ((n > 1) && (parts[1] == "get")) {
			IMessage* vmsg = new IMessage (parts[0], parts[1]);
			for (int i=2; i<n; i++)
				vmsg->add (parts[i]);
			fVarMsgs[index] = vmsg;
		}
	}
}

//----------------------------------------------------------------------
void EventMessage::decodeMessage (const string& objname, const std::string& scene, const IMessage* msg, int startindex)
{
	if ((msg->size() - startindex) < 2) return;
	string address;
	if (msg->param (startindex++, address)) {
		string oscAddress;
		decodeAddress (address, oscAddress, fDest, fPort);
		fMessage = new IMessage (checkVariableAddress(oscAddress, objname, scene));
		string msgStr;
		if ( msg->param (startindex, msgStr) ) {
			fMessage->setMessage (msgStr);
			checkVariableMsg (msgStr, -1);
			startindex++;
		}
		for (int i = startindex, n=0; i < msg->size(); i++, n++) {
			string pstr;
			fMessage->params().push_back( msg->params()[i]);
			if ( msg->param (i, pstr) ) checkVariableMsg (pstr, n);
		}
	}
}

static 	UdpSocket gEvtSocket;
OSCStream gStream (&gEvtSocket);
//----------------------------------------------------------------------
void EventMessage::sockSend (const IMessage* msg, const string& dst, int port) const
{
	gStream.setAddress (dst);
	gStream.setPort(port);
	msg->print(gStream);
}

//----------------------------------------------------------------------
void EventMessage::localSend (const IMessage* msg) const
{
	IMessage* copy = new IMessage (*msg);
	if (copy) gMsgStack->push(copy);
}

//----------------------------------------------------------------------
void EventMessage::send () const
{
	if (fMessage) {
		if (fDest.empty())	localSend (fMessage);
		else				sockSend (fMessage, fDest, fPort);
	}
}

//----------------------------------------------------------------------
bool EventMessage::parseQuant (const string& var, int& n, int& d)
{
	size_t n1 = var.find('[');
	if (n1 == string::npos) return false;
	size_t n2 = var.find('/');
	if (n2 == string::npos) return false;
	size_t n3 = var.find(']');
	if (n3 == string::npos) return false;

	int a = atoi(var.substr(n1+1, n2).c_str());
	int b = atoi(var.substr(n2+1, n3).c_str());
	if ( (a > 0) && (b > 0)) {
		n = a;
		d = b;
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
bool EventMessage::parseMap (const string& var, string& map)
{
	size_t n = var.find(':');
	size_t l = var.size();
	if (n == string::npos) return false;
	while (++n <= l) {
		char c = var[n];
		if (c == '[') break;
		else if (c == '%') break;
		else map += c;
	}
	return true;
}

//----------------------------------------------------------------------
bool EventMessage::parseFloat (const string& var, bool& floatval)
{
	floatval = false;
	size_t n = var.find('%');
	if (n == string::npos) return false;

	n++;
	char c = var[n++];
	if ((n == var.size()) && (c == 'f')) floatval = true;
	else return false;
	return true;
}

//----------------------------------------------------------------------
bool EventMessage::isDateVar (const string& var, string& mapname, int& num, int& denum, bool& relative, bool& floatval) const
{
	size_t datelength = strlen(kDateVar);
	size_t rdatelength = strlen(kRelativeDateVar);
	if (var.substr(0, rdatelength) == kRelativeDateVar)
		relative = true;
	else if (var.substr(0, datelength) != kDateVar)
		return false;
	else 
		relative = false;
	parseMap (var, mapname);
	parseQuant (var, num, denum);
	parseFloat (var, floatval);
	return true;
}

//----------------------------------------------------------------------
bool EventMessage::hasDateVar (std::string& mapname, int& num, int& denum, bool& relative, bool& floatval) const
{
	if (!fMessage) return false;
	if (isDateVar (fMessage->message(), mapname, num, denum, relative, floatval)) return true;
	int n = fMessage->size();
	for (int i=0; i<n; i++) {
		string str;
		if (fMessage->param(i, str))
			if (isDateVar (str, mapname, num, denum, relative, floatval))  return true;
	}
	return false;	
}

//----------------------------------------------------------------------
bool EventMessage::checkrange (const char* param) const
{
	while (*param) {
		if (*param == '[') return true;
		param++;
	}
	return false;
}

//----------------------------------------------------------------------
bool EventMessage::checkfloat (const char* param) const
{
	if (!checkrange(param)) return true;
	while (*param) {
		if (*param == '.') return true;
		param++;
	}
	return false;
}

//----------------------------------------------------------------------
float EventMessage::checkfloatrange (const string& param, float val) const
{
	float low, high;
	int n = sscanf (param.c_str(), "[%f,%f]", &low, &high);
	if (n == 2) {
		return val * (high - low) + low;
	}
	return val;
}

//----------------------------------------------------------------------
int EventMessage::checkintrange (const string& param, float val) const
{
	return int(checkfloatrange(param, val));
}

//----------------------------------------------------------------------
// evaluates a message variable, 
// the object argument is only used to retrieve the scene root node
// and to get the target objects from the message OSC address 
//----------------------------------------------------------------------
void EventMessage::eval (const IMessage* msg, const IObject * object, IMessage& outmsg) const
{
	IMessageList list;
	vector<const IObject*> targets;
	object->getRoot()->getObjects(msg->address(), targets);
	for (unsigned int i=0; i < targets.size(); i++) {
		list += targets[i]->getMsgs (msg);
	}

	for (IMessageList::const_iterator i = list.begin(); i != list.end(); i++) {
		IMessage * m = *i;
		for (int n=0; n < m->size(); n++) {
			outmsg.add (m->params()[n]);
		}
	}
}

//----------------------------------------------------------------------
// evaluates a single variable, 
// the variable value is taken from the context
// in case of  variable message, the message is processed and the value
// is taken from the output message parameters
//----------------------------------------------------------------------
bool EventMessage::eval (const string& var, EventContext& env, IMessage& outmsg) const
{
	string mapname;
	int num=0, denum=0;
	bool floatval;
	bool relative = false;
	if (var[1] == 'x')	{
		if (checkfloat(var.c_str())) outmsg << checkfloatrange(var.substr(2), env.mouse.fx); 
		else outmsg << checkintrange(var.substr(2), env.mouse.fx);
	}
	else if (var[1] == 'y')	{
		if (checkfloat(var.c_str())) outmsg << checkfloatrange(var.substr(2), env.mouse.fy); 
		else outmsg << checkintrange(var.substr(2), env.mouse.fy);
	}
	else if (var == kAbsXVar)		outmsg << env.mouse.fabsx;
	else if (var == kAbsYVar)		outmsg << env.mouse.fabsy;
	else if (var == kSceneXVar) 	outmsg << env.mouse.fsx;
	else if (var == kSceneYVar)		outmsg << env.mouse.fsy;
	else if (var == kNameVar)		outmsg << env.object->name();
	else if (var == kAddressVar)	outmsg << env.object->getOSCAddress();
	else if (isDateVar (var, mapname, num, denum, relative, floatval)) {
		if (!env.date.getDenominator()) return false;		// date can't be resolved
		if (num) {
			float fd = float(env.date);
			if (!floatval) {
				rational qdate (int(fd * denum / num) * num, denum);
				outmsg << qdate;
			}
			else outmsg << fd;
		}
		else if (floatval)
			outmsg << float(env.date);
		else
			outmsg << env.date;
	}
	else if (env.varmsg)	eval(env.varmsg, env.object, outmsg);
	else outmsg << var;
	return true;
}

//----------------------------------------------------------------------
// message parameters evaluation 
// actually, a variable (i.e. a param starting with a '$') is replaced by 
// its value (which may be a list of values in case of variable messages)
//----------------------------------------------------------------------
bool EventMessage::eval (const IMessage *msg, EventContext& env, IMessage& outmsg) const
{
	string strvalue = msg->message();
	map<int, SIMessage>::const_iterator mi;
	if (strvalue[0] == '$') {
		mi = fVarMsgs.find(-1);
		if (mi == fVarMsgs.end())  env.varmsg = 0;
		else env.varmsg = mi->second;
		if (!eval (strvalue, env, outmsg)) return false;
	}
	else outmsg.setMessage (strvalue);
	
	int n = fMessage->size();
	for (int i=0; i<n; i++) {
		if (fMessage->param(i, strvalue) && (strvalue[0] == '$')) {
			mi = fVarMsgs.find(i);
			if (mi == fVarMsgs.end())  env.varmsg = 0;
			else env.varmsg = mi->second;
			if (!eval (strvalue, env, outmsg)) return false;
		}
		else outmsg.add(msg->params()[i]);
	}
	return true;
}

//----------------------------------------------------------------------
void EventMessage::send(EventContext& env)
{
	if (fMessage) {
		IMessage msg (fMessage->address());
		if (eval (fMessage, env, msg)) {							// evaluate the parameters of the message
			if (fDest.empty())	localSend (&msg);
			else				sockSend (&msg, fDest, fPort);
		}
	}
}

} // end namespoace

