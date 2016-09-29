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

#include <QPen>

#include "IAppl.h"
#include "ICurve.h"
#include "VCurveView.h"

static const float kCurvePosChangeVers = 1.20f;

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
	: VMappedShapeView( scene , new MouseEventAble<QGraphicsCurveItem>(h))
    {}

//----------------------------------------------------------------------
void VCurveView::updateView( ICurve * curve )
{
    curve->cleanupSync();
    QPainterPath path;
	for ( unsigned int i = 0 ; i < curve->getPoints().size() ; i++ )
	{
		QPointF startPoint	( relative2SceneWidth(curve->getPoints()[i].fPointA.first) , relative2SceneHeight(curve->getPoints()[i].fPointA.second) );
		QPointF c1			( relative2SceneWidth(curve->getPoints()[i].fPointB.first) , relative2SceneHeight(curve->getPoints()[i].fPointB.second) );
		QPointF c2			( relative2SceneWidth(curve->getPoints()[i].fPointC.first) , relative2SceneHeight(curve->getPoints()[i].fPointC.second) );
		QPointF endPoint	( relative2SceneWidth(curve->getPoints()[i].fPointD.first) , relative2SceneHeight(curve->getPoints()[i].fPointD.second) );
		path.moveTo(startPoint);
		path.cubicTo(c1, c2, endPoint);
	}
	if ( path != item()->path() )
	{
		item()->setPath( path );
		itemChanged();
	}

	VShapeView::updateView( curve );
	if (IAppl::compatibilityVersion() >= kCurvePosChangeVers) {
		QRectF r = path.boundingRect();
		item()->moveBy (-r.x(), -r.y());
	}
}


} // end namespoace
