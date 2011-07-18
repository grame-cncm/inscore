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

#include <stdio.h>
#include <sstream>

#include "IFaustProcessor.h"
#include "IScene.h"
#include "ITLError.h"
#include "Updater.h"

#include "UI.h"

using namespace std;

namespace inscore
{

const char* kbuildUserInterface = "buildUserInterface";
const char* kcompute			= "compute";
const char* kgetNumInputs		= "getNumInputs";
const char* kgetNumOutputs		= "getNumOutputs";
const char* kfpinit				= "init";


//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
class INScoreUI : public UI
{
	IFaustProcessor* fFaustProcessor;
	
 public:
			 INScoreUI(IFaustProcessor* faust) : fFaustProcessor(faust) {}
	virtual ~INScoreUI() {}

    // -- widget's layouts
    virtual void openFrameBox(const char* label) {}
    virtual void openTabBox(const char* label) {}
    virtual void openHorizontalBox(const char* label) {}
    virtual void openVerticalBox(const char* label) {}
    virtual void closeBox() {}

    // -- active widgets
    virtual void addButton(const char* label, float* zone)			{ fFaustProcessor->addMsgHandler(label, zone); }
    virtual void addToggleButton(const char* label, float* zone)	{ fFaustProcessor->addMsgHandler(label, zone); }
    virtual void addCheckButton(const char* label, float* zone)		{ fFaustProcessor->addMsgHandler(label, zone); }
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float step)	
																	{ *zone=init; fFaustProcessor->addMsgHandler(label, zone, min, max); }
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float step)
																	{ *zone=init; fFaustProcessor->addMsgHandler(label, zone, min, max); }
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float step)
																	{ *zone=init; fFaustProcessor->addMsgHandler(label, zone, min, max); }

    // -- passive widgets
    virtual void addNumDisplay(const char* label, float* zone, int precision) {}
    virtual void addTextDisplay(const char* label, float* zone, const char* names[], float min, float max) {}
    virtual void addHorizontalBargraph(const char* label, float* zone, float min, float max) {}
    virtual void addVerticalBargraph(const char* label, float* zone, float min, float max) {}
};


//--------------------------------------------------------------------------
const string IFaustProcessor::kFaustProcessorType("faust");

//--------------------------------------------------------------------------
IFaustProcessor::IFaustProcessor( const std::string& name, IObject * parent ) : ISignal (name, parent),
	fBuildUI(0), fCompute(0), fInputs(0), fOutputs(0), fInit(0), fNumIntputs(0), fNumOutputs(0), fInBuffers(0), fOutBuffers(0)
{
	fTypeString = kFaustProcessorType;
	fGetMsgHandlerMap["in"]		= TGetParamMsgHandler<int>::create(fNumIntputs);
	fGetMsgHandlerMap["out"]	= TGetParamMsgHandler<int>::create(fNumOutputs);
}

//--------------------------------------------------------------------------
IFaustProcessor::~IFaustProcessor()
{
	for (int i= 0; i < fNumIntputs; i++)
		delete fInBuffers[i];
	for (int i= 0; i < fNumOutputs; i++)
		delete fOutBuffers[i];
	delete fInBuffers;
	delete fOutBuffers;
}

//--------------------------------------------------------------------------
void IFaustProcessor::accept (Updater* u)
{
	u->updateTo (SIFaustProcessor(this));
}

//--------------------------------------------------------------------------
void IFaustProcessor::print (IMessage& out) const
{
	out.setMessage("set");
	out << kFaustProcessorType << fLibrary;
}

//--------------------------------------------------------------------------
void IFaustProcessor::call_compute (int nframes, int index, int step)
{
	fCompute(nframes, fInBuffers, fOutBuffers);
	vector<float> values;
	int chan = 0, frame = -1;

	for (int i= 0; i < fNumOutputs; i++) {
		int c = chan % fNumOutputs;
		if (!c) frame++;
		values.push_back(fOutBuffers[c][frame]);
		chan++;
	}
	SParallelSignal s = getProjection(index, step);
	if (!s) return;
	s->put(values);	
//	ParallelSignal::put(values);	
}

//--------------------------------------------------------------------------
bool IFaustProcessor::put (const IMessage* msg, int index, int step)
{
	if (!dimension()) return true;		// nothing to do: there is no space for output signals

	int size = msg->params().size();
	if (!fNumIntputs) {
		call_compute(size, index, step);
		return true;
	}

	int chan = 0, frame = 0;
	for (int i=0; i < size; i++) {
		int c = chan % fNumIntputs;
		if (!msg->param(i, fInBuffers[c][frame])) return false;
		if (!c) frame++;
		chan++;
	}
	while (chan % fNumIntputs) {
		fInBuffers[chan % fNumIntputs] = 0;
		chan++;
	}
	call_compute (frame, index, step);
	return true;
}

//--------------------------------------------------------------------------
void IFaustProcessor::addMsgHandler (const char* name, float* zone)
{
	fMsgHandlerMap[name]	= SetFaustParamMsgHandler::create(zone);
	fGetMsgHandlerMap[name]	= GetFaustParamMsgHandler::create(zone);
}

void IFaustProcessor::addMsgHandler (const char* name, float* zone, float min, float max)
{
	fMsgHandlerMap[name]	= SetCheckedFaustParamMsgHandler::create(zone, min, max);
	fGetMsgHandlerMap[name]	= GetFaustParamMsgHandler::create(zone);
}

//--------------------------------------------------------------------------
void IFaustProcessor::init ()
{
	INScoreUI ui(this);
	fInit(44100);
	fBuildUI (&ui);
	fNumIntputs = fInputs();
	fNumOutputs = fOutputs();
	for (int i=0; i < fNumOutputs; i++) {
		stringstream sname;
		sname << fLibrary << i;
		*this << TSignal::create(sname.str(), 1);
	}

	fInBuffers  = new float*[fNumIntputs];
	fOutBuffers = new float*[fNumOutputs];
	for (int i= 0; i < fNumIntputs; i++)
		fInBuffers[i] = new float[kMaxBuffer];
	for (int i= 0; i < fNumOutputs; i++)
		fOutBuffers [i] = new float[kMaxBuffer];
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustProcessor::set (const IMessage* msg)
{
	const char* cantload = "can't load faust plugin: ";
	if (msg->size() != 2) return MsgHandler::kBadParameters;
	string library;
	if (!msg->param(1, library)) return MsgHandler::kBadParameters;
	fLibrary = library;
	if (load(getScene()->absolutePath(fLibrary).c_str())) {
		fBuildUI	= resolve<buildUserInterface>(kbuildUserInterface);	
		fCompute	= resolve<compute>(kcompute);
		fInputs		= resolve<getNumInputs>(kgetNumInputs);
		fOutputs	= resolve<getNumOutputs>(kgetNumOutputs);
		fInit		= resolve<fpinit>(kfpinit);
		if (!fBuildUI || !fCompute || !fInputs || !fOutputs || !fInit) {
			unload();
			ITLErr << cantload <<  " unresolved functions." << ITLEndl;
			return MsgHandler::kBadParameters;
		}
		init();
		return MsgHandler::kProcessed;
	}
	ITLErr << cantload <<  errorString() << ITLEndl;
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
IMessage&  IFaustProcessor::GetFaustParamMsgHandler::print(IMessage& out) const
{
	out << *fValue;
	return out;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustProcessor::SetFaustParamMsgHandler::operator ()(const IMessage* msg)
{
	if ( msg->size() != 1 ) return kBadParameters;
	float val; int ival;
	if ( msg->param(0, ival) ) val = float(ival);
	else if ( !msg->param(0, val) ) return kBadParameters;
	*fValue = check(val);
	return kProcessed;
}

//--------------------------------------------------------------------------
float IFaustProcessor::SetCheckedFaustParamMsgHandler::check(float val)
{
	if (val < fMin) return fMin;
	if (val > fMax) return fMax;
	return val;
}

}
