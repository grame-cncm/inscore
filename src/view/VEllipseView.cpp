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

#include "TComposition.h"
#include "VEllipseView.h"

#include "IEllipse.h"

namespace inscore
{

//----------------------------------------------------------------------
VEllipseView::VEllipseView(QGraphicsScene * scene, const IEllipse* h) 
	: VMappedShapeView( scene , new MouseEventAble<QGraphicsEllipseItem>(h) )
    {
        if(!h->getParent()->getDeleted() && h->getParent()->getTypeString() != IScene::kSceneType)
            setParentItem(h->getParent()->getView()?h->getParent()->getView():0);
    }

//----------------------------------------------------------------------
void VEllipseView::updateView( IEllipse * ellipse )
{
    ellipse->cleanupSync();
    if(!ellipse->getParent()->getMaster(ellipse) && !ellipse->getParent()->getDeleted())
    {
        if(ellipse->getParent()->getTypeString() != IScene::kSceneType)
            setParentItem(ellipse->getParent()->getView()?ellipse->getParent()->getView():0);
    }
	QRectF r( 0,0,  relative2SceneWidth(ellipse->getWidth()),relative2SceneHeight(ellipse->getHeight()) );
	if ( r != item()->rect() ) {
		item()->setRect( r );
		itemChanged();
	}
	VShapeView::updateView( ellipse );
}


} // end namespoace
