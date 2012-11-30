/*

  INScore Project

  Copyright (C) 2009,2012  Grame

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


#include "EventsAble.h"
#include "IMessageStream.h"
#include "TInterval.h"
#include "OSCStream.h"

using namespace std;

static const char* kMouseMoveStr	= "mouseMove";
static const char* kMouseDownStr	= "mouseDown";
static const char* kMouseUpStr		= "mouseUp";
static const char* kMouseEnterStr	= "mouseEnter";
static const char* kMouseLeaveStr	= "mouseLeave";
static const char* kMouseDoubleClickStr = "doubleClick";
static const char* kTimeEnterStr	= "timeEnter";
static const char* kTimeLeaveStr	= "timeLeave";
static const char* kDurEnterStr	= "durEnter";
static const char* kDurLeaveStr	= "durLeave";

static const char* kNewElementStr	= "newElement";

namespace inscore
{

map<string, EventsAble::eventype>	EventsAble::fTypeStr;
//----------------------------------------------------------------------
EventsAble::EventsAble ()	{}
EventsAble::~EventsAble ()	{}


//----------------------------------------------------------------------
void EventsAble::reset ()
{ 
	fMsgMap.clear();
	fTimeEnterMsgMap.clear();
	fTimeLeaveMsgMap.clear();
	fDurEnterMsgMap.clear();
	fDurLeaveMsgMap.clear();
	while (fWatchStack.size())
		fWatchStack.pop();
}

//----------------------------------------------------------------------
void EventsAble::pushWatch ()
{ 
	EventsMaps m;
	m.fMsg			= fMsgMap;
	m.fTimeEnterMsg = fTimeEnterMsgMap;
	m.fTimeLeaveMsg	= fTimeLeaveMsgMap;
	m.fDurEnterMsg	= fDurEnterMsgMap;
	m.fDurLeaveMsg	= fDurLeaveMsgMap;
	fWatchStack.push(m);
}

//----------------------------------------------------------------------
bool EventsAble::popWatch ()
{ 
	if (fWatchStack.size()) {
		EventsMaps m = fWatchStack.top();
		fMsgMap			= m.fMsg;
		fTimeEnterMsgMap= m.fTimeEnterMsg;
		fTimeLeaveMsgMap= m.fTimeLeaveMsg;
		fDurEnterMsgMap	= m.fDurEnterMsg;
		fDurLeaveMsgMap	= m.fDurLeaveMsg;
		fWatchStack.pop();
		return true;
	}
	reset();
	return false;
}

//----------------------------------------------------------------------
void EventsAble::clearTimeMsg (eventype t)
{
	switch (t) {
		case kTimeEnter:	fTimeEnterMsgMap.clear(); break;
		case kTimeLeave:	fTimeLeaveMsgMap.clear(); break;
		case kDurEnter:		fDurLeaveMsgMap.clear(); break;
		case kDurLeave:		fDurLeaveMsgMap.clear(); break;
		default:	;
	}
}

//----------------------------------------------------------------------
void EventsAble::setTimeMsg (eventype t, const RationalInterval& time, SIMessageList msgs)
{
	switch (t) {
		case kTimeEnter:	fTimeEnterMsgMap.set(time, msgs); break;
		case kTimeLeave:	fTimeLeaveMsgMap.set(time, msgs); break;
		case kDurEnter:		fDurLeaveMsgMap.set(time, msgs); break;
		case kDurLeave:		fDurLeaveMsgMap.set(time, msgs); break;
		default:	;
	}
}

//----------------------------------------------------------------------
void EventsAble::addTimeMsg (eventype t, const RationalInterval& time, SIMessageList msgs)
{
	switch (t) {
		case kTimeEnter:	fTimeEnterMsgMap.add(time, msgs); break;
		case kTimeLeave:	fTimeLeaveMsgMap.add(time, msgs); break;
		case kDurEnter:		fDurLeaveMsgMap.add(time, msgs); break;
		case kDurLeave:		fDurLeaveMsgMap.add(time, msgs); break;
		default:	;
	}
}

//----------------------------------------------------------------------
const IMessageList* EventsAble::getTimeMsgs (eventype t, const RationalInterval& time) const
{
	switch (t) {
		case kTimeEnter:	return fTimeEnterMsgMap.get(time);
		case kTimeLeave:	return fTimeLeaveMsgMap.get(time);
		case kDurEnter:		return fDurEnterMsgMap.get(time);
		case kDurLeave:		return fDurLeaveMsgMap.get(time);
		default:
			;
	}
	return 0;
}

//----------------------------------------------------------------------
SIMessage EventsAble::buildGetMsg (const char * address, const string& what, const RationalInterval& time, const IMessageList* mlist) const
{
	SIMessage msg = IMessage::create (address, "watch");
	*msg << what << int(time.first().getNumerator())
		<< int(time.first().getDenominator())
		<< int(time.second().getNumerator())
		<< int(time.second().getDenominator())
		<< mlist;
	return msg;
}

//----------------------------------------------------------------------
SIMessage EventsAble::buildGetMsg (const char * address, const string& what, const SIMessageList& msgs) const
{
	SIMessage msg = IMessage::create (address, "watch");
	*msg << what << msgs;
	return msg;
}

//----------------------------------------------------------------------
SIMessageList EventsAble::getWatch (const char* address) const
{
	SIMessageList list = IMessageList::create();
	for (_TMsgMap::const_iterator i = fMsgMap.begin(); i != fMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, type2string (i->first), i->second));

	for (_TimeMsgMap::const_iterator i = fTimeEnterMsgMap.begin(); i != fTimeEnterMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, kTimeEnterStr, i->first, i->second));

	for (_TimeMsgMap::const_iterator i = fTimeLeaveMsgMap.begin(); i != fTimeLeaveMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, kTimeLeaveStr, i->first, i->second));

	for (_TimeMsgMap::const_iterator i = fDurEnterMsgMap.begin(); i != fDurEnterMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, kDurEnterStr, i->first, i->second));

	for (_TimeMsgMap::const_iterator i = fDurLeaveMsgMap.begin(); i != fDurLeaveMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, kDurLeaveStr, i->first, i->second));
	return list;
}

//----------------------------------------------------------------------
const char* EventsAble::type2string (eventype type)
{
	switch (type) {
		case kMouseMove:	return kMouseMoveStr;
		case kMouseDown:	return kMouseDownStr;
		case kMouseUp:		return kMouseUpStr;
		case kMouseEnter:	return kMouseEnterStr;
		case kMouseLeave:	return kMouseLeaveStr;
		case kMouseDoubleClick: return kMouseDoubleClickStr;
		case kTimeEnter:	return kTimeEnterStr;
		case kTimeLeave: 	return kTimeLeaveStr;
		case kDurEnter:		return kDurEnterStr;
		case kDurLeave: 	return kDurLeaveStr;
		case kNewElement: 	return kNewElementStr;
		default: return "";
	}
}

//----------------------------------------------------------------------
void EventsAble::init ()
{
	if (!fTypeStr.size()) {
		fTypeStr[kMouseMoveStr]	= kMouseMove;
		fTypeStr[kMouseDownStr]	= kMouseDown;
		fTypeStr[kMouseUpStr]	= kMouseUp;
		fTypeStr[kMouseEnterStr]= kMouseEnter;
		fTypeStr[kMouseLeaveStr]= kMouseLeave;
		fTypeStr[kMouseDoubleClickStr]	= kMouseDoubleClick;
		fTypeStr[kTimeEnterStr]	= kTimeEnter;
		fTypeStr[kTimeLeaveStr]	= kTimeLeave;
		fTypeStr[kDurEnterStr]	= kDurEnter;
		fTypeStr[kDurLeaveStr]	= kDurLeave;
		fTypeStr[kNewElementStr]= kNewElement;
	}
}

} // end namespoace
