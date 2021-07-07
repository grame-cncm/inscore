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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <strstream>
#include <regex>

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

const char* kKeyDownEvent			= "keyDown";
const char* kKeyUpEvent				= "keyUp";
const char* kMidiEvent				= "midi";

const char* kTouchBeginEvent		= "touchBegin";
const char* kTouchEndEvent			= "touchEnd";
const char* kTouchUpdateEvent		= "touchUpdate";

const char* kTimeEnterEvent			= "timeEnter";
const char* kTimeLeaveEvent			= "timeLeave";
const char* kDurEnterEvent			= "durEnter";
const char* kDurLeaveEvent			= "durLeave";
const char* kExportEvent			= "export";
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

// midi filters keys
const char* kMidiAll				= "*";
const char* kMidiChan				= "chan";
const char* kMidiKeyon				= "keyon";
const char* kMidiKeyoff				= "keyoff";
const char* kMidiVel				= "vel";
const char* kMidiProg				= "prog";
const char* kMidiCtrl				= "ctrl";


map<size_t, std::string>	EventsAble::fHashCodes;
std::hash<string>			EventsAble::fHash;

//----------------------------------------------------------------------
EventsAble::EventsAble ():	fMouseSensible(false) { init(); }
EventsAble::~EventsAble ()	{}

//----------------------------------------------------------------------
static string getStringValue(const IMessage* msg, int i) {
	int num; string val;
	if (msg->param (i, num)) {
		stringstream str;
		str << num;
		return str.str();
	}
	if (msg->param (i, val))
		return val;
	return "";
}

//----------------------------------------------------------------------
bool EventsAble::setMidiFilterMsgs(const IMessage* msg, int index, const TMidiFilter& filter)
{
	SIMessageList watchMsg = msg->watchMsg2Msgs (index);
	if (!watchMsg) return false;
	addMidiMsg (filter, watchMsg);
	return true;
}

//----------------------------------------------------------------------
bool EventsAble::endParse(const IMessage* msg, int size, int index, const TMidiFilter& filter)
{
	if (size < index) 			// no more parameter, remove the filter
		delMidiMsg (filter);
	else return setMidiFilterMsgs (msg, index, filter);
	return true;
}

//----------------------------------------------------------------------
bool EventsAble::checkKeyEvent (const IMessage* msg, std::string& key, bool& down)
{
	if (msg->size() == 2) {
		string evt;
		if (!msg->param (0, evt) || !isKeyEvent(evt.c_str())) return false;
		if (!msg->param (1, key)) return false;
		down = (evt == kKeyDownEvent);
		return true;
	}
	return false;
}

//----------------------------------------------------------------------
bool EventsAble::checkMidiEvent (const IMessage* msg, int& data1, int& data2, int& data3)
{
	if (msg->size() == 4) {
		string evt;
		if (msg->param (0, evt) && isMidiEvent(evt.c_str()))
			return (msg->param (1, data1) && msg->param (2, data2) && msg->param (3, data3));
	}
	return false;
}

//----------------------------------------------------------------------
bool EventsAble::parseWatchMidi (const IMessage* msg, bool add)
{
	int n = msg->size();
	TMidiFilter filter;
	int i = 1;
	string evt;
	if (!msg->param (i++, evt)) return false;
	if (evt == kMidiAll) {		// accept any midi input
		return endParse (msg, n, i, filter);
	}

	if (evt == kMidiChan) {
		int chan;
		if (!msg->param (i++, chan)) return false;
		filter.setChan (chan);
		if (!msg->param (i, evt)) return endParse(msg, n, i, filter);
		else i++;
	}
	
	bool keyon = (evt == kMidiKeyon);
	if (keyon || (evt == kMidiKeyoff)) {
		string val = getStringValue(msg, i++);
		if (val.empty()) return false;
		string vel;
		if (msg->param (i, vel) && (vel == kMidiVel)) {
			i += 1;
			string vval = getStringValue(msg, i++);
			if (vval.empty() || !filter.setKey (keyon, val, vval)) return false;
		}
		else if (!filter.setKey (keyon, val)) return false;
		return endParse (msg, n, i, filter);
	}

	else if (evt == kMidiProg) {
		int num;
		if (!msg->param (i++, num) || !filter.setProg (num) ) return false;
		return endParse (msg, n, i, filter);
	}

	else if (evt == kMidiCtrl) {
		int num;
		if (!msg->param (i++, num)) return false;		// get the controler number
		string val = getStringValue(msg, i++);			// get the values
		if (val.empty() || !filter.setCtrl (num, val)) return false;
		return endParse (msg, n, i, filter);
	}
	else {
		ITLErr << "unknown MIDI selector" << evt << ITLEndl;
		return false;		// unknown selector
	}
	return true;
}

//----------------------------------------------------------------------
void EventsAble::setMsg(EventsAble::eventype t, SIMessageList msgs)
{
	fMsgMap.set(fHash(t), msgs);
	if (isMouseEvent(t)) {
		fModified = true;
		if(msgs) {
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
}

//----------------------------------------------------------------------
void EventsAble::addMsg(EventsAble::eventype t, SIMessageList msgs)
{
	size_t hash = fHash(t);
	size_t prevcount = fMsgMap.count(hash);
	fMsgMap.add(hash, msgs);
	if (isMouseEvent(t)) {
		fModified = true;
		if(!fMouseSensible) {
			fMouseSensible = true;
			setMouseEventSensibility(true);
		}
	}
}


//----------------------------------------------------------------------
void EventsAble::reset ()
{ 
	fModified = true;
	fMsgMap.clear();
	fTimeEnterMsgMap.clear();
	fTimeLeaveMsgMap.clear();
	fDurEnterMsgMap.clear();
	fDurLeaveMsgMap.clear();
	fKeyDownMsgMap.clear();
	fKeyUpMsgMap.clear();
	fMidiMsgMap.clear();
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
	m.fKeyDownMsg	= fKeyDownMsgMap;
	m.fKeyUpMsg		= fKeyUpMsgMap;
	m.fMidiMsg		= fMidiMsgMap;
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
		fKeyDownMsgMap	= m.fKeyDownMsg;
		fKeyUpMsgMap	= m.fKeyUpMsg;
		fMidiMsgMap		= m.fMidiMsg;
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
SIMessageList EventsAble::getKeyMessages (const std::string& key, bool down) const
{
	SIMessageList msgs = IMessageList::create();
	const TWatcher<std::string>& map = down ? fKeyDownMsgMap : fKeyUpMsgMap;
	for (auto elt: map) {
		if (acceptKey (elt.first, key))
			msgs->list().push_back (elt.second->list());
	}
	return msgs;
}

//----------------------------------------------------------------------
SIMessageList EventsAble::getMidiMessages (int status, int data1, int data2)
{
	SIMessageList msgs = IMessageList::create();
	TWatcher<TMidiFilter>::iterator i = fMidiMsgMap.begin();
	while (i != fMidiMsgMap.end()) {
		TMidiFilter* filter = (TMidiFilter*)&i->first;
		if (filter->accept (char(status), char(data1), char(data2)))
			msgs->list().push_back (i->second->list());
		i++;
	}
	return msgs;
}

//----------------------------------------------------------------------
bool EventsAble::acceptKey (const std::string& filter, const std::string& key) const
{
	if (filter == "*") return true;
	if (filter == key) return true;
	if (std::regex_match (key, std::regex(filter))) return true;
	return false;
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
SIMessage EventsAble::buildGetMsg (const char * address, const std::string& type, const TMidiFilter& filter, const IMessageList* mlist) const
{
	SIMessage msg = IMessage::create (address, kwatch_GetSetMethod);
	*msg << type;
	const TMidiFilter::TMsgFilter* f = filter.getCurrent();
	if (f == nullptr) {
		if (filter.getChan() < 0)
			*msg << "*";
		else *msg << kMidiChan << filter.getChan();
	}
	else {
		if (filter.getChan() >= 0)
			*msg << kMidiChan << filter.getChan();
		f->print (msg);
	}
	if (mlist) {
		SIMessageList msgs = IMessageList::create();
		*msgs = *mlist;
		*msg << msgs;
	}
	return msg;
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
SIMessage EventsAble::buildGetMsg (const char * address, const string& what, const string& key, const IMessageList* mlist) const
{
	SIMessage msg = IMessage::create (address, kwatch_GetSetMethod);
	*msg << what << key;
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

	for (auto elt: fMsgMap)
		list->list().push_back( buildGetMsg (address, fHashCodes[elt.first], elt.second));

	for (auto elt: fTimeEnterMsgMap)
		list->list().push_back( buildGetMsg (address, kTimeEnterEvent, elt.first, elt.second));

	for (auto elt: fTimeLeaveMsgMap)
		list->list().push_back( buildGetMsg (address, kTimeLeaveEvent, elt.first, elt.second));

	for (auto elt: fDurEnterMsgMap)
		list->list().push_back( buildGetMsg (address, kDurEnterEvent, elt.first, elt.second));

	for (auto elt: fDurLeaveMsgMap)
		list->list().push_back( buildGetMsg (address, kDurLeaveEvent, elt.first, elt.second));

	for (auto elt: fKeyDownMsgMap)
		list->list().push_back( buildGetMsg (address, kKeyDownEvent, elt.first, elt.second));
	for (auto elt: fKeyUpMsgMap)
		list->list().push_back( buildGetMsg (address, kKeyUpEvent, elt.first, elt.second));

	for (auto elt: fMidiMsgMap)
		list->list().push_back( buildGetMsg (address, "midi", elt.first, elt.second));

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
bool EventsAble::isKeyEvent(size_t type)
{
	return	(type == fHash(kKeyDownEvent)) ||
			(type == fHash(kKeyUpEvent));
}

//----------------------------------------------------------------------
bool EventsAble::isMidiEvent(size_t type)
{
	return	(type == fHash(kMidiEvent));
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

		hash (kKeyDownEvent);
		hash (kKeyUpEvent);
		hash (kMidiEvent);

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
