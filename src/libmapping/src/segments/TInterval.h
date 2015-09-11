/*

  INScore Project - libMapping
  Copyright (C) 2009-2012  Grame

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


#ifndef __TInterval__
#define __TInterval__

#include <algorithm>
#include <iostream>
#include <sstream>
#include <string>

#include "lmtools.h"

#ifdef WIN32
#ifdef near
#undef near
#endif
#endif

namespace libmapping
{


/*!
\addtogroup SEGMENTS Segmentations
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief intervals base class.
*/
template<typename T> class TInterval
{
	protected :
		T	fFirst;
		T	fSecond;
		
	public :
				 TInterval()						: fFirst(0), fSecond(0) {}
				 TInterval(T a)						: fFirst(a), fSecond(a) {}
				 TInterval(T a, T b)				: fFirst(std::min(a,b)), fSecond(std::max(a,b)) {}
				 TInterval(const TInterval<T>& i)	: fFirst(i.first()), fSecond(i.second()) {}
		template<typename C> TInterval(const TInterval<C>& i): fFirst(T(i.first())), fSecond(T(i.second())) {}
		virtual ~TInterval() {}

		inline const T& first() const			{ return fFirst; }
		inline const T& second() const			{ return fSecond; }

        /// equality
		inline bool operator == (const TInterval<T>& s) const { return (fFirst == s.first()) && (fSecond == s.second()); }
        /// approximate equality (for float intervals)
		inline bool eq (const TInterval<T>& s) const		  { return (fFirst == s.first()) && (fSecond == s.second()); }
		inline bool near(const TInterval<T>& s) const		  { return near::check(fFirst, s.first()) && near::check(fSecond, s.second()); }
		inline bool operator != (const TInterval<T>& s) const { return !( (*this)==s ); }
		inline TInterval<T> operator + (T val) const		  { return TInterval<T>(fFirst+val, fSecond+val); }

        /// interval size
		inline T size() const									{ return fSecond - fFirst; }
        /// interval center
		inline T center() const									{ return (fFirst + fSecond)/2; }
        /// empty property of intervals
		inline bool empty() const								{ return size() == T(0); }

        /// order relationship between intervals
		inline bool operator <	(const TInterval<T>& s) const	
				{ return (fFirst < s.first()) || ((fFirst == s.first()) && (fSecond < s.second())); }

		/// inclusion relationship between intervals
        inline bool include(const TInterval<T>& s) const		{ return (*this & s) == s; }

		/// inclusion relationship between a interval and a location
		inline bool include(const T& loc) const					{ return (fFirst <= loc) && (fSecond > loc); }
		
		/// intervals resizing
		inline TInterval<T> resize(float ca, float cb) const	{ 
			T w ( size() );
			return TInterval<T> (first() + T(w * ca), first() + T(w * cb));
		}

		/*!
			\brief intervals union
			
			Union is restricted to convex sets and gives an interval as output. 
			\param s the interval to merge
			\param epsilon tolerance for the gap between intervals
		*/
		inline TInterval<T> merge (const TInterval<T>& s, T epsilon = T(0)) const { 
			T gap = (fSecond < s.first()) ?  s.first() - fSecond : fSecond - s.first();
			if (gap > epsilon)	return TInterval<T>(0,0);
			return TInterval<T>(std::min(fFirst, s.first()), std::max(fSecond, s.second()));
		}

		/// \brief check intersection between intervals
		inline bool intersect(const TInterval<T>& s) const		{ return (*this == s) || !((*this) & s).empty(); }

		/// \brief intersection between intervals
		inline TInterval<T> operator & (const TInterval<T>& s) const { 
			T left = std::max(fFirst, s.first());
			T right = std::min(fSecond, s.second());
			return TInterval<T>(left, std::max(left, right));
		}

		/// \brief standard union of intervals
		inline TInterval<T> operator | (const TInterval<T>& s) const { 
			return TInterval<T>(std::min(fFirst, s.first()), std::max(fSecond, s.second()));
		}

		/// interval conversion to string
        operator std::string () const {
			std::ostringstream res;
			res << "[" << fFirst << ", " << fSecond << "[";
			return res.str();
		}
};

template<typename T>
std::ostream& operator << (std::ostream& out, const TInterval<T>& s) { out << std::string(s); return out; }

/*! @} */

} // end namespoace

#endif
