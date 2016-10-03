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

#include <QPainterPath>
#include <QDebug>

#include "VArcView.h"
#include "IArc.h"

namespace inscore
{

//----------------------------------------------------------------------
VArcView::VArcView(QGraphicsScene * scene, const IArc* obj)	: VMappedShapeView( scene , new MouseEventAble<QGraphicsPathItem>(obj) )
{}

//----------------------------------------------------------------------
QRectF VArcView::getBoundingRect( IObject * o ) const
{
	return QRectF(0, 0, relative2SceneWidth(o->getWidth()), relative2SceneHeight(o->getHeight()));
}

//----------------------------------------------------------------------
void VArcView::updateView( IArc * arc )
{
    arc->cleanupSync();
	
	QRectF r( 0,0,  relative2SceneWidth(arc->getWidth()),relative2SceneHeight(arc->getHeight()) );
	QPainterPath path;
	if (!arc->closed()) path.arcMoveTo(r, arc->getStartAngle());
	else path.moveTo(r.center());
	path.arcTo(r, arc->getStartAngle(), arc->getAngularRange());
	if (arc->closed()) path.closeSubpath();
	item()->setPath (path);

	VShapeView::updateView( arc );
}

} // end namespoace
