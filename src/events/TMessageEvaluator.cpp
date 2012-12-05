/*

  INScore Project

  Copyright (C) 2009-2012  Grame

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

#include "TMessageEvaluator.h"
#include "IMessageStack.h"
#include "IMessageStream.h"
#include "IObject.h"
#include "IScene.h"
#include "deelx.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

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

map<const char*, int> TMessageEvaluator::fVarLength; 

//----------------------------------------------------------------------
void TMessageEvaluator::init ()
{
	if (fVarLength.size() == 0) {
		fVarLength[kXVar]		= strlen(kXVar);
		fVarLength[kYVar]		= strlen(kYVar);
		fVarLength[kSceneXVar]	= strlen(kSceneXVar);
		fVarLength[kSceneYVar]	= strlen(kSceneYVar);
		fVarLength[kAbsXVar]	= strlen(kAbsXVar);
		fVarLength[kAbsYVar]	= strlen(kAbsYVar);
		fVarLength[kDateVar]	= strlen(kDateVar);
		fVarLength[kRelativeDateVar] = strlen(kRelativeDateVar);
		fVarLength[kSelfVar]	= strlen(kSelfVar);
		fVarLength[kNameVar]	= strlen(kNameVar);
		fVarLength[kAddressVar]	= strlen(kAddressVar);
	}
}

//----------------------------------------------------------------------
bool TMessageEvaluator::checkrange (const char* param)
{
	CRegexpT <char> regexp("\\[\\d+.*\\d*,\\d+.*\\d*\\]");
    MatchResult result = regexp.MatchExact(param);
    return result.IsMatched();
}

//----------------------------------------------------------------------
string TMessageEvaluator::evalAddress (const string& address, const IObject* obj) const
{
	const IScene* scene = obj->getScene();
	string objname = obj->name();
	string scenename = scene ? scene->name() : "";
	
	CRegexpT<char> regexp1("\\$self", EXTENDED);
	char* tmp1 = regexp1.Replace (address.c_str(), objname.c_str());

	CRegexpT<char> regexp2("\\$scene", EXTENDED);
	char* tmp2 = regexp2.Replace (tmp1, scenename.c_str());

	string outAddress = tmp2;
	regexp1.ReleaseString (tmp1);
	regexp2.ReleaseString (tmp2);
	return outAddress;
}

//----------------------------------------------------------------------
bool TMessageEvaluator::floatRequired (const char* param) const
{
	while (*param) if (*param++ == '.') return true;
	return false;
}

//----------------------------------------------------------------------
Sbaseparam TMessageEvaluator::evalRange (const string& range, float pos) const
{
	float low, high;
	int n = sscanf (range.c_str(), "[%f,%f]", &low, &high);
	if (n == 2) pos = pos * (high - low) + low;
	if (floatRequired (range.c_str()))
		return new IMsgParam<float>(pos);
	else 
		return new IMsgParam<int>(int(pos));
}

//----------------------------------------------------------------------
Sbaseparam TMessageEvaluator::evalPosition (const string& range, float pos) const
{
	if (range.size() && checkrange (range.c_str())) {
		return evalRange (range, pos);
	}
	return new IMsgParam<float>(pos);
}

//----------------------------------------------------------------------
bool TMessageEvaluator::posVariable (const string& param, const char* var) const
{
	return param.substr(0, fVarLength[var]) == var;
}

//----------------------------------------------------------------------
string TMessageEvaluator::parseMap (const string& var)
{
	CRegexpT <char> regexp(":[a-zA-Z0-9_]+");		// identifier characters set allowed after ':'
    MatchResult result = regexp.Match(var.c_str());
	int start = result.GetStart() + 1;				// ':' is stripped from th map name
	int end = result.GetEnd();
	if (result.IsMatched()) return var.substr (start, end-start);
	return "";
}

//----------------------------------------------------------------------
string TMessageEvaluator::parseQuant (const string& var)
{
	CRegexpT <char> regexp("\\[\\d+/\\d+\\]");		// quantification form is [n/d]
    MatchResult result = regexp.Match(var.c_str());
	int start = result.GetStart();
	int end = result.GetEnd();
	if (result.IsMatched()) return var.substr (start, end-start);
	return "";
}

//----------------------------------------------------------------------
bool TMessageEvaluator::floatRequested (const string& var)
{
	if (var.size() > 2)
		return var.substr (var.size()-2, 2) == "%f";
	return false;
}

//----------------------------------------------------------------------
bool TMessageEvaluator::dateVariable (const string& var, bool& relative)
{
	if (var.substr(0, fVarLength[kRelativeDateVar]) == kRelativeDateVar)
		relative = true;
	else if (var.substr(0, fVarLength[kDateVar]) == kDateVar)
		relative = false;
	else 
		return false;
	return true;
}

//----------------------------------------------------------------------
void TMessageEvaluator::parseDateVariable (const std::string& var, libmapping::rational quant, bool& floatval) const
{
	string quantstr = parseQuant(var);
	int num, denum;
	if (quantstr.size()) {
		int n = sscanf (quantstr.c_str(), "[%d/%d]", &num, &denum);
		if (n != 2) quant = rational (0,1);
		else quant = rational (num, denum);
	}
	floatval = floatRequested(var);
}

//----------------------------------------------------------------------
IMessage::argslist TMessageEvaluator::evalDate (const string& var, const EventContext& env, bool relative) const
{
	IMessage::argslist outval;
	rational quant; bool floatrequired;

	parseDateVariable (var, quant, floatrequired);
	rational date = env.date;
	if (!relative) date += env.object->getDate();
	if (quant.getNumerator()) {									// date quantification required
		date *= quant;
		date /= quant;
	}
	if (floatrequired)											// float value required
		outval.push_back ( new IMsgParam<float>(float(date)));	// push the float date value
	else {
		outval.push_back ( new IMsgParam<int>(date.getNumerator()));
		outval.push_back ( new IMsgParam<int>(date.getDenominator()));
	}
	return outval;
}

//----------------------------------------------------------------------
IMessage::argslist TMessageEvaluator::evalVariable (const string& var, const EventContext& env) const
{
	IMessage::argslist outval;
	bool relative = false;

	if (var[0] == '$') {
		if (posVariable (var, kXVar))			outval.push_back ( evalPosition (var.substr(fVarLength[kXVar]), env.mouse.fx));
		else if (posVariable (var, kYVar))		outval.push_back ( evalPosition (var.substr(fVarLength[kYVar]), env.mouse.fy));
		else if (posVariable (var, kAbsXVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kAbsXVar]), env.mouse.fabsx));
		else if (posVariable (var, kAbsYVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kAbsYVar]), env.mouse.fabsy));
		else if (posVariable (var, kSceneXVar)) outval.push_back ( evalPosition (var.substr(fVarLength[kSceneXVar]), env.mouse.fsx));
		else if (posVariable (var, kSceneYVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kSceneYVar]), env.mouse.fsy));
		
		else if (var == kNameVar)			outval.push_back ( new IMsgParam<string>(env.object->name()));
		else if (var == kAddressVar)		outval.push_back ( new IMsgParam<string>(env.object->getOSCAddress()));

		else if (dateVariable (var, relative)) {
			if (!env.date.getDenominator()) return outval;		// date can't be resolved
			outval.push_back ( evalDate (var, env, relative));
		}
		
	}
	else outval.push_back ( new IMsgParam<string>(var) );
	return outval;
}

//----------------------------------------------------------------------
bool TMessageEvaluator::hasDateVar (const IMessage *msg, string& mapname)
{
	for (int i=0; i < msg->size(); i++) {
		string str;
		if (msg->param( i, str)) {
			bool relative;
			if (dateVariable(str, relative)) {
				mapname = parseMap(str);
				return true;
			}
		}
	}
	return false;
}

//----------------------------------------------------------------------
SIMessage TMessageEvaluator::eval (const IMessage *msg, const EventContext& env) const
{
	// evaluate the address that may contain variable parts
	string address = evalAddress (msg->address(), env.object);
	// create a new message with an evaluated address
	SIMessage outmsg = IMessage::create( evalAddress (msg->address(), env.object));
	outmsg->setUrl ( msg->url() );

	// evaluate the message string
	IMessage::argslist methodlist = evalVariable(msg->message(), env);
	string method = methodlist[0]->value<string>("");
	if (method.size()) outmsg->setMessage (method);
	for (unsigned int i=1; i<methodlist.size(); i++)
		outmsg->add( methodlist[i] );

	// evaluate all the parameters
	for (int i=0; i < msg->size(); i++) {
		string str;
		if (msg->param( i, str)) {
			IMessage::argslist values = evalVariable(str, env);
			if (!values.size()) return 0;		// variables are expected to give at least one value
			outmsg->add( values );
		}
		else outmsg->add( msg->param(i) );
	}
	return outmsg;
}


//----------------------------------------------------------------------
SIMessageList TMessageEvaluator::eval (const IMessageList* msgs, const EventContext& env) const
{
	SIMessageList outmsgs = IMessageList::create();
	for (unsigned int i = 0; i <  msgs->list().size(); i++) {
		const IMessage *msg = msgs->list()[i];
		SIMessage emsg = eval (msg, env);
		if (emsg) outmsgs->list().push_back(emsg);
	}
	return outmsgs;
}

//----------------------------------------------------------------------
//string EventMessage::checkVariableAddress (const string& address, const string& objname, const string& scene) const
//{
//	CRegexpT<char> regexp1("\\$self", EXTENDED);
//	char* tmp1 = regexp1.Replace (address.c_str(), objname.c_str());
//
//	CRegexpT<char> regexp2("\\$scene", EXTENDED);
//	char* tmp2 = regexp2.Replace (tmp1, scene.c_str());
//
//	string outAddress = tmp2;
//	regexp1.ReleaseString (tmp1);
//	regexp2.ReleaseString (tmp2);
//	return outAddress;
//}

//----------------------------------------------------------------------
//string EventMessage::address () const
//{
//	return "";
//	if (fDest.empty())	return fMessage->address();
//	else {
//		stringstream address;
//		address << fDest << ':' << fPort << fMessage->address();
//		return address.str();
//	}
//}

//----------------------------------------------------------------------
//void EventMessage::decodeAddress (const std::string& address, std::string& oscAddress, std::string& host, int& port) const
//{
//	size_t startOsc = address.find_first_of('/');
//	if (startOsc != string::npos) {
//		port = kDefaultUPDPort;
//		oscAddress = address.substr (startOsc);
//		if (startOsc > 0) {
//			size_t startPort = address.find_first_of(':');
//			if ((startPort != string::npos) && (startPort < startOsc)) {
//				host = address.substr (0, startPort);
//				string portStr = address.substr (startPort+1, startOsc-1);
//				port = atoi(portStr.c_str());
//			}
//			else host = address.substr (0, startOsc);
//		}
//		else host.clear();
//	}
//}

//----------------------------------------------------------------------
//void EventMessage::splitMsg (const char * msg, vector<string>& list)
//{
//	string word;
//	while (*msg) {
//		if ((*msg ==' ') || (*msg=='	')) {
//			if (word.size()) {
//				list.push_back (word);
//				word.clear();
//			}
//		}
//		else word += *msg;
//		msg++;
//	}
//	if (word.size()) list.push_back (word);
//}

//----------------------------------------------------------------------
// check if the param is a message based variable
//void EventMessage::checkVariableMsg (const string& param, int index)
//{
//	if ((param.substr (0,2) == "$(") && (param[param.size()-1] == ')')) {
//		vector<string> parts;
//		splitMsg (param.substr(2, param.size()-3).c_str(), parts);
//		int n = parts.size();
//		if ((n > 1) && (parts[1] == "get")) {
//			SIMessage vmsg = IMessage::create (parts[0], parts[1]);
//			for (int i=2; i<n; i++)
//				vmsg->add (parts[i]);
//			fVarMsgs[index] = vmsg;
//		}
//	}
//}

//----------------------------------------------------------------------
//void EventMessage::decodeMessage (const string& objname, const std::string& scene, const IMessage* msg, int startindex)
//{
//	if ((msg->size() - startindex) < 2) return;
//	string address;
//	if (msg->param (startindex++, address)) {
//		string oscAddress;
////		decodeAddress (address, oscAddress, fDest, fPort);
//		fMessage = IMessage::create (checkVariableAddress(oscAddress, objname, scene));
//		string msgStr;
//		if ( msg->param (startindex, msgStr) ) {
//			fMessage->setMessage (msgStr);
//			checkVariableMsg (msgStr, -1);
//			startindex++;
//		}
//		for (int i = startindex, n=0; i < msg->size(); i++, n++) {
//			string pstr;
//			fMessage->add( msg->param(i));
//			if ( msg->param (i, pstr) ) checkVariableMsg (pstr, n);
//		}
//	}
//}

//----------------------------------------------------------------------
//bool EventMessage::parseQuant (const string& var, int& n, int& d)
//{
//	size_t n1 = var.find('[');
//	if (n1 == string::npos) return false;
//	size_t n2 = var.find('/');
//	if (n2 == string::npos) return false;
//	size_t n3 = var.find(']');
//	if (n3 == string::npos) return false;
//
//	int a = atoi(var.substr(n1+1, n2).c_str());
//	int b = atoi(var.substr(n2+1, n3).c_str());
//	if ( (a > 0) && (b > 0)) {
//		n = a;
//		d = b;
//		return true;
//	}
//	return false;
//}

//----------------------------------------------------------------------
//bool EventMessage::parseMap (const string& var, string& map)
//{
//	size_t n = var.find(':');
//	size_t l = var.size();
//	if (n == string::npos) return false;
//	while (++n <= l) {
//		char c = var[n];
//		if (c == '[') break;
//		else if (c == '%') break;
//		else map += c;
//	}
//	return true;
//}

//----------------------------------------------------------------------
//bool EventMessage::parseFloat (const string& var, bool& floatval)
//{
//	floatval = false;
//	size_t n = var.find('%');
//	if (n == string::npos) return false;
//
//	n++;
//	char c = var[n++];
//	if ((n == var.size()) && (c == 'f')) floatval = true;
//	else return false;
//	return true;
//}

//----------------------------------------------------------------------
//bool EventMessage::isDateVar (const string& var, string& mapname, int& num, int& denum, bool& relative, bool& floatval) const
//{
//	size_t datelength = strlen(kDateVar);
//	size_t rdatelength = strlen(kRelativeDateVar);
//	if (var.substr(0, rdatelength) == kRelativeDateVar)
//		relative = true;
//	else if (var.substr(0, datelength) != kDateVar)
//		return false;
//	else 
//		relative = false;
//	parseMap (var, mapname);
//	parseQuant (var, num, denum);
//	parseFloat (var, floatval);
//	return true;
//}

//----------------------------------------------------------------------
//bool EventMessage::hasDateVar (std::string& mapname, int& num, int& denum, bool& relative, bool& floatval) const
//{
//	if (!fMessage) return false;
//	if (isDateVar (fMessage->message(), mapname, num, denum, relative, floatval)) return true;
//	int n = fMessage->size();
//	for (int i=0; i<n; i++) {
//		string str;
//		if (fMessage->param(i, str))
//			if (isDateVar (str, mapname, num, denum, relative, floatval))  return true;
//	}
//	return false;	
//}

//----------------------------------------------------------------------
//bool EventMessage::checkrange (const char* param) const
//{
//	while (*param) {
//		if (*param++ == '[') return true;
//	}
//	return false;
//}

//----------------------------------------------------------------------
//bool EventMessage::checkfloat (const char* param) const
//{
//	if (!checkrange(param)) return true;
//	while (*param) {
//		if (*param++ == '.') return true;
//	}
//	return false;
//}

//----------------------------------------------------------------------
//float EventMessage::checkfloatrange (const string& param, float val) const
//{
//	float low, high;
//	int n = sscanf (param.c_str(), "[%f,%f]", &low, &high);
//	if (n == 2) {
//		return val * (high - low) + low;
//	}
//	return val;
//}

//----------------------------------------------------------------------
//int EventMessage::checkintrange (const string& param, float val) const
//{
//	return int(checkfloatrange(param, val));
//}

//----------------------------------------------------------------------
// evaluates a message variable, 
// the object argument is only used to retrieve the scene root node
// and to get the target objects from the message OSC address 
//----------------------------------------------------------------------
//void EventMessage::eval (const IMessage* msg, const IObject * object, SIMessage& outmsg) const
//{
//	SIMessageList list = IMessageList::create();
//	vector<const IObject*> targets;
//	object->getRoot()->getObjects(msg->address(), targets);
//	for (unsigned int i=0; i < targets.size(); i++) {
//		const IObject* o = targets[i];
//		SIMessageList l = o->getMsgs (msg);
//		list->list().push_back (l->list());
//	}
//
//	for (IMessageList::TMessageList::const_iterator i = list->list().begin(); i != list->list().end(); i++) {
//		const SIMessage& m = *i;
//		for (int n=0; n < m->size(); n++) {
//			outmsg->add (m->param(n));
//		}
//	}
//}

//----------------------------------------------------------------------
// evaluates a single variable, 
// the variable value is taken from the context
// in case of  variable message, the message is processed and the value
// is taken from the output message parameters
//----------------------------------------------------------------------
//bool EventMessage::eval (const string& var, EventContext& env, SIMessage& outmsg) const
//{
//	string mapname;
//	int num=0, denum=0;
//	bool floatval;
//	bool relative = false;
//	if (var[1] == 'x')	{
//		if (checkfloat(var.c_str())) *outmsg << checkfloatrange(var.substr(2), env.mouse.fx);
//		else *outmsg << checkintrange(var.substr(2), env.mouse.fx);
//	}
//	else if (var[1] == 'y')	{
//		if (checkfloat(var.c_str())) *outmsg << checkfloatrange(var.substr(2), env.mouse.fy);
//		else *outmsg << checkintrange(var.substr(2), env.mouse.fy);
//	}
//	else if (var == kAbsXVar)		*outmsg << env.mouse.fabsx;
//	else if (var == kAbsYVar)		*outmsg << env.mouse.fabsy;
//	else if (var == kSceneXVar) 	*outmsg << env.mouse.fsx;
//	else if (var == kSceneYVar)		*outmsg << env.mouse.fsy;
//	else if (var == kNameVar)		*outmsg << env.object->name();
//	else if (var == kAddressVar)	*outmsg << env.object->getOSCAddress();
//	else if (isDateVar (var, mapname, num, denum, relative, floatval)) {
//		if (!env.date.getDenominator()) return false;		// date can't be resolved
//		if (num) {
//			float fd = float(env.date);
//			if (!floatval) {
//				rational qdate (int(fd * denum / num) * num, denum);
//				*outmsg << qdate;
//			}
//			else *outmsg << fd;
//		}
//		else if (floatval)
//			*outmsg << float(env.date);
//		else
//			*outmsg << env.date;
//	}
//	else if (env.varmsg)	eval(env.varmsg, env.object, outmsg);
//	else *outmsg << var;
//	return true;
//}

//----------------------------------------------------------------------
// message parameters evaluation 
// actually, a variable (i.e. a param starting with a '$') is replaced by 
// its value (which may be a list of values in case of variable messages)
//----------------------------------------------------------------------
//bool EventMessage::eval (const IMessage *msg, EventContext& env, SIMessage& outmsg) const
//{
//	string strvalue = msg->message();
//	map<int, SIMessage>::const_iterator mi;
//	if (strvalue[0] == '$') {
//		mi = fVarMsgs.find(-1);
//		if (mi == fVarMsgs.end())  env.varmsg = 0;
//		else env.varmsg = mi->second;
//		if (!eval (strvalue, env, outmsg)) return false;
//	}
//	else outmsg->setMessage (strvalue);
//	
//	int n = fMessage->size();
//	for (int i=0; i<n; i++) {
//		if (fMessage->param(i, strvalue) && (strvalue[0] == '$')) {
//			mi = fVarMsgs.find(i);
//			if (mi == fVarMsgs.end())  env.varmsg = 0;
//			else env.varmsg = mi->second;
//			if (!eval (strvalue, env, outmsg)) return false;
//		}
//		else outmsg->add(msg->param(i));
//	}
//	return true;
//}

//----------------------------------------------------------------------
//void EventMessage::localSend (const IMessage* msg) const
//{
//	SIMessage copy = IMessage::create(*msg);
//	if (copy) gMsgStack->push(new SIMessage(copy));
//}

//----------------------------------------------------------------------
//void EventMessage::send(EventContext& env)
//{
//	if (fMessage) {
//		SIMessage msg = IMessage::create(fMessage->address());
//		if (eval (fMessage, env, msg)) {							// evaluate the parameters of the message
//			if (msg->extendedAddress())
//					OSCStream::sendEvent (msg, msg->url().fHostname, msg->url().fPort);
//			else	localSend (msg);
//		}
//	}
//}

//----------------------------------------------------------------------
//void EventMessage::send () const
//{
//	if (fMessage) {
//		if (fMessage->extendedAddress())
//				OSCStream::sendEvent (fMessage, fMessage->url().fHostname, fMessage->url().fPort);
//		else	localSend (fMessage);
//	}
//}

} // end namespoace

