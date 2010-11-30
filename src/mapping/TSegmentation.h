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


#ifndef __TSegmentation__
#define __TSegmentation__

#include <iostream>
#include <sstream>

#include <algorithm>
#include <string>
#include <set>
#include <vector>
//#include "TSegment.h"
#include "smartpointer.h"


namespace inscore
{

/*!
\addtogroup ITLMapping
@{
*/

template<typename T> class TSegmentation;

//--------------------------------------------------------------------------
/*!
	\brief segmentation of a resource	
*/
template<typename T> class TSegmentation : public smartable
{
	T	fResource;
	std::set<T> fSegments;

	public :
		typedef typename std::set<T>						segmentsList;
		typedef typename segmentsList::const_iterator		const_iterator;

		static SMARTP<TSegmentation<T> > create(const T& resource)	{ return new TSegmentation<T>(resource); }

		/// returns the resource associated to the segmentation
		inline const T&	getResource() const							{ return fResource; }
		
		inline const_iterator begin() const							{ return fSegments.begin(); }
		inline const_iterator end() const							{ return fSegments.end(); }

		/// adds a segment when it complies to the segmentation definition
		inline bool	add(const T& segment) { 
				if (check(segment)) {
					fSegments.insert(segment);
					return true;
				}
				return false;
			}

		/// adds a list of segments
		inline bool	add(const std::vector<T>& segments) { 
				for (unsigned int i = 0; i < segments.size(); i++)
					if (!add (segments[i])) return false;
				return true;
			}

		/// adds a list of segments
		inline bool	add(const std::set<T>& segments) { 
				
				typedef typename std::set<T>::const_iterator const_iterator;
				for (const_iterator i = segments.begin(); i != segments.end(); i++)
					if (!add (*i)) return false;
				return true;
			}

		const segmentsList& getSegmentation() const	{ return  fSegments; }

		/*! \brief gives the list of segments that intersect with a segment
			\param s a segment
			\param result on output: the segments that intersect with \c s
		*/
       void intersectWith(const T& s, std::vector<T>& result) const	{ 
			intersectPredicat<T> predicat(s);
			const_iterator i = fSegments.begin(), end = fSegments.end();
			while (i != end) {
				i = find_if (i, end, predicat);
				if (i != end) { 
					result.push_back( *i );
					i++;
				}
			}
		}

		/// checks if a segment is included in the ressource
        inline bool include(const T& s) const						{ return fResource.include(s); }
		/// checks if a location is included in the ressource
        template<typename C> inline bool include(C loc) const		{ return fResource.include(loc); }

		/*!
			\brief retrieves the segment containing the location \c loc
			\return the segment containing the location or an empty segment when no segment match			
		*/
        template<typename C> inline T find(C loc) const	{ 
			if (include(loc)) {
				includePredicat<C> p (loc);
				const_iterator i = std::find_if(fSegments.begin(), fSegments.end(), p );
				if (i != fSegments.end()) return *i;
			}
			return T();
		}

		/// segmentation conversion to string
        operator std::string () const {
			std::ostringstream res;
			res << fResource << " : ( ";
			for (const_iterator i = fSegments.begin(); i != fSegments.end(); i++)
				res << *i << " ";
			res << ")";	
			return res.str();
		}

	protected :
				 TSegmentation(const T& resource)  : fResource(resource) {}
		virtual ~TSegmentation() {}

	inline bool	check(const T& segment) const	{
//		if (segment.empty()) return false;
		if (!include(segment)) return false;
		for (const_iterator i = fSegments.begin(); i != fSegments.end(); i++)
			if ( segment.intersect (*i) ) return false;

//		for (unsigned int i=0; i < fSegments.size(); i++)
//			if ( segment.intersect (fSegments[i]) ) return false;
		return true;
	}

	private:
		/*! \brief a predicate to test location inclusion */
		template <typename C> struct includePredicat {
			C fLoc;
			includePredicat(C loc) : fLoc(loc) {}
			bool operator() (const T& s) { return s.include(fLoc); }
		};
		
		template <typename C> struct intersectPredicat {
			const C	fSegment;
					 intersectPredicat(const T& s) : fSegment(s) {}
			virtual ~intersectPredicat() {}
			virtual bool operator() (const T& s) const		{ return fSegment.intersect( s ); }
		};
};

template<typename T>
std::ostream& operator << (std::ostream& out, const TSegmentation<T>& s) { out << std::string(s); return out; }

/*! @} */

} // end namespoace

#endif
