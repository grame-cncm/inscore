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

#include <iostream>

#include "TimeEventAble.h"
#include "EventsAble.h"
#include "TInterval.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//----------------------------------------------------------------------
void TimeEventAble::handleTimeChange (rational from, rational to) const
{
	for (std::set<RationalInterval>::const_iterator i=fWatchTimeList.begin(); i != fWatchTimeList.end(); i++) {
		if (i->include(from) && !i->include(to)) {			// leaving the time interval
			send (fEventsHandler->getTimeMsgs (EventsAble::kTimeLeave, *i));
		}
		else if (!i->include(from) && i->include(to)) {		// entering the time interval
			send (fEventsHandler->getTimeMsgs (EventsAble::kTimeEnter, *i));
		}				
	}
}

//----------------------------------------------------------------------
void TimeEventAble::handleDurChange (rational from, rational to) const
{
	for (std::set<RationalInterval>::const_iterator i=fWatchDurList.begin(); i != fWatchDurList.end(); i++) {
		if (i->include(from) && !i->include(to)) {			// leaving the duration interval
			send (fEventsHandler->getTimeMsgs (EventsAble::kDurLeave, *i));
		}
		else if (!i->include(from) && i->include(to)) {		// entering the duration interval
			send (fEventsHandler->getTimeMsgs (EventsAble::kDurEnter, *i));
		}				
	}
}

//----------------------------------------------------------------------
void TimeEventAble::send (const std::vector<SEventMessage>& msgs) const
{
	for (unsigned int i=0; i<msgs.size(); i++)
		msgs[i]->send();
}

//----------------------------------------------------------------------
void TimeEventAble::watchInterval (int type, const RationalInterval& interval)
{
	switch (type) {
		case EventsAble::kTimeEnter:
		case EventsAble::kTimeLeave:
			watchTime (interval);
			break;
		case EventsAble::kDurEnter:
		case EventsAble::kDurLeave:
			watchDur (interval);
			break;
	}
}

void TimeEventAble::delInterval	(int type, const RationalInterval& interval)
{
	switch (type) {
		case EventsAble::kTimeEnter:
		case EventsAble::kTimeLeave:
			delTime (interval);
			break;
		case EventsAble::kDurEnter:
		case EventsAble::kDurLeave:
			delDur (interval);
			break;
	}
}

void TimeEventAble::clearList (int type)
{
	switch (type) {
		case EventsAble::kTimeEnter:
		case EventsAble::kTimeLeave:
			clearTime ();
			break;
		case EventsAble::kDurEnter:
		case EventsAble::kDurLeave:
			clearDur ();
			break;
	}
}

//----------------------------------------------------------------------
void TimeEventAble::watchTime(const RationalInterval& interval)	{ fWatchTimeList.insert (interval); }
void TimeEventAble::clearTime()									{ fWatchTimeList.clear(); }
void TimeEventAble::delTime(const RationalInterval& interval)	{ fWatchTimeList.erase (interval); }

//----------------------------------------------------------------------
void TimeEventAble::watchDur(const RationalInterval& interval)	{ fWatchDurList.insert (interval); }
void TimeEventAble::clearDur()									{ fWatchDurList.clear(); }
void TimeEventAble::delDur(const RationalInterval& interval)	{ fWatchDurList.erase (interval); }

} // end namespoace
