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

#include "VExport.h"

#include <QStyleOptionGraphicsItem>
#include <QPrinter>
#include <QFileInfo>
#include <QDebug>

#define PDF_FORMAT				QString(".pdf")
#define DEFAULT_EXPORT_FORMAT	PDF_FORMAT

namespace inscore
{

//------------------------------------------------------------------------------------------------------------------------
void VExport::paintOnDevice( QPaintDevice * device , QGraphicsItem * item , float xScaleFactor , float yScaleFactor )
{
	QRectF rect(0,0,device->width() , device->height() );
	QPainter painter;
	painter.begin( device );
//	painter.setRenderHint( QPainter::Antialiasing );
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

	QStyleOptionGraphicsItem option;
	option.exposedRect = item->boundingRect();
	painter.scale( xScaleFactor , yScaleFactor );
	painter.translate( -item->boundingRect().topLeft() );
	item->paint( &painter , &option , 0 );
	painter.end();
};

//------------------------------------------------------------------------------------------------------------------------
QImage VExport::itemToImage( QGraphicsItem * item , float xScaleFactor , float yScaleFactor , const QColor fillColor )
{
	QRectF picRect = item->boundingRect();
	QImage pic( (int)(picRect.width() * xScaleFactor) , (int)(picRect.height() * yScaleFactor), QImage::Format_ARGB32 );

	pic.fill( fillColor.rgba() );
	paintOnDevice( &pic , item , xScaleFactor , yScaleFactor );
	return pic;
};

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportToImage( QGraphicsItem * item , const QString& fileName , float xScaleFactor , float yScaleFactor )
{
	itemToImage(item , xScaleFactor , yScaleFactor , Qt::white ).save( fileName );
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportToPdf( QGraphicsItem * item , const QString& fileName , float xScaleFactor , float yScaleFactor )
{
	QPrinter printer;
	printer.setFullPage(true);
	printer.setOutputFileName( QString(fileName) );
	printer.setOutputFormat( QPrinter::PdfFormat );

	QSizeF pageSize(item->boundingRect().width() * xScaleFactor , item->boundingRect().height() * yScaleFactor );
	printer.setPaperSize( pageSize , QPrinter::DevicePixel );

	paintOnDevice( &printer , item , xScaleFactor , xScaleFactor );
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportItem(QGraphicsItem * item , QString fileName , float xScaleFactor , float yScaleFactor)
{
	if ( QFileInfo(fileName).suffix().isEmpty() )
		fileName += DEFAULT_EXPORT_FORMAT;

	if ( fileName.toUpper().endsWith( PDF_FORMAT.toUpper() ) )
		exportToPdf( item , fileName , xScaleFactor , yScaleFactor );
	else
		exportToImage( item , fileName , xScaleFactor , yScaleFactor );
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::paintOnDevice( QPaintDevice * device , QGraphicsView * view)
{
	QPainter painter(device);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
	view->render( &painter );
	painter.end();
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportScene( QGraphicsView * view , QString fileName )
{
	if ( QFileInfo(fileName).suffix().isEmpty() ) fileName += DEFAULT_EXPORT_FORMAT;

	QSize size (view->width() , view->height());
	if ( fileName.toUpper().endsWith( PDF_FORMAT.toUpper() ) )
	{
		QPrinter printer (QPrinter::HighResolution);
		printer.setOutputFileName( QString(fileName) );
		printer.setOutputFormat( QPrinter::PdfFormat );
		printer.setPaperSize( size , QPrinter::Point );
		paintOnDevice (&printer, view);
	}
	else
	{
		QImage image(size, QImage::Format_ARGB32_Premultiplied);
		image.fill( view->backgroundBrush().color().rgba() );
		paintOnDevice (&image, view);
		image.save( fileName );			
	}
}

} // end namespoace
