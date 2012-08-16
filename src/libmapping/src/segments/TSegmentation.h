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


#ifndef __TSegmentation__
#define __TSegmentation__

#include <iostream>
#include <sstream>

#include <algorithm>
#include <string>
#include <set>
#include <vector>
#include "TSegment.h"
#include "smartpointer.h"


namespace libmapping
{

/*
\addtogroup SEGMENTS
@{
*/

template<typename T, unsigned int D> class TSegmentation;

//--------------------------------------------------------------------------
/*!
	\brief segmentation of a resource
	
	A resource segmentation is defined as a set of disjoined segments included in the resource.
	Actually, checking that the segments are included in the resource and disjoined is the client
	responsability: the \c add methods do not check for anything but the \c check , \c include 
	and disjoint methods, are provided to clients.
*/
template<typename T, unsigned int D> class TSegmentation : public smartable
{
	public :
		typedef TSegment<T,D>		SegmentT;
	
	protected :
		SegmentT			fResource;
		std::set<SegmentT>	fSegments;

	public :
		typedef typename std::set<SegmentT>::const_iterator		const_iterator;

		static SMARTP<TSegmentation<T,D> > create()							{ return new TSegmentation<T,D>(); }
		static SMARTP<TSegmentation<T,D> > create(const SegmentT& resource)	{ return new TSegmentation<T,D>(resource); }

		/// returns the resource associated to the segmentation
		inline const SegmentT&	getResource() const			{ return fResource; }

		/// sets the resource associated to the segmentation to the union of the enclosed segments
		inline const SegmentT&	setResource()				{ 
			const_iterator i = fSegments.begin();
			if (i != fSegments.end()) {
				fResource = *i;
				for (++i; i != fSegments.end(); i++) fResource = fResource | *i;
			}
			return fResource; 
		}
		
		inline const_iterator begin() const					{ return fSegments.begin(); }
		inline const_iterator end() const					{ return fSegments.end(); }

		/// adds a segment
		inline void	add(const SegmentT& segment)			{ fSegments.insert(segment); }
		/// adds a list of segments
		inline void	add(const std::vector<SegmentT>& segments)	{ for (unsigned int i = 0; i < segments.size(); i++) add (segments[i]); }
		/// adds a list of segments
		inline void	add(const std::set<SegmentT>& segments)		{ 
				typedef typename std::set<T>::const_iterator const_iterator;
				for (const_iterator i = segments.begin(); i != segments.end(); i++) add (*i);
			}

		/*! \brief gives the list of segments that intersect with a segment
			\param s a segment
			\param result on output: the segments that intersect with \c s
		*/
       void intersectWith(const SegmentT& s, std::vector<SegmentT>& result) const	{ 
			intersectPredicat<SegmentT> predicat(s);
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
        inline bool include(const SegmentT& s) const				{ return fResource.include(s); }
		/// checks if a location is included in the ressource
        template<typename C> inline bool include(C loc) const		{ return fResource.include(loc); }

		/*!
			\brief check if the segment intersect with any existing segment
			\param segment a segment
			\return true when the segment is disjoint, false otherwise			
		*/
		inline bool	disjoint(const SegmentT& segment) const	{
			for (const_iterator i = fSegments.begin(); i != fSegments.end(); i++)
				if ( segment.intersect (*i) ) return false;
			return true;
		}

		/*!
			\brief retrieves the segment containing the location \c loc
			\return the segment containing the location or an empty segment when no segment match			
		*/
        template<typename C> inline SegmentT find(C loc) const	{ 
			if (include(loc)) {
				includePredicat<C> p (loc);
				const_iterator i = std::find_if(fSegments.begin(), fSegments.end(), p );
				if (i != fSegments.end()) return *i;
			}
			return SegmentT();
		}


		/*!
			\brief check a segmentation consistency
			
			Check that all segments are disjoint and included in the segment resource.
			\return true when there is no overlap between segments		
		*/
		bool	check() const	{
			if (fSegments.empty()) return true;
			const_iterator i = fSegments.begin();
			if (!include(*i)) {
				std::cerr << "TSegmentation::check failed: segment " << *i << " not included in " << fResource << std::endl;
				return false;
			}
			const_iterator next = i;
			for (++next; next != fSegments.end(); next++) {
				if ( i->intersect (*next) ) {
					std::cerr << "TSegmentation::check failed with segments " << *i << " and " << *next << std::endl;
					return false;
				}
				i++;
			}
			if (!include(*i)) {
				std::cerr << "TSegmentation::check failed: segment " << *i << " not included in " << fResource << std::endl;
				return false;
			}
			return true;
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
				 TSegmentation() {}
				 TSegmentation(const SegmentT& resource) : fResource(resource) {}
		virtual ~TSegmentation() {}

	private:
		/*! \brief a predicate to test location inclusion */
		template <typename C> struct includePredicat {
			C fLoc;
			includePredicat(C loc) : fLoc(loc) {}
			bool operator() (const SegmentT& s)					{ return s.include(fLoc); }
		};
		
		/*! \brief a predicate to test intersection of a segment with the segmentation */
		template <typename C> struct intersectPredicat {
			const C	fSegment;
					 intersectPredicat(const SegmentT& s) : fSegment(s) {}
			virtual ~intersectPredicat() {}
			virtual bool operator() (const SegmentT& s) const	{ return fSegment.intersect( s ); }
		};
};

template<typename T, unsigned int D>
std::ostream& operator << (std::ostream& out, const SMARTP<TSegmentation<T,D> >& s) { out << std::string(*s); return out; }

/*! @} */

} // end namespoace

#endif
