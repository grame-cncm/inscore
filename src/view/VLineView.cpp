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

#include "VLineView.h"
#include "ILine.h"

namespace interlude
{

//----------------------------------------------------------------------
VLineView::VLineView(QGraphicsScene * scene, const EventsAble* h) 
	: VMappedShapeView( scene , new IQGraphicsPathItem(h)) {}

//----------------------------------------------------------------------
void VLineView::updateView( ILine * line )
{
	QPainterPath myPath;
	myPath.moveTo(0,0);
	myPath.lineTo( relative2SceneX(line->getPoint().x()) , relative2SceneY(line->getPoint().y()) );

	if ( myPath != item()->path() )
	{
		item()->setPath( myPath );
		itemChanged();
	}
	VShapeView::updateView( line );
}


} // end namespoace
