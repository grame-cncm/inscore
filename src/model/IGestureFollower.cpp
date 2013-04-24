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

#include "GestureFollower.h"
#include "IGestureFollower.h"
#include "IGesture.h"
#include "IMessage.h"
#include "ITLError.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string IGestureFollower::kGestureFollowerType("imtrgf");

//--------------------------------------------------------------------------
IGestureFollower::IGestureFollower( const std::string& name, IObject* parent ) : IRectShape(name, parent), fGFLib(0), fGesturesOffset(0), fLearner(0)
{ 
	fTypeString = kGestureFollowerType;
	
	setColor (IColor(255,255,255));
	setWidth (0.5);
	setHeight (0.5);

	fMsgHandlerMap["*"]								= TMethodMsgHandler<IGestureFollower>::create(this, &IGestureFollower::data);
	fMsgHandlerMap[klearn_SetMethod]				= TSetMethodMsgHandler<IGestureFollower,string>::create(this, &IGestureFollower::learn);
	fMsgHandlerMap[kfollow_SetMethod]				= TMethodMsgHandler<IGestureFollower,void (IGestureFollower::*)()>::create(this, &IGestureFollower::follow);
	fMsgHandlerMap[kstop_SetMethod]					= TMethodMsgHandler<IGestureFollower,void (IGestureFollower::*)()>::create(this, &IGestureFollower::stop);
	fMsgHandlerMap[klikelihoodwindow_GetSetMethod]	= TSetMethodMsgHandler<IGestureFollower,int>::create(this, &IGestureFollower::setLikelyhoodWindow);
	fMsgHandlerMap[ktolerance_GetSetMethod]			= TSetMethodMsgHandler<IGestureFollower,float>::create(this, &IGestureFollower::setTolerance);

	fGetMsgHandlerMap[klikelihoodwindow_GetSetMethod]	= TGetParamMethodHandler<IGestureFollower, int (IGestureFollower::*)() const>::create(this, &IGestureFollower::getLikelyhoodWindow);
	fGetMsgHandlerMap[ktolerance_GetSetMethod]			= TGetParamMethodHandler<IGestureFollower, float (IGestureFollower::*)() const>::create(this, &IGestureFollower::getTolerance);
	setA(100);
}

//--------------------------------------------------------------------------
IGestureFollower::~IGestureFollower()
{ 
	delete fGFLib;
}

//--------------------------------------------------------------------------
void IGestureFollower::accept (Updater* u)
{
	u->updateTo (SIGestureFollower(this));
}

//--------------------------------------------------------------------------
bool IGestureFollower::following() const	{ return fGFLib->getState() == kDecoding; }
bool IGestureFollower::learning() const		{ return fGFLib->getState() == kLearning; }
bool IGestureFollower::idle() const			{ return fGFLib->getState() == kIdle; }

//--------------------------------------------------------------------------
IGesture* IGestureFollower::getGesture (const std::string& name) const
{
	for (unsigned int i = fGesturesOffset; i< elements().size(); i++) {
		if (elements()[i]->name() == name)
			return dynamic_cast<IGesture*>((IObject*)elements()[i]);
	}
	return 0;
}

//--------------------------------------------------------------------------
IGesture* IGestureFollower::getGesture (int index) const
{
	index += fGesturesOffset;
	return (index < elements().size()) ? dynamic_cast<IGesture*>((IObject*)elements()[index]) : 0;
}

//--------------------------------------------------------------------------
float IGestureFollower::likelihoodThreshold(int index) const
{
	float val = 1.f;
	index += fGesturesOffset;
	if (index < elements().size()) {
		IGesture * gesture = dynamic_cast<IGesture*>((IObject*)elements()[index]);
		if (gesture) val = gesture->getLikelihoodThreshold();
	}
	return val;
}

//--------------------------------------------------------------------------
bool IGestureFollower::createGestureFollower (int sigDimension, int buffsize, vector<string>& gestures)
{
	fGFLib = new TGestureFollowerPlugin (gestures.size(), sigDimension, buffsize);
	if (fGFLib && fGFLib->isAvailable()) {
		fGesturesOffset = elements().size();
		for (unsigned int i = 0; i < gestures.size(); i++) {
			SIGesture g = IGesture::create (gestures[i], this, i, fGFLib);
			add (g);
		}
	}
	else return false;
	setVisible(false);
	return true;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGestureFollower::data (const IMessage* msg)
{
	MsgHandler::msgStatus status = MsgHandler::kProcessed;
	int n = msg->size();
	int fs = fGFLib->getFrameSize();
	// check for correct data count regarding the frame size
	if ((n == 0) || (n % fs)) return MsgHandler::kBadParameters;

	float * values = new float[n];
	float val;
	for (int i=0; i<n; i++) {
		if (msg->param(i, val)) values[i] = val;
		else {
			status = MsgHandler::kBadParameters;
			break;
		}
	}
	if (status == MsgHandler::kProcessed) {
		if (fLearner) fLearner->observe(values, n);
		else if (fGFLib->following()) {
			for (int i=0; i<n; i+=fs)
				fGFLib->observation (&values[i], fs);
			const float * likelihoods = fGFLib->likelihood();
			const float * pos = fGFLib->where();
			const float * speed = fGFLib->speed();
			for (int i=0; i<fGFLib->getMaxPhrases(); i++) {
				IGesture * g = getGesture(i);
				if (g) g->likelihood(likelihoods[i], pos[i], speed[i]);
			}
		}
	}
	delete[] values;
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGestureFollower::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	int n = msg->size();
	if (n > 3) {
		int dim, buffsize;
		if (!msg->param(1, dim) || !msg->param(2, buffsize)) 
			return MsgHandler::kBadParameters;
		vector<string> gestures;
		for (int i=3; i < n; i++) {
			string str;
			if (!msg->param(i, str))
				return MsgHandler::kBadParameters;
			else gestures.push_back (str);
		}
		if (!createGestureFollower (dim, buffsize, gestures))
			return MsgHandler::kCreateFailure;
		newData(true);
		status = MsgHandler::kProcessed;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

//--------------------------------------------------------------------------
SIMessageList IGestureFollower::getSetMsg () const
{
	SIMessageList outmsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	*msg << kGestureFollowerType << fGFLib->getFrameSize() << fGFLib->getCapacity();
	for (unsigned int i = fGesturesOffset; i< elements().size(); i++) {
		*msg << elements()[i]->name();
	}
	outmsgs->list().push_back (msg);
	for (unsigned int i = fGesturesOffset; i< elements().size(); i++) {
		IGesture * gesture = dynamic_cast<IGesture*>((IObject*)elements()[i]);
		if (gesture) {
			SIMessageList l = gesture->getSetMsg();
			if (l) outmsgs->list().push_back (l->list());
		}
	}
	return outmsgs;	
}

//--------------------------------------------------------------------------
void IGestureFollower::setLikelyhoodWindow (int size)		{ fGFLib->setLikelihoodWindow (size); }
void IGestureFollower::setTolerance (float t)				{ fGFLib->setTolerance (t); }

//--------------------------------------------------------------------------
int IGestureFollower::getLikelyhoodWindow () const	{ return fGFLib ? fGFLib->getLikelihoodWindow () : 0; }
float IGestureFollower::getTolerance () const		{ return fGFLib ? fGFLib->getTolerance () : 0.; }
void IGestureFollower::follow ()					{ stop(); fGFLib->startFollow(); }

//--------------------------------------------------------------------------
void IGestureFollower::learn (const std::string& name)
{
	IGesture * gesture = getGesture(name);
	if (gesture) {
		fLearner = gesture;
		gesture->startLearn();
	}
	else ITLErr << "no such gesture:" << name << ITLEndl;
}

//--------------------------------------------------------------------------
void IGestureFollower::stop ()
{
	if (fLearner) {
		fLearner->stopLearn();
		fLearner = 0;
	}
	else fGFLib->stopFollow ();
}

}
