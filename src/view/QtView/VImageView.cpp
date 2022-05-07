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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
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
bool VImageView::initView (IObject* obj)
{
	IImage* img = static_cast<IImage*>(obj);
	QString file = VApplView::toQString( img->getPath().c_str() );
	if ( QFile::exists( file ) ) {
		if ( !QImageReader( file ).canRead() ) { 	// Invalid/Unsupported file format
			ITLErr << "invalid image file :" << img->getFile() << ITLEndl;
			return false;
		}
		else {
			setImage( file );
			updateObjectSize (img);
			updateLocalMapping (img);
		}
	}
	else {
		ITLErr << img->getFile() << ": no such file" << ITLEndl;
		return false;
	}
	return true;
}

//----------------------------------------------------------------------
void VImageView::updateLocalMapping (IImage* img)
{
	QRectF r = fImageItem->boundingRect();
	img->setBoundingRect (long(r.x()), long(r.y()), long(r.width()), long(r.height()));
	img->updateLocalMapping();
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
	float w = relative2SceneWidth(img->getWidth());
	QRectF r = fImageItem->boundingRect();
	float ratio = w ? w / r.width() : 1;
	fImageItem->setScale(ratio);
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
	setImage ((const unsigned char *)data.data(), data.size());
	itemChanged();
}

//----------------------------------------------------------------------
void VImageView::setImage(const QString& fileName)
{
	fImageItem->image().load( fileName );
	itemChanged();
}

//----------------------------------------------------------------------
void VImageView::setImage(const unsigned char * data, int len)
{
    fImageItem->image().loadFromData(data, len);
    itemChanged();
}

} // end namespoace
