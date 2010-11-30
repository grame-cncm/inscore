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

#ifndef __TVirtualRelation__
#define __TVirtualRelation__

#include "TSegment.h"
#include "TRelation.h"
#include "MapTools.h"

namespace INScore
{

/*!
\addtogroup ITLMapping
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief virtual relation between sets

	Virtual relations extend the relation mechanism to segments that are virtually included
	in the segmentation i.e. which bounds (start and end) are included in actual segments of 
	the segmentation. The virtual relation is obtained by linear interpolation.
*/
template<typename T1, typename T2> class TVirtualRelation 
{
	protected:
		typedef typename TRelation<T1, T2>::const_iterator	const_iterator;
		typedef typename std::set<T2>::const_iterator		const_iterator2;
		const TRelation<T1, T2>& fRelation;

	public:
				 TVirtualRelation(const TRelation<T1, T2>& relation) : fRelation(relation) {}
		virtual ~TVirtualRelation() {}

		/*! \brief gives the 'virtual' relations of an object
		
			\param s an object to look for in the relation set
			\return a reference to the relations list
		*/
		virtual std::set<T2> get (const T1& s) const; 

		//--------------------------------------------------------------------------------------------
		virtual void print(std::ostream& out) const {
			for (const_iterator i = fRelation.begin(); i != fRelation.end(); i++) {
				const std::set<T2>& relations = get (i->first);
				out << i->first << " -> ";
				for (const_iterator2 j = relations.begin(); j != relations.end(); j++)
					out << *j << " ";
				out << std::endl;
			}
		}

	protected:

		static void interpolate (const_iterator src, const T1& s, std::set<T2>& outlist) {
			T1 inter = (src->first & s);
			if (inter.size() && s.size()) {
				MapTools::SegmRelation  r = MapTools::relation(src->first, inter);
				for (const_iterator2 j = src->second.begin(); j != src->second.end(); j++) {
					T2 sr = MapTools::related(*j, r);
					outlist.insert (sr);
				}
			}
		}
};

template<typename T1, typename T2>
std::ostream& operator << (std::ostream& out, const TVirtualRelation<T1,T2>& s) { s.print(out); return out; }


template<typename T1, typename T2>
std::set<T2> TVirtualRelation<T1,T2>::get (const T1& s) const 
{ 
	std::set<T2> outlist;
	for (const_iterator i = fRelation.begin(); i != fRelation.end(); i++) {
		if (i->first == s) {			// s  is an existing segment
			for (const_iterator2 j = i->second.begin(); j != i->second.end(); j++)
				outlist.insert (*j);	// inserts s related elements into the output list
		}
		else interpolate (i, s, outlist);
	}
	return outlist;
}

/*! @} */

} // end namespoace

#endif
