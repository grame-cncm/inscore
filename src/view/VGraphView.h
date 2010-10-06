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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __VGraphView__
#define __VGraphView__

#include "VShapeView.h"
#include "MouseEventAble.h"

#if newVersion
#include "QGraphicsGraphItemNew.h"
#else
#include "QGraphicsGraphItem.h"
#endif

namespace interlude
{

class EventsAble;

/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IGraphic.
*/
class VGraphView: public VShapeView
{
#if newVersion
	MouseEventAble<QGraphicsGraphItemNew>* item() const	{ return (MouseEventAble<QGraphicsGraphItemNew>*)fItem; }
#else
	MouseEventAble<QGraphicsGraphItem>* item() const	{ return (MouseEventAble<QGraphicsGraphItem>*)fItem; }
#endif

	public :
				 VGraphView(QGraphicsScene * scene, const EventsAble*);
		virtual ~VGraphView() {}
		
		virtual void updateView( IGraphicSignal * graph );
		virtual void updateObjectSize( IObject * object ) {}
		virtual void updateLocalMapping (IGraphicSignal*);
		
	protected:
		GraphicSegment getGraphicSegment( const FrameSegment& frameSegment , const IGraphicSignal * object , bool& mapOk ) const;
};

/*!@} */

} // end namespoace

#endif
