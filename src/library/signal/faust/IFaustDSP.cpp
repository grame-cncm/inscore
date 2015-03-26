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

#include "IFaustDSP.h"
#include "IScene.h"
#include "ITLError.h"
#include "Updater.h"

#include "UI.h"
#include "UIGlue.h"

#include <QApplication>
#include <QFileInfo>
#include <QDir>
#include <QDebug>

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
//--------------------------------------------------------------------------
class INScoreUI : public UI
{
	IFaustDSP* fFaustProcessor;
	
 public:
			 INScoreUI(IFaustDSP* faust) : fFaustProcessor(faust) {}
	virtual ~INScoreUI() {}

    // -- widget's layouts
    virtual void openFrameBox(const char* )			{}
    virtual void openTabBox(const char* )			{}
    virtual void openHorizontalBox(const char* )	{}
    virtual void openVerticalBox(const char* )		{}
    virtual void closeBox() {}

    // -- active widgets
    virtual void addButton(const char* label, float* zone)			{ 
        fFaustProcessor->addMsgHandler(label, zone); 
    }
    virtual void addToggleButton(const char* label, float* zone)	{ 
        fFaustProcessor->addMsgHandler(label, zone); 
    }
    virtual void addCheckButton(const char* label, float* zone)		{ 
        fFaustProcessor->addMsgHandler(label, zone); 
    }
    virtual void addVerticalSlider(const char* label, float* zone, float init, float min, float max, float ){
        *zone=init; fFaustProcessor->addMsgHandler(label, zone, min, max); 
    }
    virtual void addHorizontalSlider(const char* label, float* zone, float init, float min, float max, float ){
        *zone=init; fFaustProcessor->addMsgHandler(label, zone, min, max); 
    }
    virtual void addNumEntry(const char* label, float* zone, float init, float min, float max, float ){
        *zone=init; fFaustProcessor->addMsgHandler(label, zone, min, max); 
    }

    // -- passive widgets
    virtual void addNumDisplay(const char* , float* , int ) {}
    virtual void addTextDisplay(const char* , float* , const char* [], float , float ) {}
    virtual void addHorizontalBargraph(const char* , float* , float , float ) {}
    virtual void addVerticalBargraph(const char* , float* , float , float ) {}
};


//--------------------------------------------------------------------------
const string IFaustDSP::kFaustDSPType("faustdsp");

//--------------------------------------------------------------------------
IFaustDSP::IFaustDSP( const std::string& name, IObject * parent ) : IFaustSignal (name, parent), fFD_Instance(0), fFD_Factory(0)
{
	fTypeString = kFaustDSPType;
    fSetParam = "";
	fGetMsgHandlerMap[kin_GetMethod]	= TGetParamMsgHandler<int>::create(fNumIntputs);
	fGetMsgHandlerMap[kout_GetMethod]	= TGetParamMsgHandler<int>::create(fNumOutputs);
    
    fFDPlugin = TFaustDSPPlugin::getInstance();
}

//--------------------------------------------------------------------------
IFaustDSP::~IFaustDSP(){
    deleteFaustDSP();
    
    TFaustDSPPlugin::releaseInstance();
}

//--------------------------------------------------------------------------
void IFaustDSP::accept (Updater* u)
{
	u->updateTo (SIFaustDSP(this));
}

//--------------------------------------------------------------------------
void IFaustDSP::print (IMessage& out) const
{
	out.setMessage(kset_SetMethod);
	out << kFaustDSPType << fSetParam;
}

//--------------------------------------------------------------------------
void IFaustDSP::call_compute (int nframes, int index, int step)
{
	if(!fFDPlugin || !fFD_Instance)
		return;

	fFDPlugin->fCompute(fFD_Instance, nframes, fInBuffers, fOutBuffers);

	vector<float> values;
	for (int i= 0; i < nframes; i++) {
		for (int j=0; j< fNumOutputs; j++) {
			values.push_back(fOutBuffers[j][i]);
		}
	}
	SParallelSignal s = getProjection(index, step);
	if (!s) return;
	s->put(values);		
}

//--------------------------------------------------------------------------
void IFaustDSP::init ()
{
	INScoreUI ui(this);
      
	fFDPlugin->fInitInstance(fFD_Instance, 44100);
    
//    Translation CPP interface into C interface
    UIGlue myGlueUI;
    buildUIGlue(&myGlueUI, &ui);
	fFDPlugin->fBuildUserInterface(fFD_Instance, &myGlueUI);
    
	fNumIntputs = fFDPlugin->fGetNumInputs(fFD_Instance);
	fNumOutputs = fFDPlugin->fGetNumOutputs(fFD_Instance);
    
	for (int i=0; i < fNumOutputs; i++) {
		stringstream sname;
		sname << name() << i;
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
MsgHandler::msgStatus IFaustDSP::set (const IMessage* msg)
{
    MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	int n = msg->size();
	if (n == 2) {
		if (!msg->param(1, fSetParam)) 
			status = MsgHandler::kBadParameters;
		else{
            deleteFaustDSP();
            if (!createFaustDSP (fSetParam))
			return MsgHandler::kCreateFailure;
        }
		status = MsgHandler::kProcessed;
        
        init();        
        createVirtualNodes();

	}
	else status = MsgHandler::kBadParameters;
	return status; 
}
    
//--------------------------------------------------------------------------
void IFaustDSP::deleteFaustDSP(){
    if(fFD_Instance){
        fFDPlugin->fDeleteInst(fFD_Instance);
        fFD_Instance = NULL;
    }
    if(fFD_Factory){
        fFDPlugin->fDelFactory(fFD_Factory);
        fFD_Factory = NULL;
    }
}
    
//-------- Creation of DSP Factory & DSP Instance
bool IFaustDSP::createFaustDSP (const std::string& dsp_content)
{        
    if(!fFDPlugin->load())
            return false;
    
    char err[512];
    
#ifdef WIN32	
    const char* argv[2];
    argv[0] = "-l";
    
    QString dir(QApplication::applicationDirPath());
    
    dir += "\\PlugIns\\llvm_math.ll";
    string directory = dir.toStdString();
    argv[1] = directory.c_str();
    fFD_Factory = fFDPlugin->fNewSFactory(name().c_str(), dsp_content.c_str(), 2, argv, "", err, 3);
#else
    fFD_Factory = fFDPlugin->fNewSFactory(name().c_str(), dsp_content.c_str(), 0, NULL, "", err, 3);
#endif        
    if(fFD_Factory){
        
        fFD_Instance = fFDPlugin->fCreateInst(fFD_Factory);
        
        if(!fFD_Instance){
            ITLErr << "Impossible to create faust dsp instance" << ITLEndl;
            return false;
        }
    }
    else{
        ITLErr << "Faust Compiler error : " << err << ITLEndl;
        return false;
    }
    
    setVisible(false);
    
    return true;
}
}


