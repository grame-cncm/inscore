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
	fGetMsgHandlerMap[kin_GetMethod]		= TGetParamMsgHandler<int>::create(fNumIntputs);
	fGetMsgHandlerMap[kout_GetMethod]	= TGetParamMsgHandler<int>::create(fNumOutputs);
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
	out.setMessage(kset_SetMethod);
	out << kFaustProcessorType << fLibrary;
}

//--------------------------------------------------------------------------
void IFaustProcessor::call_compute (int nframes, int index, int step)
{
	fCompute(nframes, fInBuffers, fOutBuffers);

	vector<float> values;
	for (int i= 0; i < nframes; i++) {
		for (int j=0; j< fNumOutputs; j++) {
			values.push_back(fOutBuffers[j][i]);
		}
	}
	SParallelSignal s = getProjection(index, step);
	if (!s) return;
	s->put(values);	
//	ParallelSignal::put(values);	
}

//--------------------------------------------------------------------------
bool IFaustProcessor::putAt (const IMessage* msg, int index, int step)
{
	if (!dimension()) return true;		// nothing to do: there is no space for output signals

	int size = msg->params().size();
	if (!fNumIntputs) {
		call_compute(size, index, step);
		return true;
	}

	for (int i=0; i < size; i++) {
		int c = i % fNumIntputs;
		int frame = i / fNumIntputs;
		if (!msg->param(i, fInBuffers[c][frame])) return false;
	}
	call_compute (size/fNumIntputs, index, step);
	return true;
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
const char* IFaustProcessor::translate (const char* name) const
{
	static char buffer[1024];
	char * ptr = buffer; int n=1;
	while (*name && (n++ < 1024)) {
		switch (*name) {
			case ' ': case '	':
				*ptr++ = '_';
				break;
			case '#': case '*': case ',': case '/': case '?':
			case '[': case ']': case '{': case '}':
				*ptr++ = '_';
				break;
			default: 
				*ptr++ = *name;
		}
		name++;
	}
	*ptr = 0;
	return buffer;
}

//--------------------------------------------------------------------------
void IFaustProcessor::addMsgHandler (const char* name, float* zone)
{
	fMsgHandlerMap[translate(name)]	= SetFaustParamMsgHandler::create(zone);
	fGetMsgHandlerMap[translate(name)]	= GetFaustParamMsgHandler::create(zone);
}

void IFaustProcessor::addMsgHandler (const char* name, float* zone, float min, float max)
{
	fMsgHandlerMap[translate(name)]	= SetCheckedFaustParamMsgHandler::create(zone, min, max);
	fGetMsgHandlerMap[translate(name)]	= GetFaustParamMsgHandler::create(zone);
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
	const char* cantload = "can't load faust plugin:";
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
			ITLErr << cantload <<  "unresolved functions." << ITLEndl;
			return MsgHandler::kBadParameters;
		}
		init();
		cout << "INScore: FAUST plugin " << library << " loaded" << endl;
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
