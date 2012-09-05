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


#ifndef __TRefinedComposition__
#define __TRefinedComposition__

#include "TMapping.h"
#include "TComposition.h"
#include "TRefinement.h"
#include "TRefinedRelation.h"

namespace libmapping
{

/*!
\addtogroup Relations
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief refined relations composition
	
	A class to compute refined relations based on the intermediate segmentation
	and the refined composition going from T1,D1 to T3,D3, using the intermediate
	refined relations.
*/
template<typename T1, unsigned int D1, typename T2, unsigned int D2, typename T3, unsigned int D3> 
class TRefinedComposition : public TMapping<T1,D1,T3,D3>
{
	protected:
		typedef TRelation<T2,D2,T1,D1>			rtype1;
		typedef TRelation<T2,D2,T3,D3>			rtype2;
		typedef SMARTP<TSegmentation<T1,D1> >	segmtype1;
		typedef SMARTP<TSegmentation<T2,D2> >	segmtype2;
		typedef typename TSegmentation<T2,D2>::const_iterator	const_iterator;

				 TRefinedComposition(const rtype1& r1, const rtype2& r2) {
					TRefinement<T2,D2> refine;
					// first computes the refinement of the common segmentation space
					segmtype2 s = refine(r1.getPrimarySet(), r2.getPrimarySet());
					// next computes the refinement of the refined relations using the refined segmentation
					TRefinedRelation <T2,D2,T1,D1> rr1 (r1, s);
					TRefinedRelation <T2,D2,T3,D3> rr2 (r2, s);
					// create a mapping that will be used to revert the first relation set
					SMARTP<TMapping<T2,D2,T1,D1> > map = TMapping<T2,D2,T1,D1>::create();
					map->add (rr1);
					// and uses a standard composition with the refined relations
					SMARTP<TMapping<T1,D1,T3,D3> > comp = TComposition<T1,D1,T2,D2,T3,D3>::create(map->reverse(),rr2);
					this->add (*comp);
				 }
				
		virtual ~TRefinedComposition() {}
	
	public:
		/// creates a new composition
		static SMARTP<TMapping<T1,D1,T3,D3> >create(const rtype1& m1, const rtype2& m2)	
			{ return new TRefinedComposition<T1,D1,T2,D2,T3,D3>(m1, m2); }
};

/*! @} */

} // end namespoace

#endif
