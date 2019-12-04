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

#include "VShapeView.h"

#include "IShape.h"
#include "TComposition.h"

#include <QBrush>
#include <QPen>
#include <QGraphicsScene>

namespace inscore
{

#define DOT_LENGTH		0.5f
#define DASH_LENGTH		3.0f
#define SPACE_LENGTH	3.0f

//----------------------------------------------------------------------
void VShapeView::setQPenStyle(const std::string& penStyle , QPen& pen) const
{
	if ( penStyle == IShape::kSolidStyle )
		pen.setStyle( Qt::SolidLine );
	else if ( penStyle == IShape::kDotStyle )
	{
		pen.setStyle( Qt::CustomDashLine );
		pen.setDashPattern(  QVector<qreal>() << DOT_LENGTH << SPACE_LENGTH );
	}
	else if ( penStyle == IShape::kDashStyle )
	{
		pen.setStyle( Qt::CustomDashLine );
		pen.setDashPattern(  QVector<qreal>() << DASH_LENGTH << SPACE_LENGTH );
	}
	else if ( penStyle == IShape::kDashDotStyle )
	{
		pen.setStyle( Qt::CustomDashLine );
		pen.setDashPattern(  QVector<qreal>() << DASH_LENGTH << SPACE_LENGTH << DOT_LENGTH << SPACE_LENGTH );
	}
	else if ( penStyle == IShape::kDashDotDotStyle )
	{
		pen.setStyle( Qt::CustomDashLine );
		pen.setDashPattern(  QVector<qreal>() << DASH_LENGTH << SPACE_LENGTH << DOT_LENGTH << SPACE_LENGTH << DOT_LENGTH << SPACE_LENGTH );
	}
	else
		pen.setStyle( Qt::SolidLine );
}

void VShapeView::setQBrushStyle(const std::string& brushStyle , QBrush& brush) const
{
    if ( brushStyle == IShape::kSolidBrushStyle )
        brush.setStyle( Qt::SolidPattern );
    else if ( brushStyle == IShape::kDense1BrushStyle )
    {
        brush.setStyle( Qt::Dense1Pattern );
    }
    else if ( brushStyle == IShape::kDense2BrushStyle )
    {
        brush.setStyle( Qt::Dense2Pattern );
    }
    else if ( brushStyle == IShape::kDense3BrushStyle )
    {
        brush.setStyle( Qt::Dense3Pattern );
    }
    else if ( brushStyle == IShape::kDense4BrushStyle )
    {
        brush.setStyle( Qt::Dense4Pattern );
    }
    else if ( brushStyle == IShape::kDense5BrushStyle )
    {
        brush.setStyle( Qt::Dense5Pattern );
    }
    else if ( brushStyle == IShape::kDense6BrushStyle )
    {
        brush.setStyle( Qt::Dense6Pattern );
    }
    else if ( brushStyle == IShape::kDense7BrushStyle )
    {
        brush.setStyle( Qt::Dense7Pattern );
    }
    else if ( brushStyle == IShape::kNoBrushStyle )
    {
        brush.setStyle( Qt::NoBrush );
    }
    else if ( brushStyle == IShape::kHorBrushStyle )
    {
        brush.setStyle( Qt::HorPattern );
    }
    else if ( brushStyle == IShape::kVerBrushStyle )
    {
        brush.setStyle( Qt::VerPattern );
    }
    else if ( brushStyle == IShape::kCrossBrushStyle )
    {
        brush.setStyle( Qt::CrossPattern );
    }
    else if ( brushStyle == IShape::kBDiagBrushStyle )
    {
        brush.setStyle( Qt::BDiagPattern );
    }
    else if ( brushStyle == IShape::kFDiagBrushStyle )
    {
        brush.setStyle( Qt::FDiagPattern );
    }
    else if ( brushStyle == IShape::kDiagCrossBrushStyle )
    {
        brush.setStyle( Qt::DiagCrossPattern );
    }
    else
        brush.setStyle( Qt::SolidPattern );
}
    
//----------------------------------------------------------------------
VShapeView::VShapeView(QGraphicsScene * scene , QAbstractGraphicsShapeItem * abstractGraphicsShapeItem )
 : VGraphicsItemView( scene , abstractGraphicsShapeItem )
{
	fAbstractGraphicsShapeItem = abstractGraphicsShapeItem;
	
	fAbstractGraphicsShapeItem->setBrush( QBrush( Qt::white ) );
	fAbstractGraphicsShapeItem->setPen( QPen( Qt::white ) );
}

//----------------------------------------------------------------------
void VShapeView::updateView( IObject * shape  )
{
	QColor color(shape->getR(), shape->getG(), shape->getB() , shape->getA());
	QPen pen = Qt::NoPen;
	if ( shape->getPenWidth() > 0 )
	{
		pen = QPen( QColor(shape->getPenColor().getR(), shape->getPenColor().getG(), shape->getPenColor().getB() , shape->getPenColor().getA()) , shape->getPenWidth() );
		setQPenStyle( shape->getPenStyle() , pen );
        pen.setCapStyle( Qt::RoundCap );
		pen.setJoinStyle( Qt::RoundJoin );
	}
    
    
	if ( pen != fAbstractGraphicsShapeItem->pen() )
	{
		fAbstractGraphicsShapeItem->setPen( pen );
		itemChanged();
	}
	
    
//	if ( color != fAbstractGraphicsShapeItem->brush().color() )
//	{
        QBrush brush = QBrush(color);
        setQBrushStyle( shape->getBrushStyle() , brush );
		fAbstractGraphicsShapeItem->setBrush( brush );
		itemChanged();
//	}
    
    VGraphicsItemView::updateView (shape);
}

} // end namespoace
