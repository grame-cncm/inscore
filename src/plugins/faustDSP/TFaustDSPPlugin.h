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

/*
 This class aims to create a Faust DSP on-the-fly, charging faust compiler library. 
*/

#ifndef __TFaustDSPPlugin__
#define __TFaustDSPPlugin__

#include <string>
#include "TPlugin.h"
#include "llvm-c-dsp.h"

struct Meta;

namespace inscore
{

class TFaustDSPPlugin : public TPlugin {

//    Prototypes of libfaust functions to resolve
		typedef llvm_dsp_factory*   (* TNewFFactory) (const char* filename, int argc, const char* argv[], const char* target, char* error_msg, int opt_level);
		typedef llvm_dsp_factory*   (* TNewSFactory) (const char* name_app, const char* dsp_content, int argc, const char* argv[], const char* target, char* error_msg, int opt_level);
		typedef void				(* TDeleteFactory) (llvm_dsp_factory* gf);
		typedef void				(* TMetaFactory) (llvm_dsp_factory* gf, Meta* meta);
		typedef llvm_dsp*			(* TCreateInst) (llvm_dsp_factory* factory);
		typedef void				(* TDeleteInst) (llvm_dsp* dsp);
        typedef int                 (* TGetNum)     (llvm_dsp* dsp);
        typedef void                (* TInitInst)   (llvm_dsp* dsp, int samplingFreq);
        typedef void                (* TBuildUI)    (llvm_dsp* dsp, UIGlue* interface);
        typedef void                (*TComputeInst) (llvm_dsp* dsp, int count, FAUSTFLOAT** input, FAUSTFLOAT** output);
		
		bool				load ();
		static bool			isResolved ();
    
        static TFaustDSPPlugin*    _pluginInstance;
        static int                 _fPluginNumber;

	public:
				 TFaustDSPPlugin();
		virtual ~TFaustDSPPlugin();
    
        bool        isAvailable ();
    
//Returns the instance of the Plugin 
//    --> That way, the symbols are only resolved once
        static TFaustDSPPlugin*     getInstance();
        static void                 releaseInstance();
    
    //    Pointers on libfaust functions
        static TNewFFactory     fNewFFactory;
        static TNewSFactory		fNewSFactory;
        static TDeleteFactory	fDelFactory;
        static TMetaFactory		fMetaDataFactory;
        static TCreateInst      fCreateInst;
        static TDeleteInst		fDeleteInst;
        static TGetNum          fGetNumInputs;
        static TGetNum          fGetNumOutputs;
        static TInitInst        fInitInstance;
        static TBuildUI         fBuildUserInterface;
        static TComputeInst     fCompute;
};


} // end namespace

#endif

