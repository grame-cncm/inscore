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
	painter.setRenderHint( QPainter::Antialiasing );

	QStyleOptionGraphicsItem option;
	option.exposedRect = item->boundingRect();
	painter.scale( xScaleFactor , yScaleFactor );
	painter.translate( -item->boundingRect().topLeft() );
	item->paint( &painter , &option , 0 );
	painter.end();
};

//------------------------------------------------------------------------------------------------------------------------
#ifdef PIXMAPBASED
QPixmap VExport::itemToImage( QGraphicsItem * item , float xScaleFactor , float yScaleFactor , const QColor fillColor )
{
	QRectF picRect = item->boundingRect();
	QPixmap pic( (int)(picRect.width() * xScaleFactor) , (int)(picRect.height() * yScaleFactor) );

	pic.fill( fillColor );
	paintOnDevice( &pic , item , xScaleFactor , yScaleFactor );
	return pic;
};
#else
QImage VExport::itemToImage( QGraphicsItem * item , float xScaleFactor , float yScaleFactor , const QColor fillColor )
{
	QRectF picRect = item->boundingRect();
	QImage pic( (int)(picRect.width() * xScaleFactor) , (int)(picRect.height() * yScaleFactor), QImage::Format_ARGB32 );

	pic.fill( fillColor.rgba() );
	paintOnDevice( &pic , item , xScaleFactor , yScaleFactor );
	return pic;
};
#endif

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
void VExport::exportScene( QGraphicsView * scene , QString fileName )
{
	if ( QFileInfo(fileName).suffix().isEmpty() )
		fileName += DEFAULT_EXPORT_FORMAT;

	if ( fileName.toUpper().endsWith( PDF_FORMAT.toUpper() ) )
	{
		QPrinter printer;
		printer.setFullPage(true);
		printer.setOutputFileName( QString(fileName) );
		printer.setOutputFormat( QPrinter::PdfFormat );

		QSizeF pageSize(scene->width() , scene->height() );
		printer.setPaperSize( pageSize , QPrinter::DevicePixel );

		QPainter painter(&printer);
		scene->render( &painter );
		painter.end();
	}
	else
	{
#ifdef PIXMAPBASED
		QPixmap pixmap(scene->width() , scene->height());
		pixmap.fill( scene->backgroundBrush().color() );
#else
		QImage pixmap(scene->width() , scene->height(), QImage::Format_ARGB32_Premultiplied);
		pixmap.fill( scene->backgroundBrush().color().rgba() );
#endif
		QPainter painter(&pixmap);
		painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
		scene->render( &painter );
		painter.end();
		pixmap.save( fileName );			
	}
}

} // end namespoace
