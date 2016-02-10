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

#include <QDebug>
#include <QPainter>
#include <QByteArray>

#include "OSCStream.h"
#include "TComposition.h"
#include "VSVGView.h"
#include "VApplView.h"
#include "ITLError.h"

#include "ISVGFile.h"
#include "VIntPointObjectView.h"

namespace inscore
{

//----------------------------------------------------------------------
VSVGItem::~VSVGItem() { if (fTimerID) fRenderer.killTimer(fTimerID); }

//----------------------------------------------------------------------
bool VSVGItem::setFile( const char* filename)
{
	QString file = QString::fromUtf8( filename );
	if (!fRenderer.load(QString(file))) {
		ITLErr << "cannot load SVG file" << filename << ITLEndl;
		return false;
	}
	if (!fFramesPerSecond) fFramesPerSecond = fRenderer.framesPerSecond();
	fRenderer.setFramesPerSecond(0);
	return true;
}

//----------------------------------------------------------------------
bool VSVGItem::setText( const char* text)
{
	if (!fRenderer.load(QByteArray(text))) {
		ITLErr << "cannot load svg data" << text << ITLEndl;
		return false;
	}
	fFramesPerSecond = fRenderer.framesPerSecond();
	return true;
}

void VSVGItem::paint ( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * )
{
	if (fRenderer.isValid()) {
		fRenderer.render (painter, boundingRect());
		if (fAnimate) {
			if (!fTimerID && fFramesPerSecond) {
				fRenderer.setFramesPerSecond(fFramesPerSecond);
				fTimerID = fRenderer.startTimer(1000 / fFramesPerSecond);
			}
		}
		else if (fTimerID) {
			fRenderer.killTimer(fTimerID);
			fTimerID = 0;
			fRenderer.setFramesPerSecond(0);
		}
	}
}

//----------------------------------------------------------------------
VSVGView::VSVGView(QGraphicsScene * scene, const ISVGFile* svg) 
	: VIntPointObjectView( scene , new MouseEventAble<VSVGItem>(svg) )
    {}
VSVGView::VSVGView(QGraphicsScene * scene, const ISVG* svg) 
	: VIntPointObjectView( scene , new MouseEventAble<VSVGItem>(svg) )
    {}

//----------------------------------------------------------------------
void VSVGView::updateView( ISVGFile * svg  )
{
    svg->cleanupSync();
    if (svg->changed()) {
        if(svg->hasData())
            item()->setText(svg->data());
        else
            item()->setFile (svg->getFile().c_str());
		svg->changed(false);
	}
	float alpha = svg->getA() / 255.f;
	item()->setOpacity (alpha);
	item()->setAnimate(svg->getAnimate());
	svg->setAnimated(item()->getAnimated());
	VIntPointObjectView::updateView( svg );
}

//----------------------------------------------------------------------
void VSVGView::updateView( ISVG * svg  )
{
    svg->cleanupSync();
    if (svg->newData()) {
		item()->setText (svg->getText().c_str());
	}
	float alpha = svg->getA() / 255.f;
	item()->setOpacity (alpha);
	item()->setAnimate(svg->getAnimate());
	VIntPointObjectView::updateView( svg );
}

//----------------------------------------------------------------------
void VSVGView::updateLocalMapping (ISVG* svg)
{
	if (item()->size().width() <= 0)
		item()->setText (svg->getText().c_str());
	VIntPointObjectView::updateLocalMapping( svg );
}

//----------------------------------------------------------------------
void VSVGView::updateLocalMapping (ISVGFile* svg)
{
	if (item()->size().width() <= 0)
    {
        if(svg->hasData())
            item()->setText(svg->data());
        else
            item()->setFile (svg->getFile().c_str());
	}
    VIntPointObjectView::updateLocalMapping( svg );
}

//----------------------------------------------------------------------
GraphicSegment VSVGView::getGraphicSegment( const IntPointSegment& segm , const IGraphicBasedObject * object , bool& mapOk ) const
{
	QRectF rect = item()->boundingRect();
	TLongPoint intPointA (segm.xinterval().first(), segm.yinterval().first());
	TLongPoint intPointB (segm.xinterval().second(), segm.yinterval().second());
	
	QPointF a (segm.xinterval().first(), segm.yinterval().first());
	QPointF b (segm.xinterval().second(), segm.yinterval().second());
	
	QPointF ep;
	mapOk=false;
	if ( !rect.contains(a) ) 	ep = a;			
	if ( !rect.contains(b) )	ep = b;
	else mapOk = true;
	if ( !mapOk ) {
		const char* msg1 = "svg mapping of object";
		const char* msg2 = "refers to 'out of bounds' position:";
		ITLErr << msg1 << object->getOSCAddress() << msg2 << "[" << int(ep.x()) << ";" << int(ep.y()) << "]" << ITLEndl;
		return GraphicSegment();
	}
	TFloatPoint startPoint = qGraphicsItem2IObject( longPointToQPoint(intPointA) , rect );
	TFloatPoint endPoint = qGraphicsItem2IObject( longPointToQPoint(intPointB) , rect );
	
	return GraphicSegment( startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y() );
}

} // end namespoace
