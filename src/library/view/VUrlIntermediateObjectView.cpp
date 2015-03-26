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

#include <iostream>

#include "VUrlIntermediateObjectView.h"
#include "IUrlIntermediateObject.h"


namespace inscore
{

//----------------------------------------------------------------------
VUrlIntermediateObjectView::VUrlIntermediateObjectView(QGraphicsScene * scene, const IUrlIntermediateObject* h)
					: VMappedShapeView( scene , new MouseEventAble<QGraphicsRectItem>(h) )
{
	fText = new QGraphicsTextItem (h->name().c_str(), item());
	fUrl  = 0;
}

VUrlIntermediateObjectView::~VUrlIntermediateObjectView() { delete fText; delete fUrl; }

//----------------------------------------------------------------------
void VUrlIntermediateObjectView::updateView( IUrlIntermediateObject * obj  )
{
	if (!fUrl)	fUrl = new QGraphicsTextItem (obj->getFile().c_str(), item());

    obj->cleanupSync();
    QRectF newRect( 0,0,  relative2SceneWidth(obj->getWidth()), relative2SceneHeight(obj->getHeight()) );
	if ( newRect != item()->rect() )
	{
		item()->setRect( newRect );
		QRectF trect = fText->boundingRect();
		QRectF urect = fUrl->boundingRect();
		fText->setPos (newRect.width()/2 - trect.width()/2, newRect.height()/2 - trect.height()/2);
		fUrl->setPos (newRect.width()/2 - urect.width()/2, newRect.height()/2 + urect.height()/2);
        itemChanged();
	}
	VShapeView::updateView( obj );
}

}