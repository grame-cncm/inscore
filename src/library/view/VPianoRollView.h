/*

  INScore Project

  Copyright (C) 2015  Grame

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


#ifndef __VPianoRollView__
#define __VPianoRollView__

#include "VGuidoItemView.h"
#include "MouseEventAble.h"

#include <QPixmap>
#include <map>
#include <string>

#include "QPRollGraphicsItem.h"

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
*	\brief a graphic view of a Guido piano roll.
*/
class VPianoRollView: public VGraphicsItemView
{
	typedef MouseEventAble<QPRollGraphicsItem>	IQPRollGraphicsItem;
	
	IQPRollGraphicsItem*	item()	{ return (IQPRollGraphicsItem *)fItem; }
	void					updateCommon( IGuidoPianoRoll * proll );

	public :
		using VGraphicsItemView::updateLocalMapping;
		using VGraphicsItemView::updateView;

				 VPianoRollView(QGraphicsScene * scene, const IGuidoPianoRoll*);
		virtual ~VPianoRollView() {}

		virtual void updateView( IGuidoPianoRoll * proll );
		virtual void updateView( IGuidoPianoRollStream * prollstream );
		virtual void updateLocalMapping (IGuidoPianoRoll* proll);
		virtual void updateLocalMapping (IGuidoPianoRollStream* proll);

	protected:
		/// update to guido code i.e. update ar and gr handlers
		virtual void updateMappingCommon (IGuidoPianoRoll* proll);
};

/*!@} */

} // end namespoace

#endif
