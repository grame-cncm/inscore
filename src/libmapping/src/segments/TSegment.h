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


#ifndef __TSegment__
#define __TSegment__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "TInterval.h"


namespace libmapping
{

/*!
\addtogroup SEGMENTS Segmentations
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief segments base class.
*/
template<typename T, unsigned int D> class TSegment {};

//--------------------------------------------------------------------------
/*!
	\brief one dimension segment
*/
template<typename T> class TSegment<T, 1>
{
	protected :
		TInterval<T> fInterval;
	
	public :
				 TSegment () {}
				 TSegment (T a)						: fInterval(a,a) {}
				 TSegment (T a, T b)				: fInterval(a,b) {}
				 TSegment (const TInterval<T>& i)	: fInterval (i) {}
		virtual ~TSegment() {}

       /// return the segment interval
		inline TInterval<T> interval() const			{ return fInterval; }
       /// return the segment start value
		inline T start() const							{ return fInterval.first(); }
       /// return the segment end value
		inline T end() const							{ return fInterval.second(); }
       /// return the segment dimension
		inline unsigned int dimension() const			{ return 1; }
       /// return the segment size
		inline T size() const							{ return fInterval.size(); }

        /// comparison operator, necessary to build relations between segments
		inline bool operator <	(const TSegment<T,1>& s) const	{ return  fInterval < s.interval();  }
        /// segments == operator
		inline bool operator== (const TSegment<T,1>& s) const	{ return interval() == s.interval(); }
        /// segments != operator
		inline bool operator!= (const TSegment<T,1>& s) const	{ return interval() != s.interval(); }
		/// empty property of a segment
		inline bool empty() const								{ return size() == T(0); }

		/// inclusion relationship between a segment and a location
		inline bool include(const T& loc) const					{ return fInterval.include(loc); }
		/// inclusion relationship between segments
		inline bool include(const TSegment& s) const			{ return fInterval.include(s.interval()); }
		/// intersection relationship between segments
		inline bool intersect(const TSegment<T,1>& s) const		{ return fInterval.intersect (s.interval()); }

		/// intersection between segments
		inline TSegment<T,1> operator & (const TSegment<T,1>& s) const	{ return TSegment<T,1>( fInterval & s.interval()); }

		/// union of segments
		inline TSegment<T,1> operator | (const TSegment<T,1>& s) const	{ return TSegment<T,1>( fInterval | s.interval()); }

		/*!
			\brief segments merge
			
			merge is restricted to convex sets and gives a segment as output. 
			\param s the segment to merge
			\param epsilon tolerance for the gap between segments
		*/
		inline TSegment<T,1> merge (const TSegment<T,1>& s, T epsilon = T(0)) const
								{ return TSegment<T,1>( fInterval.merge(s.interval(), epsilon)); }

		/// segment conversion to string
        virtual operator std::string () const {
			std::ostringstream res;
			res << "( " << std::string(fInterval) << " )";
			return res.str();			
		}
};

//--------------------------------------------------------------------------
/*!
	\brief two dimensions segment
*/
template<typename T> class TSegment<T, 2>
{
	protected :
		TInterval<T> fXInterval;
		TInterval<T> fYInterval;
	
	public :
				 TSegment ()	{}
				 TSegment (T x1, T y1, T x2, T y2)							: fXInterval(x1, x2), fYInterval(y1,y2) {}
				 TSegment (const TInterval<T>& i)							: fXInterval(i), fYInterval(i) {}
				 TSegment (const TInterval<T>& x, const TInterval<T>& y)	: fXInterval(x), fYInterval(y) {}
		virtual ~TSegment() {}

       /// return the segment interval on the x dimension
		inline const TInterval<T>& xinterval() const		{ return fXInterval; }
       /// return the segment interval on the x dimension
	   /// provided for compatibility with 1D segments
	   /// defines also a default dimension
		inline const TInterval<T>& interval() const			{ return fXInterval; } 
       /// return the segment interval on the y dimension
		inline const TInterval<T>& yinterval() const		{ return fYInterval; }
       /// return the segment dimension
		inline unsigned int dimension() const				{ return 2; }
       /// return the segment size
		inline T size() const								{ return xinterval().size() * yinterval().size(); }
		/// empty property of a segment
		inline bool empty() const							{ return size() == T(0); }

        /// comparison operator, necessary to build relations between segments
		inline bool operator <	(const TSegment<T,2>& s) const	{ 
			return	(yinterval().first() < s.yinterval().first()) || 
					((yinterval().first() == s.yinterval().first()) && (xinterval() < s.xinterval())); 
		}

		/// inclusion relationship between a segment and a location
		inline bool include(T x, T y) const						{ return xinterval().include(x) && yinterval().include(y); }
		/// inclusion relationship between segments
		inline bool include(const TSegment<T, 2>& s) const		{ return  xinterval().include(s.xinterval()) && yinterval().include(s.yinterval()); }
		/// intersection relationship between segments
		inline bool intersect(const TSegment<T, 2>& s) const	{  return xinterval().intersect(s.xinterval()) && yinterval().intersect(s.yinterval()); }

		/*!
			\brief segments merge on x axis
			
			\param s the segment to merge
			\param epsilon tolerance for the gap between segments
		*/
		inline TSegment<T,2> xmerge (const TSegment<T,2>& s, T epsilon = T(0)) const
								{ return (yinterval() == s.yinterval())
									? TSegment<T,2>( xinterval().merge(s.xinterval(), epsilon), yinterval())
									: TSegment<T,2>( TInterval<T>(), yinterval()); }

		/*!
			\brief segments merge on y axis
			
			\param s the segment to merge
			\param epsilon tolerance for the gap between segments
		*/
		inline TSegment<T,2> ymerge (const TSegment<T,2>& s, T epsilon = T(0)) const
								{ return (xinterval() == s.xinterval())
									? TSegment<T,2>( yinterval().merge(s.yinterval(), epsilon), xinterval())
									: TSegment<T,2>( yinterval(), TInterval<T>()); }

        /// segments == operator
		inline bool operator== (const TSegment<T, 2>& s) const	{ return (xinterval() == s.xinterval()) && (yinterval() == s.yinterval()); }
		inline bool operator!= (const TSegment<T, 2>& s) const	{ return (xinterval() != s.xinterval()) || (yinterval() != s.yinterval()); }

		/// intersection between segments
		inline TSegment<T, 2> operator & (const TSegment<T, 2>& s) const	{ 
			return TSegment<T, 2>(xinterval() & s.xinterval(), yinterval() & s.yinterval());
		}

		/// union of segments
		inline TSegment<T,2> operator | (const TSegment<T,2>& s) const		{ 
			return TSegment<T,2>(xinterval() | s.xinterval(), yinterval() | s.yinterval()); 
		}

       /// return the segment left coordinate
		inline T left() const								{ return xinterval().first(); }
       /// return the segment top coordinate
		inline T top() const								{ return yinterval().first(); }
       /// return the segment right coordinate
		inline T right() const								{ return xinterval().second(); }
       /// return the segment bottom coordinate
		inline T bottom() const								{ return yinterval().second(); }

		/// segment conversion to string
        virtual operator std::string () const {
			std::ostringstream res;
			res << "( " << std::string(xinterval()) << " " << std::string(yinterval()) << " )";
			return res.str();			
		}
};


template <typename T, unsigned int D>
std::ostream& operator << (std::ostream& out, const TSegment<T,D>& s) { out << std::string(s); return out; }


/*! @} */

} // end namespoace

#endif
