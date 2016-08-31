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

#include "TGestureFollowerPlugin.h"
#include "IGesture.h"
#include "IGestureFollower.h"
#include "IMessage.h"
#include "ITLError.h"
#include "TMessageEvaluator.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

#define kDefaultThreshold 0.5

//--------------------------------------------------------------------------
IGesture::IGesture( const std::string& name, IObject* parent, int index, TGestureFollowerPlugin * gf ) 
		: IVNode (name, parent), 
		  fGF (gf), fIndex(index), fLikelihoodThreshold (kDefaultThreshold), fCurrentLikelihood(0.f)
{ 	
	fMsgHandlerMap[kset_SetMethod]						= TMethodMsgHandler<IGesture>::create(this, &IGesture::set);
	fMsgHandlerMap[kclear_SetMethod]					= TMethodMsgHandler<IGesture,void (IGesture::*)()>::create(this, &IGesture::clearGesture);
	fMsgHandlerMap[klearn_SetMethod]					= TMethodMsgHandler<IGesture>::create(this, &IGesture::learn);
	fMsgHandlerMap[klikelihoodthreshold_GetSetMethod]	= TSetMethodMsgHandler<IGesture,float>::create(this, &IGesture::setLikelihoodThreshold);

	fGetMsgHandlerMap[klikelihoodthreshold_GetSetMethod]= TGetParamMethodHandler<IGesture, float (IGesture::*)() const>::create(this, &IGesture::getLikelihoodThreshold);
	fGetMsgHandlerMap[ksize_GetSetMethod]				= TGetParamMethodHandler<IGesture, int (IGesture::*)() const>::create(this, &IGesture::getSize);
}

//--------------------------------------------------------------------------
IGesture::~IGesture()
{ 
}

//--------------------------------------------------------------------------
void IGesture::accept (Updater* u)
{
	u->updateTo (SIGesture(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGesture::_watchMsg(const IMessage* msg, bool add)
{ 
	MsgHandler::msgStatus status = IObject::_watchMsg (msg, add);
	if (status == MsgHandler::kProcessed) return status;

	string what;
	if (!msg->param (0, what))				// can't decode event to watch when not a string
		return MsgHandler::kBadParameters;	// exit with bad parameter
		
	EventsAble::eventype t = EventsAble::string2type (what);
	switch (t) {
		case EventsAble::kGFEnter:
		case EventsAble::kGFLeave:
		case EventsAble::kGFActive:
		case EventsAble::kGFIdle:
			if (msg->size() > 1) {
				SIMessageList watchMsg = msg->watchMsg2Msgs (1);
				if (!watchMsg) return MsgHandler::kBadParameters;

				if (add) eventsHandler()->addMsg (t, watchMsg);
				else eventsHandler()->setMsg (t, watchMsg);
			}
			else if (!add) eventsHandler()->setMsg (t, 0);
			status = MsgHandler::kProcessed;
			break;
		default: break;
	}
	return status;
}

//--------------------------------------------------------------------------
int IGesture::getSize () const						{ return fGF->getPhraseSize(fIndex); }
const float* IGesture::data () const				{ return fGF->getPhraseData(fIndex); }
float IGesture::getLikelihoodThreshold () const		{ return fLikelihoodThreshold; }
void IGesture::setLikelihoodThreshold (float value)	{ fParent->setModified(); fLikelihoodThreshold = value; }

//--------------------------------------------------------------------------
void IGesture::clearGesture ()						{ fParent->setModified(); fGF->clear (fIndex); }
void IGesture::startLearn ()						{ fGF->stop(); fGF->startLearn (fIndex); }
void IGesture::stopLearn ()							{ fGF->stopLearn(); }
void IGesture::observe (float* values, int size)	{
	int avail = fGF->getCapacity() - getSize();
	if (size > avail) size = avail;
	int n = fGF->getFrameSize();
	for (int i=0; i < size; i+=n) fGF->observation (&values[i], n);
}

//--------------------------------------------------------------------------
void IGesture::likelihood (float likelihood, float pos, float speed)
{
	SIMessageList msgs = IMessageList::create();
	const IMessageList*	tmp = 0;
	if ((fCurrentLikelihood < fLikelihoodThreshold) && (likelihood >= fLikelihoodThreshold))		// enter gesture
		tmp = EventsAble::getMessages (EventsAble::kGFEnter);
	else if ((fCurrentLikelihood >= fLikelihoodThreshold) && (likelihood < fLikelihoodThreshold))	// leave gesture
		tmp = getMessages (EventsAble::kGFLeave);
	if (tmp) msgs->list().push_back(tmp->list());

	if (fCurrentLikelihood >= fLikelihoodThreshold)
		tmp = EventsAble::getMessages (EventsAble::kGFActive);
	else
		tmp = EventsAble::getMessages (EventsAble::kGFIdle);
	if (tmp) msgs->list().push_back(tmp->list());

	if (msgs->list().size()) {
		MouseLocation mouse (0, 0, 0, 0, 0, 0);
		EventContext env(mouse, getDate(), this);
		GestureContext g (likelihood, pos, speed);
		env.set(g);
		TMessageEvaluator me;
		SIMessageList outmsgs = me.eval (msgs, env);
		if (outmsgs && outmsgs->list().size()) outmsgs->send();
	}
	fCurrentLikelihood = likelihood;
}

//--------------------------------------------------------------------------
SIMessageList IGesture::getSetMsg () const
{
	SIMessageList outmsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	int n = getSize();
	const float * values = data();
	for (int i = 0; i < n; i++)
		*msg << values[i];
	outmsgs->list().push_back(msg);
	return outmsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGesture::learn (const IMessage* msg)
{
	if  (msg->size()) return MsgHandler::kBadParameters;
	IGestureFollower* gf = static_cast<IGestureFollower*>(fParent);
	gf->learn (this);
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGesture::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = MsgHandler::kProcessed;
	int n = msg->size();
	if (n > 0) {
		float* values = new float[n];
		float val; int ival;
		for (int i=0; i<n; i++) {
			if (msg->param(i, val))			values[i] = val;
			else if (msg->param(i, ival))	values[i] = float(ival);
			else status = MsgHandler::kBadParameters;
		}
		if (status == MsgHandler::kProcessed) learn (values, n);
		delete[] values;
	}
	else learn (0, 0);
	return status;
}

//--------------------------------------------------------------------------
void IGesture::learn (float* values, int size)
{
	startLearn	();
	if ( size ) observe (values, size);
	stopLearn();
	fParent->setModified();
}

}
