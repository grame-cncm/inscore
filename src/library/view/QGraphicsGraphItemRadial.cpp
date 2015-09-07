/*

  INScore Project

  Copyright (C) 2015  Grame

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

#include "QGraphicsGraphItemRadial.h"

#define GRAPHICS_GRAPH_ITEM_SIZE QRect(0,0,100,100)

#include <QLineF>
#include <QPainter>
#include <QtDebug>
#include <QPair>
#include <math.h>

#include "TSignal.h"
#include "GraphicSignal.h"
#include "QColorTool.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
QGraphicsGraphItemRadial::QGraphicsGraphItemRadial (QGraphicsItem * parent)
	: QGraphicsRectItem(GRAPHICS_GRAPH_ITEM_SIZE , parent), fSignals (0) {}

//--------------------------------------------------------------------------
QGraphicsGraphItemRadial::~QGraphicsGraphItemRadial()		{}


#define kPI	3.14159265359
//--------------------------------------------------------------------------
void QGraphicsGraphItemRadial::drawSignal( ParallelSignal * sig, QPainter * painter, unsigned short size, double step, double xr, double yr)
{
	const int n = sig->dimension();

	STSignal ysig	=  sig->signal(0);
	STSignal tsig;
	if (n > 1) tsig = sig->signal(1);
	else tsig = ConstTSignal::create(0.f);
	SColorSignal colorSig = ColorSignal::create();
	for (int i=2; i < n; i++) *colorSig << sig->signal(i);
	
	QPen pen( painter->pen() );
	double a = kPI;
	double prevx = -1000;
	double prevy = -1000;
	double prevtx, prevty;
	double ew = 0.7;
	QBrush brush (Qt::SolidPattern);
	for (unsigned int i=0; i < size; i++) {
		double t = tsig->get(i)/4;				// thickness of the graphic signal (in [-1, 1])
		double s = (ysig->get(i) + 1) / 2;		// the current signal y value (scaled to 0 1)
		double ex = xr * cos(a);				// x coordinate of the current ellipse border
		double ey = yr * sin(a);				// y coordinate of the current ellipse border

		double x = xr + s * ex;			// the y deviation x coordinate
		double y = yr + s * ey; 		// the y deviation y coordinate
		s += t;
		double tx = xr + (s+t) * ex;	// the thickness deviation x coordinate
		double ty = yr + (s+t) * ey;	// the thickness deviation y coordinate
		
		pen.setColor( HSBA2QColor(colorSig->get(i)) );
		painter->setPen (pen);
#if 1
		if (prevx >=0) {
//			QLineF line(xr, yr, x, y);
			QLineF line(prevx, prevy, x, y);
			painter->drawLine(line);
			
			QPainterPath path(QPointF(prevx, prevy));
			path.lineTo(prevtx, prevty);
			path.lineTo(tx, ty);
			path.lineTo(x, y);
			path.lineTo(prevx, prevy);
			path.setFillRule(Qt::WindingFill);
			brush.setColor (HSBA2QColor(colorSig->get(i)));
			painter->fillPath(path, brush);
			painter->drawPath(path);
		}
#else
		QLineF line(xr, yr, tx, ty);
		painter->drawLine(line);
#endif
		prevx = x;
		prevy = y;
		prevtx = tx;
		prevty = ty;
//		painter->drawEllipse(QPointF(ex+xr, ey+yr), ew*(a-kPI), ew*(a-kPI));
		a += step;
	}
}

//--------------------------------------------------------------------------
void QGraphicsGraphItemRadial::paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * )
{
	QRectF bb = boundingRect();
	unsigned short size = signal()->size();
	const float k = 2*kPI;
	const float border = 4;

//qDebug() << "QGraphicsGraphItemRadial::paint" << bb << "size:" << size;
	double re = bb.width()/2 - border;
	double ri = bb.height()/2 - border;
	double step = k / (size - 1);

	painter->setClipRect( bb );
//	QPen pen( QBrush(Qt::SolidPattern), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
//	painter->setPen(pen);
	int n = signal()->dimension();
	for (int i=0; i < n; i += GraphicFrame::FrameSize()) {
		SParallelSignal	sig = signal()->getProjection (i, 1, i + GraphicFrame::FrameSize());
		if (sig) drawSignal (sig, painter, size, step, re, ri);
	}
//	QPen pen( QBrush(Qt::SolidPattern), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
//	painter->setPen(pen);
//	painter->drawEllipse(re, ri, 3, 3);
}

} // end namespoace
