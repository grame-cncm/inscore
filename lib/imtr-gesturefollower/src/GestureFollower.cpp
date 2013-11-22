/**
 * @file   GestureFollower.h
 * @author D. Fober
 * 
 * @brief  interface file for the gesture follower library.
 *
 * Copyright (C) 2013 by Grame, Lyon, France.
 * 
 */


#include "GestureFollower.h"
#include "GFLib.h"

//--------------------------------------------------------------------------
// C interface
//--------------------------------------------------------------------------
GestureFollower * newGestureFollower (int maxPhrases, int vecSize, long capacity)
													{ return new GestureFollower (maxPhrases, vecSize, capacity); }
void delGestureFollower (GestureFollower * gf)		{ delete gf; }

void		startLearn	(GestureFollower * gf, int phraseIndex)			{ gf->startLearn(phraseIndex); }
void		stopLearn	(GestureFollower * gf)							{ gf->stopLearn(); }
void		clear		(GestureFollower * gf, int phraseIndex)			{ gf->clear(phraseIndex); }
void		clearAll	(GestureFollower * gf)							{ gf->clearAll(); }
void		startFollow	(GestureFollower * gf)							{ gf->startFollow(); }
void		stopFollow	(GestureFollower * gf)							{ gf->stopFollow(); }
void		setLikelihoodWindow (GestureFollower * gf, int size)		{ gf->setLikelihoodWindow (size); }
int			getMaxPhrases (GestureFollower * gf)						{ return gf->getMaxPhrases (); }
int			getFrameSize (GestureFollower * gf)							{ return gf->getFrameSize (); }
int			getCapacity (GestureFollower * gf)							{ return gf->getCapacity (); }
int			getLikelihoodWindow (GestureFollower * gf)					{ return gf->getLikelihoodWindow (); }
void		setTolerance (GestureFollower * gf, float tolerance)		{ gf->setTolerance (tolerance); }
float		getTolerance (GestureFollower * gf)							{ return gf->getTolerance (); }
void		observation (GestureFollower * gf, float* data, int size)	{ gf->observation (data, size); }
int				likeliest(GestureFollower * gf)							{ return gf->likeliest (); }
const float*	where(GestureFollower * gf)								{ return gf->where (); }
const float*	likelihood(GestureFollower * gf)						{ return gf->likelihood (); }
const float*	speed (GestureFollower * gf)							{ return gf->speed (); }
int				getState(GestureFollower * gf)							{ return gf->getState (); }

//--------------------------------------------------------------------------
// C++ implementation
//--------------------------------------------------------------------------
GestureFollower::GestureFollower(int maxPhrases, int vecSize, long capacity) : fGF(0)
{
	fGF = new GF(0, maxPhrases,	vecSize, capacity, 0, 0, 0);
}

//--------------------------------------------------------------------------
GestureFollower::~GestureFollower()						{ delete fGF; }

//--------------------------------------------------------------------------
int GestureFollower::getMaxPhrases () const				{ return fGF->maxPhrases; }
int GestureFollower::getFrameSize () const				{ return 1; }
int GestureFollower::getCapacity () const				{ return 2048; }
		
//--------------------------------------------------------------------------
void GestureFollower::startLearn (int phraseIndex)		{ fGF->setLearning (phraseIndex); }
void GestureFollower::stopLearn	()						{ fGF->setLearningOff(); }

//--------------------------------------------------------------------------
void GestureFollower::clear	(int phraseIndex)			{ fGF->clear (phraseIndex); }
void GestureFollower::clearAll ()						{ fGF->clearAll(); }

//--------------------------------------------------------------------------
void GestureFollower::startFollow ()					{ fGF->setDecoding (1); }
void GestureFollower::stopFollow ()						{ fGF->setDecoding (0); }

//--------------------------------------------------------------------------
void GestureFollower::setLikelihoodWindow (int size)	{ fGF->setLikelihoodWindow (size); }
void GestureFollower::setTolerance (float tolerance)	{ fGF->setTolerance (tolerance); }

int		GestureFollower::getLikelihoodWindow ()	const	{ return fGF->likelihoodWindowSize; }
float	GestureFollower::getTolerance () const			{ return fGF->tolerance; }

//--------------------------------------------------------------------------
void GestureFollower::observation (float* data, int size)
{
	fGF->observation (data, size, false);
}


//--------------------------------------------------------------------------
int GestureFollower::likeliest() const					{ return fGF->likeliest; }
const float* GestureFollower::where() const				{ return fGF->n_index; }
const float* GestureFollower::likelihood() const		{ return fGF->n_likelihood; }
const float* GestureFollower::speed () const			{ return fGF->speed; }


//--------------------------------------------------------------------------
GestureFollower::state GestureFollower::getState() const
{
	GestureFollower::state result = kIdle;
	if (fGF->isLearning) result = kLearning;
	else if (fGF->isDecoding) result = kDecoding;
	return result;
}

