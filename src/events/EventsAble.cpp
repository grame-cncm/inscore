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
	fFileMessageMap.clear();
}

//----------------------------------------------------------------------
void EventsAble::addMsg (eventype t, SEventMessage msg)
{ 
	if (msg) fMsgMap[t].push_back (msg); 
}

//----------------------------------------------------------------------
void EventsAble::clearTimeMsg (eventype t)
{
	if (t == kTimeEnter)		fTimeEnterMsgMap.clear();
	else if (t == kTimeLeave)	fTimeLeaveMsgMap.clear();
}

//----------------------------------------------------------------------
void EventsAble::setTimeMsg (eventype t, const RationalInterval& time, SEventMessage msg)
{
	if (t == kTimeEnter)		fTimeEnterMsgMap[time].clear();
	else if (t == kTimeLeave)	fTimeLeaveMsgMap[time].clear();
	addTimeMsg (t, time, msg);
}

//----------------------------------------------------------------------
void EventsAble::addTimeMsg (eventype t, const RationalInterval& time, SEventMessage msg)
{
	if (msg) {
		if (t == kTimeEnter)		fTimeEnterMsgMap[time].push_back(msg);
		else if (t == kTimeLeave)	fTimeLeaveMsgMap[time].push_back(msg);
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
	if (t == kTimeEnter) {
		i = fTimeEnterMsgMap.find(time);
		end = fTimeEnterMsgMap.end();
	}
	else if (t == kTimeLeave) {
		i = fTimeLeaveMsgMap.find(time);
		end = fTimeLeaveMsgMap.end();
	}
	else return _static_nomsgs;
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
						  const vector<SEventMessage>& evm, IMessageList& list) const
{
	const char * msg = "watch";
	for (vector<SEventMessage>::const_iterator i = evm.begin(); i != evm.end(); i++) {
		list += getMsg (address, type, msg, time, *i);
		msg = "watch+";
	}	
}

//----------------------------------------------------------------------
void EventsAble::getMsgs (const char * address, const string& type, const string& file, 
						  const vector<SEventMessage>& evm, IMessageList& list) const
{
	const char * msg = "watch";
	for (vector<SEventMessage>::const_iterator i = evm.begin(); i != evm.end(); i++) {
		list += getMsg (address, type, msg, file, *i);
		msg = "watch+";
	}	
}

//----------------------------------------------------------------------
void EventsAble::getMsgs (const char * address, const string& type, const vector<SEventMessage>& evm, IMessageList& list) const
{
	const char * msg = "watch";
	for (vector<SEventMessage>::const_iterator i = evm.begin(); i != evm.end(); i++) {
		list += getMsg (address, type, msg, *i);
		msg = "watch+";
	}
}

IMessage* EventsAble::getMsg (const char * address, const string& type, const char* mth, 
		const RationalInterval& time, const SEventMessage& ev) const
{
	IMessage * msg = new IMessage (address, mth);
	msg->add (type);
	msg->add (int(time.first().getNumerator()));
	msg->add (int(time.first().getDenominator()));
	msg->add (int(time.second().getNumerator()));
	msg->add (int(time.second().getDenominator()));
	return putMsg (msg, ev);
}

IMessage* EventsAble::getMsg (const char * address, const string& type, const char* mth, 
		const string& file, const SEventMessage& ev) const
{
	IMessage * msg = new IMessage (address, mth);
	msg->add (type);
	msg->add (file);
	return putMsg (msg, ev);
}

IMessage* EventsAble::getMsg (const char * address, const string& type, const char* mth, const SEventMessage& ev) const
{
	IMessage * msg = new IMessage (address, mth);
	msg->add (type);
	return putMsg (msg, ev);
}

//----------------------------------------------------------------------
IMessage* EventsAble::putMsg (IMessage * msg, const SEventMessage& ev) const
{
	const IMessage * evmsg = ev->message();
	if (msg && evmsg) {
		msg->add (ev->address());
		msg->add (evmsg->message());
		for (int i=0; i < evmsg->size(); i++)
			msg->add (evmsg->params()[i]);
	}
	return msg;
}

//----------------------------------------------------------------------
IMessageList EventsAble::getWatch (const char* address) const
{
	IMessageList list;
	for (_TMsgMap::const_iterator i = fMsgMap.begin(); i != fMsgMap.end(); i++) {
		getMsgs (address, type2string (i->first), i->second, list);
	}
	for (_TimeMsgMap::const_iterator i = fTimeEnterMsgMap.begin(); i != fTimeEnterMsgMap.end(); i++) {
		getMsgs (address, kTimeEnterStr, i->first, i->second, list);
	}
	for (_TimeMsgMap::const_iterator i = fTimeLeaveMsgMap.begin(); i != fTimeLeaveMsgMap.end(); i++) {
		getMsgs (address, kTimeLeaveStr, i->first, i->second, list);
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
		fTypeStr[kNewElementStr]= kNewElement;
	}
}

} // end namespoace
