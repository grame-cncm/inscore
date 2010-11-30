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

using namespace std;

namespace INScore
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
const vector<SEventMessage>& EventsAble::getMsgs (eventype t) const
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
void EventsAble::init ()
{
	if (!fTypeStr.size()) {
		fTypeStr["mouseDown"]	= kMouseDown;
		fTypeStr["mouseUp"]		= kMouseUp;
		fTypeStr["mouseEnter"]	= kMouseEnter;
		fTypeStr["mouseLeave"]	= kMouseLeave;
		fTypeStr["doubleClick"]	= kMouseDoubleClick;
		fTypeStr["file"]		= kFile;
		fTypeStr["timeEnter"]	= kTimeEnter;
		fTypeStr["timeLeave"]	= kTimeLeave;
	}
}

} // end namespoace
