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

namespace inscore
{

class EventsAble;
//--------------------------------------------------------------------------
/*!
	\brief an object position data with message handlers.
*/
class IDate : public TimeEventAble
{
		/// \brief moves the date according to the tempo
		void			move () const;
		/// \brief an abstract method to get the object osc address
		virtual std::string getOSCAddress() const = 0;

	protected:
		libmapping::rational fDate;					///< the object date
		libmapping::rational fDuration;				///< the object duration
		float				 fTempo;				///< the object tempo

		bool	fDateChanged;
		bool	fDurationChanged;

	protected:
				 IDate(const EventsAble*);
		virtual ~IDate();
	
	public:	
		/// \brief returns the object date
		virtual libmapping::rational getDate () const;
		/// \brief returns the object duration
		virtual libmapping::rational getDuration () const		{ return fDuration; }

		/// \brief returns the object modification state
		virtual bool	modified () const			{ return fDateChanged || fDurationChanged; }
		virtual bool	dateModified () const		{ return fDateChanged; }
		virtual bool	durationModified () const	{ return fDurationChanged; }

		/// \brief cleanup stuff
		virtual void	cleanup ();
		/// \brief clock handling
		virtual void	clock()			{ addDate ( libmapping::rational(1, 96) ); }
		/// \brief clock applied to duration
		virtual void	durclock()		{ addDuration ( libmapping::rational(1, 96) ); }

		virtual void	print (std::ostream& out) const;

		/// \brief sets the object date \param date a date expressed as a rational
		virtual void	setDate (const libmapping::rational& date);
		/// \brief sets the object duration \param dur a duration expressed as a rational
		virtual void	setDuration (const libmapping::rational& dur);
		/// \brief sets the object date \param date a date expressed as a rational
		virtual void	setTempo (float tempo);
		/// \brief moves the date
		virtual void	addDate (const libmapping::rational& date)		{ setDate( libmapping::rational(double(fDate) + double(date))); }
		/// \brief moves the duration
		virtual void	addDuration (const libmapping::rational& dur)	{ fDuration += dur; fDurationChanged = true; }
		/// \brief moves the tempo
		virtual void	addTempo (int dt)								{ fTempo += dt; }
};


/*! @} */

} // end namespoace

#endif
