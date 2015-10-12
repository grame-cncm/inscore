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


#ifndef __EventsAble__
#define __EventsAble__

#include <map>
#include <string>
#include <vector>
#include <stack>

#include "IMessage.h"
#include "maptypes.h"
#include "TWatcher.h"

namespace inscore
{

//----------------------------------------------------------------------
class EventsAble
{
	public:
		enum eventype { kUnknownEvent=0, 
			kMouseDown, kMouseUp, kMouseDoubleClick, kMouseEnter, kMouseLeave, kMouseMove,
			kTouchBegin, kTouchEnd, kTouchUpdate,
			kTimeEnter, kTimeLeave, kDurEnter, kDurLeave, kNewElement, kExport, kEndPaint,
			kGFEnter, kGFLeave, kGFActive, kGFIdle, kDelete, kNewData, kSuccess, kError, kCancel };
			
				 EventsAble();
		virtual ~EventsAble();
		
		/// \brief replaces the message list associated to the event t
		void			setMsg (eventype t, SIMessageList msgs)		{ fMsgMap.set(t, msgs); }
		/// \brief adds a message list to the messages associated to the event t
		void			addMsg (eventype t, SIMessageList msgs)		{ fMsgMap.add(t, msgs); }

		/// \brief replaces the message list associated to the time event \c t and the interval \c time
		void			setTimeMsg (eventype t, const RationalInterval& time, SIMessageList msg);
		/// \brief adds a message list to the messages associated to the time event \c t and the interval \c time
		void			addTimeMsg (eventype t, const RationalInterval& time, SIMessageList msg);
		/// \brief clear a time message list
		void			clearTimeMsg (eventype t);

		virtual void		pushWatch ();		///< push the current watched events and associated msgs on a stack
		virtual bool		popWatch ();		///< restore watched events and associated messages from the stack

		const IMessageList*	getMessages (eventype t) const			{ return fMsgMap.get(t); }
		const IMessageList*	getMouseMsgs (eventype t) const			{ return fMsgMap.get(t); }
		const IMessageList*	getTimeMsgs (eventype t, const RationalInterval& time) const;

		void triggerEvent(eventype t, const bool& delay=false) const {fMsgMap.trigger(t,delay);}

		SIMessageList	getWatch (const char* address) const;	///< returns a list of 'watch' messages
        SIMessageList	getStack (const char* address) const;	///< returns a list of the states in the fWatchStack
		void			reset();								///< clear all the messages maps

		static void	init ();
		static eventype	string2type (const std::string& str)		{ return fTypeStr[str]; }
		static const char* type2string (eventype type);

	private:
		typedef TWatcher<eventype>			_TMsgMap;
		typedef TWatcher<RationalInterval>	_TimeMsgMap;
		typedef struct EventsMaps {
			_TMsgMap	fMsg;
			_TimeMsgMap	fTimeEnterMsg;
			_TimeMsgMap	fTimeLeaveMsg;
			_TimeMsgMap	fDurEnterMsg;
			_TimeMsgMap	fDurLeaveMsg;
		} EventsMaps;
		std::stack<EventsMaps>	fWatchStack;
		
		_TMsgMap	fMsgMap;
		_TimeMsgMap	fTimeEnterMsgMap;
		_TimeMsgMap	fTimeLeaveMsgMap;
		_TimeMsgMap	fDurEnterMsgMap;
		_TimeMsgMap	fDurLeaveMsgMap;
		
		SIMessage	buildGetMsg (const char * address, const std::string& type, const SIMessageList&) const;
		SIMessage	buildGetMsg (const char * address, const std::string& type, const RationalInterval&, const IMessageList*) const;

	static std::map<std::string, eventype>	fTypeStr;
	static std::map<eventype, const char*>	fTypeNum;
};

} // end namespoace

#endif
