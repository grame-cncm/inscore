/*

  INScore Project

  Copyright (C) 2009,2021  Grame

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
#include "IMessageHandlers.h"
#include "IScene.h"
#include "ITLError.h"
#include "OSCAddress.h"
#include "OSCRegexp.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string kButtonAutoOffMethod = "autoOff";

//--------------------------------------------------------------------------
const string IFaustProcessor::kFaustProcessorType("faust");

//--------------------------------------------------------------------------
IFaustProcessor::IFaustProcessor( const std::string& name, IObject * parent ) :
	IRectShape (name, parent)
{
	fTypeString = kFaustProcessorType;

	fMsgHandlerMap[kkeyon_SetMethod]		= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::keyon);
	fMsgHandlerMap[kkeyoff_SetMethod]		= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::keyoff);
	fMsgHandlerMap[kallnotesoff_SetMethod]	= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::allNotesOff);
	fMsgHandlerMap[kconnect_GetSetMethod]	= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::connect);
	fMsgHandlerMap[kdisconnect_SetMethod]	= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::disconnect);
	fMsgHandlerMap[kcompute_GetSetMethod]	= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::compute);
	fMsgHandlerMap[kButtonAutoOffMethod]	= TMethodMsgHandler<IFaustProcessor>::create(this, &IFaustProcessor::buttonAuto);

	fGetMsgHandlerMap[kcompute_GetSetMethod]= TGetParamMsgHandler<bool>::create(fCompute);
	fGetMsgHandlerMap[kButtonAutoOffMethod] = TGetParamMsgHandler<bool>::create(fButtonAutoOff);
	fGetMsgHandlerMap[kin_GetMethod]		= TGetParamMsgHandler<int>::create(fNumInputs);
	fGetMsgHandlerMap[kout_GetMethod]		= TGetParamMsgHandler<int>::create(fNumOutputs);
	fGetMsgHandlerMap[kconnect_GetSetMethod]= TGetParamMethodHandler<AudioNode, vector<string> (AudioNode::*)() const>::create(this, &IFaustProcessor::getconnect);
	fGetMsgHandlerMap[kwasm_GetMethod]		= TGetParamMethodHandler<IFaustProcessor, string (IFaustProcessor::*)()>::create(this, &IFaustProcessor::getWasm);
	fGetMultiMsgHandlerMap[kui_GetMethod]	= TGetParamMultiMethodHandler<IFaustProcessor, SIMessageList (IFaustProcessor::*)() const>::create(this, &IFaustProcessor::getUI);
	setPending ();
}

//--------------------------------------------------------------------------
void IFaustProcessor::cleanup ()
{
	IObject::cleanup();
	AudioNode::cleanup(getOutputs());
	fWasmExport = false;
}

//--------------------------------------------------------------------------
void IFaustProcessor::setParamValue (const std::string& address, float val, int type)
{
	fNewValues.push_back (TFaustParamUpdate(address, val, type));
}

//--------------------------------------------------------------------------
void IFaustProcessor::setFaustUI (std::string type, std::string label, std::string address, float init, float min, float max, float step)
{
	FaustProcessorUIElement elt(type, label, init, min, max, step);
	fAddressSpace[address] = elt;
}

//--------------------------------------------------------------------------
string IFaustProcessor::getWasm ()
{
	string msg = "will be exported to " + name() + ".wasm and " + name() + ".json";
	fWasmExport = true;
	setModified();
	return msg;
}

//--------------------------------------------------------------------------
SIMessageList IFaustProcessor::getUI () const
{
	SIMessageList list = IMessageList::create();
	for (auto elt: fAddressSpace) {
		const FaustProcessorUIElement& ui = elt.second;
		SIMessage msg = IMessage::create (getOSCAddress() + elt.first);
		*msg << ui.fType << ui.fLabel << ui.fMin << ui.fMax << ui.fStep;
		list->list().push_back (msg);
	}
	return list;
}

//--------------------------------------------------------------------------
IFaustProcessor::~IFaustProcessor(){}

//--------------------------------------------------------------------------
void IFaustProcessor::accept (Updater* u)
{
	u->updateTo (SIFaustProcessor(this));
}

//--------------------------------------------------------------------------
SIMessageList IFaustProcessor::getSetMsg() const
{
	SIMessageList outMsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	print (*msg);
	outMsgs->list().push_back(msg);
	return outMsgs;
}

//--------------------------------------------------------------------------
void IFaustProcessor::print (IMessage& out) const
{
	out << kFaustProcessorType;
	if (fVoices) out << fVoices;
	out << fDspCode;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustProcessor::compute(const IMessage* msg)
{
	int state = 0;
	if ((msg->size() == 1) && msg->param(0,state)) {
		fCompute = (state != 0);
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustProcessor::buttonAuto(const IMessage* msg)
{
	int state = 0;
	if ((msg->size() == 1) && msg->param(0,state)) {
		fButtonAutoOff = (state != 0);
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
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
		if (getPending()) {
			msg->send(true);
			return MsgHandler::kProcessedNoChange;
		}

		vector<string> faustaddresses = oscaddress2faustaddress(addressTail);
		if (faustaddresses.empty()) return IRectShape::processMsg (address, addressTail, msg);
	
		for (string faustaddress: faustaddresses) {
			FaustProcessorUIElement& ui = fAddressSpace[faustaddress];
			float val;
			if ((msg->size() == 1) && msg->cast_param(0, val)) {
				if (val < ui.fMin) val = ui.fMin;
				if (val > ui.fMax) val = ui.fMax;
				ui.fValue = val;
				setParamValue (faustaddress, val, (ui.fType=="button" ? TFaustParamUpdate::kButton : TFaustParamUpdate::kOther));
				setModified();
			}
			else if (msg->message() == kget_SetMethod) {
				int ret = IRectShape::get (msg);
				if ((ret != MsgHandler::kProcessed) || (ret != MsgHandler::kProcessedNoChange)) return ret;
			}
			else return MsgHandler::kBadParameters;
		}
	}
	return MsgHandler::kProcessed;
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
	if ((n>0) && address[n])
		return &address[n-1];
	return "";
}

//--------------------------------------------------------------------------
vector<string> IFaustProcessor::oscaddress2faustaddress (const string& oscaddress) const
{
	vector<string> out;
	OSCRegexp re (oscaddress.c_str());
	for (auto elt: fAddressSpace) {
		if (re.match(elt.first.c_str())) {
			out.push_back(elt.first);
		}
	}
	return out;
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
	vector<string> faustparams = oscaddress2faustaddress(tail);

	if (faustparams.empty()) return IRectShape::getMsgs (msg);
	
	SIMessageList outMsgs = IMessageList::create();
	for (auto faustaddress: faustparams) {
		string what;
		auto p = fAddressSpace.find (faustaddress);
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
				else ITLErr << address << " incorrect parameter attribute: " << what << ITLEndl;
			}
			else ITLErr << address << " incorrect parameter attribute: " << what << ITLEndl;
		}
	}
	return outMsgs;
}

}
