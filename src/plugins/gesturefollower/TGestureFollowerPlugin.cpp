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
#include "GestureFollower.h"
#include "TGestureFollowerPlugin.h"

using namespace std;

namespace inscore
{

static const char* gflibName = "GFLib";
static const char* gflibNewStr = "newGestureFollower";
static const char* gflibDelStr = "delGestureFollower";

static const char* gflibVersionStr			= "gfVersionStr";
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
static const char* gflibGetPhraseSizeStr	= "getPhraseSize";
static const char* gflibGetPhraseDataStr	= "getPhraseData";
static const char* gflibGetStateStr			= "getState";

TGestureFollowerPlugin::TNewFunction		TGestureFollowerPlugin::fNew = 0;
TGestureFollowerPlugin::TVoidVoidFunction	TGestureFollowerPlugin::fDel = 0;
TGestureFollowerPlugin::TVoidIntFunction	TGestureFollowerPlugin::fStartLearn = 0;
TGestureFollowerPlugin::TVoidVoidFunction	TGestureFollowerPlugin::fStopLearn = 0;
TGestureFollowerPlugin::TVoidIntFunction	TGestureFollowerPlugin::fClear = 0;
TGestureFollowerPlugin::TVoidVoidFunction	TGestureFollowerPlugin::fClearAll = 0;
TGestureFollowerPlugin::TVoidVoidFunction	TGestureFollowerPlugin::fStartFollow = 0;
TGestureFollowerPlugin::TVoidVoidFunction	TGestureFollowerPlugin::fStopFollow = 0;
TGestureFollowerPlugin::TVoidIntFunction	TGestureFollowerPlugin::fSetLikelihoodWindow = 0;
TGestureFollowerPlugin::TIntVoidFunction	TGestureFollowerPlugin::fGetMaxPhrases = 0;
TGestureFollowerPlugin::TIntVoidFunction	TGestureFollowerPlugin::fGetFrameSize = 0;
TGestureFollowerPlugin::TIntVoidFunction	TGestureFollowerPlugin::fGetCapacity = 0;
TGestureFollowerPlugin::TIntVoidFunction	TGestureFollowerPlugin::fGetLikelihoodWindow = 0;
TGestureFollowerPlugin::TVoidFloatFunction	TGestureFollowerPlugin::fSetTolerance = 0;
TGestureFollowerPlugin::TFloatVoidFunction	TGestureFollowerPlugin::fGetTolerance = 0;
TGestureFollowerPlugin::TVoidFloatPIntFunction TGestureFollowerPlugin::fObservation = 0;
TGestureFollowerPlugin::TIntVoidFunction	TGestureFollowerPlugin::fLikeliest = 0;
TGestureFollowerPlugin::TFloatPVoidFunction	TGestureFollowerPlugin::fWhere = 0;
TGestureFollowerPlugin::TFloatPVoidFunction	TGestureFollowerPlugin::fLikelihood = 0;
TGestureFollowerPlugin::TFloatPVoidFunction	TGestureFollowerPlugin::fSpeed = 0;
TGestureFollowerPlugin::TIntIntFunction		TGestureFollowerPlugin::fGetPhraseSize = 0;
TGestureFollowerPlugin::TFloatPIntFunction	TGestureFollowerPlugin::fGetPhraseData = 0;
TGestureFollowerPlugin::TIntVoidFunction	TGestureFollowerPlugin::fGetState = 0;
TGestureFollowerPlugin::TCharPVoidFunction	TGestureFollowerPlugin::fVersionStr = 0;


//----------------------------------------------------------------------------
bool TGestureFollowerPlugin::isResolved ()
{
	return	fNew && fDel && fStartLearn && fStopLearn && fClear && fClearAll &&
			fStartFollow && fStopFollow && fSetLikelihoodWindow && fGetMaxPhrases && fGetFrameSize &&
			fGetCapacity && fGetLikelihoodWindow && fSetTolerance && fGetTolerance && fObservation &&
			fLikeliest && fWhere && fLikelihood && fSpeed && fGetPhraseSize && fGetState && fVersionStr;
}

//----------------------------------------------------------------------------
bool TGestureFollowerPlugin::load ()
{
	if (isLoaded()) return isResolved();

	if (TPlugin::load(gflibName)) {
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
		fGetPhraseSize				= resolve<TIntIntFunction> (gflibGetPhraseSizeStr);
		if (fGetPhraseSize == 0) return false;
		fGetPhraseData				= resolve<TFloatPIntFunction> (gflibGetPhraseDataStr);
		if (fGetPhraseData == 0) return false;
		fGetState				= resolve<TIntVoidFunction> (gflibGetStateStr);
		if (fGetState == 0) return false;
		fVersionStr				= resolve<TCharPVoidFunction> (gflibVersionStr);
		if (fVersionStr == 0) return false;
	}
	else return false;
	oscout << OSCStart("IMTR Gesture follower version") << fVersionStr() << "loaded" << OSCEnd();;
	return true;
}

//----------------------------------------------------------------------------
TGestureFollowerPlugin::TGestureFollowerPlugin(int maxPhrases, int vecSize, long capacity) : fGF(0)
{
	if (load())
		fGF = create (maxPhrases, vecSize, capacity);
	else
		ITLErr << "cannot load gesture follower plugin" << ITLEndl;
}

//----------------------------------------------------------------------------
TGestureFollowerPlugin::~TGestureFollowerPlugin()		{ if (fDel && fGF) fDel(fGF); }

bool TGestureFollowerPlugin::isAvailable ()		{ return isLoaded() && isResolved() && fGF; }
		
//----------------------------------------------------------------------------
GestureFollower * TGestureFollowerPlugin::create (int maxPhrases, int vecSize, long capacity) const
		{ return fNew ? fNew( maxPhrases, vecSize, capacity, 0) : 0; }

//----------------------------------------------------------------------------
void TGestureFollowerPlugin::stop ()
{
	switch (getState()) {
		case kDecoding:
			stopFollow();
			break;
		case kLearning:
			stopLearn();
			break;
	}
}

const char*	TGestureFollowerPlugin::versionStr ()	{ return fVersionStr(); }

bool TGestureFollowerPlugin::following	()		{ return getState() == kDecoding; }
bool TGestureFollowerPlugin::learning	()		{ return getState() == kLearning; }
bool TGestureFollowerPlugin::idle		()		{ return getState() == kIdle; }

void TGestureFollowerPlugin::del () const						{ fDel(fGF); }
void TGestureFollowerPlugin::startLearn	(int phraseIndex)		{ fStartLearn(fGF, phraseIndex); }
void TGestureFollowerPlugin::stopLearn	()						{ fStopLearn (fGF); }
void TGestureFollowerPlugin::clear		(int phraseIndex)		{ stop(); fClear (fGF, phraseIndex); }
void TGestureFollowerPlugin::clearAll	()						{ stop(); fClearAll (fGF); }
void TGestureFollowerPlugin::startFollow()						{ stop(); fStartFollow (fGF); }
void TGestureFollowerPlugin::stopFollow	()						{ fStopFollow (fGF); }
void TGestureFollowerPlugin::setLikelihoodWindow (int size)		{ fSetLikelihoodWindow (fGF, size); }
int  TGestureFollowerPlugin::getMaxPhrases () const				{ return fGetMaxPhrases (fGF); }
int  TGestureFollowerPlugin::getFrameSize () const				{ return fGetFrameSize (fGF); }
int  TGestureFollowerPlugin::getCapacity ()	const				{ return fGetCapacity (fGF); }

int  TGestureFollowerPlugin::getLikelihoodWindow () const		{ return fGetLikelihoodWindow (fGF); }
void TGestureFollowerPlugin::setTolerance (float tolerance)		{ fSetTolerance (fGF, tolerance); }
float TGestureFollowerPlugin::getTolerance () const				{ return fGetTolerance(fGF); }

void TGestureFollowerPlugin::observation (float* data, int size) {
	if (getState() != kIdle) fObservation (fGF, data, size);
}

int  TGestureFollowerPlugin::likeliest() const					{ return fLikeliest (fGF); }
const float* TGestureFollowerPlugin::where() const				{ return fWhere (fGF); }
const float* TGestureFollowerPlugin::likelihood() const			{ return fLikelihood (fGF); }
const float* TGestureFollowerPlugin::speed () const				{ return fSpeed (fGF); }
int  TGestureFollowerPlugin::getPhraseSize(int index) const		{ return fGetPhraseSize (fGF, index); }
const float* TGestureFollowerPlugin::getPhraseData(int index) const	{ return fGetPhraseData (fGF, index); }
int  TGestureFollowerPlugin::getState() const					{ return fGetState (fGF); }


} // end namespace
