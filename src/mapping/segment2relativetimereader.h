/*
  Interlude Library
  Copyright (C) 2009  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __segment2relativetimereader__
#define __segment2relativetimereader__

#include "relativetimereader.h"
#include "TMapping.h"
#include "smartpointer.h"

namespace interlude 
{

//______________________________________________________________________________
/*!
\brief	A class to read graphic or absolute time to relative time mapping
*/
template <typename T> class segment2relativetimereader : public relativetimereader
{
	public:
		typedef SMARTP<TMapping<T,RelativeTimeSegment> >	SMapping;


	protected:

	typedef typename TSegmentation<T>::segmentsList	baseSegmentationList;

	std::set<T>					fBaseSegments;			///< the set of first segments
	SMapping					fMapping;				///< the segment to relative time mapping
	
	SMARTP<TSegmentation<T> >	fBaseSegmentation;		///< the first segmentation
	
		/*! \brief performs initialization when one of the \c read methods is called

			Initialization consists in clearing the existing mapping, segmentations and segments sets
			that could come from a previous \c read call.
			\return false in case of memory allocation failure
		*/
		bool initialize()
		{
			relativetimereader::initialize();
			fBaseSegments.clear();
			fBaseSegmentation = 0;
			fMapping = TMapping<T,RelativeTimeSegment>::create();
			return fMapping != 0;
		}
	
		/*! \brief converts a segments set to a segments vector
			\param set the set of segments
			\param v on output, a sorted vector of segments
			\return the output vector size
		*/
		int getSegments(const std::set<T>& set , baseSegmentationList& v) const;
	
		/*! \brief creates a segmentation from a segments set
			\param set the set of segments
			\return a segmentation smart pointer
		*/
		SMARTP<TSegmentation<T> > createSegmentation(const std::set<T>& set) const
			{
				baseSegmentationList v;
				int n = getSegments (set, v);
				if (n) {
					T resource(v[0] | v[n-1]);
					SMARTP<TSegmentation<T> > s = TSegmentation<T>::create(resource);
					if (s) s->add (v);
					return s;
				}
				return 0;
			}


	public:
				 segment2relativetimereader() {}
		virtual ~segment2relativetimereader() {}

		/*! \brief gives the graphic segmentation
		
			The graphic segmentation is computed from the set of graphic segments
			and cached into a SGraphicSegmentation internal field.
			\return a graphic segmentation smart pointer
		*/
		SMARTP<TSegmentation<T> >	getBaseSegmentation()
			{ if (!fBaseSegmentation) fBaseSegmentation = createSegmentation (fBaseSegments); return fBaseSegmentation; }

		/*! \brief gives the mapping
			\return a segment to relative time mapping
		*/
		const SMapping& getMapping() const				{ return fMapping; }
		
		//_______________________________________________________________________
		// mapreader implementation
		virtual bool map(const IntPointSegment&, const RelativeTimeSegment&);
		virtual bool map(const FrameSegment&, const RelativeTimeSegment&);
		virtual bool map(const GraphicSegment&, const RelativeTimeSegment&);
		virtual bool map(const FloatSegment&, const RelativeTimeSegment&);
};

} // namespace

#endif
