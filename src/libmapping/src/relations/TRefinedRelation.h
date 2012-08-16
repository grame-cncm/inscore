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


#ifndef __TRefinedMapping__
#define __TRefinedMapping__

#include "TRelation.h"
#include "TRefinement.h"
#include "TVariety.h"

namespace libmapping
{

/*!
\addtogroup Relations
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief refined relations support
*/
template<typename T1, unsigned int D1, typename T2, unsigned int D2> 
class TRefinedRelation : public TRelation<T1,D1,T2,D2>
{
	protected:
		typedef TRelation<T1,D1,T2,D2>			rtype;
		typedef SMARTP<TSegmentation<T1,D1> >	segmtype1;
		typedef typename std::set<TSegment<T1,D1> >::const_iterator	const_iterator;
		typedef typename std::set<TSegment<T2,D2> >::const_iterator	const_iterator2;
	
	public:
				 /*! \brief The constructor builds a refined relation
				 
					\param m a relation which segmentation is for refinement
					\param r a segmentation used for refinement
					
					The refined relation is the relation computed from the intersection of the relation segmentation
					and the segmentation given as parameter. A linear interpolation variety function is used to compute
					the relation.
				 */
				 TRefinedRelation (const rtype& m, const segmtype1& r) {
					// first we get the primary segmentation of the relation
					segmtype1 s = m.getPrimarySet();
					// for each segment of the refined segmentation given as argument
					for (const_iterator i = r->begin(); i!= r->end(); i++) {
						// find its container segment in the primary segmentation
						TSegment<T1,D1> container = s->find (*i);
						if (!container.empty()) {		// empty segments are discarded
							// next we get the transform function to go from the container to the refined segment
							TAXBFunction<T1> f(container.interval(), i->interval());
							// we retrieve the relations of the container
							std::set<TSegment<T2,D2> > rel = m.get(container);
							// and for each relation
							for (const_iterator2 j = rel.begin(); j != rel.end(); j++) {
								// adds a relation between the refined segment and refined relation
								add (*i, TSegmentVariety<T2,D2>(*j, &f).get());
							}
						}
					}
				}

		virtual ~TRefinedRelation() {}
};

/*! @} */

} // end namespoace

#endif
