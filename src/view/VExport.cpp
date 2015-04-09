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

#define USING_PD_FWRITER
#ifdef USING_PD_FWRITER
#include <QPdfWriter>
#endif


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
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::paintChildrenOnDevice(QPainter * painter, QStyleOptionGraphicsItem option, QList<QGraphicsItem*> list)
{
    QList<QGraphicsItem*>::iterator it;

    for(it = list.begin(); it != list.end(); it++)
    {
        const QTransform initMatrix = painter->transform();
        
        painter->translate((*it)->x(), (*it)->y()); // the painter goes to the center of the child element
        
        QTransform matrix = (*it)->transform();
		// Apply scale to matrix
		matrix.scale((*it)->scale(), (*it)->scale());
        painter->setTransform(matrix, true);
        
        //painter->translate(-(*it)->boundingRect().center()); // the painter goes to the top left corner of the child element
        
        (*it)->paint( painter , &option , 0 );

        QList<QGraphicsItem*> listOfChildren = (*it)->childItems();
        if(!listOfChildren.empty())
            paintChildrenOnDevice(painter, option, listOfChildren);
        
        painter->setTransform(initMatrix);
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
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportToImage( QGraphicsItem * item , const QString& fileName , float& xScale , float& yScale, bool drawChildren )
{
	itemToImage(item , xScale , yScale , Qt::white, drawChildren ).save( fileName );
}

//------------------------------------------------------------------------------------------------------------------------
void VExport::exportToPdf( QGraphicsItem * item , const QString& fileName , float xScaleFactor , float yScaleFactor, bool drawChildren )
{
#ifndef IOS
    QRectF rect = item->boundingRect();
	// if we export the children with the object, they might be out of its bounds :
	// we have to take the smallest boundingRect that contains the item AND its children
	if(drawChildren) {
        rect |= item->childrenBoundingRect();
	}
    float dx = item->boundingRect().x() - rect.x();
    float dy = item->boundingRect().y() - rect.y();

#ifdef USING_PD_FWRITER
	QPdfWriter pdf(fileName);
	pdf.setCreator("INScore");
	QSize pageSize(rect.width() * xScaleFactor, rect.height() * yScaleFactor);
	QPageSize size (pageSize);
	pdf.setResolution(96);
	pdf.setPageSize(size);
	pdf.setPageMargins(QMarginsF(0,0,0,0));
	paintOnDevice( &pdf , item , xScaleFactor , xScaleFactor, dx, dy, drawChildren );

//bool	setPageLayout(const QPageLayout & newPageLayout)
//bool	setPageMargins(const QMarginsF & margins)
//bool	setPageMargins(const QMarginsF & margins, QPageLayout::Unit units)
//bool	setPageOrientation(QPageLayout::Orientation orientation)
//bool	setPageSize(const QPageSize & pageSize)
//void	setResolution(int resolution)

#else
	QPrinter printer;
	printer.setColorMode(QPrinter::Color);
	printer.setFullPage(true);
	printer.setOutputFileName( QString(fileName) );
	printer.setOutputFormat( QPrinter::PdfFormat );
#ifdef USEPAPERSIZE			// QPageSize is not available for QT < 5.3
	QSizeF pageSize(rect.width() * xScaleFactor , rect.height() * yScaleFactor );
	printer.setPaperSize( pageSize , QPrinter::DevicePixel );
#else
	QSize size(rect.width() * xScaleFactor , rect.height() * yScaleFactor );
	QPageSize ps(size);
	printer.setPageSize(ps);
#endif

	paintOnDevice( &printer , item , xScaleFactor , xScaleFactor, dx, dy, drawChildren );
#endif
#endif
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
#ifndef IOS
	if ( QFileInfo(fileName).suffix().isEmpty() ) fileName = nextFreeName(fileName, DEFAULT_EXPORT_FORMAT);

	if ( fileName.toUpper().endsWith( PDF_FORMAT.toUpper() ) )
	{
		QSize size (view->width() , view->height());
		#ifdef USING_PD_FWRITER
		QPdfWriter pdf(fileName);
		pdf.setCreator("INScore");
		QPageSize pagesize (size);
		pdf.setResolution(1200);
		pdf.setPageSize(pagesize);
		pdf.setPageMargins(QMarginsF(0,0,0,0));
		paintOnDevice( &pdf, view);
		#else
		QPrinter printer (QPrinter::HighResolution);
		printer.setOutputFileName( QString(fileName) );
		printer.setOutputFormat( QPrinter::PdfFormat );
		printer.setPaperSize( size , QPrinter::Point );
		paintOnDevice (&printer, view);
		#endif
	}
	else
	{
		QImage image = sceneToImage(view);
		image.save( fileName );			
	}
#endif
}

QImage	VExport::sceneToImage(QGraphicsView * sceneview)
{
	QSize size (sceneview->width() , sceneview->height() );
	QImage image(size, QImage::Format_ARGB32_Premultiplied);
	image.fill( sceneview->backgroundBrush().color().rgba() );
	paintOnDevice (&image, sceneview);
	return image;
}

} // end namespoace
