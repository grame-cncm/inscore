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


#ifndef __VGraphView__
#define __VGraphView__

#include "VShapeView.h"
#include "MouseEventAble.h"

#include "QGraphicsGraphItemNew.h"
#include "QGraphicsGraphItemRadial.h"
#include "QGraphicsGraphItem.h"

namespace inscore
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
	MouseEventAble<QGraphicsGraphItem>* item() const	{ return (MouseEventAble<QGraphicsGraphItem>*)fItem; }

	public :
		using VShapeView::updateView;
		using VShapeView::updateLocalMapping;

				 VGraphView(QGraphicsScene * scene, const IGraphicSignal*);
				 VGraphView(QGraphicsScene * scene, const IGraphicSignal*, QAbstractGraphicsShapeItem *);
		virtual ~VGraphView() {}
		
		virtual void drawBoundingBox (IObject* o);
		virtual void updateView( IGraphicSignal * graph );
		virtual void updateObjectSize( IObject *  )			{}
		virtual void updateLocalMapping (IGraphicSignal*);
		
	protected:
		GraphicSegment getGraphicSegment( const FrameSegment& frameSegment , const IGraphicSignal * object , bool& mapOk ) const;
};

//--------------------------------------------------------------------------
/**
*	\brief fast rendering graphic view of a IGraphic.
*/
class VSGraphView: public VGraphView
{
	MouseEventAble<QGraphicsGraphItemNew>* item() const	{ return (MouseEventAble<QGraphicsGraphItemNew>*)fItem; }
	public :
				 VSGraphView(QGraphicsScene * scene, const IGraphicSignal*);
		virtual ~VSGraphView() {}
		virtual void updateView( IGraphicSignal * graph );
};

//--------------------------------------------------------------------------
/**
*	\brief a radial rendering view of a IGraphic.
*/
class VRGraphView: public VGraphView
{
	MouseEventAble<QGraphicsGraphItemRadial>* item() const	{ return (MouseEventAble<QGraphicsGraphItemRadial>*)fItem; }
	public :
				 VRGraphView(QGraphicsScene * scene, const IGraphicSignal*);
		virtual ~VRGraphView() {}
		virtual void updateView( IGraphicSignal * graph );
};

/*!@} */

} // end namespoace

#endif
