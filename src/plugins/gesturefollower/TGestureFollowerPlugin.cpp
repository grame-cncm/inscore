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
#include "TGestureFollowerPlugin.h"

using namespace std;

namespace inscore
{

static const char* gflibName = "GFLib";
static const char* gflibNewStr = "newGestureFollower";
static const char* gflibDelStr = "delGestureFollower";

static const char* gflibStartLearnStr		= "startLearn";
static const char* gflibStopLearnStr		= "stopLearn";
static const char* gflibClearStr			= "clear";
static const char* gflibClearAllStr			= "clearAll";
static const char* gflibStartFollowStr		= "startFollow";
static const char* gflibStopFollowStr		= "stopFollow";
static const char* gflibSetLikelihoodWindowStr = "setLikelihoodWindow";
static const char* gflibGetMaxPhrasesStr	= "getMaxPhrases";
static const char* gflibGetFrameSizeStr		= "getFrameSize";
static const char* gflibGetCapacityStr		= "getCapacity";
static const char* gflibGetLikelihoodWindowStr = "getLikelihoodWindow";
static const char* gflibSetToleranceStr		= "setTolerance";
static const char* gflibGetToleranceStr		= "getTolerance";
static const char* gflibObservationStr		= "observation";
static const char* gflibLikeliestStr		= "likeliest";
static const char* gflibWhereStr			= "where";
static const char* gflibLikelihoodStr		= "likelihood";
static const char* gflibSpeedStr			= "speed";
static const char* gflibGetStateStr			= "getState";



//----------------------------------------------------------------------------
bool TGestureFollowerPlugin::load ()
{
	string file = IAppl::absolutePath (gflibName);
	if (TPlugin::load(file.c_str())) {
		fNew = resolve<TNewFunction> (gflibNewStr);
		if (fNew == 0) return false;
		fDel = resolve<TVoidVoidFunction> (gflibDelStr);
		if (fDel == 0) return false;

		fStartLearn				= resolve<TVoidIntFunction> (gflibStartLearnStr);
		if (fStartLearn == 0) return false;
		fStopLearn				= resolve<TVoidVoidFunction> (gflibStopLearnStr);
		if (fStopLearn == 0) return false;
		fClear					= resolve<TVoidIntFunction> (gflibClearStr);
		if (fClear == 0) return false;
		fClearAll				= resolve<TVoidVoidFunction> (gflibClearAllStr);
		if (fClearAll == 0) return false;
		fStartFollow			= resolve<TVoidVoidFunction> (gflibStartFollowStr);
		if (fStartFollow == 0) return false;
		fStopFollow				= resolve<TVoidVoidFunction> (gflibStopFollowStr);
		if (fStopFollow == 0) return false;
		fSetLikelihoodWindow	= resolve<TVoidIntFunction> (gflibSetLikelihoodWindowStr);
		if (fSetLikelihoodWindow == 0) return false;
		fGetMaxPhrases			= resolve<TIntVoidFunction> (gflibGetMaxPhrasesStr);
		if (fGetMaxPhrases == 0) return false;
		fGetFrameSize			= resolve<TIntVoidFunction> (gflibGetFrameSizeStr);
		if (fGetFrameSize == 0) return false;
		fGetCapacity			= resolve<TIntVoidFunction> (gflibGetCapacityStr);
		if (fGetCapacity == 0) return false;
		fGetLikelihoodWindow	= resolve<TIntVoidFunction> (gflibGetLikelihoodWindowStr);
		if (fGetLikelihoodWindow == 0) return false;
		fSetTolerance			= resolve<TVoidFloatFunction> (gflibSetToleranceStr);
		if (fSetTolerance == 0) return false;
		fGetTolerance			= resolve<TFloatVoidFunction> (gflibGetToleranceStr);
		if (fGetTolerance == 0) return false;
		fObservation			= resolve<TVoidFloatPIntFunction> (gflibObservationStr);
		if (fObservation == 0) return false;
		fLikeliest				= resolve<TIntVoidFunction> (gflibLikeliestStr);
		if (fLikeliest == 0) return false;
		fWhere					= resolve<TFloatPVoidFunction> (gflibWhereStr);
		if (fWhere == 0) return false;
		fLikelihood				= resolve<TFloatPVoidFunction> (gflibLikelihoodStr);
		if (fLikelihood == 0) return false;
		fSpeed					= resolve<TFloatPVoidFunction> (gflibSpeedStr);
		if (fSpeed == 0) return false;
		fGetState				= resolve<TIntVoidFunction> (gflibGetStateStr);
		if (fGetState == 0) return false;
	}
	else return false;
	return true;
}
		
//----------------------------------------------------------------------------
GestureFollower * TGestureFollowerPlugin::create (int maxPhrases, int vecSize, long capacity) const
		{ return fNew ? fNew( maxPhrases, vecSize, capacity) : 0; }

void TGestureFollowerPlugin::del (GestureFollower * gf) const						{ fDel(gf); }
void TGestureFollowerPlugin::startLearn	(GestureFollower * gf, int phraseIndex)		{ fStartLearn(gf, phraseIndex); }
void TGestureFollowerPlugin::stopLearn	(GestureFollower * gf)						{ fStopLearn (gf); }
void TGestureFollowerPlugin::clear		(GestureFollower * gf, int phraseIndex)		{ fClear (gf, phraseIndex); }
void TGestureFollowerPlugin::clearAll	(GestureFollower * gf)						{ fClearAll (gf); }
void TGestureFollowerPlugin::startFollow(GestureFollower * gf)						{ fStartFollow (gf); }
void TGestureFollowerPlugin::stopFollow	(GestureFollower * gf)						{ fStopFollow (gf); }
void TGestureFollowerPlugin::setLikelihoodWindow (GestureFollower * gf, int size)	{ fSetLikelihoodWindow (gf, size); }
int  TGestureFollowerPlugin::getMaxPhrases (GestureFollower * gf) const				{ return fGetMaxPhrases (gf); }
int  TGestureFollowerPlugin::getFrameSize (GestureFollower * gf) const				{ return fGetFrameSize (gf); }
int  TGestureFollowerPlugin::getCapacity (GestureFollower * gf)	const				{ return fGetCapacity (gf); }

int  TGestureFollowerPlugin::getLikelihoodWindow (GestureFollower * gf) const		{ return fGetLikelihoodWindow (gf); }
void TGestureFollowerPlugin::setTolerance (GestureFollower * gf, float tolerance)	{ fSetTolerance (gf, tolerance); }
float TGestureFollowerPlugin::getTolerance (GestureFollower * gf) const				{ return fGetTolerance(gf); }
void TGestureFollowerPlugin::observation (GestureFollower * gf, float* data, int size) { fObservation (gf, data, size); }
int  TGestureFollowerPlugin::likeliest(GestureFollower * gf) const					{ return fLikeliest (gf); }
const float* TGestureFollowerPlugin::where(GestureFollower * gf) const				{ return fWhere (gf); }
const float* TGestureFollowerPlugin::likelihood(GestureFollower * gf) const			{ return fLikelihood (gf); }
const float* TGestureFollowerPlugin::speed (GestureFollower * gf) const				{ return fSpeed (gf); }
int  TGestureFollowerPlugin::getState(GestureFollower * gf) const					{ return fGetState (gf); }


} // end namespace
