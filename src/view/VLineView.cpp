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
#include <math.h>
#include <QDebug>
namespace inscore
{
// Arbitrary graphic size to draw arrow heads
const float VLineView::sArrowHeadSize = 12.0;

//----------------------------------------------------------------------
VLineView::VLineView(QGraphicsScene * scene, const ILine* h) 
	: VMappedShapeView( scene , new IQGraphicsPathItem(h))
	{}

//----------------------------------------------------------------------
void VLineView::updateView( ILine * line )
{
    line->cleanupSync();

	double x = relative2SceneX(line->getPoint().x());
	double y = relative2SceneY(line->getPoint().y());
	double xo = 0;
	double yo = 0;

	if (fParent) {	// a parent is a QGraphicsItem that differs from a scene regarding the reference rect:
		QRectF r = referenceRect(0);	// a scene origin (the point in 0,0) is centered on the scene
		x -= r.width()/2;				// while a QGraphicsItem origin is at the top left corner
		y -= r.height()/2;				// this part is intended to compensate this difference
	}

	bool isLeft = true;
	if ((x < 0) && (y < 0)) {
		x = -x;
		y = -y;
		// Coordinate modification, inverse side of arrow
		isLeft = !isLeft;
	} else if (x < 0) {
		yo = y;
		x = -x;
		y = 0;
		// Coordinate modification, inverse side of arrow
		isLeft = !isLeft;
	}
	else if (y < 0) {
		yo = -y;
		y = 0;
	}

	QPainterPath myPath;
	myPath.moveTo( xo,yo);
	myPath.lineTo( x, y );

	// Save bounding rect of path (which has a pen width of 0) before drawing arrow heads.
	QRectF before = myPath.boundingRect();

	// Create an Arrow
	QPointF p0(xo, yo);
	QPointF p1(x, y);
	ArrowHeadFactory f;
	// Draw left arrow
	f.addArrowHead(myPath, line->getArrowLeft(), p0, p1, line->getArrowSizeLeft() * sArrowHeadSize, isLeft);
	// Draw right arrow
	f.addArrowHead(myPath, line->getArrowRight(), p0, p1, line->getArrowSizeLeft() * sArrowHeadSize, !isLeft);

	if ( myPath != item()->path() )
	{
		item()->setPath( myPath );
		itemChanged();
	}

	// Copy pen color in color of shape to have plain arrow head with line color.
	IColor c(line->getPenColor().getR(), line->getPenColor().getG(), line->getPenColor().getB() , line->getPenColor().getA());
	line->setColor(c);
	VShapeView::updateView( line );

	// Get bouding box and translate line with saved bounding rect because
	// pen width and arrow head size have not to be include in translation.
	QRectF after = item()->boundingRect();
	xo = after.width()  * (line->getXOrigin() + 1) * line->getScale() / 2;
	yo = after.height() * (line->getYOrigin() + 1) * line->getScale() / 2;
	x = before.width()  * (line->getXOrigin() + 1) * line->getScale() / 2;
	y = before.height() * (line->getYOrigin() + 1) * line->getScale() / 2;
	item()->setTransform(QTransform::fromTranslate(xo - x, yo - y), true);
}

void VLineView::updateObjectSize(IObject* o)
{
    ILine * p = dynamic_cast<ILine*>(o);
    if(p)
        updateView(p);
    VGraphicsItemView::updateObjectSize(o);
}

ArrowHeadFactory::ArrowHeadFactory()
{
}

ArrowHeadFactory::~ArrowHeadFactory()
{
}

//----------------------------------------------------------------------
void ArrowHeadFactory::addArrowHead(QPainterPath &myPath, enum ILine::ArrowHeadType type, const QPointF &p0, const QPointF &p1, double arrowSize, bool isLeft)
{
	switch(type) {
		case ILine::NONE: // Do nothing
			break;
		case ILine::TRIANGLE:
			addTriangleArrowHead(myPath, p0, p1, arrowSize, isLeft);
			break;
		case ILine::DIAMOND:
			addDiamondArrowHead(myPath, p0, p1, arrowSize, isLeft);
			break;
		case ILine::DISK:
			addDiskArrowHead(myPath, p0, p1, arrowSize, isLeft);
			break;
		default:
			break;
	}
}

double ArrowHeadFactory::getAngle(const QPointF &p0, const QPointF &p1, bool isLeft)
{
	double x = p0.x() ? p0.x() : p1.x();
	double y = p0.y() ? p0.y() : p1.y();

	double angle = ::atan(y / x);
	if(p1.y() - p0.y() >= 0) {
		angle = - angle;
	}
	if(!isLeft) {
		angle += M_PI;
	}
	return angle;
}

void ArrowHeadFactory::addTriangleArrowHead(QPainterPath &myPath, const QPointF &p0, const QPointF &p1, double arrowSize, bool isLeft)
{
	QPointF p;
	if (isLeft) {
		p = p0;
	} else {
		p = p1;
	}

	double angle = getAngle(p0, p1, isLeft);
	QPointF arrowP1 = p + QPointF(sin(angle + M_PI / 3) * arrowSize,
									cos(angle + M_PI / 3) * arrowSize);
	QPointF arrowP2 = p + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
									cos(angle + M_PI - M_PI / 3) * arrowSize);

	// Return point of the triangle.
	QPointF returnPoint = p - QPointF(cos(angle + M_PI) * arrowSize * 0.6,
									-sin(angle + M_PI) * arrowSize * 0.6);

	QPolygonF arrowHead;
	arrowHead << p << arrowP1 << returnPoint << arrowP2;
	myPath.addPolygon(arrowHead);
	myPath.closeSubpath();
}

void ArrowHeadFactory::addDiamondArrowHead(QPainterPath &myPath, const QPointF &p0, const QPointF &p1, double arrowSize, bool isLeft)
{
	QPointF p;
	if (isLeft) {
		p = p0;
	} else {
		p = p1;
	}

	double angle = getAngle(p0, p1, isLeft);

	// P2 is opposite to the terminate point of the line.
	/* losange
	double sizeP2 = cos(M_PI / 6.0) * arrowSize * 2.0;
	QPointF arrowP2 = p - QPointF(cos(angle + M_PI) * sizeP2,
									-sin(angle + M_PI) * sizeP2);

	QPointF arrowP1 = p + QPointF(sin(angle + M_PI / 3) * arrowSize,
									cos(angle + M_PI / 3) * arrowSize);
	QPointF arrowP3 = p + QPointF(sin(angle + M_PI - M_PI / 3) * arrowSize,
									cos(angle + M_PI - M_PI / 3) * arrowSize);
	*/
	// Square
	arrowSize *= 0.9;
	double sizeP2 = cos(M_PI / 4.0) * arrowSize * 2.0;
	QPointF arrowP2 = p - QPointF(cos(angle + M_PI) * sizeP2,
									-sin(angle + M_PI) * sizeP2);

	QPointF arrowP1 = p + QPointF(sin(angle + M_PI / 4) * arrowSize,
									cos(angle + M_PI / 4) * arrowSize);
	QPointF arrowP3 = p + QPointF(sin(angle + M_PI - M_PI / 4) * arrowSize,
									cos(angle + M_PI - M_PI / 4) * arrowSize);

	QPolygonF arrowHead;
	arrowHead << p << arrowP1 << arrowP2 << arrowP3;
	myPath.addPolygon(arrowHead);
	myPath.closeSubpath();
}

void ArrowHeadFactory::addDiskArrowHead(QPainterPath &myPath, const QPointF &p0, const QPointF &p1, double arrowSize, bool isLeft)
{
	QPointF p;
	if (isLeft) {
		p = p0;
	} else {
		p = p1;
	}

	double angle = getAngle(p0, p1, isLeft);

	// P2 is the center of the disk
	arrowSize *= 0.9;
	double size = cos(M_PI / 3.0) * arrowSize;
	QPointF center = p - QPointF(cos(angle + M_PI) * size,
									-sin(angle + M_PI) * size);
	myPath.addEllipse(center, size, size);
}

} // end namespoace
