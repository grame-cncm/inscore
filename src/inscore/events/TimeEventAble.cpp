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
#include "TMessageEvaluator.h"
#include "TInterval.h"
#include "IObject.h"
#include "Events.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//----------------------------------------------------------------------
void TimeEventAble::eval (const IMessageList* msgs, const EventContext& env) const
{
	if (msgs && msgs->list().size()) {
		TMessageEvaluator me;
		SIMessageList evaluated = me.eval (msgs, env);
		evaluated->send();
	}
}

//----------------------------------------------------------------------
void TimeEventAble::handleTimeChange (rational from, rational to) const
{
	TMessageEvaluator me;
	EventContext env (to, dynamic_cast<const IObject*>(this));
	for (std::set<RationalInterval>::const_iterator i=fWatchTimeList.begin(); i != fWatchTimeList.end(); i++) {
		if (i->include(from) && !i->include(to)) {			// leaving the time interval
			eval (fEventsHandler->getTimeMsgs (kTimeLeaveEvent, *i), env);
		}
		else if (!i->include(from) && i->include(to)) {		// entering the time interval
			eval (fEventsHandler->getTimeMsgs (kTimeEnterEvent, *i), env);
		}
	}
}

//----------------------------------------------------------------------
void TimeEventAble::handleDurChange (rational from, rational to) const
{
	TMessageEvaluator me;
	EventContext env (to, dynamic_cast<const IObject*>(this));
	for (std::set<RationalInterval>::const_iterator i=fWatchDurList.begin(); i != fWatchDurList.end(); i++) {
		if (i->include(from) && !i->include(to)) {			// leaving the duration interval
			eval (fEventsHandler->getTimeMsgs (kDurLeaveEvent, *i), env);
		}
		else if (!i->include(from) && i->include(to)) {		// entering the duration interval
			eval (fEventsHandler->getTimeMsgs (kDurEnterEvent, *i), env);
		}
	}
}

//----------------------------------------------------------------------
void TimeEventAble::watchInterval (eventype type, const RationalInterval& interval)
{
	if (EventsAble::isDurEvent (type))
		watchDur (interval);
	else
		watchTime (interval);
}

void TimeEventAble::delInterval	(eventype type, const RationalInterval& interval)
{
	if (EventsAble::isDurEvent (type))
		delDur (interval);
	else
		delTime (interval);
}

void TimeEventAble::clearList (eventype type)
{
	if (EventsAble::isDurEvent (type))
		clearDur ();
	else
		clearTime ();
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
