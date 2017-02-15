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


#ifndef __TimeEventAble__
#define __TimeEventAble__

#include <set>

#include "rational.h"
#include "maptypes.h"

namespace inscore
{

class EventsAble;
class IMessageList;
struct EventContext;
//----------------------------------------------------------------------
/**
* \brief support for time related events

	The TimeEventAble stores the watched time and duration intervals.
	When it applies, it retrieves the messages associated to a watched interval.
*/
class TimeEventAble
{
	public:
		typedef const char* eventype;
	
				 TimeEventAble(const EventsAble* h) : fEventsHandler(h)	{}
		virtual ~TimeEventAble() {}

		/// \brief handles changes in time
		void handleTimeChange (libmapping::rational from, libmapping::rational to) const;

		/// \brief handles changes in duration
		void handleDurChange  (libmapping::rational from, libmapping::rational to) const;

		/// \brief adds an interval to the watched intervals list
		void watchInterval	(eventype type, const RationalInterval&);

		/// \brief removes an interval from the watched intervals list
		void delInterval	(eventype type, const RationalInterval&);

		/// \brief clear a watched intervals list
		void clearList		(eventype type);

	protected:

		void watchTime	(const RationalInterval&);
		void delTime	(const RationalInterval&);
		void clearTime	();

		void watchDur	(const RationalInterval&);
		void delDur		(const RationalInterval&);
		void clearDur	();

		void eval (const IMessageList* msgs, const EventContext& env) const;

		const EventsAble *			fEventsHandler;
		std::set<RationalInterval>	fWatchTimeList;
		std::set<RationalInterval>	fWatchDurList;
};

} // end namespoace

#endif
