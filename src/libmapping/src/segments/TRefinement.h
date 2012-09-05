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


#ifndef __TRefinement__
#define __TRefinement__

#include "TSegmentation.h"

namespace libmapping
{

/*
\addtogroup SEGMENTS
@{
*/

template<typename T, unsigned int D> class TRefinement;

//--------------------------------------------------------------------------
/*!
	\brief an utility for segmentations refinement
	
	TRefinement computes the common refinement of two segmentations.
	It may be viewed as the intersection of the segmentations.
*/
template<typename T, unsigned int D> class TRefinement
{
	typedef typename TSegmentation<T,D>::const_iterator		const_iterator;
	typedef			 TSegment<T,D>							SegmentT;

	public :
		typedef SMARTP<TSegmentation<T,D> >	SegmentationT;

				 TRefinement() {}
		virtual ~TRefinement() {}
		
		SegmentationT operator () (const SegmentationT& s1, const SegmentationT& s2, bool check = false) {
			// first computes the intersection of the segmentations resources
			SegmentT rsrc = s1->getResource() & s2->getResource();
			// and creates a new segmentation with this resource
			SegmentationT outsgt = TSegmentation<T,D>::create (rsrc);
			if (rsrc.empty()) return outsgt;				// done when the resource is empty
			if (!check || (s1->check() && s2->check())) {	// optional check of the segmentations consistency
				const_iterator i1 = s1->begin();			// start browsing the first segmentation
				const_iterator i2 = s2->begin();			// and the second segmentation
				while (i1 != s1->end() && i2 != s2->end()) {
					SegmentT inter = *i1 & *i2;				// compute the current segments intersection
					if (!inter.empty()) 					// when not empty
						outsgt->add (inter);				// adds the intersection to the segmentation
					if (*i2 < *i1) i2++;					// moves the smallest segment (see segments < operator)
					else if (!inter.empty()) i2++;
					else i1++;
				}
			}
			return outsgt;
		}
};

/*! @} */

} // end namespoace

#endif
