/************************************************************************

	IMPORTANT NOTE : this file contains two clearly delimited sections : 
	the ARCHITECTURE section (in two parts) and the USER section. Each section 
	is governed by its own copyright and license. Please check individually 
	each section for license and copyright information.
*************************************************************************/

/*******************BEGIN ARCHITECTURE SECTION (part 1/2)****************/

/************************************************************************
    FAUST Architecture File
	Copyright (C) 2003-2011 GRAME, Centre National de Creation Musicale
    ---------------------------------------------------------------------
    This Architecture section is free software; you can redistribute it 
    and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 3 of 
	the License, or (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License 
	along with this program; If not, see <http://www.gnu.org/licenses/>.

	EXCEPTION : As a special exception, you may create a larger work 
	that contains this FAUST architecture section and distribute  
	that work under terms of your choice, so long as this FAUST 
	architecture section is not modified. 


 ************************************************************************
 ************************************************************************/

#ifdef WIN32
# ifdef INSCORE_EXPORTS
#  define EXP __declspec(dllexport)
# else
#  define EXP __declspec(dllimport)
# endif

#else

# ifdef INSCORE_EXPORTS
#  define EXP	__attribute__ ((visibility("default")))
# else
#  define EXP
# endif
#endif

#include <iostream>
#include "audio/dsp.h"
#include "gui/UI.h"
#include "misc.h"


/**************************BEGIN USER SECTION **************************/

/******************************************************************************
*******************************************************************************

							       VECTOR INTRINSICS

*******************************************************************************
*******************************************************************************/

<<includeIntrinsic>>

<<includeclass>>

/***************************END USER SECTION ***************************/

/*******************BEGIN ARCHITECTURE SECTION (part 2/2)***************/
					
mydsp	DSP;

#ifdef __cplusplus
extern "C" {
#endif

EXP void buildUserInterface (UI* ui)						{ DSP.buildUserInterface (ui); }
EXP void compute(int len, float** inputs, float** outputs)	{ DSP.compute (len, inputs, outputs); }
EXP int getNumInputs() 										{ return DSP.getNumInputs (); }
EXP int getNumOutputs() 									{ return DSP.getNumOutputs (); }
EXP void init(int samplingRate) 							{ DSP.init (samplingRate); }


#ifdef __cplusplus
}
#endif


/********************END ARCHITECTURE SECTION (part 2/2)****************/

