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

#include "VRectView.h"
#include "IRect.h"

namespace inscore
{

//----------------------------------------------------------------------
VRectView::VRectView(QGraphicsScene * scene, const IRect* h) 
	: VMappedShapeView( scene , new MouseEventAble<QGraphicsRectItem>(h) )
    {}

//----------------------------------------------------------------------
void VRectView::updateView( IRect * rect  )
{
    if(rect->getParent()->getTypeString() != IAppl::kApplType && rect->getParent()->getTypeString() != IScene::kSceneType)
        setParentItem(rect->getParent()->getView()?rect->getParent()->getView():0);
	QRectF newRect( 0,0,  relative2SceneWidth(rect->getWidth()), relative2SceneHeight(rect->getHeight()) );
	if ( newRect != item()->rect() )
	{
		item()->setRect( newRect );
		itemChanged();
	}
	VShapeView::updateView( rect );
}


} // end namespoace
