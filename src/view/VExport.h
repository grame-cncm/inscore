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


#ifndef __VExport__
#define __VExport__

//#include "export.h"

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsView>

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief A set of export to pdf/image functions.
*/
class VExport
{

		/*!	\brief Paints the QGraphicsItem on the QPainterDevice.
		*
		*	The drawing can be sterched vertically and horizontally with xScaleFactor and yScaleFactor.
		*/
		static void		paintOnDevice(QPaintDevice * device, QGraphicsItem * item, float xScaleFactor, float yScaleFactor);
	
        /*!	\brief Paints the children on the QPainterDevice.
		*
		*	The drawing can be sterched vertically and horizontally with xScaleFactor and yScaleFactor.
		*/
		static void		paintChildrenOnDevice( QPainter * painter, QStyleOptionGraphicsItem option, QList<QGraphicsItem*> list);
    
		/*!	\brief Paints the QGraphicsView on the QPainterDevice.
		*/
		static void		paintOnDevice(QPaintDevice * device, QGraphicsView * item);

	public :
	
		/*!
		*	\brief Exports the specified QGraphicsItem to a pdf or image ; the format is infered from
		*	the fileName's extension.
		*
		*	Supported extensions (formats) are:
		*	pdf, bmp, gif, jpeg, png, pgm, ppm, tiff, xbm, xpm.
		*
		*	The output image can be horizontally and vertically streched with xScaleFactor and yScaleFactor.
		*/
		static void		exportItem(QGraphicsItem * item , QString fileName , 
										float xScaleFactor , float yScaleFactor);

		/*!
		*	\brief Exports the QGraphicsScene to the specified fileName ; the format is infered from
		*	the fileName's extension.
		*
		*	Supported extensions (formats) are:
		*	pdf, bmp, gif, jpeg, png, pgm, ppm, tiff, xbm, xpm.
		*/
		static void		exportScene( QGraphicsView * sceneview , QString fileName );
										
		/*!	\brief Paints the QGraphicsItem on a QImage and returns the QImage.
		*
		*	The image can be streched vertically and horizontally with xScale and yScale.
		* \param item the object to draw to the image
		* \param xScale a reference to the x scale factor. Note that it may be dynamically changed to ensure a minimum size of 10 x 10
		* \param yScale a reference to the y scale factor. Note that it may be dynamically changed to ensure a minimum size of 10 x 10
		*/
		static QImage	itemToImage( QGraphicsItem * item, float& xScale, float& yScale, const QColor fillColor = QColor(255,255,255,0) );

		/*!
		*	\brief Exports the specified QGraphicsItem to an image ; the format is infered from
		*	the fileName's extension.
		*
		*	Supported extensions (formats) are:
		*	bmp, gif, jpeg, png, pgm, ppm, tiff, xbm, xpm.
		*
		*	The output image can be horizontally and vertically streched with xScaleFactor and yScaleFactor.
		*/
		static void		exportToImage( QGraphicsItem * item, const QString& fileName, float& xScale, float& yScale );
		
		/*!
		*	\brief Exports the specified QGraphicsItem to a pdf ; the format is infered from
		*	the fileName's extension.
		*
		*	The output image can be horizontally and vertically streched with xScaleFactor and yScaleFactor.
		*/
		static void		exportToPdf( QGraphicsItem * item, const QString& fileName, float xScaleFactor, float yScaleFactor);
	
};

/*!@} */

} // end namespoace

#endif
