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

#include "IDate.h"
#include "EventsAble.h"
#include "IAppl.h"
#include "IMessage.h"

#include <iostream>

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
// IDate implementation
//--------------------------------------------------------------------------
IDate::IDate(const EventsAble* h)
	: TimeEventAble(h), fDate(0,1), fDuration(1,1), fTempo(0), fPendingMove(false), fDateChanged(true), fDurationChanged(true) {}
//--------------------------------------------------------------------------
IDate::~IDate()		{}

//--------------------------------------------------------------------------
void IDate::cleanup ()
{ 
	fDateChanged = fDurationChanged = fPendingMove = false;
}

//--------------------------------------------------------------------------
void IDate::setDate (const rational& date)
{ 
	if (date.getDenominator() == 0) return;
	if (fDate != date) {
		handleTimeChange(fDate, date);
		fDate = date;
		fDateChanged = true;
	}
	if (fTempo && !fPendingMove) {
		fPendingMove = true;
		move();
	}
}

//--------------------------------------------------------------------------
void IDate::move () const
{ 
	rational dd ( int(IAppl::getRealRate() * fTempo), 60000 * 4);
	dd.rationalize();
	SIMessage msg = IMessage::create(getOSCAddress(), kddate_SetMethod);
	msg->add(int(dd.getNumerator()));
	msg->add(int(dd.getDenominator()));
	msg->send(true);
}

//--------------------------------------------------------------------------
void IDate::setTempo (int tempo)
{ 
	fTempo = tempo;
	if (fTempo) {
		fPendingMove = true;
		move();
	}
}

//--------------------------------------------------------------------------
void IDate::setDuration (const rational& dur)
{  
	if (dur.getDenominator() == 0) return;
	if (fDuration != dur) {
		handleDurChange(fDuration, dur);
		fDuration = dur;
		fDurationChanged = true;
	}
}

//--------------------------------------------------------------------------
// debugging facilities
//--------------------------------------------------------------------------
void IDate::print (ostream& out) const
{
	out << "  date: " << getDate() << " duration: " << getDuration() << endl;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const IDate& o)
{
	o.print(out);
	return out;
}

}
