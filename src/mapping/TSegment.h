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


#ifndef __TSegment__
#define __TSegment__

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include "TInterval.h"


namespace inscore
{

/*!
\addtogroup ITLMapping Ressources mapping
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
		typedef typename std::pair<float,float> Relation;

				 TSegment ()						: fInterval(0)   {}
				 TSegment (T a)						: fInterval(a,a) {}
				 TSegment (T a, T b)				: fInterval(a,b) {}
				 TSegment (const TInterval<T>& i)	: fInterval(i) {}
		virtual ~TSegment() {}

		inline const TInterval<T>& interval() const			{ return fInterval; }
		inline T start() const								{ return fInterval.first(); }
		inline T end() const								{ return fInterval.second(); }

       /// a segment size
		inline unsigned int dimension() const				{ return 1; }

       /// a segment size
		inline T size() const								{ return fInterval.size(); }

        /// empty property of segments
		inline bool empty() const							{ return size() == T(0); }

        /// arbitrary comparison operator, necessary to build relations between segments
		inline bool operator <	(const TSegment<T,1>& s) const	{ return interval() < s.interval(); }

		/// inclusion relationship between a segment and a location
		inline bool include(const T& loc) const				{ return fInterval.include(loc); }

		/// inclusion relationship between segments
		inline bool include(const TSegment& s) const		{ return ((*this) & s) == s; }

		/// inclusion relationship between segments
		inline bool intersect(const TSegment& s) const		{ TSegment<T,1> inter = (*this) & s; return !inter.empty() || (inter == *this) || (inter == s); }

        /// segments == operator
		inline bool operator== (const TSegment<T,1>& s) const		{ return interval() == s.interval(); }
		inline bool operator!= (const TSegment<T,1>& s) const		{ return interval() != s.interval(); }
		
		inline TSegment<T,1> unite (const TSegment<T,1>& s, T epsilon = T(0)) const	{ 
			return TSegment<T,1>( fInterval.unite(s.interval(), epsilon) );
		}

		/// intersection between segments
		inline TSegment<T,1> operator & (const TSegment<T,1>& s) const	{ 
			return TSegment<T,1>( fInterval & s.interval()) ;
		}

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
		typedef typename std::vector<std::pair<float,float> > Relation;

				 TSegment ()												: fXInterval(T(0)), fYInterval(T(0)) {}
				 TSegment (T x1, T y1, T x2, T y2)							: fXInterval(x1, x2), fYInterval(y1,y2) {}
				 TSegment (const TInterval<T>& i)							: fXInterval(i), fYInterval(i) {}
				 TSegment (const TInterval<T>& x, const TInterval<T>& y)	: fXInterval(x), fYInterval(y) {}
		virtual ~TSegment() {}

		inline const TInterval<T>& xinterval() const		{ return fXInterval; }
		inline const TInterval<T>& yinterval() const		{ return fYInterval; }

		inline std::pair<T,T> start() const					{ return std::pair<T,T>(xinterval().first(), yinterval().first()); }
		inline std::pair<T,T> end() const					{ return std::pair<T,T>(xinterval().second(), yinterval().second()); }

       /// a segment size
		inline unsigned int dimension() const				{ return 2; }

       /// a segment size
		inline T size() const								{ return fXInterval.size() * fYInterval.size(); }

        /// empty property of segments
		inline bool empty() const							{ return size() == T(0); }

        /// arbitrary comparison operator, necessary to build relations between segments
		inline bool operator <	(const TSegment<T,2>& s) const	{ 
			return	(yinterval().first() < s.yinterval().first()) || 
					((yinterval().first() == s.yinterval().first()) && (xinterval() < s.xinterval())); 
		}

		/// inclusion relationship between a segment and a location
		inline bool include(const std::pair<T,T>& location) const	{ return xinterval().include(location.first) && yinterval().include(location.second); }

		/// inclusion relationship between segments
		inline bool include(const TSegment<T, 2>& s) const		{ return ((*this) & s) == s; }

		/// intersection relationship between segments
		inline bool intersect(const TSegment<T, 2>& s) const	{  TSegment<T, 2> inter = *this & s; return !inter.empty() || (inter == *this) || (inter == s); }

        /// segments == operator
		inline bool operator== (const TSegment<T, 2>& s) const { return (xinterval() == s.xinterval()) && (yinterval() == s.yinterval()); }
		inline bool operator!= (const TSegment<T, 2>& s) const { return (xinterval() != s.xinterval()) || (yinterval() != s.yinterval()); }
		
		/// segments union
		inline TSegment<T, 2> unite (const TSegment<T, 2>& s, T epsilon = T(0)) const	{ 
			if (yinterval().near (s.yinterval()) ) 
				return TSegment<T, 2>(xinterval().unite(s.xinterval(), epsilon), yinterval());
			return TSegment<T, 2>(TInterval<T>(0,0), TInterval<T>(0,0));
		}

		/// intersection between segments
		inline TSegment<T, 2> operator & (const TSegment<T, 2>& s) const	{ 
			return TSegment<T, 2>(xinterval() & s.xinterval(), yinterval() & s.yinterval());
		}

		/// segment conversion to string
        virtual operator std::string () const {
			std::ostringstream res;
			res << "( " << std::string(xinterval()) << ", " << std::string(yinterval()) << " )";
			return res.str();			
		}
};

template <typename T, unsigned int D>
std::ostream& operator << (std::ostream& out, const TSegment<T,D>& s) { out << std::string(s); return out; }


/*! @} */

} // end namespoace

#endif
