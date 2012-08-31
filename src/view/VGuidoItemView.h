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


#ifndef __VGuidoItemView__
#define __VGuidoItemView__

#include "VGraphicsItemView.h"
#include "MouseEventAble.h"

#include <map>
#include <string>

class QGuidoGraphicsItem;

namespace inscore
{

class GuidoMapCollector;
class EventsAble;

/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IGuidoFile or a IGuidoCode.
*/
class VGuidoItemView: public VGraphicsItemView
{
	static float fCm2GuidoUnit;
	typedef MouseEventAble<QGuidoGraphicsItem>	IQGuidoGraphicsItem;
	IQGuidoGraphicsItem* fGuidoItem;

	public :
		using VGraphicsItemView::updateView;

		VGuidoItemView(QGraphicsScene * scene, const IGuidoCode*);
		virtual ~VGuidoItemView() {}

		virtual void updateView( IGuidoCode * guidoCode );
		virtual void updateLocalMapping (IGuidoCode* guidoCode);

	protected:
		/// update to guido code i.e. update ar and gr handlers
		bool						gmnUpdate (IGuidoCode* guidoCode);
		/// update the page format
		void						pageFormatUpdate (IGuidoCode* guidoCode);
		/// computes the rolled to unrolled time mapping
		SRelativeTimeSegmentation	timeMapUpdate (SRelativeTime2RelativeTimeMapping& map);
		/// computes the time to graphic mapping
		void						graphMapUpdate (IGuidoCode* guidoCode, SRelativeTime2RelativeTimeMapping& map, SRelativeTimeSegmentation& timeseg);
		
		GuidoMapCollector * getMapBuilder (const std::string& mapName) const;
};

/*!@} */

} // end namespoace

#endif
