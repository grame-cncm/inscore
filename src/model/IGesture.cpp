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
#include "IMessage.h"
#include "ITLError.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

#define kDefaultThreshold 0.7

//--------------------------------------------------------------------------
IGesture::IGesture( const std::string& name, IObject* parent, int index, TGestureFollowerPlugin * gf ) 
		: IVNode (name, parent), 
		  fGF (gf), fIndex(index), fLikelihoodThreshold (kDefaultThreshold)		   
{ 	
	fMsgHandlerMap[klikelihoodthreshold_GetSetMethod]	= TSetMethodMsgHandler<IGesture,float>::create(this, &IGesture::setLikelihoodThreshold);
	fGetMsgHandlerMap[klikelihoodthreshold_GetSetMethod]= TGetParamMethodHandler<IGesture, float (IGesture::*)() const>::create(this, &IGesture::getLikelihoodThreshold);
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
void IGesture::clearGesture ()						{ fValues.clear(); fGF->clear (fIndex); }
void IGesture::startLearn ()						{ fGF->stop(); fValues.clear(); fGF->startLearn (fIndex); }
void IGesture::stopLearn ()							{ fGF->stopLearn(); }
void IGesture::observe (float* values, int size)	{
	for (int i=0; i < size; i++) fValues.push_back(values[i]);
	fGF->observation (values, size);
}

//--------------------------------------------------------------------------
SIMessageList IGesture::getSetMsg () const
{
	SIMessageList outmsgs = IMessageList::create();
	unsigned int n = fValues.size();
	if (n < 2) return outmsgs;

	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	for (unsigned int i = 0; i < n; i++)
		*msg << fValues[i];
	return outmsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGesture::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	int n = msg->size();
	float* values = new float[n];
	if (n > 2) {
		float val; int ival;
		for (int i=0; i<n; i++) {
			if (msg->param(i, val))			values[i] = val;
			else if (msg->param(i, ival))	values[i] = float(ival);
			else return MsgHandler::kBadParameters;
		}
		learn (values, n);
		delete[] values;
		status = MsgHandler::kProcessed;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

//--------------------------------------------------------------------------
void IGesture::learn (float* values, int size)
{
	startLearn	();
	observe (values, size);
	stopLearn();
}

}
