/*
  Interlude Library
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

#ifndef __relativetimereader__
#define __relativetimereader__

#include <set>

//#include "mapping.h"
#include "maptypes.h"
#include "TSegment.h"
#include "TSegmentation.h"

#include "mapreader.h"

namespace INScore 
{

//______________________________________________________________________________
/*!
\brief	the base class to read segment<T> to relative time mapping
*/
class relativetimereader : public mapreader
{
	protected:
		typedef RelativeTimeSegmentation::segmentsList	relTimeSegmentsList;
		std::set<RelativeTimeSegment>	fRelTimeSegments;		///< the set of relative time segments
		SRelativeTimeSegmentation		fRelTimeSegmentation;	///< the relative time segmentation
	
		/*! \brief performs initialization when one of the \c read methods is called

			Initialization consists in clearing the existing mapping, segmentations and segments sets
			that could come from a previous \c read call.
			\return false in case of memory allocation failure
		*/
		bool initialize();
	
		/*! \brief converts a segments set to a segments vector
			\param set the set of relative time segments
			\param v on output, a sorted vector of segments
			\return the output vector size
		*/
		int getSegments(const std::set<RelativeTimeSegment>& set, relTimeSegmentsList& v) const;

	public:
				 relativetimereader() {}
		virtual ~relativetimereader() {}

		/*! \brief gives the relative time segmentation
		
			The relative time segmentation is computed from the set of relative time segments
			and cached into a SRelativeTimeSegmentation internal field.
			\return a relative time segmentation smart pointer
		*/
		SRelativeTimeSegmentation	getRelativeTimeSegmentation();		
};

} // namespace

#endif
