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
#include "Methods.h"
#include "OSCStream.h"

using namespace std;


namespace inscore
{

const char* kMouseMoveEvent			= "mouseMove";
const char* kMouseDownEvent			= "mouseDown";
const char* kMouseUpEvent			= "mouseUp";
const char* kMouseEnterEvent		= "mouseEnter";
const char* kMouseLeaveEvent		= "mouseLeave";
const char* kMouseDoubleClickEvent	= "doubleClick";

const char* kTouchBeginEvent		= "touchBegin";
const char* kTouchEndEvent			= "touchEnd";
const char* kTouchUpdateEvent		= "touchUpdate";

const char* kTimeEnterEvent			= "timeEnter";
const char* kTimeLeaveEvent			= "timeLeave";
const char* kDurEnterEvent			= "durEnter";
const char* kDurLeaveEvent			= "durLeave";
const char* kExportEvent			= "export";
//const char* kDeleteEvent			= "del";		'del' is now part of the common set of accepted events
const char* kNewDataEvent			= "newData";

// gesture specific events
const char* kGFEnterEvent			= "gfEnter";
const char* kGFLeaveEvent			= "gfLeave";
const char* kGFActiveEvent			= "gfActive";
const char* kGFIdleEvent			= "gfIdle";

// URL specific events
const char* kSuccessEvent			= "success";
const char* kErrorEvent				= "error";
const char* kCancelEvent			= "cancel";

// scene specific events
const char* kEndPaintEvent			= "endPaint";
const char* kNewElementEvent		= "newElement";

// score specific events
const char* kPageCountEvent			= "pageCount";

// media specific events
const char* kEndEvent				= "end";
const char* kReadyEvent				= "ready";

map<size_t, std::string>	EventsAble::fHashCodes;
std::hash<string>			EventsAble::fHash;

//----------------------------------------------------------------------
EventsAble::EventsAble ():	fMouseSensible(false) { init(); }
EventsAble::~EventsAble ()	{}

//----------------------------------------------------------------------
void EventsAble::setMsg(EventsAble::eventype t, SIMessageList msgs)
{
	fMsgMap.set(fHash(t), msgs);

	if(msgs && isMouseEvent(t)){
		if(fMouseSensible){
			if(!msgs->list().size() && !checkMouseSensibility()){
				fMouseSensible = false;
				setMouseEventSensibility(false);
			}
		}else if(!msgs->list().empty()){
			fMouseSensible = true;
			setMouseEventSensibility(true);
		}
	}
}

//----------------------------------------------------------------------
void EventsAble::addMsg(EventsAble::eventype t, SIMessageList msgs)
{
	fMsgMap.add(fHash(t), msgs);

	if(!fMouseSensible && isMouseEvent(t)) {
		fMouseSensible = true;
		setMouseEventSensibility(true);
	}
}


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

	if(fMouseSensible){
		setMouseEventSensibility(false);
		fMouseSensible = false;
	}
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

		fMouseSensible = checkMouseSensibility();
		return true;
	}
	reset();
	return false;
}

//----------------------------------------------------------------------
void EventsAble::clearTimeMsg (eventype t)
{
	size_t ht = fHash(t);
	if (ht == fHash(kTimeEnterEvent))			fTimeEnterMsgMap.clear();
	else if (ht == fHash(kTimeLeaveEvent))		fTimeLeaveMsgMap.clear();
	else if (ht == fHash(kDurEnterEvent))		fDurEnterMsgMap.clear();
	else if (ht == fHash(kDurLeaveEvent))		fDurLeaveMsgMap.clear();
}

//----------------------------------------------------------------------
void EventsAble::setTimeMsg (eventype t, const RationalInterval& time, SIMessageList msgs)
{
	size_t ht = fHash(t);
	if (ht == fHash(kTimeEnterEvent))			fTimeEnterMsgMap.set(time, msgs);
	else if (ht == fHash(kTimeLeaveEvent))		fTimeLeaveMsgMap.set(time, msgs);
	else if (ht == fHash(kDurEnterEvent))		fDurEnterMsgMap.set (time, msgs);
	else if (ht == fHash(kDurLeaveEvent))		fDurLeaveMsgMap.set (time, msgs);
}

//----------------------------------------------------------------------
void EventsAble::addTimeMsg (eventype t, const RationalInterval& time, SIMessageList msgs)
{
	size_t ht = fHash(t);
	if (ht == fHash(kTimeEnterEvent))			fTimeEnterMsgMap.add(time, msgs);
	else if (ht == fHash(kTimeLeaveEvent))		fTimeLeaveMsgMap.add(time, msgs);
	else if (ht == fHash(kDurEnterEvent))		fDurEnterMsgMap.add (time, msgs);
	else if (ht == fHash(kDurLeaveEvent))		fDurLeaveMsgMap.add (time, msgs);
}

//----------------------------------------------------------------------
const IMessageList* EventsAble::getTimeMsgs (eventype t, const RationalInterval& time) const
{
	const IMessageList* msgs = 0;
	size_t ht = fHash(t);
	if (ht == fHash(kTimeEnterEvent))			msgs = fTimeEnterMsgMap.get(time);
	else if (ht == fHash(kTimeLeaveEvent))		msgs = fTimeLeaveMsgMap.get(time);
	else if (ht == fHash(kDurEnterEvent))		msgs = fDurEnterMsgMap.get(time);
	else if (ht == fHash(kDurLeaveEvent))		msgs = fDurLeaveMsgMap.get(time);
	return msgs;
}

//----------------------------------------------------------------------
SIMessage EventsAble::buildGetMsg (const char * address, const string& what, const RationalInterval& time, const IMessageList* mlist) const
{
	SIMessage msg = IMessage::create (address, kwatch_GetSetMethod);
	*msg << what << time.first() << time.second();
	if (mlist) {
		SIMessageList msgs = IMessageList::create();
		*msgs = *mlist;
		*msg << msgs;
	}
	return msg;
}

//----------------------------------------------------------------------
SIMessage EventsAble::buildGetMsg (const char * address, const string& what, const SIMessageList& msgs) const
{
	SIMessage msg = IMessage::create (address, kwatch_GetSetMethod);
	*msg << what << msgs;
	return msg;
}

//----------------------------------------------------------------------
SIMessageList EventsAble::getWatch (const char* address) const
{
	SIMessageList list = IMessageList::create();
	for (TWatcher<size_t>::const_iterator i = fMsgMap.begin(); i != fMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, fHashCodes[i->first], i->second));

	for (TWatcher<RationalInterval>::const_iterator i = fTimeEnterMsgMap.begin(); i != fTimeEnterMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, kTimeEnterEvent, i->first, i->second));

	for (TWatcher<RationalInterval>::const_iterator i = fTimeLeaveMsgMap.begin(); i != fTimeLeaveMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, kTimeLeaveEvent, i->first, i->second));

	for (TWatcher<RationalInterval>::const_iterator i = fDurEnterMsgMap.begin(); i != fDurEnterMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, kDurEnterEvent, i->first, i->second));

	for (TWatcher<RationalInterval>::const_iterator i = fDurLeaveMsgMap.begin(); i != fDurLeaveMsgMap.end(); i++)
		list->list().push_back( buildGetMsg (address, kDurLeaveEvent, i->first, i->second));

	if (list->list().empty()) list->list().push_back(IMessage::create (address, kwatch_GetSetMethod));
	return list;
}

//----------------------------------------------------------------------
SIMessageList EventsAble::getStack (const char* address) const
{
	SIMessageList list = IMessageList::create();
    
    stack<EventsMaps> temp = fWatchStack;
    stack<EventsMaps> tempInverted;

    while(temp.size())
    {
        EventsMaps m = temp.top();
        temp.pop();
        tempInverted.push(m);
    }
    while(tempInverted.size())
    {
        EventsMaps m = tempInverted.top();
        for (TWatcher<size_t>::const_iterator i = m.fMsg.begin(); i != m.fMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, fHashCodes[i->first], i->second));

        for (TWatcher<RationalInterval>::const_iterator i = m.fTimeEnterMsg.begin(); i != m.fTimeEnterMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, kTimeEnterEvent, i->first, i->second));

        for (TWatcher<RationalInterval>::const_iterator i = m.fTimeLeaveMsg.begin(); i != m.fTimeLeaveMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, kTimeLeaveEvent, i->first, i->second));

        for (TWatcher<RationalInterval>::const_iterator i = m.fDurEnterMsg.begin(); i != m.fDurEnterMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, kDurEnterEvent, i->first, i->second));

        for (TWatcher<RationalInterval>::const_iterator i = m.fDurLeaveMsg.begin(); i != m.fDurLeaveMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, kDurLeaveEvent, i->first, i->second));
        
        SIMessage msg = IMessage::create(address, kpush_SetMethod);
        list->list().push_back(msg);
        
        tempInverted.pop();

    }
    return list;
}

//----------------------------------------------------------------------
bool EventsAble::isTimeEvent(size_t type)
{
	return	(type == fHash(kTimeEnterEvent))	||
			(type == fHash(kTimeLeaveEvent))	||
			(type == fHash(kDurEnterEvent))		||
			(type == fHash(kDurLeaveEvent));
}

//----------------------------------------------------------------------
bool EventsAble::isDurEvent(size_t type)
{
	return	(type == fHash(kDurEnterEvent))		||
			(type == fHash(kDurLeaveEvent));
}

//----------------------------------------------------------------------
bool EventsAble::isMouseEvent(size_t type)
{
	return	(type == fHash(kMouseMoveEvent))		||
			(type == fHash(kMouseDownEvent))		||
			(type == fHash(kMouseUpEvent))			||
			(type == fHash(kMouseEnterEvent))		||
			(type == fHash(kMouseLeaveEvent))		||
			(type == fHash(kMouseDoubleClickEvent)) ||
			(type == fHash(kTouchBeginEvent))		||
			(type == fHash(kTouchEndEvent))			||
			(type == fHash(kTouchUpdateEvent));
}

//----------------------------------------------------------------------
bool EventsAble::checkMouseSensibility() const
{
	for(auto it = fMsgMap.begin(); it != fMsgMap.end(); it++){
		if(isMouseEvent(it->first))
			return true;
	}
	return false;
}

//----------------------------------------------------------------------
bool EventsAble::hash(eventype t)
{
	size_t h = fHash(t);
	map<size_t, std::string>::const_iterator i = fHashCodes.find(h);
	if (i != fHashCodes.end()) {	// hash code is already in the table
		bool collision = (i->second != t);
		if (collision)
			ITLErr << "Warning: hash code collision in events management" << t << "vs" << i->second << ITLEndl;
		return !collision;		// compare with the existing value
	}
	// hash code is not in the table
//cout << "EventsAble::hash " << t << " -> " << h << endl;
	fHashCodes[h] = t;
	return true;
}

//----------------------------------------------------------------------
void EventsAble::init ()
{
	if (!fHashCodes.size()) {
		hash (kMouseMoveEvent);
		hash (kMouseDownEvent);
		hash (kMouseUpEvent);
		hash (kMouseEnterEvent);
		hash (kMouseLeaveEvent);
		hash (kMouseDoubleClickEvent);

		hash (kTouchBeginEvent);
		hash (kTouchEndEvent);
		hash (kTouchUpdateEvent);

		hash (kTimeEnterEvent);
		hash (kTimeLeaveEvent);
		hash (kDurEnterEvent);
		hash (kDurLeaveEvent);

		hash (kNewElementEvent);
		hash (kEndPaintEvent);

		hash (kGFEnterEvent);
		hash (kGFLeaveEvent);
		hash (kGFActiveEvent);
		hash (kGFIdleEvent);

		hash (kNewDataEvent);
		hash (kSuccessEvent);
		hash (kErrorEvent);
		hash (kCancelEvent);

		hash (kPageCountEvent);
		hash (kEndEvent);
		hash (kReadyEvent);
	}
}

} // end namespoace
