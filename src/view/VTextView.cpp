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

#include <iostream>

#include "VTextView.h"
#include "VApplView.h"
#include "ITLError.h"

#include <QTextDocument>
#include <QTextBlock>
#include <QTextLine>
#include <QFile>
#include <QAbstractTextDocumentLayout>
#include <QTextLayout>

//#include "QTextTilerItem.h"

namespace INScore
{

//----------------------------------------------------------------------
VTextView::VTextView(QGraphicsScene * scene, const EventsAble* h)
 :	VIntPointObjectView( scene , new IQGraphicsTextItem(h) )
{
	fTextItem = (IQGraphicsTextItem*)(fItem);
	fTextItem->document()->setDocumentMargin(0);
}

//----------------------------------------------------------------------
void VTextView::updateView( IText * text )
{
	// 1. Update color
	QColor color(text->getR(), text->getG(), text->getB() , text->getA());
	if ( color != fTextItem->defaultTextColor() )
	{
		fTextItem->setDefaultTextColor( color );
		itemChanged();
	}
	VGraphicsItemView::updateView( text );
}

//-------------------------------------------------------------------------
void VTextView::updateLocalMapping (IText* text)
{
	PlainTextInterface interface(fTextItem);
	updateLocalMapping(text,interface);
}

//-------------------------------------------------------------------------
void VTextView::updateLocalMapping (IHtml* text)
{
	HtmlTextInterface interface(fTextItem);
	updateLocalMapping(text,interface);
}

//-------------------------------------------------------------------------
void VTextView::updateLocalMapping (IText* text, TextInterface& textInterface)
{
	// 1. Update text
	QString newText = VApplView::toQString( text->getText().c_str() );
	if ( textInterface.get() != newText )
	{
		textInterface.set( newText );
		updateQtTextTable();	// computes at list of lists of rectangles in Qt coordinates for each [line,char]
		itemChanged();
	}

	VIntPointObjectView::updateLocalMapping( text );
}

//-------------------------------------------------------------------------
QString getFileContent(const QString& fileName)
{
	QString content = "";
    QFile file(fileName);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
	{
		file.close();
		return "";
	}

    while (!file.atEnd()) 
	{
        QByteArray line = file.readLine();
        content += line;
    }
	file.close();
	return content;
}

//----------------------------------------------------------------------
void VTextView::updateQtTextTable()
{
	fCharRects.clear();

	// text is organized  in blocks, each block may contain several text lines
	for ( QTextBlock bloc = fTextItem->document()->begin() ; bloc != fTextItem->document()->end() ; bloc = bloc.next() )
	{
		for ( int lineIndex = 0 ; lineIndex < bloc.layout()->lineCount() ; lineIndex++ )
		{
			QTextLine line = bloc.layout()->lineAt(lineIndex);
			// coordinates are relative to the block and to the current line
			QRectF lineRect( line.rect().translated( bloc.layout()->position() + line.position() ) );
			// adds a new rects list for the current line
			fCharRects << QList<QRectF>();
			int curPos = 0;
			// get the first character x position
			float xPos = line.cursorToX( &curPos ,  QTextLine::Leading );
			for ( curPos = 1 ; curPos <= line.textLength() ; curPos++ )
			{
				float oldPos = xPos;
				// get the current character x position
				xPos = line.cursorToX( &curPos ,  QTextLine::Leading );
				// builds the current character x position
				QRectF charRect( lineRect.x() + oldPos , lineRect.y(), xPos - oldPos , lineRect.height() );
				// and finally adds the rect to the rects list
				fCharRects.last() << charRect;
			}
		}
	}

/*
	// Debug: Show character rects
	while ( fCharItems.size() )
	{
		delete fCharItems[0];
		fCharItems.removeAt(0);
	}
	for ( int i = 0 ; i < fCharRects.size() ; i++ )
		for ( int j = 0 ; j < fCharRects[i].size() ; j++ )
		{
			QGraphicsRectItem * item = new QGraphicsRectItem( fCharRects[i][j] , fTextItem );
			item->setPen( QPen( Qt::blue ) );
			fCharItems << item;
		}
	// End debug
*/
}

//----------------------------------------------------------------------
// converts a segment expressed in text coordinates in a segment expressed in Interlude coordinates
// using the list of rects list build by updateQtTextTable
GraphicSegment VTextView::getGraphicSegment( const IntPointSegment& intPointSegment , const IGraphicBasedObject * object , bool& mapOk ) const
{
	TLongPoint textPointA (intPointSegment.xinterval().first(), intPointSegment.yinterval().first());
	TLongPoint textPointB (intPointSegment.xinterval().second()-1, intPointSegment.yinterval().second()-1);
	
	TLongPoint errPoint;
	mapOk = true;
	if ( ( textPointA.y() >= fCharRects.size() ) || ( textPointA.x() >= fCharRects[textPointA.y()].size() ) )
	{
		errPoint = textPointA;			
		mapOk = false;
	}
	if ( ( textPointB.y() >= fCharRects.size() ) || ( textPointB.x() > fCharRects[textPointB.y()].size() ) )
	{
		errPoint = textPointB;
		mapOk = false;
	}

	if ( !mapOk )
	{
		const char* msg1 = "text mapping of object";
		const char* msg2 = "refers to 'out of bounds' character:";
		ITLErr << msg1 << object->getOSCAddress() << msg2 << "[" << errPoint.x() << ";" << errPoint.y() << "]" << ITLEndl;
		return GraphicSegment();
	}
	else
	{
		QPointF startPointQt, endPointQt;
		startPointQt = fCharRects[textPointA.y()][textPointA.x()].topLeft();
		endPointQt  = (textPointB.x() == fCharRects[textPointB.y()].size()) ?	// check line end
				fCharRects[textPointB.y()][textPointB.x()-1].bottomRight()		
			:	fCharRects[textPointB.y()][textPointB.x()].bottomLeft();
	
		TFloatPoint a = qGraphicsItem2IObject( startPointQt , fTextItem->boundingRect() );
		TFloatPoint b = qGraphicsItem2IObject( endPointQt , fTextItem->boundingRect() );
		return GraphicSegment( a.x(), a.y() , b.x(), b.y() );
	}
}


} // end namespoace
