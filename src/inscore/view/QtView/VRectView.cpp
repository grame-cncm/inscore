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

#include <QDebug>
#include "VRectView.h"
#include "IRect.h"
#include "TRect.h"

namespace inscore
{

//----------------------------------------------------------------------
void GraphicsRoundedRectItem::paint(QPainter *painter, const QStyleOptionGraphicsItem * , QWidget *)
{
//	qDebug() << "GraphicsRoundedRectItem::paint using brush" << brush();
	QRectF r = boundingRect();
	QPen p = pen();
	if (p != Qt::NoPen) {
		qreal w = p.width();
		r.setWidth (r.width() - w);
		r.setHeight (r.height() - w);
		r.translate (w/2, w/2);
	}
	painter->setBrush (brush());
	painter->setPen (p);
	painter->drawRoundedRect(r, fXRadius, fYRadius, Qt::RelativeSize);
}

//----------------------------------------------------------------------
VRectView::VRectView(QGraphicsScene * scene, const IRect* h)
	: VMappedShapeView( scene , new MouseEventAble<GraphicsRoundedRectItem>(h) )
    {}

//----------------------------------------------------------------------
void VRectView::updateView( IRect * rect  )
{
    rect->cleanupSync();
    QRectF newRect( 0,0,  relative2SceneWidth(rect->getWidth()), relative2SceneHeight(rect->getHeight()) );
	if ( newRect != item()->rect() )
	{
		item()->setRect( newRect );
		itemChanged();
	}
	TFloatSize radius = rect->getRadius();
	if (radius.width() != item()->getXRadius() || radius.height() != item()->getYRadius()) {
		item()->setXRadius( radius.width() );
		item()->setYRadius( radius.height() );
		itemChanged();
	}
	VShapeView::updateView( rect );
}


} // end namespoace
