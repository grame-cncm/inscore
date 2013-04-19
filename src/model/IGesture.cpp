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
#include "IGesture.h"
#include "IMessage.h"
#include "ITLError.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

#define kDefaultThreshold 0.7

//--------------------------------------------------------------------------
IGesture::IGesture( const std::string& name, IObject* parent, int index, GestureFollower * gf ) 
		: IVNode (name, parent), 
		  fGF (gf), fIndex(index), fLikelihoodThreshold (kDefaultThreshold)		   
{ 	
	fMsgHandlerMap[klearn_SetMethod]					= TMethodMsgHandler<IGesture,void (IGesture::*)()>::create(this, &IGesture::learn);
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
void IGesture::clearGesture ()
{
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGesture::set (const IMessage* msg)	
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
		newData(true);
		status = MsgHandler::kProcessed;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}


//--------------------------------------------------------------------------
void IGesture::learn ()
{
}

}
