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

#include "EventMessage.h"
#include "IMessage.h"
#include "maptypes.h"

namespace inscore
{

//----------------------------------------------------------------------
class EventsAble
{
	public:
		enum eventype { kUnknownEvent=0, 
			kMouseDown, kMouseUp, kMouseDoubleClick, kMouseEnter, kMouseLeave, kMouseMove,
			kFile, kTimeEnter, kTimeLeave, kDurEnter, kDurLeave, kNewElement };
			
				 EventsAble();
		virtual ~EventsAble();
		
		void			setMsg (eventype t, SEventMessage msg);
		void			addMsg (eventype t, SEventMessage msg);

		void			setTimeMsg (eventype t, const RationalInterval& time, SEventMessage msg);
		void			addTimeMsg (eventype t, const RationalInterval& time, SEventMessage msg);
		void			clearTimeMsg (eventype t);

		void			setFileMsg (const std::string& file, SEventMessage msg);
		void			addFileMsg (const std::string& file, SEventMessage msg);

		SIMessageList	getWatch (const char* address) const;
		void			reset();

		void			pushWatch ();		// push the current watched events and associated msgs on a stack
		bool			popWatch ();		// restore watched events and associated messages from the stack

		const std::vector<SEventMessage>&	getMessages (eventype t) const;
		const std::vector<SEventMessage>&	getMouseMsgs (eventype t) const;
		const std::vector<SEventMessage>&	getTimeMsgs (eventype t, const RationalInterval& time) const;
		const std::vector<SEventMessage>&	getFileMsgs (const std::string& file) const;

		static void	init ();
		static eventype	string2type (const std::string& str);
		static const char* type2string (eventype type);

	private:
	typedef std::map<eventype, std::vector<SEventMessage> >			_TMsgMap;
	typedef std::map<RationalInterval, std::vector<SEventMessage> >	_TimeMsgMap;
	typedef std::map<std::string, std::vector<SEventMessage> >		_FileMsgMap;
	typedef struct EventsMaps {
		_TMsgMap	fMsg;
		_TimeMsgMap	fTimeEnterMsg;
		_TimeMsgMap	fTimeLeaveMsg;
		_TimeMsgMap	fDurEnterMsg;
		_TimeMsgMap	fDurLeaveMsg;
		_FileMsgMap fFileMessage;	
	} EventsMaps;
	std::stack<EventsMaps>	fWatchStack;
	
	_TMsgMap	fMsgMap;
	_TimeMsgMap	fTimeEnterMsgMap;
	_TimeMsgMap	fTimeLeaveMsgMap;
	_TimeMsgMap	fDurEnterMsgMap;
	_TimeMsgMap	fDurLeaveMsgMap;
	_FileMsgMap fFileMessageMap;
	
	void		getMsgs (const char * address, const std::string& type, const std::vector<SEventMessage>&, SIMessageList&) const;
	void		getMsgs (const char * address, const std::string& type, const RationalInterval&, const std::vector<SEventMessage>&, SIMessageList&) const;
	void		getMsgs (const char * address, const std::string& type, const std::string&, const std::vector<SEventMessage>&, SIMessageList&) const;
	SIMessage	getMsg (const char * address, const std::string& type, const char* msg, const SEventMessage&) const;
	SIMessage	getMsg (const char * address, const std::string& type, const char* msg, const RationalInterval&, const SEventMessage&) const;
	SIMessage	getMsg (const char * address, const std::string& type, const char* msg, const std::string&, const SEventMessage&) const;
	SIMessage	putMsg (SIMessage& msg, const SEventMessage&) const;

	static std::map<std::string, eventype>	fTypeStr;
};

} // end namespoace

#endif
