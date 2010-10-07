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

#ifndef __IDate__
#define __IDate__

#include <map>
#include <iostream>

#include "IMessageHandlers.h"
#include "TimeEventAble.h"
#include "rational.h"

namespace interlude
{

class EventsAble;
//--------------------------------------------------------------------------
/*!
	\brief an object position data with message handlers.
*/
class IDate : public TimeEventAble
{
	protected:
		rational fDate;					///< the object date
		rational fDuration;				///< the object duration
	protected:
		bool	fDateChanged;
		bool	fDurationChanged;

	protected:
				 IDate(const EventsAble*);
		virtual ~IDate() {}
	
	public:	
		/// \brief returns the object date
		virtual rational getDate () const			{ return fDate; }
		/// \brief returns the object duration
		virtual rational getDuration () const		{ return fDuration; }

		/// \brief returns the object modification state
		virtual bool	modified () const			{ return fDateChanged || fDurationChanged; }
		virtual bool	dateModified () const		{ return fDateChanged; }
		virtual bool	durationModified () const	{ return fDurationChanged; }

		/// \brief cleanup stuff
		virtual void	cleanup ();
		/// \brief clock handling
		virtual void	clock()			{ addDate ( rational(1, 96) ); }
		/// \brief clock applied to duration
		virtual void	durclock()		{ addDuration ( rational(1, 96) ); }

		virtual void	print (std::ostream& out) const;

		/// \brief sets the object date \param date a date expressed as a rational
		virtual void	setDate (const rational& date)		{ handleTimChange(fDate, date); fDate = date;  fDateChanged = true; }
		/// \brief sets the object duration \param dur a duration expressed as a rational
		virtual void	setDuration (const rational& dur)	{  fDuration = dur;  fDurationChanged = true;  }
		/// \brief moves the date
		virtual void	addDate (const rational& date)		{ setDate(fDate + date); }
		/// \brief moves the duration
		virtual void	addDuration (const rational& dur)	{ fDuration += dur; fDurationChanged = true; }
};


/*! @} */

} // end namespoace

#endif
