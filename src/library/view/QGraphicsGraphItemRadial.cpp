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


//--------------------------------------------------------------------------
//void QGraphicsGraphItemRadial::drawSignal( ParallelSignal * sig, QPainter * painter, unsigned short size, float stepWidth, float yHeight)
//{
//	int n = sig->dimension();
//	STSignal ysig	=  sig->signal(0);
//	STSignal tsig;
//	if (n > 1) tsig = sig->signal(1);
//	else tsig = ConstTSignal::create(0.f);
//	SColorSignal colorSig = ColorSignal::create();
//	for (int i=2; i < n; i++) *colorSig << sig->signal(i);
//	
//	QPen pen( painter->pen() );
//	float xpos = 0;
//	for (unsigned short i=0; i < size; i++) {
//		float y = yHeight - (ysig->get(i) * yHeight);
//		float t = tsig->get(i) * yHeight/2;
//		pen.setColor( HSBA2QColor(colorSig->get(i)) );
//		painter->setPen (pen);
//		painter->drawLine(xpos, y - t, xpos, y + t);
//		xpos += stepWidth;
//	}
//}

//--------------------------------------------------------------------------
void QGraphicsGraphItemRadial::drawSignal( ParallelSignal * sig, QPainter * painter, unsigned short size, double step, double xr, double yr)
{
	const int n = sig->dimension();
	const int maxwidth = 5;

	STSignal ysig	=  sig->signal(0);
	STSignal tsig;
	if (n > 1) tsig = sig->signal(1);
	else tsig = ConstTSignal::create(0.f);
	SColorSignal colorSig = ColorSignal::create();
	for (int i=2; i < n; i++) *colorSig << sig->signal(i);
	
	QPen pen( painter->pen() );
	double a = 0;
	double prevx = -1000;
	double prevy = -1000;
	double x0, y0;
	for (unsigned int i=0; i < size; i++) {
		double ex = xr * cos(a);
		double ey = yr * sin(a);
		double s = (ysig->get(i) + 1) / 2;
		double x = xr + s * ex;
		double y = yr + s * ey;
		
//		double t = (tsig->get(i)+1) * maxwidth;
		pen.setColor( HSBA2QColor(colorSig->get(i)) );
//		pen.setWidthF( t );
		painter->setPen (pen);
		if (prevx >=0) {
//			QLineF line(xr, yr, x, y);
			QLineF line(prevx, prevy, x, y);
			painter->drawLine(line);
		}
		else {
			x0 = x;
			y0 = y;
		}
		prevx = x;
		prevy = y;
		painter->drawEllipse(ex+xr, ey+yr, 2, 2);
		a += step;
	}
	QLineF line(prevx, prevy, x0, y0);
	painter->drawLine(line);
}

//--------------------------------------------------------------------------
void QGraphicsGraphItemRadial::paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * )
{
	QRectF bb = boundingRect();
	unsigned short size = signal()->size();
	const float k = 2*3.14159265359;

//qDebug() << "QGraphicsGraphItemRadial::paint" << bb << "size:" << size;
	double re = bb.width()/2;
	double ri = bb.height()/2;
	double step = k / size;

	painter->setClipRect( bb );
//	QPen pen( QBrush(Qt::SolidPattern), 1, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
//	painter->setPen(pen);
	int n = signal()->dimension();
	for (int i=0; i < n; i += GraphicFrame::FrameSize()) {
		SParallelSignal	sig = signal()->getProjection (i, 1, i + GraphicFrame::FrameSize());
		if (sig) drawSignal (sig, painter, size, step, re, ri);
	}
	QPen pen( QBrush(Qt::SolidPattern), 2, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
	painter->setPen(pen);
	painter->drawEllipse(re, ri, 3, 3);
}

} // end namespoace
