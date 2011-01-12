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

#include <QImageReader>
#include <QFile>
#include <QDebug>

using namespace std;

namespace inscore
{

//----------------------------------------------------------------------
VImageView::VImageView(QGraphicsScene * scene, const IImage* h)
 :	VIntPointObjectView( scene , new IQGraphicsPixmapItem(h) )
{
	fPixmapItem = (IQGraphicsPixmapItem*)(fItem);
#ifdef PIXMAPBASED
	fPixmapItem->setTransformationMode( Qt::SmoothTransformation );
#endif
}

//----------------------------------------------------------------------
void VImageView::updateLocalMapping (IImage* img)
{
	// 1. Update pixmap
	if ( QFile::exists(  img->getFile().c_str()  ) )
	{
		QString imageFile = VApplView::toQString( img->getFile().c_str() );
		if ( !QImageReader( imageFile ).canRead() )
		{
			// Invalid/Unsupported file format
			ITLErr << "invalid image file :" << img->getFile() << ITLEndl;
		}
		else
			setImage( imageFile );
	}
	else
	{
		// File not found. Do nothing. (Error msg is handled by the model.)
	}

	// 2. Update mapping
	VIntPointObjectView::updateLocalMapping( img );
}

//----------------------------------------------------------------------
GraphicSegment VImageView::getGraphicSegment( const IntPointSegment& intPointSegment , const IGraphicBasedObject * object , bool& mapOk ) const
{
//	TLongPoint intPointA = iter.getFirst();
//	TLongPoint intPointB = iter.getSecond();

	TLongPoint intPointA (intPointSegment.xinterval().first(), intPointSegment.yinterval().first());
	TLongPoint intPointB (intPointSegment.xinterval().second(), intPointSegment.yinterval().second());
	
	TLongPoint errPoint;
	mapOk=true;
	if ( (intPointA.y() >= fPixmapItem->pixmap().height()) || (intPointA.x() >= fPixmapItem->pixmap().width()) )
	{
		errPoint = intPointA;			
		mapOk = false;
	}
	if ( (intPointB.y() >= fPixmapItem->pixmap().height()) || (intPointB.x() > fPixmapItem->pixmap().width()) )
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
	TFloatPoint startPoint = qGraphicsItem2IObject( longPointToQPoint(intPointA) , fPixmapItem->boundingRect() );
	TFloatPoint endPoint = qGraphicsItem2IObject( longPointToQPoint(intPointB) , fPixmapItem->boundingRect() );
	
	return GraphicSegment( startPoint.x(), startPoint.y(), endPoint.x(), endPoint.y() );

}

//----------------------------------------------------------------------
void VImageView::updateView ( IImage * img)
{
	float alpha = img->getA() / 255.f;
	fPixmapItem->setOpacity (alpha);
	VIntPointObjectView::updateView (img);
}

//----------------------------------------------------------------------
void VImageView::setImage(const QString& fileName)
{
#ifdef PIXMAPBASED
	fPixmapItem->setPixmap( QPixmap( fileName ) );
#else
	fPixmapItem->pixmap().load( fileName );
	if (!fPixmapItem->pixmap().hasAlphaChannel())
		qDebug() << "VImageView::setImage no alpha channel for " << fileName;
#endif
	itemChanged();
}

} // end namespoace
