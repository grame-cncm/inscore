/*

  INScore Project

  Copyright (C) 2009,2020  Grame

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

#include <stdio.h>
#include <sstream>

#include "IFaustProcessor.h"
#include "IScene.h"
#include "ITLError.h"
#include "OSCAddress.h"
#include "OSCRegexp.h"
#include "Updater.h"

using namespace std;

namespace inscore
{


//--------------------------------------------------------------------------
const string IFaustProcessor::kFaustProcessorType("faust");

//--------------------------------------------------------------------------
IFaustProcessor::IFaustProcessor( const std::string& name, IObject * parent ) :
	IRectShape (name, parent)
{
	fTypeString = kFaustProcessorType;

	fMsgHandlerMap[kplay_GetSetMethod]		= TSetMethodMsgHandler<IFaustProcessor,bool>::create(this, &IFaustProcessor::setPlay);
	fMsgHandlerMap[kkeyon_SetMethod]		= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::keyon);
	fMsgHandlerMap[kkeyoff_SetMethod]		= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::keyoff);
	fMsgHandlerMap[kallnotesoff_SetMethod]	= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::allNotesOff);

	fGetMsgHandlerMap[""]					= TGetParamMsgHandler<string>::create(fDspCode);
	fGetMsgHandlerMap[kin_GetMethod]		= TGetParamMsgHandler<int>::create(fNumInputs);
	fGetMsgHandlerMap[kout_GetMethod]		= TGetParamMsgHandler<int>::create(fNumOutputs);
	fGetMsgHandlerMap[kplay_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fPlaying);
	fGetMultiMsgHandlerMap[kpaths_GetMethod]= TGetParamMultiMethodHandler<IFaustProcessor, SIMessageList (IFaustProcessor::*)() const>::create(this, &IFaustProcessor::getPaths);
	setPending ();
}

//--------------------------------------------------------------------------
SIMessageList IFaustProcessor::getPaths() const
{
	SIMessageList list = IMessageList::create();
	for (auto elt: fPaths) {
		SIMessage msg = IMessage::create (elt.fAddress, elt.fType);
		msg->add (elt.fLabel);
		if (elt.fType != "button") {
			msg->add (elt.fValue);
			msg->add (elt.fMin);
			msg->add (elt.fMax);
			msg->add (elt.fStep);
		}
		list->list().push_back (msg);
	}
	return list;
}

//--------------------------------------------------------------------------
void IFaustProcessor::addMsgHandler (const std::string& address, const std::string& name, float min, float max)
{
	fMsgHandlerMap[name] 	= SetFaustParamMsgHandler::create(this, &IFaustProcessor::setParamValue, address, min, max);
	fGetMsgHandlerMap[name]	= GetFaustParamMethodHandler::create(this, &IFaustProcessor::getParamValue, address);
}

//--------------------------------------------------------------------------
void IFaustProcessor::addMsgHandler (const std::string& address, const std::string& name)
{
	fMsgHandlerMap[name] 	= SetFaustParamMsgHandler::create(this, &IFaustProcessor::setButtonValue, address, 0, 1);
	fGetMsgHandlerMap[name]	= GetFaustParamMethodHandler::create(this, &IFaustProcessor::getParamValue, address);
}

//--------------------------------------------------------------------------
float IFaustProcessor::getParamValue (const std::string& address) const 
{
	TParamsValues::const_iterator i = fParamValues.find (address);
	if (i != fParamValues.end()) return i->second;
	ITLErr << getOSCAddress() << " " << address << ": no such parameter." << ITLEndl;
	return 0;
}

//--------------------------------------------------------------------------
void IFaustProcessor::setButtonValue(const std::string& address, float val)
{
	fNewValues.push_back (TFaustParamUpdate(address, val, TFaustParamUpdate::kButton));
	fParamValues[address] = val;
}

//--------------------------------------------------------------------------
void IFaustProcessor::setParamValue (const std::string& address, float val)
{
	fNewValues.push_back (TFaustParamUpdate(address, val));
	fParamValues[address] = val;
}

//--------------------------------------------------------------------------
void IFaustProcessor::setFaustUI (std::string type, std::string label, std::string address, float init, float min, float max, float step)
{
	FaustProcessorUIElement elt(type, label, init, min, max, step);
	fAddressSpace[address] = elt;
	fPaths.push_back ( oldFaustProcessorUIElement(type, label, address, init, min, max, step));
	string msg = address2msg(address.c_str());
	fParamValues[address] = init;
	if (type == "button")
		addMsgHandler (address, msg);
	else
		addMsgHandler (address, msg, min, max);
}

//--------------------------------------------------------------------------
IFaustProcessor::~IFaustProcessor(){}

//--------------------------------------------------------------------------
void IFaustProcessor::accept (Updater* u)
{
	u->updateTo (SIFaustProcessor(this));
}

//--------------------------------------------------------------------------
void IFaustProcessor::print (IMessage& out) const
{
	out.setMessage(kset_SetMethod);
	out << kFaustProcessorType << fDspCode;
}

//--------------------------------------------------------------------------
/*
There are potential conflicts between the Faust UI objects naming scheme and
the OSC address space. An OSC symbolic names is an ASCII string consisting of
printable characters other than the following:
	space
#	number sign
*	asterisk
,	comma
/	forward
?	question mark
[	open bracket
]	close bracket
{	open curly brace
}	close curly brace

a simple solution to address the problem consists in replacing
space or tabulation with '_' (underscore)
all the other osc excluded characters with '-' (hyphen)
*/
//--------------------------------------------------------------------------
std::string IFaustProcessor::address2msg (const char* address) const
{
	string out;
	const char* subst = "";
	while (*address) {
		char c = *address++;
		switch (c) {
			case ' ': case '	':
				out += '_';
				break;
			case '#': case '*': case ',': case '?':
			case '[': case ']': case '{': case '}':
				out += '_';
				break;
			case '/':
				out += subst;
				subst = "_";
				break;
			default:
				out += c;
		}
	}
	return out;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustProcessor::allNotesOff(const IMessage*)
{
	fKeyValues.push_back (TFaustKeysUpdate( TFaustKeysUpdate::kAllNotesOff, 0, 0, 0));
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustProcessor::keyon (const IMessage* msg)
{
	int chan, pitch, vel;
	if ((msg->size() != 3) || !msg->param(0, chan) || !msg->param(1,pitch) || !msg->param(2,vel)) return MsgHandler::kBadParameters;
	if (!fVoices) {
		ITLErr << "Unsupported " << kkeyon_SetMethod << " message addressed to monophonic dsp at " << getOSCAddress() << ITLEndl;
		return MsgHandler::kBadParameters;
	}
	fKeyValues.push_back (TFaustKeysUpdate( TFaustKeysUpdate::kKeyOn, chan, pitch, vel));
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustProcessor::keyoff (const IMessage* msg)
{
	int chan, pitch, vel;
	if ((msg->size() != 3) || !msg->param(0, chan) || !msg->param(1,pitch) || !msg->param(2,vel)) return MsgHandler::kBadParameters;
	if (!fVoices) {
		ITLErr << "Unsupported " << kkeyoff_SetMethod << " message addressed to monophonic dsp at " << getOSCAddress() << ITLEndl;
		return MsgHandler::kBadParameters;
	}
	fKeyValues.push_back (TFaustKeysUpdate( TFaustKeysUpdate::kKeyOff, chan, pitch, vel));
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustProcessor::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	int n = msg->size();
	string code; int voices;
	status = MsgHandler::kBadParameters;
	switch (n) {
		case 2:
			if (msg->param(1, code)) fDspCode = code;
			else return MsgHandler::kBadParameters;
			break;
		case 3:
			if (msg->param(1, voices) && msg->param(2, code)) {
				fVoices = voices;
				fDspCode = code;
				status = MsgHandler::kProcessed;
			}
			else return MsgHandler::kBadParameters;
			break;
		default:
			return MsgHandler::kBadParameters;
	}
	newData(true);
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
// messages processing
//--------------------------------------------------------------------------
int IFaustProcessor::processMsg (const string& address, const string& addressTail, const IMessage* msg)
{
	if (IObject::accept(address, msg)) {				// first make sure that the object is part of the address
		string faustaddress = oscaddress2faustaddress(addressTail);
		if (!faustaddress.empty()) {
			FaustProcessorUIElement& ui = fAddressSpace[faustaddress];
			float val;
			if ((msg->size() == 1) && msg->cast_param(0, val)) {
				if (val < ui.fMin) val = ui.fMin;
				if (val > ui.fMax) val = ui.fMax;
				ui.fValue = val;
				setParamValue (faustaddress, val);
				setModified();
				return MsgHandler::kProcessed;
			}
			if (msg->message() == kget_SetMethod) {
				return IRectShape::get (msg);
			}
			return MsgHandler::kBadParameters;
		}
	}
	return IRectShape::processMsg (address, addressTail, msg);
}

static int getDepth (const char* addr) {
	int count = 0;
	while (*addr) {
		if (*addr++ == '/') count++;
	}
	return count;
}
static string stripDepth (const string& address, int depth) {
	size_t n=0;
	const char* ptr = address.c_str();
	while ((depth >=0) && *ptr) {
		n++;
		if (*ptr++ == '/') depth--;
	}
	return (n>0) ? &address[n-1] : "/";
}

//--------------------------------------------------------------------------
string IFaustProcessor::oscaddress2faustaddress (const string& oscaddress) const
{
	OSCRegexp re (oscaddress.c_str());
	for (auto elt: fAddressSpace) {
		if (re.match(elt.first.c_str())) {
			return elt.first;
		}
	}
	return "";
}

//--------------------------------------------------------------------------
SIMessage IFaustProcessor::getParamMsg (const std::string& target, float value ) const
{
	SIMessage msg = IMessage::create(target);
	msg->add (value);
	return msg;
}

//--------------------------------------------------------------------------
SIMessageList IFaustProcessor::getAll() const
{
	string address = getOSCAddress();
	SIMessageList out = IRectShape::getAll ();
	for (auto elt: fAddressSpace)
		out->list().push_back (getParamMsg(address + elt.first, elt.second.fValue));
	return out;
}

//--------------------------------------------------------------------------
SIMessageList IFaustProcessor::getMsgs (const IMessage* msg) const
{
	string address = getOSCAddress();
  	string tail = stripDepth(msg->address(), getDepth (address.c_str()));
	string faustaddress = oscaddress2faustaddress(tail);
	if (!faustaddress.empty()) {
		string what;
		auto p = fAddressSpace.find (faustaddress);
		SIMessageList outMsgs = IMessageList::create();
		int n = msg->size();
		string target = address + faustaddress;
		if (n == 0) {
			outMsgs->list().push_back (getParamMsg(target, p->second.fValue));
		}
		else if ((msg->size() == 1) && msg->param(0, what) && (what == "*")) {
			outMsgs->list().push_back (getParamMsg(target, "min", p->second.fMin));
			outMsgs->list().push_back (getParamMsg(target, "max", p->second.fMax));
			outMsgs->list().push_back (getParamMsg(target, "step", p->second.fStep));
			outMsgs->list().push_back (getParamMsg(target, "type", p->second.fType));
			outMsgs->list().push_back (getParamMsg(target, "label", p->second.fLabel));
		}
		else for (int i=0; i<n; i++) {
			if (msg->param(i, what)) {
				if (what == "min") 			outMsgs->list().push_back (getParamMsg(target, "min", p->second.fMin));
				else if (what == "max") 	outMsgs->list().push_back (getParamMsg(target, "max", p->second.fMax));
				else if (what == "step") 	outMsgs->list().push_back (getParamMsg(target, "step", p->second.fStep));
				else if (what == "type") 	outMsgs->list().push_back (getParamMsg(target, "type", p->second.fType));
				else if (what == "label") 	outMsgs->list().push_back (getParamMsg(target, "label", p->second.fLabel));
				else ITLErr << address << "incorrect parameter attribute:" << what << ITLEndl;
			}
			else ITLErr << address << "incorrect parameter attribute:" << what << ITLEndl;
		}
		return outMsgs;
	}
	return IRectShape::getMsgs (msg);
}

}
