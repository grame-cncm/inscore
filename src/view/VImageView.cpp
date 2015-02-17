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

#include "IImage.h"
#include "ITLError.h"

#include "VApplView.h"
#include "VImageView.h"
#include "VSceneView.h"
#include "VExport.h"

#include <QImageReader>
#include <QFile>
#include <QBuffer>
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
    img->setWidth(scene2RelativeWidth(fImageItem->boundingRect().width()));
    img->setHeight(scene2RelativeHeight(fImageItem->boundingRect().height()));

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
void VImageView::setImage(VObjectView* src)
{
	QImage img;
	VGraphicsItemView * itemview = dynamic_cast<VGraphicsItemView*>(src);
	VSceneView * sceneview = dynamic_cast<VSceneView*>(src);
	if (itemview) {
		QGraphicsItem *item = itemview->item();
		float xScale = 1.;
		float yScale = 1.;
		img = VExport::itemToImage( item, xScale, yScale, QColor(255,255,255,0), true, true );
	}
	else if (sceneview) {
		QGraphicsView *view = sceneview->view();
		img = VExport::sceneToImage( view );
	}
	
	QByteArray data;
	QBuffer buffer( &data);
	buffer.open(QIODevice::WriteOnly);
	img.save(&buffer, "PNG"); // writes image into ba in PNG format
	setImage (data);
	itemChanged();
}

//----------------------------------------------------------------------
void VImageView::setImage(QByteArray data)
{
    fImageItem->image().loadFromData(data);
    itemChanged();
}

} // end namespoace
