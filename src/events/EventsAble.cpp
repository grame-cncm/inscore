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


#include "EventsAble.h"
#include "EventMessage.h"
#include "TInterval.h"
#include "OSCStream.h"

using namespace std;

const char* kMouseMoveStr	= "mouseMove";
const char* kMouseDownStr	= "mouseDown";
const char* kMouseUpStr		= "mouseUp";
const char* kMouseEnterStr	= "mouseEnter";
const char* kMouseLeaveStr	= "mouseLeave";
const char* kMouseDoubleClickStr = "doubleClick";
const char* kFileStr		= "file";
const char* kTimeEnterStr	= "timeEnter";
const char* kTimeLeaveStr	= "timeLeave";
const char* kDurEnterStr	= "durEnter";
const char* kDurLeaveStr	= "durLeave";

const char* kNewElementStr	= "newElement";

namespace inscore
{
static vector<SEventMessage> _static_nomsgs;

map<string, EventsAble::eventype>	EventsAble::fTypeStr;
//----------------------------------------------------------------------
EventsAble::EventsAble ()	{}
EventsAble::~EventsAble ()	{}

//----------------------------------------------------------------------
void EventsAble::setMsg (eventype t, SEventMessage msg)		
{ 
	fMsgMap[t].clear(); 
	addMsg (t, msg);
}

//----------------------------------------------------------------------
void EventsAble::reset ()
{ 
	fMsgMap.clear();
	fTimeEnterMsgMap.clear();
	fTimeLeaveMsgMap.clear();
	fDurEnterMsgMap.clear();
	fDurLeaveMsgMap.clear();
	fFileMessageMap.clear();
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
	m.fFileMessage	= fFileMessageMap;	
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
		fFileMessageMap = m.fFileMessage;	
		fWatchStack.pop();
		return true;
	}
	reset();
	return false;
}

//----------------------------------------------------------------------
void EventsAble::addMsg (eventype t, SEventMessage msg)
{ 
	if (msg) fMsgMap[t].push_back (msg); 
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
void EventsAble::setTimeMsg (eventype t, const RationalInterval& time, SEventMessage msg)
{
	switch (t) {
		case kTimeEnter:	fTimeEnterMsgMap[time].clear(); break;
		case kTimeLeave:	fTimeLeaveMsgMap[time].clear(); break;
		case kDurEnter:		fDurLeaveMsgMap[time].clear(); break;
		case kDurLeave:		fDurLeaveMsgMap[time].clear(); break;
		default:	;
	}
	addTimeMsg (t, time, msg);
}

//----------------------------------------------------------------------
void EventsAble::addTimeMsg (eventype t, const RationalInterval& time, SEventMessage msg)
{
	if (msg) {
		switch (t) {
			case kTimeEnter:	fTimeEnterMsgMap[time].push_back(msg); break;
			case kTimeLeave:	fTimeLeaveMsgMap[time].push_back(msg); break;
			case kDurEnter:		fDurEnterMsgMap[time].push_back(msg); break;
			case kDurLeave:		fDurLeaveMsgMap[time].push_back(msg); break;
			default:	;
		}
	}
}

//----------------------------------------------------------------------
void EventsAble::setFileMsg (const std::string& file, SEventMessage msg)
{
	fFileMessageMap[file].clear();
	addFileMsg (file, msg);
}

//----------------------------------------------------------------------
void EventsAble::addFileMsg (const std::string& file, SEventMessage msg)
{
	if (msg) fFileMessageMap[file].push_back (msg); 
}

//----------------------------------------------------------------------
EventsAble::eventype EventsAble::string2type (const string& str)
{
	return fTypeStr[str];
}

//----------------------------------------------------------------------
const vector<SEventMessage>& EventsAble::getMouseMsgs (eventype t) const
{
	return getMessages(t);
}

//----------------------------------------------------------------------
const vector<SEventMessage>& EventsAble::getMessages (eventype t) const
{
	_TMsgMap::const_iterator i = fMsgMap.find(t);
	if (i != fMsgMap.end())
		return i->second;
	return _static_nomsgs;
}

//----------------------------------------------------------------------
const vector<SEventMessage>& EventsAble::getTimeMsgs (eventype t, const RationalInterval& time) const
{
	_TimeMsgMap::const_iterator i, end;
	switch (t) {
		case kTimeEnter:	
			i	= fTimeEnterMsgMap.find(time);
			end = fTimeEnterMsgMap.end();
			break;
		case kTimeLeave:
			i	= fTimeLeaveMsgMap.find(time);
			end = fTimeLeaveMsgMap.end();
			break;
		case kDurEnter:
			i	= fDurEnterMsgMap.find(time);
			end = fDurEnterMsgMap.end();
			break;
		case kDurLeave:
			i	= fDurLeaveMsgMap.find(time);
			end = fDurLeaveMsgMap.end();
			break;
		default:
			return _static_nomsgs;
	}
	if (i != end)
		return i->second;
	return _static_nomsgs;
}

//----------------------------------------------------------------------
const vector<SEventMessage>& EventsAble::getFileMsgs (const std::string& file) const
{
	_FileMsgMap::const_iterator i = fFileMessageMap.find(file);
	if (i != fFileMessageMap.end())
		return i->second;
	return _static_nomsgs;
}

//----------------------------------------------------------------------
void EventsAble::getMsgs (const char * address, const string& type, const RationalInterval& time, 
						  const vector<SEventMessage>& evm, SIMessageList& list) const
{
	const char * method = "watch";
	for (vector<SEventMessage>::const_iterator i = evm.begin(); i != evm.end(); i++) {
		SIMessage msg = getMsg (address, type, method, time, *i);
		list->list().push_back ( msg );
		method = "watch+";
	}	
}

//----------------------------------------------------------------------
void EventsAble::getMsgs (const char * address, const string& type, const string& file, 
						  const vector<SEventMessage>& evm, SIMessageList& list) const
{
	const char * method = "watch";
	for (vector<SEventMessage>::const_iterator i = evm.begin(); i != evm.end(); i++) {
		SIMessage msg = getMsg (address, type, method, file, *i);
		list->list().push_back ( msg );
		method = "watch+";
	}	
}

//----------------------------------------------------------------------
void EventsAble::getMsgs (const char * address, const string& type, const vector<SEventMessage>& evm, SIMessageList& list) const
{
	const char * method = "watch";
	for (vector<SEventMessage>::const_iterator i = evm.begin(); i != evm.end(); i++) {
		SIMessage msg = getMsg (address, type, method, *i);
		list->list().push_back ( msg );
		method = "watch+";
	}
}

SIMessage EventsAble::getMsg (const char * address, const string& type, const char* mth,
		const RationalInterval& time, const SEventMessage& ev) const
{
	SIMessage msg = IMessage::create (address, mth);
	msg->add (type);
	msg->add (int(time.first().getNumerator()));
	msg->add (int(time.first().getDenominator()));
	msg->add (int(time.second().getNumerator()));
	msg->add (int(time.second().getDenominator()));
	return putMsg (msg, ev);
}

SIMessage EventsAble::getMsg (const char * address, const string& type, const char* mth,
		const string& file, const SEventMessage& ev) const
{
	SIMessage msg = IMessage::create (address, mth);
	msg->add (type);
	msg->add (file);
	return putMsg (msg, ev);
}

SIMessage EventsAble::getMsg (const char * address, const string& type, const char* mth, const SEventMessage& ev) const
{
	SIMessage msg = IMessage::create (address, mth);
	msg->add (type);
	return putMsg (msg, ev);
}

//----------------------------------------------------------------------
SIMessage EventsAble::putMsg (SIMessage& msg, const SEventMessage& ev) const
{
	const IMessage * evmsg = ev->message();
	if (msg && evmsg) {
		msg->add (ev->address());
		msg->add (evmsg->message());
		for (int i=0; i < evmsg->size(); i++)
			msg->add (evmsg->param(i));
	}
	return msg;
}

//----------------------------------------------------------------------
SIMessageList EventsAble::getWatch (const char* address) const
{
	SIMessageList list = IMessageList::create();
	for (_TMsgMap::const_iterator i = fMsgMap.begin(); i != fMsgMap.end(); i++) {
		getMsgs (address, type2string (i->first), i->second, list);
	}
	for (_TimeMsgMap::const_iterator i = fTimeEnterMsgMap.begin(); i != fTimeEnterMsgMap.end(); i++) {
		getMsgs (address, kTimeEnterStr, i->first, i->second, list);
	}
	for (_TimeMsgMap::const_iterator i = fTimeLeaveMsgMap.begin(); i != fTimeLeaveMsgMap.end(); i++) {
		getMsgs (address, kTimeLeaveStr, i->first, i->second, list);
	}
	for (_TimeMsgMap::const_iterator i = fDurEnterMsgMap.begin(); i != fDurEnterMsgMap.end(); i++) {
		getMsgs (address, kDurEnterStr, i->first, i->second, list);
	}
	for (_TimeMsgMap::const_iterator i = fDurLeaveMsgMap.begin(); i != fDurLeaveMsgMap.end(); i++) {
		getMsgs (address, kDurLeaveStr, i->first, i->second, list);
	}
	for (_FileMsgMap::const_iterator i = fFileMessageMap.begin(); i != fFileMessageMap.end(); i++) {
		getMsgs (address, kFileStr, i->first, i->second, list);
	}
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
		case kFile:			return kFileStr;
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
		fTypeStr[kFileStr]		= kFile;
		fTypeStr[kTimeEnterStr]	= kTimeEnter;
		fTypeStr[kTimeLeaveStr]	= kTimeLeave;
		fTypeStr[kDurEnterStr]	= kDurEnter;
		fTypeStr[kDurLeaveStr]	= kDurLeave;
		fTypeStr[kNewElementStr]= kNewElement;
	}
}

} // end namespoace
