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

#include "QGraphicsGraphItem.h"

#define GRAPHICS_GRAPH_ITEM_SIZE QRect(0,0,200,100)

#include <QPainter>
#include <QPixmap>
#include <QtDebug>
#include <QPair>
#include <math.h>

#define MAX(a,b)		( (a)>(b) ? (a) : (b) )
#define MIN(a,b)		( (a)<(b) ? (a) : (b) )

namespace interlude
{

//--------------------------------------------------------------------------
QGraphicsGraphItem::QGraphicsGraphItem(QGraphicsItem * parent) :
	QGraphicsRectItem(GRAPHICS_GRAPH_ITEM_SIZE , parent),
	mMin(-1) , mMax(1),
	fNewData(-1),fBufferSize(0), // fCache(0),
	fLineStyle( kCurveLine ), 
	fDrawPath( kBoth ),
	fDefaultFrame(std::vector<float>())
{
//	setThicknessMode( kThicknessCentered );
	fBottomLineComputeFunction = YMinusHalfT;
	fTopLineComputeFunction = YPlusHalfT;
	fCurrentDrawer = 0;
	updateDrawer();
}

//--------------------------------------------------------------------------
QGraphicsGraphItem::~QGraphicsGraphItem()
{
//	if (fCache) delete fCache;
	if (fCurrentDrawer) delete fCurrentDrawer;
}

//--------------------------------------------------------------------------
float QGraphicsGraphItem::getY( float value , float yMin , float yMax ) const
{
	float yRatio = ( value - mMin ) / (mMax - mMin);
	return yMin + yRatio * (yMax - yMin);
}

//--------------------------------------------------------------------------
float QGraphicsGraphItem::getX(int index) const
{
	float xRatio = float( index ) / float( fCurrentDrawer->numberOfStripes(fBufferSize) );
	return xRatio * cacheWidth();
}

//--------------------------------------------------------------------------
int QGraphicsGraphItem::computeCacheHeight() const
{
	return sceneBoundingRect().height();
}

//-------------------------------------------------------------------------
int QGraphicsGraphItem::computeCacheWidth() const
{
	return stripeWidth() * fCurrentDrawer->numberOfStripes(fBufferSize);
}

//--------------------------------------------------------------------------
int QGraphicsGraphItem::computeStripeWidth() const
{
	if ( fCurrentDrawer->numberOfStripes(fBufferSize) )
	{
		int bw = ( sceneBoundingRect().width() / float(fCurrentDrawer->numberOfStripes(fBufferSize)) + 0.5f );
		return qMax(bw,1);
	}
	else
		return sceneBoundingRect().width();
}

//--------------------------------------------------------------------------
QPointF QGraphicsGraphItem::getPoint( float value , int index , float yMin , float yMax ) const
{
	return QPointF( getX(index) , getY(value , yMin , yMax) );
}

//--------------------------------------------------------------------------
QPointF QGraphicsGraphItem::getPoint( float value , int index ) const
{
	return getPoint( value , index , cacheHeight() , 0 );
}

//--------------------------------------------------------------------------
void QGraphicsGraphItem::StepDrawer::setPath( QPainterPath& path , const QList<QPointF>& points , int index , int stripeWidth, bool backWard ) const
{
//	QPointF current = path.currentPosition();
//	path.lineTo( ( points[index].x() + current.x() )/2.0f , current.y() );
//	path.lineTo( ( points[index].x() + current.x() )/2.0f , points[index].y() );
//	path.lineTo( points[index] );
	if ( backWard )
	{
		path.lineTo( points[index].x() + stripeWidth , points[index].y() );
		path.lineTo( points[index] );
	}
	else
	{
		path.lineTo( points[index] );
		path.lineTo( points[index].x() + stripeWidth , points[index].y() );
	}
}

//--------------------------------------------------------------------------
void QGraphicsGraphItem::CurveDrawer::setPath( QPainterPath& path , const QList<QPointF>& points , int index , int stripeWidth, bool ) const
{
	path.lineTo( points[index] );
}


/*
QPointF QGraphicsGraphItem::drawPathElement( QPainter& painter , const QPainterPath& path , const QPointF& startPoint , int style , int index ) const
{
	switch ( style )
	{
		case kStepLine:
		{
			painter.drawLine( startPoint , QPointF(path.elementAt(index*2)) );
			painter.drawLine( QPointF(path.elementAt(index*2)) , path.elementAt(index*2+1) );
			return path.elementAt(index*2+1);
		}
		case kCurveLine:
		default:
			painter.drawLine( startPoint , path.elementAt(index) );
			return path.elementAt(index);
	}
	return QPointF();
}
*/

#define TO_0_1(a) ((a/2.0f)+0.5f)
//--------------------------------------------------------------------------
QColor buildColor( float h , float s , float b , float a )
{
	if ( h<0 ) h+=2;
	float clippedH = h/2.0f;
	float clippedS = TO_0_1(s);
	float clippedB = TO_0_1(b);
	float clippedA = TO_0_1(a);
	clippedH = MAX( MIN( clippedH , 1 ) , 0 );
	clippedS = MAX( MIN( clippedS , 1 ) , 0 );
	clippedB = MAX( MIN( clippedB , 1 ) , 0 );
	clippedA = MAX( MIN( clippedA , 1 ) , 0 );
	return QColor::fromHsvF( clippedH , clippedS , clippedB , clippedA );
}

//--------------------------------------------------------------------------
void QGraphicsGraphItem::setSize( int bufferSize )
{
	if ( bufferSize != fBufferSize )
	{
		fBufferSize = bufferSize;
		while ( fFrames.size() > (unsigned int)(fBufferSize) )
			fFrames.erase( fFrames.begin() );

		updateDrawer();
		update();
	}
}

//--------------------------------------------------------------------------
// startIndex and endIndex are provided for possible optimizations
// actually draws from 0 to buffer size - 1
void QGraphicsGraphItem::paint( QPainter * painter , int startIndex , int endIndex )
{
	if ( fFrames.size() < 1 )				// Needs at least 1 frames
		return;

	while ( fFrames.size() > (unsigned int)(fBufferSize) )
		fFrames.erase( fFrames.begin() );

	// for each graphic signal (each group of 6 signals)
	for ( unsigned int parallelIndex = 0 ; parallelIndex < fFrames[0].size() ; parallelIndex++ )
	{	
		// should be changed to a list of pairs
		QPair< QList<QPointF> , QList<QPointF> > points;

		// -----------------------------------------------------------------------------------
		// A. Read the frame data and build the list of points defining the shape of the graph.
		// -----------------------------------------------------------------------------------
		int i;
		// If const pos & thickness
		if ( fConstSignals[parallelIndex][0] &&	fConstSignals[parallelIndex][1] )
		{
			GraphicFrame frame(fFrames[startIndex][parallelIndex]);
			// Start of the line
			points.first << getPoint( fBottomLineComputeFunction( frame ) , startIndex );
			points.second << getPoint( fTopLineComputeFunction( frame ) , startIndex );

			// End of the line
			points.first << getPoint( fBottomLineComputeFunction( frame ) , endIndex );
			points.second << getPoint( fTopLineComputeFunction( frame ) , endIndex );
		}
		else
		{
			for ( i = startIndex ; i <= endIndex ; i++ )
			{
				GraphicFrame frame(fFrames[i][parallelIndex]);
				points.first << getPoint( fBottomLineComputeFunction( frame ) , i );
				points.second << getPoint( fTopLineComputeFunction( frame ) , i );
			}
		}

		// -----------------------------------------------------------------------------------
		// B. Build the curve-path from the point list.
		// -----------------------------------------------------------------------------------
		QPainterPath path, topLine, bottomLine;

		path.moveTo( points.first.first().x() , points.first.first().y() );
		
		topLine.moveTo( points.second.first().x() , points.second.first().y() );
		bottomLine.moveTo( points.first.last().x() , points.first.last().y() );

		// ------------------------------------------------------------
		// B. 1. Build the top-bound of the curve path.
		for ( i = 0 ; i < points.second.size() ; i++ )
		{
			fCurrentDrawer->setPath( topLine , points.second , i , stripeWidth() );
			fCurrentDrawer->setPath( path , points.second , i , stripeWidth() );
		}

		// ------------------------------------------------------------
		// B. 2. Build the bottom-bound of the curve path.
		for ( i = points.first.size() - 1 ; i >= 0 ; i-- )
		{
			fCurrentDrawer->setPath( bottomLine , points.first , i , stripeWidth() , true );
			fCurrentDrawer->setPath( path , points.first , i , stripeWidth() , true );
		}

		// -----------------------------------------------------------------------------------
		// C. Use the curve-path to draw the graph.
		// -----------------------------------------------------------------------------------
		if ( (	fConstSignals[parallelIndex][2]				// If the signal has a constant color.
			&&	fConstSignals[parallelIndex][3]
			&&	fConstSignals[parallelIndex][4]
			&&	fConstSignals[parallelIndex][5]
			)
//			|| ( fIgnoreSignalColor && fPenIgnoreSignalColor )	// If the color signal is ignored.
//			|| ( fIgnoreSignalColor && ( pen() == Qt::NoPen ) )	// If the color signal is ignored for filling and there's no pen.
			)
		{


			// ------------------------------------------------------------
			// C.1 Constant color case.
			GraphicFrame frame(fFrames[startIndex][parallelIndex]);
			QColor color = buildColor(frame.getHue(), frame.getSaturation(), frame.getBrightness(), frame.getTransparency());
			
			// Fill the inside of the graph with its color
//			painter->setBrush( QBrush( fIgnoreSignalColor ? fDefaultFillColor : color ) );
			painter->setBrush( QBrush( color ) );
			painter->setPen( Qt::NoPen );
			painter->setClipPath( path );		// First, set the clip path with the shape of the graph.
			painter->drawRect( QRect( 0 , 0 , cacheWidth() , cacheHeight() ) ); // Then fill the entire graph rect: it will fill only the graph shape,
																					// because of the clip path.
			painter->setClipPath( path , Qt::NoClip );	// Finally, disable the clip path.

			if ( pen() != Qt::NoPen )	// If there's a valid pen defined, draw the border
			{
				QPen graphPen( pen() );
//				graphPen.setColor( fPenIgnoreSignalColor ? fDefaultPenColor : color );
				graphPen.setColor( color );

				painter->setPen( graphPen );
				painter->setBrush( QBrush( Qt::NoBrush ) );
				
				if ( fDrawPath == kBottom || fDrawPath == kBoth )
					painter->drawPath( bottomLine );

				if ( fDrawPath == kTop )
					painter->drawPath( topLine );
				else if ( fDrawPath == kBoth )
					if ( !fConstSignals[parallelIndex][1] || frame.getThickness() )		// Draw the top line if the signal's thickness is not null
						painter->drawPath( topLine );
			}
		}
		else
		{
			// ------------------------------------------------------------
			// C.2 Variable color case.
			
			painter->setClipPath( path );
			painter->setPen( Qt::NoPen );
			
			float currentX = fCurrentDrawer->startX( startIndex , stripeWidth() );
			QPointF currentPos(0,0);
			for ( i = startIndex ; i <= endIndex ; i++ )		// draw all stripes one by one
			{
				GraphicFrame frame(fFrames[i][parallelIndex]);
				QColor stripeColor = buildColor(frame.getHue(), frame.getSaturation(), frame.getBrightness(), frame.getTransparency());

//				painter->setBrush( QBrush( fIgnoreSignalColor ? fDefaultFillColor : stripeColor ) );
				painter->setBrush( QBrush( stripeColor ) );
				painter->drawRect( currentX , 0 , stripeWidth() , cacheHeight() );

				// paints the graph border using the current pen if any
				// this is optional regarding the graphic signals definition
				if ( pen() != Qt::NoPen )
				{
					QPen graphPen( pen() );
//					graphPen.setColor( fPenIgnoreSignalColor ? fDefaultPenColor : stripeColor );
					graphPen.setColor( stripeColor );
					
					// set a clipping for each stripe (very expensive !)
					painter->setClipRect( currentX , 0 , stripeWidth() , cacheHeight() );
					painter->setPen( graphPen );
//					painter->setBrush( Qt::NoBrush );
//					painter->drawRect( currentX , 0 , w , cacheHeight() );

//					currentPos = drawPathElement(*painter , path , currentPos , fLineStyle , i - startIndex );

					if ( fDrawPath == kBottom || fDrawPath == kBoth )
						painter->drawPath( bottomLine );

					if ( fDrawPath == kTop )
						painter->drawPath( topLine );
					else if ( fDrawPath == kBoth )
						if ( !fConstSignals[parallelIndex][1] || frame.getThickness() )		// Draw the top line if the signal's thickness is not null
							painter->drawPath( topLine );

					painter->setClipPath( path );
				}

				currentX += stripeWidth();
			}
			painter->setClipPath( path , Qt::NoClip );
			
		}
	}
}

//--------------------------------------------------------------------------
//void QGraphicsGraphItem::clear()
//{
//	fFrames.clear();
//}

//--------------------------------------------------------------------------
void QGraphicsGraphItem::updateDrawer()	// Update the current Drawer (indirection object ).
{
	if ( fCurrentDrawer ) delete fCurrentDrawer;
	
	if ( fBufferSize == 1 )	// If 1 value only, use a StepDrawer (a CurveDrawer needs at least 2 values to draw).
		fCurrentDrawer = new StepDrawer;
	else
		// The current Drawer is defined according to the fLineStyle.
		if ( fLineStyle == kCurveLine )
			fCurrentDrawer = new CurveDrawer;
		else
			fCurrentDrawer = new StepDrawer;
}

//--------------------------------------------------------------------------
void QGraphicsGraphItem::notifyConst( int signal , int dimension , bool isConst )
{
	while ( (unsigned int)(signal) >= fConstSignals.size() )
		fConstSignals.push_back( std::vector<bool>() );
	while ( (unsigned int)(dimension) >= fConstSignals[signal].size() )
		fConstSignals[signal].push_back( false );
	
	fConstSignals[signal][dimension] = isConst;
}

//--------------------------------------------------------------------------
QGraphicsGraphItem& QGraphicsGraphItem::operator << (const GraphicFrames& frame)
{ 
	fFrames.push_back(frame);

	update();
	return *this; 
}

//--------------------------------------------------------------------------
void QGraphicsGraphItem::paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * )
{
	fStripeWidth = computeStripeWidth();
	fCacheHeight = computeCacheHeight();
//	fBandWidth = computeBandWidth();
	fCacheWidth = computeCacheWidth();

	// Update all
//	if ( fCache )
//		delete fCache;
//	fCache = new QPixmap( cacheWidth() , cacheHeight() );
//	fCache->fill( QColor(255,255,255,0) );

	QPixmap cache( cacheWidth() , cacheHeight() );
	cache.fill( QColor(255,255,255,0) );
	QPainter pixmapPainter(&cache);
	paint( &pixmapPainter , 0 , fBufferSize-1 );
	
	painter->setRenderHints( QPainter::Antialiasing | QPainter::SmoothPixmapTransform );
	painter->drawPixmap( rect() , cache , QRect( 0 , 0 , cache.width() , cache.height() ) );
}

} // end namespoace
