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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
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
#include "TMidiFilter.h"
#include "TWatcher.h"

namespace inscore
{

//----------------------------------------------------------------------
class EventsAble
{
	bool	fModified = false;   // a flag for EMCC, active for mouse events  only
	
	bool 	setMidiFilterMsgs(const IMessage* msg, int index, const TMidiFilter& filter);
	bool 	endParse(const IMessage* msg, int size, int index, const TMidiFilter& filter);

	public:
		typedef const char* eventype;
	
				 EventsAble();
		virtual ~EventsAble();

		bool modified() const 		{ return fModified; }
		void cleanup () 			{ fModified = false; }

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
		/// \brief clear the key message list
		void			clearKeyMsg (bool down)									{ if (down) clearKeyDownMsg(); else clearKeyUpMsg(); }
		void			clearKeyDownMsg ()										{ fKeyDownMsgMap.clear(); }
		void			clearKeyUpMsg ()										{ fKeyUpMsgMap.clear(); }
		/// \brief add  a key event handler
		void			addKeyMsg (const std::string& expr, SIMessageList msg, bool down)	{ if (down) addKeyDownMsg(expr, msg); else addKeyUpMsg(expr, msg); }
		void			addKeyDownMsg (const std::string& expr, SIMessageList msg)	{ fKeyDownMsgMap.set (expr, msg); }
		void			addKeyUpMsg (const std::string& expr, SIMessageList msg)	{ fKeyUpMsgMap.set (expr, msg); }
		/// \brief remove  a key event handler
		void			delKeyMsg (const std::string& expr, bool down)				{ if (down) delKeyDownMsg(expr); else delKeyUpMsg(expr); }
		void			delKeyDownMsg (const std::string& expr)						{ fKeyDownMsgMap.set (expr, nullptr); }
		void			delKeyUpMsg (const std::string& expr)						{ fKeyUpMsgMap.set (expr, nullptr); }
		/// \brief clear the midi message list
		void			clearMidiMsg ()												{ fMidiMsgMap.clear(); }
		/// \brief add  a midi event handler
		void			addMidiMsg (const TMidiFilter& filter, SIMessageList msg)	{ fMidiMsgMap.set (filter, msg); }
		/// \brief remove  a midi event handler
		void			delMidiMsg (const TMidiFilter& filter)						{ fMidiMsgMap.set (filter, nullptr); }
		
		bool 			parseWatchMidi (const IMessage* msg, bool add);
		bool 			checkMidiEvent (const IMessage* msg, int& data1, int& data2, int& data3);
		bool 			checkKeyEvent (const IMessage* msg, std::string& key, bool& down);


		virtual void		pushWatch ();		///< push the current watched events and associated msgs on a stack
		virtual bool		popWatch ();		///< restore watched events and associated messages from the stack

		const IMessageList*	getMessages (eventype t) const					{ return fMsgMap.get(fHash(t)); }
		const IMessageList*	getMouseMsgs (eventype t) const					{ return fMsgMap.get(fHash(t)); }
		const IMessageList*	getTimeMsgs (eventype t, const RationalInterval& time) const;
		const size_t		countMouseMsgs (eventype t) const				{ return fMsgMap.count(fHash(t)); }
		SIMessageList		getKeyMessages (const std::string& key, bool down) const;
		SIMessageList		getMidiMessages (int status, int data1, int data2);

		void triggerEvent(eventype t, const bool& delay=false) const		{fMsgMap.trigger(fHash(t), delay);}

		SIMessageList	getWatch (const char* address) const;	///< returns a list of 'watch' messages
        SIMessageList	getStack (const char* address) const;	///< returns a list of the states in the fWatchStack
		void			reset();								///< clear all the messages maps

		static void	init ();
		static bool		isMouseEvent(size_t hashtype);
		static bool		isMouseEvent(eventype t)				{ return isMouseEvent(fHash(t)); }
		static bool 	isKeyEvent(size_t hashtype);
		static bool		isKeyEvent(eventype t)					{ return isKeyEvent (fHash(t)); }
		static bool 	isMidiEvent(size_t type);
		static bool		isMidiEvent(eventype t)					{ return isMidiEvent (fHash(t)); }
		static bool 	isReadyEvent(size_t t);
		static bool 	isReadyEvent(eventype t)				{ return isReadyEvent(fHash(t)); }
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
			TWatcher<std::string>		fKeyDownMsg;
			TWatcher<std::string>		fKeyUpMsg;
			TWatcher<TMidiFilter>		fMidiMsg;
		} EventsMaps;
		std::stack<EventsMaps>	fWatchStack;
		
		TWatcher<size_t>			fMsgMap;
		TWatcher<RationalInterval>	fTimeEnterMsgMap;
		TWatcher<RationalInterval>	fTimeLeaveMsgMap;
		TWatcher<RationalInterval>	fDurEnterMsgMap;
		TWatcher<RationalInterval>	fDurLeaveMsgMap;
		TWatcher<std::string>		fKeyDownMsgMap;
		TWatcher<std::string>		fKeyUpMsgMap;
		TWatcher<TMidiFilter>		fMidiMsgMap;

		SIMessage	buildGetMsg (const char * address, const std::string& type, const SIMessageList&) const;
		SIMessage	buildGetMsg (const char * address, const std::string& type, const RationalInterval&, const IMessageList*) const;
		SIMessage	buildGetMsg (const char * address, const std::string& type, const std::string&, const IMessageList*) const;
		SIMessage	buildGetMsg (const char * address, const std::string& type, const TMidiFilter&, const IMessageList*) const;

		bool acceptKey (const std::string& filter, const std::string& key) const;
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
