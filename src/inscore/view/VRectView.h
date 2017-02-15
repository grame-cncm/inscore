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


#ifndef __VRectView__
#define __VRectView__

#include <QGraphicsRectItem>

#include "VMappedShapeView.h"
#include "MouseEventAble.h"

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

class GraphicsRoundedRectItem : public QGraphicsRectItem
{
	public:
				 GraphicsRoundedRectItem (QGraphicsItem* parent=Q_NULLPTR) : QGraphicsRectItem(parent), fXRadius(0), fYRadius(0) {}
		virtual ~GraphicsRoundedRectItem () {}
	
		void	setXRadius (qreal r)	{ fXRadius = r; }
		void	setYRadius (qreal r)	{ fYRadius = r; }
		qreal	getXRadius () const		{ return fXRadius; }
		qreal	getYRadius () const		{ return fYRadius; }

	protected:
		qreal	fXRadius;
		qreal	fYRadius;
		virtual void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = Q_NULLPTR);
};


//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IRect.
*/
class VRectView: public VMappedShapeView
{
	MouseEventAble<GraphicsRoundedRectItem>*  item() const			{ return (MouseEventAble<GraphicsRoundedRectItem>*)fItem; }

	public :
		using VMappedShapeView::updateView;

				 VRectView(QGraphicsScene * scene, const IRect* h);
		virtual ~VRectView() {}

		virtual void updateView( IRect * rect );
		virtual void updateObjectSize( IObject *  )		{}
};

/*!@} */

} // end namespoace

#endif
