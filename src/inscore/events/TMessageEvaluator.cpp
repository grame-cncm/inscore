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

#ifdef WIN32
#pragma warning (disable : 4996 4267)
#endif

#include <stdlib.h>
#include <sstream>

#include "TMessageEvaluator.h"
#include "IMessageStack.h"
#include "IMessageStream.h"
#include "IObject.h"
#include "IScene.h"
#include "ITLparser.h"
#include "IGlue.h"
#include "IAppl.h"

#include "deelx.h"

#include "INScore.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

extern IGlue* gGlue;

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
const char* kSceneVar	= "$scene";
const char* kAddressVar	= "$address";
const char* kVersion	= "$version";

// gesture follower variables
const char* kLikelihoodVar	= "$gflikelihood";
const char* kPosVar			= "$gfpos";
const char* kSpeedVar		= "$gfspeed";

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
		fVarLength[kSceneVar]	= strlen(kSceneVar);
		fVarLength[kAddressVar]	= strlen(kAddressVar);
		fVarLength[kVersion]	= strlen(kVersion);

		fVarLength[kLikelihoodVar]	= strlen(kLikelihoodVar);
		fVarLength[kPosVar]			= strlen(kPosVar);
		fVarLength[kSpeedVar]		= strlen(kSpeedVar);
	}
}

//----------------------------------------------------------------------
bool TMessageEvaluator::checkrange (const char* param)
{
	CRegexpT <char> regexp("\\[.+,.+\\]");
    MatchResult result = regexp.MatchExact(param);
    return result.IsMatched();
}

//----------------------------------------------------------------------
string TMessageEvaluator::evalAddress (const string& address, const IObject* obj) const
{
	if (!obj) return address;

	const IScene* scene = obj->getScene();
	string objname = obj->name();
	string scenename = scene ? scene->name() : "scene";
	
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
	else ITLErr << "incorrect range:" << range << ITLEndl;
	if (floatRequired (range.c_str()))
		return new IMsgParam<float>(pos);
	else 
		return new IMsgParam<int>(int(pos));
}

//----------------------------------------------------------------------
Sbaseparam TMessageEvaluator::evalPosition (const string& range, float pos) const
{
	if (!range.empty() && checkrange (range.c_str())) {
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
bool TMessageEvaluator::gestVariable (const string& param, const char* var) const
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
bool TMessageEvaluator::messageVariable (const string& var)
{
	size_t n = var.size();
	return (n > 4) && (var[1] == '(') && (var[n-1] == ')');
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
	if (env.object && !relative) date += env.object->getDate();
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
// evaluation of a message variable
IMessage::argslist TMessageEvaluator::evalMessage (const IMessage* msg, const EventContext& env) const
{
	IMessage::argslist outval;

	vector<const IObject*> targets;			// first get the message target objects
	const IObject * root = env.object ? env.object->getRoot() : gGlue->root();
	root->getObjects( evalAddress(msg->address(), env.object), targets);

	size_t n = targets.size();
	if (!n) return outval;					// no target: exit
	
	SIMessageList msgs = IMessageList::create();			// prepare for getting messages from the targets
	for (unsigned int i=0; i< n; i++) {
		SIMessageList l = targets[i]->getMsgs (msg);		// call each target getMsgs method
		if (l && l->list().size())							// when getMsgs returns a valid list of messages
			msgs->list().push_back (l->list());				// push them to the list
	}
	n = msgs->list().size();
	for (unsigned int i=0; i< n; i++) {			
		const IMessage* reply = msgs->list()[i];			// next for each reply
		for (int p = 0; p < reply->size(); p++) {
			outval.push_back(reply->param(p));
		}
	}
	return outval;
}

//----------------------------------------------------------------------
// evaluation of a message variable string
IMessage::argslist TMessageEvaluator::evalMessage (const string& var, const EventContext& env) const
{
	IMessage::argslist outval;
	IObject* o = const_cast<IObject*>(env.object);			// an UGLY const_cast just to be able to retrieve the js and lua engines
	if (!o) {
		ITLErr << "no target object to evaluate" << var << ITLEndl;
		return outval;										// no target object in the environment: return an empty list
	}

	stringstream stream (var);
	ITLparser p(&stream, 0, o->getAppl(), false);			// create a parser with the app as parser environment and without exec flag
	bool ret = p.parse ();						// parses the string
	if (!ret) return outval;							// parsing failed : return an empty list

	SIMessageList outmsgs = p.messages ();						// parses the string
	if (!outmsgs) return outval;							// parsing failed : return an empty list
	
	for (unsigned int i=0; i < outmsgs->list().size(); i++) {
		const IMessage* msg = outmsgs->list()[i];			// and for each parsed message
		outval.push_back( evalMessage (msg, env) );			// evaluate the message and push the result in outval
	}
	return outval;
}

//----------------------------------------------------------------------
string TMessageEvaluator::getVar (const char* ptr) const
{
	string str; bool scaling = false; bool inMsg = false;
	while (*ptr) {
		if ((*ptr == '$') || ((*ptr >= 'a') && (*ptr <= 'z')))
			str += *ptr;
		else if (!scaling && *ptr == '[') {
			scaling = true;
			str += *ptr;
		}
		else if (scaling) {
			str += *ptr;
			if (*ptr == ']') break;
		}
		else if (!inMsg && *ptr == '(') {
			inMsg = true;
			str += *ptr;
		}
		else if (inMsg) {
			str += *ptr;
			if (*ptr == ')') break;
		}
		else break;
		ptr++;
	}
	return str;
}

//----------------------------------------------------------------------
IMessage::argslist TMessageEvaluator::evalVariableString (const string& var, const EventContext& env) const
{
	IMessage::argslist outval;

	size_t n = 0;
	vector<pair<string, string> > res;						// list of strings for regular expressions
	do {
		n = var.find('$', n);
		if (n != string::npos) {							// there is a variable inside the parameter
			string s = getVar(&var.c_str()[n]);				// get the variable
			IMessage::argslist args = evalVariable(s, env);	// evaluate this variable
			stringstream stream;
			string sep;
			for (unsigned int i=0; i < args.size(); i++) {	// and convert the results into a string
				stream << sep;
				args[i]->print(stream);
				sep = " ";
			}
			n++;
			string re ("\\Q");								// build the string for regexp use
			re += s;
			re += "\\E";									// i.e. disable metacharacters from \Q till \E
			res.push_back(make_pair(re, stream.str()));		// and store with the replacement value
		}
		else break;
	} while (true);

	if (res.size()) {										// variables have been expanded
		string newparam(var);								// the string for new value storage
		for (unsigned int i=0; i<res.size(); i++) {			// loop until no more var is expanded
			CRegexpT<char> regexp(res[i].first.c_str(), EXTENDED);						// use the previous as a regexp
			char * replaced = regexp.Replace (newparam.c_str(), res[i].second.c_str());	// and replace with the associated value
			newparam = replaced;
			regexp.ReleaseString (replaced);
		}
		outval.push_back ( new IMsgParam<string>(newparam) );
	}
	else outval.push_back ( new IMsgParam<string>(var) );	// no variable part: put the var as is
	return outval;
}

//----------------------------------------------------------------------
// converts a variable name into an index,
// return 0 when it fails
// differs from standard atoi or strtoul because
//		a $ is expected at first character
//		+ or - are not allowed
static int var2index (const char* var)
{
	if (*var++ != '$') return 0;
	int index = 0;
	while (*var) {
		index *= 10;
		int v = int(*var++) - '0';
		if ((v < 0) || (v > 9))	// not a number
			return 0;
		index += v;
	}
	return index;
}

//----------------------------------------------------------------------
IMessage::argslist TMessageEvaluator::evalVariable (const string& var, const EventContext& env, const IMessage::argslist& args) const
{
	IMessage::argslist outval;
	
	// check first for indexed variables ($1, $2, etc...)
	size_t n = args.size();
	int index = var2index(var.c_str());
	if ((index > 0) && (index <= n)) {
		outval.push_back (args[index-1]);
		return outval;
	}
	return evalVariable (var, env);
}

//----------------------------------------------------------------------
IMessage::argslist TMessageEvaluator::evalVariable (const string& var, const EventContext& env) const
{
	IMessage::argslist outval;
	if (var.empty()) return outval;

	bool relative = false;
	if (var[0] == '$') {
		if (posVariable (var, kXVar))			outval.push_back ( evalPosition (var.substr(fVarLength[kXVar]), env.mouse.fx));
		else if (posVariable (var, kYVar))		outval.push_back ( evalPosition (var.substr(fVarLength[kYVar]), env.mouse.fy));
		else if (posVariable (var, kAbsXVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kAbsXVar]), env.mouse.fabsx));
		else if (posVariable (var, kAbsYVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kAbsYVar]), env.mouse.fabsy));
		else if (posVariable (var, kSceneXVar)) outval.push_back ( evalPosition (var.substr(fVarLength[kSceneXVar]), env.mouse.fsx));
		else if (posVariable (var, kSceneYVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kSceneYVar]), env.mouse.fsy));

		else if (env.gesture.isSet()) {
			if (gestVariable (var, kLikelihoodVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kLikelihoodVar]), env.gesture.likelihood));
			else if (gestVariable (var, kPosVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kPosVar]), env.gesture.position));
			else if (gestVariable (var, kSpeedVar))	outval.push_back ( evalPosition (var.substr(fVarLength[kSpeedVar]), env.gesture.speed));
		}
		
		else if (var == kNameVar)			outval.push_back ( new IMsgParam<string>(env.object->name()));
		else if (var == kAddressVar)		outval.push_back ( new IMsgParam<string>(env.object->getOSCAddress()));
		else if (var == kSceneVar)			outval.push_back ( new IMsgParam<string>(env.object->getScene()->name()));
		else if (var == kVersion)			outval.push_back ( new IMsgParam<float>(INScore::version()));

		else if (dateVariable (var, relative)) {
			if (!env.date.getDenominator()) return outval;		// date can't be resolved
			outval.push_back ( evalDate (var, env, relative));
		}
		
		else if (messageVariable (var)) {
			string msg = var.substr(2, var.size()-3);
			size_t n = msg.find_last_of(';');
			if (n == string::npos) msg += ';';
			outval.push_back ( evalMessage (msg, env) );
		}
		else outval.push_back ( new IMsgParam<string>(var) );	// default for unknown variable: push the variable name
		return outval;
	}
	return evalVariableString (var, env);		// not a direct variable, try to decode variables inside strings (for javascript run method)
}

//----------------------------------------------------------------------
bool TMessageEvaluator::hasDateVar (const IMessage *msg, string& mapname)
{
	bool relative;
	string str = msg->message();
	if (dateVariable(str, relative)) {
		mapname = parseMap(str);
		return true;
	}
	for (int i=0; i < msg->size(); i++) {
		if (msg->param( i, str)) {
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
	// create a new message with an evaluated address
	SIMessage outmsg = IMessage::create( evalAddress (msg->address(), env.object));
	outmsg->setUrl ( msg->url() );

	// evaluate the message string
	IMessage::argslist methodlist = evalVariable(msg->message(), env);
	if (methodlist.size()) {
		string method = methodlist[0]->value<string>("");
		if (method.size()) outmsg->setMessage (method);
		else outmsg->add( methodlist[0] );
		for (unsigned int i=1; i<methodlist.size(); i++)
			outmsg->add( methodlist[i] );
	}

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
SIMessage TMessageEvaluator::eval (const IMessage *msg, const EventContext& env, const IMessage::argslist& args) const
{
	// create a new message with an evaluated address
	SIMessage outmsg = IMessage::create( evalAddress (msg->address(), env.object));
	outmsg->setUrl ( msg->url() );

	// evaluate the message string
	IMessage::argslist methodlist = evalVariable(msg->message(), env, args);
	if (methodlist.size()) {
		string method = methodlist[0]->value<string>("");
		if (method.size()) outmsg->setMessage (method);
		else outmsg->add( methodlist[0] );
		for (unsigned int i=1; i<methodlist.size(); i++)
			outmsg->add( methodlist[i] );
	}

	// evaluate all the parameters
	for (int i=0; i < msg->size(); i++) {
		string str;
		if (msg->param( i, str)) {
			IMessage::argslist values = evalVariable(str, env, args);
			if (!values.size()) return 0;		// variables are expected to give at least one value
			outmsg->add( values );
		}
		else outmsg->add( msg->param(i) );
	}
	return outmsg;
}

//----------------------------------------------------------------------
SIMessageList TMessageEvaluator::eval (const IMessageList* msgs, const EventContext& env, const IMessage::argslist& args) const
{
	SIMessageList outmsgs = IMessageList::create();
	for (unsigned int i = 0; i <  msgs->list().size(); i++) {
		const IMessage *msg = msgs->list()[i];
		SIMessage emsg = eval (msg, env, args);
		if (emsg) outmsgs->list().push_back(emsg);
	}
	return outmsgs;
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

} // end namespoace

