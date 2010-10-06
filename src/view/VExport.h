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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __VExport__
#define __VExport__

//#include "export.h"

#include <QPainter>
#include <QGraphicsItem>
#include <QGraphicsView>

namespace interlude
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
		*	\brief Exports the QGraphicsView to the specified fileName ; the format is infered from
		*	the fileName's extension.
		*
		*	Supported extensions (formats) are:
		*	pdf, bmp, gif, jpeg, png, pgm, ppm, tiff, xbm, xpm.
		*/
		static void		exportScene( QGraphicsView * view , QString fileName );

		/*!	\brief Paints the QGraphicsItem on the QPainterDevice.
		*
		*	The drawing can be sterched vertically and horizontally with xScaleFactor and yScaleFactor.
		*/
		static void		paintOnDevice( QPaintDevice * device , QGraphicsItem * item , 
										float xScaleFactor , float yScaleFactor );
										
		/*!	\brief Paints the QGraphicsItem on a QPixmap and returns the QPixmap.
		*
		*	The pixmap can be streched vertically and horizontally with xScaleFactor and yScaleFactor.
		*/
		static QPixmap	itemToImage( QGraphicsItem * item , 
										float xScaleFactor , float yScaleFactor , 
										const QColor fillColor = QColor(255,255,255,0) );
		
		/*!
		*	\brief Exports the specified QGraphicsItem to an image ; the format is infered from
		*	the fileName's extension.
		*
		*	Supported extensions (formats) are:
		*	bmp, gif, jpeg, png, pgm, ppm, tiff, xbm, xpm.
		*
		*	The output image can be horizontally and vertically streched with xScaleFactor and yScaleFactor.
		*/
		static void		exportToImage( QGraphicsItem * item , const QString& fileName , 
										float xScaleFactor , float yScaleFactor );
		
		/*!
		*	\brief Exports the specified QGraphicsItem to a pdf ; the format is infered from
		*	the fileName's extension.
		*
		*	The output image can be horizontally and vertically streched with xScaleFactor and yScaleFactor.
		*/								
		static void		exportToPdf( QGraphicsItem * item , const QString& fileName , 
										float xScaleFactor , float yScaleFactor );
	
};

/*!@} */

} // end namespoace

#endif
