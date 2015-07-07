/*
 * QGuidoGraphicsItem.cpp
 *
 * Created by Christophe Daudin on 12/05/09.
 * Copyright 2009 Grame. All rights reserved.
 *
 * This Source Code Form is subject to the terms of the Mozilla Public
 * License, v. 2.0. If a copy of the MPL was not distributed with this
 * file, You can obtain one at http://mozilla.org/MPL/2.0/.

 * Grame Research Laboratory, 11, cours de Verdun Gensoul 69002 Lyon - France
 * research@grame.fr
 */

//#include <QPainter>
#include <QStyleOptionGraphicsItem>

#include "QGuidoPainter.h"
#include "QPRollGraphicsItem.h"
#include "QGuidoPainter.h"

//-------------------------------------------------------------------------
QPRollGraphicsItem::QPRollGraphicsItem(QGraphicsItem * parent)
	: QGraphicsRectItem (parent)
{
    fPianoRoll = 0;
	fGuidoPainter = QGuidoPainter::createGuidoPainter();
}

QPRollGraphicsItem::~QPRollGraphicsItem() {
	QGuidoPainter::destroyGuidoPainter( fGuidoPainter );
}


//-------------------------------------------------------------------------
QString QPRollGraphicsItem::gmnCode() const
{
	return fGuidoPainter->gmnCode();
}

//-------------------------------------------------------------------------
bool QPRollGraphicsItem::setGMNCode(const QString& gmnCode)
{
    return fGuidoPainter->setGMNCode( gmnCode, 0);
}

//-------------------------------------------------------------------------
QString QPRollGraphicsItem::getLastErrorMessage() const
{
	return fGuidoPainter->getLastErrorMessage();
}

//-------------------------------------------------------------------------
void QPRollGraphicsItem::paint( QPainter * painter, const QStyleOptionGraphicsItem *, QWidget * )
{
	if (!fPianoRoll) return;

	painter->setBrush(QBrush(QColor(0,0,0)));
	painter->setPen(QColor(255,0,0));
	QRect rect = boundingRect().toRect();
	fGuidoPainter->drawPianoRoll(painter, rect, fPianoRoll);

//	for ( int i = mPageManager->firstVisiblePage() ; i <= mPageManager->lastVisiblePage() ; i++ )
//    {
//        QRectF pageRect;
//		pageRect.moveTo( mPageManager->pagePos(i) );
//		pageRect.setSize( mPageManager->pageSize(i) );
//		fGuidoPainter->drawPianoRoll(painter, pageRect.toRect(), fPianoRoll);
//    }
}

//-------------------------------------------------------------------------
void QPRollGraphicsItem::setPianoRoll(PianoRoll * pRoll)
{
	fPianoRoll = pRoll;
}
