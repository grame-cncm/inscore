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

static const char* kMouseMoveStr	= "mouseMove";
static const char* kMouseDownStr	= "mouseDown";
static const char* kMouseUpStr		= "mouseUp";
static const char* kMouseEnterStr	= "mouseEnter";
static const char* kMouseLeaveStr	= "mouseLeave";
static const char* kMouseDoubleClickStr = "doubleClick";

static const char* kTouchBeginStr	= "touchBegin";
static const char* kTouchEndStr		= "touchEnd";
static const char* kTouchUpdateStr	= "touchUpdate";

static const char* kTimeEnterStr	= "timeEnter";
static const char* kTimeLeaveStr	= "timeLeave";
static const char* kDurEnterStr		= "durEnter";
static const char* kDurLeaveStr		= "durLeave";
static const char* kExportStr		= "export";
static const char* kDeleteStr		= "del";
static const char* kNewDataStr		= "newData";

// gesture specific events
static const char* kGFEnterStr		= "gfEnter";
static const char* kGFLeaveStr		= "gfLeave";
static const char* kGFActiveStr		= "gfActive";
static const char* kGFIdleStr		= "gfIdle";

// URL specific events
static const char* kSuccessStr		= "success";
static const char* kErrorStr		= "error";
static const char* kCancelStr		= "cancel";

// scene specific events
static const char* kEndPaintStr		= "endPaint";
static const char* kNewElementStr	= "newElement";

// score specific events
static const char* kPageCountStr	= "pageCount";

namespace inscore
{

map<string, EventsAble::eventype>		EventsAble::fTypeStr;
map<EventsAble::eventype, const char*>	EventsAble::fTypeNum;

//----------------------------------------------------------------------
EventsAble::EventsAble ():	fMouseSensible(false){}
EventsAble::~EventsAble ()	{}

//----------------------------------------------------------------------
void EventsAble::setMsg(EventsAble::eventype t, SIMessageList msgs)
{
	fMsgMap.set(t, msgs);

	if(isMouseEventType(t)){
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
	fMsgMap.add(t, msgs);

	if(!fMouseSensible && isMouseEventType(t)){
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
        for (_TMsgMap::const_iterator i = m.fMsg.begin(); i != m.fMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, type2string (i->first), i->second));

        for (_TimeMsgMap::const_iterator i = m.fTimeEnterMsg.begin(); i != m.fTimeEnterMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, kTimeEnterStr, i->first, i->second));

        for (_TimeMsgMap::const_iterator i = m.fTimeLeaveMsg.begin(); i != m.fTimeLeaveMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, kTimeLeaveStr, i->first, i->second));

        for (_TimeMsgMap::const_iterator i = m.fDurEnterMsg.begin(); i != m.fDurEnterMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, kDurEnterStr, i->first, i->second));

        for (_TimeMsgMap::const_iterator i = m.fDurLeaveMsg.begin(); i != m.fDurLeaveMsg.end(); i++)
            list->list().push_back( buildGetMsg (address, kDurLeaveStr, i->first, i->second));
        
        SIMessage msg = IMessage::create(address, kpush_SetMethod);
        list->list().push_back(msg);
        
        tempInverted.pop();

    }
    return list;
}

//----------------------------------------------------------------------
const char* EventsAble::type2string (eventype type)
{
	const char* typestr = fTypeNum[type];
	return typestr ? typestr : "";
}

//----------------------------------------------------------------------
bool EventsAble::isMouseEventType(EventsAble::eventype type)
{
	switch(type){
		case kMouseMove:
		case kMouseDown:
		case kMouseUp:
		case kMouseEnter:
		case kMouseLeave:
		case kMouseDoubleClick:
		case kTouchBegin:
		case kTouchEnd:
		case kTouchUpdate:
			return true;
		default: ;
			}
	return false;
}

//----------------------------------------------------------------------
bool EventsAble::checkMouseSensibility() const
{
	for(auto it = fMsgMap.begin(); it != fMsgMap.end(); it++){
		if(isMouseEventType(it->first))
			return true;
	}
	return false;
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

		fTypeStr[kTouchBeginStr]= kTouchBegin;
		fTypeStr[kTouchEndStr]	= kTouchEnd;
		fTypeStr[kTouchUpdateStr]= kTouchUpdate;

		fTypeStr[kTimeEnterStr]	= kTimeEnter;
		fTypeStr[kTimeLeaveStr]	= kTimeLeave;
		fTypeStr[kDurEnterStr]	= kDurEnter;
		fTypeStr[kDurLeaveStr]	= kDurLeave;

		fTypeStr[kExportStr]	= kExport;
		fTypeStr[kNewElementStr]= kNewElement;
		fTypeStr[kEndPaintStr]	= kEndPaint;

		fTypeStr[kGFEnterStr]	= kGFEnter;
		fTypeStr[kGFLeaveStr]	= kGFLeave;
		fTypeStr[kGFActiveStr]	= kGFActive;
		fTypeStr[kGFIdleStr]	= kGFIdle;

		fTypeStr[kDeleteStr]	= kDelete;
		fTypeStr[kNewDataStr]	= kNewData;
		fTypeStr[kSuccessStr]	= kSuccess;
		fTypeStr[kErrorStr]     = kError;
		fTypeStr[kCancelStr]	= kCancel;

		fTypeStr[kPageCountStr]	= kPageCount;
	}
	
	if (!fTypeNum.size()) {
		fTypeNum[kMouseMove]	= kMouseMoveStr;
		fTypeNum[kMouseDown]	= kMouseDownStr;
		fTypeNum[kMouseUp]		= kMouseUpStr;
		fTypeNum[kMouseEnter]	= kMouseEnterStr;
		fTypeNum[kMouseLeave]	= kMouseLeaveStr;
		fTypeNum[kMouseDoubleClick]	= kMouseDoubleClickStr;

		fTypeNum[kTouchBegin]	= kTouchBeginStr;
		fTypeNum[kTouchEnd]		= kTouchEndStr;
		fTypeNum[kTouchUpdate]	= kTouchUpdateStr;

		fTypeNum[kTimeEnter]	= kTimeEnterStr;
		fTypeNum[kTimeLeave]	= kTimeLeaveStr;
		fTypeNum[kDurEnter]		= kDurEnterStr;
		fTypeNum[kDurLeave]		= kDurLeaveStr;

		fTypeNum[kExport]		= kExportStr;
		fTypeNum[kNewElement]	= kNewElementStr;
		fTypeNum[kNewData]		= kNewDataStr;
		fTypeNum[kEndPaint]		= kEndPaintStr;

		fTypeNum[kGFEnter]		= kGFEnterStr;
		fTypeNum[kGFLeave]		= kGFLeaveStr;
		fTypeNum[kGFActive]		= kGFActiveStr;
		fTypeNum[kGFIdle]		= kGFIdleStr;

		fTypeNum[kDelete]		= kDeleteStr;

		fTypeNum[kSuccess]		= kSuccessStr;
		fTypeNum[kError]		= kErrorStr;
		fTypeNum[kCancel]		= kCancelStr;

		fTypeNum[kPageCount]	= kPageCountStr;
	}
}

} // end namespoace
