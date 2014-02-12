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
void VExport::paintOnDevice( QPaintDevice * device , QGraphicsItem * item , float xScaleFactor , float yScaleFactor, float dx, float dy, bool drawChildren )
{
//	QRectF rect(0,0,device->width() , device->height() ); // not used ?
	QPainter painter;
	painter.begin( device );
//	painter.setRenderHint( QPainter::Antialiasing );
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);

	QStyleOptionGraphicsItem option;
	option.exposedRect = item->boundingRect();
	painter.scale( xScaleFactor , yScaleFactor );
	painter.translate( -item->boundingRect().topLeft() );
    painter.translate( dx, dy);
	item->paint( &painter , &option , 0 );
    if(drawChildren)
    {
        QList<QGraphicsItem*> list = item->childItems();
        paintChildrenOnDevice(&painter, option, list);
	}
    painter.end();
};

//------------------------------------------------------------------------------------------------------------------------
void VExport::paintChildrenOnDevice( QPainter * painter, QStyleOptionGraphicsItem option, QList<QGraphicsItem*> list)
{
    QList<QGraphicsItem*>::iterator it;
    float dx = 0;
    float dy = 0;
    for(it = list.begin(); it != list.end(); it++)
    {
        painter->translate((*it)->x(), (*it)->y()); // the painter goes to the center of the child element
        painter->translate(-(*it)->boundingRect().center()); // the painter goes to the top left corner of the child element
        (*it)->paint( painter , &option , 0 );
        
        dx = (*it)->boundingRect().center().x()-(*it)->x();
        dy = (*it)->boundingRect().center().y()-(*it)->y();
        
        QList<QGraphicsItem*> listOfChildren = (*it)->childItems();
        if(!listOfChildren.empty())
            paintChildrenOnDevice(painter, option, listOfChildren);
        
        painter->translate(dx,dy); // we replace the painter at the "origin" position : top left corner of the parent (item).
        
    }
}

//------------------------------------------------------------------------------------------------------------------------
QImage VExport::itemToImage( QGraphicsItem * item , float& xScaleFactor , float& yScaleFactor , const QColor fillColor, bool drawChildren, bool extend )
{
    QRectF rect = item->boundingRect();
	// if we export the children with the object, they might be out of its bounds : we have to take the smallest boundingRect that contains the item AND its children.
    // nonetheless, we keep the different behaviors : draw children ot not, extend the bounding rect or not.
    if(drawChildren && extend)
    {
        rect |= item->childrenBoundingRect();
    }
    float dx = item->boundingRect().x() - rect.x();
    float dy = item->boundingRect().y() - rect.y();
	QImage pic( int(rect.width() * xScaleFactor), int(rect.height() * yScaleFactor), QImage::Format_ARGB32 );
	pic.fill( fillColor.rgba() );
	paintOnDevice( &pic , item , xScaleFactor , yScaleFactor, dx, dy, drawChildren );
    
    return pic;
};

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportToImage( QGraphicsItem * item , const QString& fileName , float& xScale , float& yScale, bool drawChildren )
{
	itemToImage(item , xScale , yScale , Qt::white, drawChildren ).save( fileName );
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportToPdf( QGraphicsItem * item , const QString& fileName , float xScaleFactor , float yScaleFactor, bool drawChildren )
{
	QPrinter printer;
	printer.setFullPage(true);
	printer.setOutputFileName( QString(fileName) );
	printer.setOutputFormat( QPrinter::PdfFormat );

    QRectF rect = item->boundingRect();
	//if we export the children with the object, they might be out of its bounds : we have to take the smallest boundingRect that contains the item AND its children
	if(drawChildren)
    {
        rect |= item->childrenBoundingRect();
    }
    float dx = item->boundingRect().x() - rect.x();
    float dy = item->boundingRect().y() - rect.y();
	QSizeF pageSize(rect.width() * xScaleFactor , rect.height() * yScaleFactor );
	printer.setPaperSize( pageSize , QPrinter::DevicePixel );

	paintOnDevice( &printer , item , xScaleFactor , xScaleFactor, dx, dy, drawChildren );
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportItem(QGraphicsItem * item , QString fileName , float xScaleFactor , float yScaleFactor, bool drawChildren)
{
	if ( QFileInfo(fileName).suffix().isEmpty() )
		fileName += DEFAULT_EXPORT_FORMAT;

	if ( fileName.toUpper().endsWith( PDF_FORMAT.toUpper() ) )
		exportToPdf( item , fileName , xScaleFactor , yScaleFactor, drawChildren );
	else
		exportToImage( item , fileName , xScaleFactor , yScaleFactor, drawChildren );
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::paintOnDevice( QPaintDevice * device , QGraphicsView * view)
{
	QPainter painter(device);
	painter.setRenderHints(QPainter::Antialiasing | QPainter::TextAntialiasing | QPainter::SmoothPixmapTransform);
	view->render( &painter );
	painter.end();
}

//--------------------------------------------------------------------------
static bool exists (const QString& filename) 
{
	QFileInfo file (filename);
	return file.exists();
}

//--------------------------------------------------------------------------
static QString nextFreeName (const QString& filename, const QString& extension) 
{
	QString name = filename + extension;
	if (!exists (name)) return name;
	int n = 1;
	while (n < 1000) {
		QString num;
		num.setNum(n++);
		name = filename + '_' + num + extension;
		if (!exists (name)) break;
	}
	return name;
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportScene( QGraphicsView * view , QString fileName )
{
//	if ( QFileInfo(fileName).suffix().isEmpty() ) fileName += DEFAULT_EXPORT_FORMAT;
	if ( QFileInfo(fileName).suffix().isEmpty() ) fileName = nextFreeName(fileName, DEFAULT_EXPORT_FORMAT);

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
