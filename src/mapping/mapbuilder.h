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

#ifndef __mapbuilder__
#define __mapbuilder__

#include <set>

#include "IModelTypes.h"
#include "mapping.h"
#include "mapreader.h"
#include "TRect.h"

namespace inscore 
{

//______________________________________________________________________________
/*!
	\brief	A class to build a mapping
	
	The builder should be called when the view of the target object is up to date. 
	The basic scheme to compute the mapping is the following:
	- call the \c start method with the target object as argument to get the first segment to be mapped
	- compute the corresponding graphic segment
	- call the \c map method to associate the graphic and text segments
	- call the \c next method to get the next segment to be mapped
	- etc. up to the end of the list denoted by the \c end() method
*/
template <class S, class D> class mapbuilder
{
	typedef typename TSegmentation<S>::segmentsVector		srcSegmentationVector;
	typedef typename TSegmentation<D>::segmentsVector		dstSegmentationVector;
	typedef typename dstSegmentationVector::const_iterator  const_segiterator;

	std::set<S>				fSrcSegments;		///< the set of graphic segments
	SMARTP<mapping<S,D> >	fMapping;			///< the D to S mapping
	
	typename std::vector<D>::const_iterator	fIterator;
	typename std::vector<D>::const_iterator	fEndIterator;
	enum { kEndSegmentValue = 0x7fffffff };

		/*! \brief converts a segments set to a segments vector
			\param s the set of segments
			\param v on output, a sorted vector of segments
		*/
		void getSegments(const std::set<S>& s , srcSegmentationVector& v) const {
			for (typename std::set<S>::const_iterator i = s.begin(); i != s.end(); i++)
				v.push_back(*i);
			sort(v.begin(), v.end());
		}

	public:
				 mapbuilder() {}
		virtual ~mapbuilder() {}
		
		/*! \brief gives the first segment to be mapped
			\param begin 
			\param end 
			\return the first segment
		*/
		 D start(const_segiterator begin, const_segiterator end) {
			fMapping = mapping<S,D>::create();
			fIterator = begin;
			fEndIterator = end;
			return next();
		}
		
		/*! \brief gives the next text segment to be mapped
			\return the next text segment
		*/
		 D next() {
			if (fIterator != fEndIterator) {
				D segm = *fIterator;
				fIterator++;
				return segm;
			}
			return end();
		}
		
		/*! \brief gives a segment denoting the end of the segment list
			\return the end segment (actually an empty segment)
		*/
		 D end() const		{ return D(kEndSegmentValue); };
		
		/*! \brief associate a graphic and a text segments
			\param gsegm the graphic segment
			\param tsegm the text segment
		*/
		void map(const S& gsegm, const D& tsegm) {
			fSrcSegments.insert (gsegm);
			fMapping->addRelation (gsegm, tsegm);
		}
		
		/*! \brief gives the src segmentation
		
			The src segmentation is computed from the set of src segments
			\return a src segmentation smart pointer
		*/
		SMARTP<TSegmentation<S> >	getSrcSegmentation() const {
			srcSegmentationVector v;
			getSegments (fSrcSegments, v);
			int n = v.size();
			if (n) {
				S resource(v[0] | v[n-1]);
				SMARTP<TSegmentation<S> > s = TSegmentation<S>::create(resource);
				if (s) s->add (v);
				return s;
			}
			return 0;
		}
		
		/*! \brief gives the src to dst mapping		
			\return the computer mapping
		*/
		const SMARTP<mapping<S,D> >& getMapping() const		 { return fMapping; }
};

typedef mapbuilder<GraphicSegment, IntPointSegment>				graphic2IntPointMapBuilder;
typedef mapbuilder<GraphicSegment, RelativeTimeSegment>			graphic2RelativeTimeMapBuilder;
typedef mapbuilder<RelativeTimeSegment, RelativeTimeSegment>	relativeTime2RelativeTimeMapBuilder;


} // namespace

#endif
