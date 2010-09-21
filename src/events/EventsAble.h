/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __EventsAble__
#define __EventsAble__

#include <map>
#include <string>
#include <vector>

#include "EventMessage.h"
#include "maptypes.h"

namespace interlude
{

//----------------------------------------------------------------------
class EventsAble
{
	public:
		enum eventype { kUnknownEvent=0, 
			kMouseDown, kMouseUp, kMouseDoubleClick, kMouseEnter, kMouseLeave,
			kFile, kTimeEnter, kTimeLeave };
			
				 EventsAble();
		virtual ~EventsAble();
		
		void					setMsg (eventype t, SEventMessage msg);
		void					addMsg (eventype t, SEventMessage msg);

		void					setTimeMsg (eventype t, const RationalInterval& time, SEventMessage msg);
		void					addTimeMsg (eventype t, const RationalInterval& time, SEventMessage msg);
		void					clearTimeMsg (eventype t);

		void					setFileMsg (const std::string& file, SEventMessage msg);
		void					addFileMsg (const std::string& file, SEventMessage msg);

		const std::vector<SEventMessage>&	getMsgs (eventype t) const;
		const std::vector<SEventMessage>&	getTimeMsgs (eventype t, const RationalInterval& time) const;
		const std::vector<SEventMessage>&	getFileMsgs (const std::string& file) const;

	static eventype	string2type (const std::string& str);
	static void	init ();

	private:
	typedef std::map<eventype, std::vector<SEventMessage> >			_TMsgMap;
	typedef std::map<RationalInterval, std::vector<SEventMessage> >	_TimeMsgMap;
	typedef std::map<std::string, std::vector<SEventMessage> >		_FileMsgMap;
	_TMsgMap	fMsgMap;
	_TimeMsgMap	fTimeEnterMsgMap;
	_TimeMsgMap	fTimeLeaveMsgMap;
	_FileMsgMap fFileMessageMap;

	static std::map<std::string, eventype>	fTypeStr;
};

} // end namespoace

#endif
