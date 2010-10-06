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

#include "VShapeView.h"

#include "IShape.h"
#include "TComposition.h"

#include <QBrush>
#include <QPen>
#include <QGraphicsScene>

namespace interlude
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

//----------------------------------------------------------------------
VShapeView::VShapeView(QGraphicsScene * scene , QAbstractGraphicsShapeItem * abstractGraphicsShapeItem )
 : VGraphicsItemView( scene , abstractGraphicsShapeItem )
{
	fAbstractGraphicsShapeItem = abstractGraphicsShapeItem;
	
	fAbstractGraphicsShapeItem->setBrush( QBrush( Qt::white ) );
	fAbstractGraphicsShapeItem->setPen( QPen( Qt::white ) );
}

//----------------------------------------------------------------------
void VShapeView::updateView( IShape * shape  )
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
	
	if ( color != fAbstractGraphicsShapeItem->brush().color() )
	{
		fAbstractGraphicsShapeItem->setBrush( QBrush( color ) );
		itemChanged();
	}
	VGraphicsItemView::updateView (shape);
}

} // end namespoace
