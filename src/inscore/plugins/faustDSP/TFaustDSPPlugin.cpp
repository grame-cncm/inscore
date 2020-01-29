/*
  Copyright (c) Grame 2009

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#include <iostream>
#include "IAppl.h"
#include "OSCStream.h"
#include "ITLError.h"
#include "TFaustDSPPlugin.h"

using namespace std;

namespace inscore
{
//Name of faust compiler library to load
static const char* fdlibName = "faust";
    
//Name of the faust compiler functions to resolve
static const char* fdlibCreateFactoryF		= "createCDSPFactoryFromFile";
static const char* fdlibCreateFactoryS		= "createCDSPFactoryFromString";
static const char* fdlibDeleteFactory		= "deleteCDSPFactory";
static const char* fdlibMetadata			= "metadataCDSPFactory";
static const char* fdlibCreateInstance		= "createCDSPInstance";
static const char* fdlibDeleteInstance		= "deleteCDSPInstance";
static const char* fdlibInitInstance		= "initCDSPInstance";
static const char* fdlibBuildInterface      = "buildUserInterfaceCDSPInstance";
static const char* fdlibGetNumInputs        = "getNumInputsCDSPInstance";
static const char* fdlibGetNumOutputs		= "getNumOutputsCDSPInstance";
static const char* fdlibComputeInstance		= "computeCDSPInstance";
    
//Initializing function pointers
TFaustDSPPlugin::TNewFFactory   TFaustDSPPlugin::fNewFFactory = 0;
TFaustDSPPlugin::TNewSFactory	TFaustDSPPlugin::fNewSFactory = 0;
TFaustDSPPlugin::TDeleteFactory	TFaustDSPPlugin::fDelFactory = 0;
TFaustDSPPlugin::TMetaFactory	TFaustDSPPlugin::fMetaDataFactory = 0;
TFaustDSPPlugin::TCreateInst    TFaustDSPPlugin::fCreateInst = 0;
TFaustDSPPlugin::TDeleteInst	TFaustDSPPlugin::fDeleteInst = 0;
TFaustDSPPlugin::TGetNum        TFaustDSPPlugin::fGetNumInputs = 0;
TFaustDSPPlugin::TGetNum        TFaustDSPPlugin::fGetNumOutputs = 0;
TFaustDSPPlugin::TInitInst      TFaustDSPPlugin::fInitInstance = 0;
TFaustDSPPlugin::TBuildUI       TFaustDSPPlugin::fBuildUserInterface = 0;
TFaustDSPPlugin::TComputeInst   TFaustDSPPlugin::fCompute = 0;
    
TFaustDSPPlugin* TFaustDSPPlugin::_pluginInstance = 0;
int TFaustDSPPlugin::_fPluginNumber = 0;
    
//----------------------------------------------------------------------------
bool TFaustDSPPlugin::isResolved (){
    return	fNewFFactory && fNewSFactory && fDelFactory && fMetaDataFactory && fCreateInst && fDeleteInst;
}
    
bool TFaustDSPPlugin::isAvailable (){ 
    return isLoaded() && isResolved(); 
}

//----------------------------------------------------------------------------
bool TFaustDSPPlugin::error(){
    ITLErr << errorString() << ITLEndl;
    return false; 
}
    
bool TFaustDSPPlugin::load ()
{
	if (isLoaded()){ return isResolved();}

	if (QPlugin::load(fdlibName)) {
        
		fNewSFactory = resolve<TNewSFactory> (fdlibCreateFactoryS);
		if (fNewSFactory == 0)
            return error();
        
		fNewFFactory = resolve<TNewFFactory> (fdlibCreateFactoryF);
		if (fNewFFactory == 0)
            return error();

		fDelFactory = resolve<TDeleteFactory> (fdlibDeleteFactory);
		if (fDelFactory == 0)
            return error();
        
		fMetaDataFactory = resolve<TMetaFactory> (fdlibMetadata);
		if (fMetaDataFactory == 0)
            return error();
        
		fCreateInst = resolve<TCreateInst> (fdlibCreateInstance);
		if (fCreateInst == 0)
            return error();
        
		fDeleteInst = resolve<TDeleteInst> (fdlibDeleteInstance);
		if (fDeleteInst == 0)
            return false;
        
        fGetNumInputs = resolve<TGetNum> (fdlibGetNumInputs);
		if (fGetNumInputs == 0)
            return error();
        
        fGetNumOutputs = resolve<TGetNum> (fdlibGetNumOutputs);
		if (fGetNumOutputs == 0)
            return error();
        
        fInitInstance = resolve<TInitInst> (fdlibInitInstance);
		if (fInitInstance == 0)
            return error();
        
        fBuildUserInterface = resolve<TBuildUI> (fdlibBuildInterface);
		if (fBuildUserInterface == 0)
            return error();
        
        fCompute = resolve<TComputeInst> (fdlibComputeInstance);
		if (fCompute == 0)
            return error();
	}
	else return error();
//    oscerr << OSCStart("Faust")<<"Compiler loaded"<< OSCEnd();

	return true;
}

//----------------------------------------------------------------------------
//Creating a Faust DSP Plugin = loading faust compiler library
    TFaustDSPPlugin::TFaustDSPPlugin()
{
    TFaustDSPPlugin::_fPluginNumber = 0;
}

//----------------------------------------------------------------------------
TFaustDSPPlugin::~TFaustDSPPlugin(){
//        oscout << OSCStart("Faust")<<"Compiler unloaded"<< OSCEnd();
//    cout << "Faust Compiler unloaded" << endl;
}
    
TFaustDSPPlugin* TFaustDSPPlugin::getInstance(){
    if(TFaustDSPPlugin::_pluginInstance == 0)
        TFaustDSPPlugin::_pluginInstance = new TFaustDSPPlugin();
        
    TFaustDSPPlugin::_fPluginNumber++;
        
    return TFaustDSPPlugin::_pluginInstance;
}

void TFaustDSPPlugin::releaseInstance(){
       
    TFaustDSPPlugin::_fPluginNumber--;
    if(TFaustDSPPlugin::_fPluginNumber == 0){
        delete TFaustDSPPlugin::_pluginInstance;
        TFaustDSPPlugin::_pluginInstance = NULL;
    }
}
    
} // end namespace
