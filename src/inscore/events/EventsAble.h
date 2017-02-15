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

#include <functional>
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
		typedef const char* eventype;
	
				 EventsAble();
		virtual ~EventsAble();
		
		/// \brief replaces the message list associated to the event t
		void			setMsg (eventype t, SIMessageList msgs);
		/// \brief adds a message list to the messages associated to the event t
		void			addMsg (eventype t, SIMessageList msgs);

		/// \brief replaces the message list associated to the time event \c t and the interval \c time
		void			setTimeMsg (eventype t, const RationalInterval& time, SIMessageList msg);
		/// \brief adds a message list to the messages associated to the time event \c t and the interval \c time
		void			addTimeMsg (eventype t, const RationalInterval& time, SIMessageList msg);
		/// \brief clear a time message list
		void			clearTimeMsg (eventype t);

		virtual void		pushWatch ();		///< push the current watched events and associated msgs on a stack
		virtual bool		popWatch ();		///< restore watched events and associated messages from the stack

		const IMessageList*	getMessages (eventype t) const					{ return fMsgMap.get(fHash(t)); }
		const IMessageList*	getMouseMsgs (eventype t) const					{ return fMsgMap.get(fHash(t)); }
		const IMessageList*	getTimeMsgs (eventype t, const RationalInterval& time) const;

		void triggerEvent(eventype t, const bool& delay=false) const		{fMsgMap.trigger(fHash(t), delay);}

		SIMessageList	getWatch (const char* address) const;	///< returns a list of 'watch' messages
        SIMessageList	getStack (const char* address) const;	///< returns a list of the states in the fWatchStack
		void			reset();								///< clear all the messages maps

		static void	init ();
		static bool		isMouseEvent(size_t hashtype);
		static bool		isMouseEvent(eventype t)				{ return isMouseEvent(fHash(t)); }
		static bool		isTimeEvent(size_t hashtype);
		static bool		isTimeEvent(eventype t)					{ return isTimeEvent(fHash(t)); }
		static bool		isDurEvent(size_t hashtype);
		static bool		isDurEvent(eventype t)					{ return isDurEvent(fHash(t)); }

		// store the event hash code to the hash codes map
		// check for potential collision
		// in case of collision, return false and leave the map unchanged
		static bool		hash(eventype t);

	private:
		typedef struct EventsMaps {
			TWatcher<size_t>			fMsg;
			TWatcher<RationalInterval>	fTimeEnterMsg;
			TWatcher<RationalInterval>	fTimeLeaveMsg;
			TWatcher<RationalInterval>	fDurEnterMsg;
			TWatcher<RationalInterval>	fDurLeaveMsg;
		} EventsMaps;
		std::stack<EventsMaps>	fWatchStack;
		
		TWatcher<size_t>			fMsgMap;
		TWatcher<RationalInterval>	fTimeEnterMsgMap;
		TWatcher<RationalInterval>	fTimeLeaveMsgMap;
		TWatcher<RationalInterval>	fDurEnterMsgMap;
		TWatcher<RationalInterval>	fDurLeaveMsgMap;

		SIMessage	buildGetMsg (const char * address, const std::string& type, const SIMessageList&) const;
		SIMessage	buildGetMsg (const char * address, const std::string& type, const RationalInterval&, const IMessageList*) const;

		bool checkMouseSensibility() const;

	static std::hash<std::string> fHash;
	static std::map<size_t, std::string>	fHashCodes;

	protected:
		 virtual void setMouseEventSensibility(bool) {}
	private:
		bool fMouseSensible;
};

} // end namespoace

#endif
