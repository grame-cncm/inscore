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
bool EventMessage::isDateVar (const string& var, string& mapname) const
{
	string base (kDateVar);
	if (var == base) return true;
	if (var.compare (0, base.size(), base) == 0) {
		if (var[base.size()] == ':') {
			mapname = var.substr(base.size()+1);
			return true;
		}
	}
	return false;
}

//----------------------------------------------------------------------
bool EventMessage::hasDateVar (std::string& mapname) const
{
	if (!fMessage) return false;
	if (isDateVar (fMessage->message(), mapname)) return true;
	int n = fMessage->size();
	for (int i=0; i<n; i++) {
		string str;
		if (fMessage->param(i, str))
			if (isDateVar (str, mapname))  return true;
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
void EventMessage::eval (const string& var, EventContext& env, IMessage& outmsg) const
{
	string mapname;
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
	else if (isDateVar (var, mapname))	outmsg << env.date;
	else if (env.varmsg)	eval(env.varmsg, env.object, outmsg);
	else outmsg << var;
}

//----------------------------------------------------------------------
// message parameters evaluation 
// actually, a variable (i.e. a param starting with a '$') is replaced by 
// its value (which may be a list of values in case of variable messages)
//----------------------------------------------------------------------
void EventMessage::eval (const IMessage *msg, EventContext& env, IMessage& outmsg) const
{
	string strvalue = msg->message();
	map<int, SIMessage>::const_iterator mi;
	if (strvalue[0] == '$') {
		mi = fVarMsgs.find(-1);
		if (mi == fVarMsgs.end())  env.varmsg = 0;
		else env.varmsg = mi->second;
		eval (strvalue, env, outmsg);
	}
	else outmsg.setMessage (strvalue);
	
	int n = fMessage->size();
	for (int i=0; i<n; i++) {
		if (fMessage->param(i, strvalue) && (strvalue[0] == '$')) {
			mi = fVarMsgs.find(i);
			if (mi == fVarMsgs.end())  env.varmsg = 0;
			else env.varmsg = mi->second;
			eval (strvalue, env, outmsg);
		}
		else outmsg.add(msg->params()[i]);
	}
}

//----------------------------------------------------------------------
void EventMessage::send(EventContext& env)
{
	if (fMessage) {
		IMessage msg (fMessage->address());
		eval (fMessage, env, msg);							// evaluate the parameters of the message
		if (fDest.empty())	localSend (&msg);
		else				sockSend (&msg, fDest, fPort);
	}
}

} // end namespoace

