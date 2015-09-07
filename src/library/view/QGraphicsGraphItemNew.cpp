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

#include "QGraphicsGraphItemNew.h"

#define GRAPHICS_GRAPH_ITEM_SIZE QRect(0,0,200,100)

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
QGraphicsGraphItemNew::QGraphicsGraphItemNew (QGraphicsItem * parent) 
	: QGraphicsRectItem(GRAPHICS_GRAPH_ITEM_SIZE , parent), fSignals (0) {}

//--------------------------------------------------------------------------
QGraphicsGraphItemNew::~QGraphicsGraphItemNew()		{}


//--------------------------------------------------------------------------
void QGraphicsGraphItemNew::drawSignal( ParallelSignal * sig, QPainter * painter, unsigned short size, float stepWidth, float yHeight)
{
	int n = sig->dimension();
	STSignal ysig	=  sig->signal(0);
	STSignal tsig;
	if (n > 1) tsig = sig->signal(1);
	else tsig = ConstTSignal::create(0.f);
	SColorSignal colorSig = ColorSignal::create();
	for (int i=2; i < n; i++) *colorSig << sig->signal(i);
	
	QPen pen( painter->pen() );
	float xpos = 0;
	for (unsigned short i=0; i < size; i++) {
		float y = yHeight - (ysig->get(i) * yHeight);
		float t = tsig->get(i) * yHeight/2;
		pen.setColor( HSBA2QColor(colorSig->get(i)) );
		painter->setPen (pen);
		painter->drawLine(xpos, y - t, xpos, y + t);
		xpos += stepWidth;
	}
}


//--------------------------------------------------------------------------
void QGraphicsGraphItemNew::paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * )
{
	QRectF bb = boundingRect();
	unsigned short size = signal()->size();
	float stepWidth = bb.width() / size;
	float yHeight = bb.height() / 2;
	
	painter->setClipRect( bb );
	QPen pen( QBrush(Qt::SolidPattern), stepWidth, Qt::SolidLine, Qt::FlatCap, Qt::MiterJoin );
	painter->setPen(pen);
	int n = signal()->dimension();
	for (int i=0; i < n; i += GraphicFrame::FrameSize()) {
		SParallelSignal	sig = signal()->getProjection (i, 1, i + GraphicFrame::FrameSize());
		if (sig) drawSignal (sig, painter, size, stepWidth, yHeight);
	}
}

} // end namespoace
