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

#include "ICurve.h"
#include "TComposition.h"
#include "VCurveView.h"

#include <QPen>

// QGraphicsPathItem derived class using the exact bounding-rect of the path.
class QGraphicsCurveItem: public QGraphicsPathItem
{
	public:
		QGraphicsCurveItem(QGraphicsItem* parent = 0) : QGraphicsPathItem(parent) {}		
		QRectF boundingRect () const { return path().boundingRect(); }
};

namespace inscore
{

//----------------------------------------------------------------------
VCurveView::VCurveView(QGraphicsScene * scene, const ICurve* h) 
	: VMappedShapeView( scene , new MouseEventAble<QGraphicsPathItem>(h))
    {}

//----------------------------------------------------------------------
void VCurveView::updateView( ICurve * curve )
{
    curve->cleanupSync();
    QPainterPath myPath;
	for ( unsigned int i = 0 ; i < curve->getPoints().size() ; i++ )
	{
		QPoint startPoint	( relative2SceneWidth(curve->getPoints()[i].fPointA.first) , relative2SceneHeight(curve->getPoints()[i].fPointA.second) );
		QPoint c1			( relative2SceneWidth(curve->getPoints()[i].fPointB.first) , relative2SceneHeight(curve->getPoints()[i].fPointB.second) );
		QPoint c2			( relative2SceneWidth(curve->getPoints()[i].fPointC.first) , relative2SceneHeight(curve->getPoints()[i].fPointC.second) );
		QPoint endPoint		( relative2SceneWidth(curve->getPoints()[i].fPointD.first) , relative2SceneHeight(curve->getPoints()[i].fPointD.second) );
		myPath.moveTo(startPoint);
		myPath.cubicTo(c1, c2, endPoint);
	}
	if ( myPath != item()->path() )
	{
		item()->setPath( myPath );
		itemChanged();
	}
	VShapeView::updateView( curve );
}


//----------------------------------------------------------------------
void VCurveView::updateObjectSize(IObject* o)
{
    ICurve * p = dynamic_cast<ICurve*>(o);
    if(p)
        updateView(p);
    VGraphicsItemView::updateObjectSize(o);
}


} // end namespoace
