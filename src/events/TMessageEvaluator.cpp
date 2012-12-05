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
	if (methodlist.size()) {
		string method = methodlist[0]->value<string>("");
		if (method.size()) outmsg->setMessage (method);
	}
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

} // end namespoace

