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
IGestureFollower::IGestureFollower( const std::string& name, IObject* parent ) : IRectShape(name, parent), fGF(0), fGesturesOffset(0)
{ 
	fTypeString = kGestureFollowerType;
	
	setColor (IColor(255,255,255));
	setWidth (0.5);
	setHeight (0.5);

	fMsgHandlerMap[klearn_SetMethod]				= TSetMethodMsgHandler<IGestureFollower,string>::create(this, &IGestureFollower::learn);
	fMsgHandlerMap[kfollow_SetMethod]				= TMethodMsgHandler<IGestureFollower,void (IGestureFollower::*)()>::create(this, &IGestureFollower::follow);
	fMsgHandlerMap[kstop_SetMethod]					= TMethodMsgHandler<IGestureFollower,void (IGestureFollower::*)()>::create(this, &IGestureFollower::stop);
	fMsgHandlerMap[klikelihoodwindow_GetSetMethod]	= TSetMethodMsgHandler<IGestureFollower,int>::create(this, &IGestureFollower::setLikelyhoodWindow);
	fMsgHandlerMap[ktolerance_GetSetMethod]			= TSetMethodMsgHandler<IGestureFollower,float>::create(this, &IGestureFollower::setTolerance);

	fGetMsgHandlerMap[klikelihoodwindow_GetSetMethod]	= TGetParamMethodHandler<IGestureFollower, int (IGestureFollower::*)() const>::create(this, &IGestureFollower::getLikelyhoodWindow);
	fGetMsgHandlerMap[ktolerance_GetSetMethod]			= TGetParamMethodHandler<IGestureFollower, float (IGestureFollower::*)() const>::create(this, &IGestureFollower::getTolerance);
}

//--------------------------------------------------------------------------
IGestureFollower::~IGestureFollower()
{ 
	fGFLib.del (fGF);
}

//--------------------------------------------------------------------------
void IGestureFollower::accept (Updater* u)
{
	u->updateTo (SIGestureFollower(this));
}

//--------------------------------------------------------------------------
void IGestureFollower::clearGestureFollower ()
{
	fGFLib.del (fGF);
	fGF = 0;
	elements().clear();
}

//--------------------------------------------------------------------------
bool IGestureFollower::createGestureFollower (int sigDimension, int buffsize, vector<string>& gestures)
{
	if (!fGFLib.load()) {
		ITLErr << "the gesture follower library is missing" << ITLEndl;
		return false;
	}
	cout << "creating gesture follower with dim " << sigDimension << " bufsize " << buffsize << " gest count: " << gestures.size() << endl;
	fGF = fGFLib.create (gestures.size(), sigDimension, buffsize);
	if (fGF) {
		fCapacity = buffsize;
		fFrameSize = sigDimension;
		fGesturesOffset = elements().size();
		for (unsigned int i = 0; i < gestures.size(); i++) {
			SIGesture g = IGesture::create (gestures[i], this, i, fGF);
			add (g);
		}
	}
	else return false;
	return true;
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
	*msg << kGestureFollowerType << fFrameSize << fCapacity;
	for (unsigned int i = fGesturesOffset; i< elements().size(); i++) {
		*msg << elements()[i]->name();
	}
	outmsgs->list().push_back (msg);
	return outmsgs;	
}

//--------------------------------------------------------------------------
void IGestureFollower::setLikelyhoodWindow (int size) 
{
}

//--------------------------------------------------------------------------
void IGestureFollower::setTolerance (float t)
{
}

//--------------------------------------------------------------------------
int IGestureFollower::getLikelyhoodWindow () const	{ return 0; }
float IGestureFollower::getTolerance () const		{ return 1.0; }

//--------------------------------------------------------------------------
void IGestureFollower::follow ()
{
}

//--------------------------------------------------------------------------
void IGestureFollower::learn (const std::string& gesture)
{
}

//--------------------------------------------------------------------------
void IGestureFollower::stop ()
{
}

}
