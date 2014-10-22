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

#include "ITLError.h"
#include "TComposition.h"
#include "VImageView.h"
#include "VApplView.h"
#include "IImage.h"
#include "VApplView.h"

#include "QFileDownloader.h"
#include <QImageReader>
#include <QFile>
#include <QDebug>

using namespace std;

namespace inscore
{

//----------------------------------------------------------------------
VImageView::VImageView(QGraphicsScene * scene, const IImage* h)
 :	VIntPointObjectView( scene , new IQGraphicsImageItem(h) )
{
	fImageItem = (IQGraphicsImageItem*)(fItem);
}

//----------------------------------------------------------------------
void VImageView::updateLocalMapping (IImage* img)
{
	// 1. Update image
    
    setImage(img->getData());
    
    img->setWidth(scene2RelativeWidth(fImageItem->boundingRect().width()));
    img->setHeight(scene2RelativeHeight(fImageItem->boundingRect().height()));

	// 2. Update mapping
	VIntPointObjectView::updateLocalMapping( img );
}

//----------------------------------------------------------------------
GraphicSegment VImageView::getGraphicSegment( const IntPointSegment& intPointSegment , const IGraphicBasedObject * object , bool& mapOk ) const
{
	TLongPoint intPointA (intPointSegment.xinterval().first(), intPointSegment.yinterval().first());
	TLongPoint intPointB (intPointSegment.xinterval().second(), intPointSegment.yinterval().second());
	
	TLongPoint errPoint;
	mapOk=true;
	if ( (intPointA.y() >= fImageItem->image().height()) || (intPointA.x() >= fImageItem->image().width()) )
	{
		errPoint = intPointA;			
		mapOk = false;
	}
	if ( (intPointB.y() >= fImageItem->image().height()) || (intPointB.x() > fImageItem->image().width()) )
	{
		errPoint = intPointB;
		mapOk = false;
	}
	if ( !mapOk )
	{
		const char* msg1 = "pixel mapping of object";
		const char* msg2 = "refers to 'out of bounds' position:";
		ITLErr << msg1 << object->getOSCAddress() << msg2 << "[" << errPoint.x() << ";" << errPoint.y() << "]" << ITLEndl;
		return GraphicSegment();
	}
	TFloatPoint startPoint = qGraphicsItem2IObject( longPointToQPoint(intPointA) , fImageItem->boundingRect() );
	TFloatPoint endPoint = qGraphicsItem2IObject( longPointToQPoint(intPointB) , fImageItem->boundingRect() );
	
	return GraphicSegment( startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y() );

}

//----------------------------------------------------------------------
void VImageView::updateView ( IImage * img)
{
    img->cleanupSync();
    float alpha = img->getA() / 255.f;
	fImageItem->setOpacity (alpha);
	VIntPointObjectView::updateView (img);
}

//----------------------------------------------------------------------
void VImageView::setImage(QByteArray data)
{
    fImageItem->image().loadFromData(data);
    itemChanged();
}

} // end namespoace
