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


#ifndef __IMappingUpdater__
#define __IMappingUpdater__

#include "Updater.h"
#include "IObject.h"
#include "IRect.h"
#include "IEllipse.h"
#include "ILine.h"
#include "ICurve.h"
#include "IVideo.h"
#include "IPolygon.h"
#include "IScene.h"
#include "ISync.h"
#include "TReverseComposition.h"
#include "TMappingComposer.h"
#include "TVirtualRelation.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

class IShapeMap;
//--------------------------------------------------------------------------
/*!
	\brief an updater that computes a mapping according to a sync relation
*/
class IMappingUpdater : public SlaveMapUpdater
{
	protected:
				void			hstretchUpdate (IObject* o, const Master* m);				
				void			VStretch		(IObject* o, const GraphicSegment& gseg);
				bool			updateNOHStretch (IObject* o, const Master* m);
				
				GraphicSegment	updateNoStretch (IObject*, const Master* master);
				void			updateVStretch  (IObject*, const Master* master);

		/// check adjacent segments and make sure the end and begin of successives egments match at an epsilon approximate
		SGraphic2GraphicMapping			relink (const Graphic2GraphicRelation& rel, float epsilon) const;
		/// time shift a time to graphic mapping
		SRelativeTime2GraphicMapping	timeshift (const SRelativeTime2GraphicMapping& map, const rational& date) const;
		/// adjust the segments vertical dimension and position
		SGraphic2GraphicMapping			verticalAdjust (const SGraphic2GraphicMapping& map, IObject* o, const Master* master) const;
		/// compute the intersection of two time segmentations
		void	intersect (const RelativeTime2GraphicRelation& r1, const RelativeTime2GraphicRelation& r2, std::set<RelativeTimeSegment>& outlist) const;

	public:
				 IMappingUpdater() {}
		virtual ~IMappingUpdater() {}
		
				void updateIObject (IObject* o);

		inline  void updateTo (IText* o)			{ updateIObject ( (IObject*)o); }
		inline  void updateTo (ITextFile* o)		{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IGuidoCode* o)		{ updateIObject ( (IObject*)o); }
		inline  void updateTo (IGuidoFile* o)		{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IGraphicSignal* o)	{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IRect * o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IEllipse * o)		{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IPolygon * o)		{ updateIObject ( (IObject*)o); }
		inline	void updateTo (ICurve * o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (ILine * o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IVideo * o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IImage* o)			{ updateIObject ( (IObject*)o); }

		inline	void updateTo (IHtml* o)			{ updateIObject ( (IObject*)o); }
		inline	void updateTo (IHtmlFile* o)		{ updateIObject ( (IObject*)o); }
};
typedef class SMARTP<IMappingUpdater>	SIMappingUpdater;


/*!@} */

} // end namespoace

#endif
