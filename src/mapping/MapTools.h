/*

  INScore Project
  Copyright (C) 2010  Grame

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


#ifndef __MapTools__
#define __MapTools__

#include <vector>
#include <set>

#include "rational.h"
#include "maptypes.h"
#include "TInterval.h"
#include "TSegment.h"
#include "TSegmentation.h"
#include "TMapping.h"

namespace inscore
{

/*!
\addtogroup ITLMapping Ressources mapping
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief tools for intervals and segments
*/
class MapTools
{
	public :

		//--------------------------------------------------------------------------------
		// location relative position to intervals
		//--------------------------------------------------------------------------------
		/*!
			\brief gives the relative position of a location in an interval
			\param loc a location expressed in the interval coordinates
			\param i a non empty interval
			\return a double value in the interval [0, 1] when the location is included in the interval
			\warning it's the caller responsibility to check for empty intervals
		*/
		template <typename T> static libmapping::rational relativepos (const T& loc, const libmapping::TInterval<T>& i)				
											{ return libmapping::rational(loc - i.first(), i.size()); }

		//--------------------------------------------------------------------------------
		// segments sets union
		//--------------------------------------------------------------------------------
		template <typename T> static std::set<T> merge (const std::set<T>& s1, const std::set<T>& s2 )
		{
			std::set<T> outset;
			if (s1.size() != s2.size()) return outset;

			typedef typename std::set<T>::const_iterator const_iterator;
			const_iterator i1 = s1.begin(), i2 = s2.begin();
			while (i1 != s1.end()) {
				T  inter = *i1 & *i2;
				T  u = i1->merge(*i2, 0.00001);
				if (u.empty() || inter.size()) {
					outset.clear();
					break;
				}
				outset.insert (u);
				i1++; i2++;
			}
			return outset;
		}

		//--------------------------------------------------------------------------------
		// time to time mapping reduction i.e. merge segments when possible
		//--------------------------------------------------------------------------------
		static SRelativeTime2RelativeTimeMapping reduce (const SRelativeTime2RelativeTimeMapping& map)
		{
			SRelativeTime2RelativeTimeMapping outmap = RelativeTime2RelativeTimeMapping::create();
			const RelativeTime2RelativeTimeRelation& rel = map->direct();
			typedef RelativeTime2RelativeTimeRelation::const_iterator const_iterator;

			RelativeTimeSegment seg;
			std::set<RelativeTimeSegment> related;
			for (const_iterator i = rel.begin(); i != rel.end(); i++) {
				if (!related.size()) {		// first time (just entering the loop)
					seg = i->first;
					related = i->second;
				}
				else {
					RelativeTimeSegment u1 = seg.merge(i->first);
					std::set<RelativeTimeSegment> u2 = MapTools::merge (related, i->second);
					if (u1.empty() || !u2.size()) {
						outmap->add (seg, related);
						seg = i->first;
						related = i->second;
					}
					else {
						seg = u1;
						related = u2;
					}
				}
			}
			if (related.size())
				outmap->add (seg, related);
			return outmap;
		}
		
		template <typename T, unsigned int D>
		RelativeTimeSegment static find (const libmapping::rational& date, const libmapping::TRelation<libmapping::rational,1,T,D>& rel)
			{
				typedef typename libmapping::TRelation<libmapping::rational,1,T,D>::const_iterator const_iterator;
				for (const_iterator i = rel.begin(); i != rel.end(); i++)
					if ( i->first.interval().include(date) ) return i->first;
				return RelativeTimeSegment (libmapping::rational(0), libmapping::rational(0));
			}
};


/*! @} */

} // end namespoace

#endif
