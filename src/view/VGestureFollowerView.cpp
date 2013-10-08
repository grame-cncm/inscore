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

#include <QDebug>
#include <QPainter>
#include <algorithm>
#include <QGraphicsRectItem>

#include "VGestureFollowerView.h"
#include "IGestureFollower.h"

using namespace std;
using namespace libmapping;

namespace inscore
{


#define kAlpha	120
#define kLow	10
#define kMed	100
#define kColorsCount 10
static QColor gColors[] = {
	QColor(255, kLow, kLow, kAlpha),
	QColor(kLow, 255, kLow, kAlpha),
	QColor(kLow, kLow, 255, kAlpha),
	QColor(200, 200, kLow, kAlpha),
	QColor(kLow, 200, 200, kAlpha),
	QColor(200, kLow, 200, kAlpha),
	QColor(120, 120, 120, kAlpha),
	QColor(255, kMed, kMed, kAlpha),
	QColor(kMed, 255, kMed, kAlpha),
	QColor(kMed, kMed, 255, kAlpha),
};

//----------------------------------------------------------------------
class GFRect : public QGraphicsRectItem
{
	const IGestureFollower* fGF;
	public:
			GFRect (QGraphicsItem * parent = 0): fGF(0) {}
		virtual ~GFRect() {}
		
	void setGF (const IGestureFollower* gf)		{ fGF = gf; }
	void paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0);
};

//----------------------------------------------------------------------
void GFRect::paint(QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget)
{
	QGraphicsRectItem::paint(painter, option, widget);
	QRectF ir = boundingRect();
	float border = 5;
	QRectF r (border, border, ir.width()-(border*2), ir.height()-(border*2));
	if (fGF->learning()) {
		painter->setPen(QColor(Qt::red));
		painter->drawRect( ir );
		painter->fillRect( ir, QColor (150,150,150,fGF->getA()));
	}

	int n = fGF->gesturesCount();
	float wl = r.width()/n;
	float hl = r.height()/(n*2);

	QColor borderColor = fGF->idle() ? Qt::gray : Qt::black;
	QColor thresholdColor = QColor(50,50,50);
	
	float x = r.left();
	const float* likelihood = fGF->likelihood();
	float h = r.height()/2;
	for (int i=0; i<n; x+=wl, i++) {
		float eqh = r.top() + h - (h * fGF->likelihoodThreshold(i));
		painter->setPen(borderColor);
		painter->drawRect( QRectF (x, r.top(), wl, h) );
		if (fGF->following()) {
			float hlike = h * likelihood[i];
			QColor color = gColors[i % kColorsCount];
			color.setAlpha (fGF->getA());
			painter->fillRect( QRectF(x, r.top()+h-hlike, wl, hlike), color );
		}
		else {
			float fill = (h * fGF->getPhraseSize (i) * fGF->getFrameSize()) / fGF->getCapacity();
			painter->fillRect( QRectF(x, r.top()+h-fill, wl, fill), QColor(100, 100, 200, fGF->getA()));
		}
		painter->setPen(thresholdColor);
		painter->drawLine( x, eqh, x+wl, eqh );
	}

	float y = r.top() + r.height()/2;
	const float* where = fGF->where();
	painter->setPen(borderColor);
	for (int i=0; i<n; y+=hl, i++) {
		QRectF lr (r.left(), y, r.width(), hl);
		painter->drawRect( QRectF (r.left(), y, r.width(), hl) );
		if (fGF->following()) {
			float plike = r.width() * where[i];
			QColor color = gColors[i % kColorsCount];
			color.setAlpha (fGF->getA());
			painter->fillRect( QRectF(r.left(), y, plike, hl), color);
		}
	}
}

//----------------------------------------------------------------------
MouseEventAble<GFRect>*  VGestureFollowerView::item() const		{ return (MouseEventAble<GFRect>*)fItem; }

//----------------------------------------------------------------------
VGestureFollowerView::VGestureFollowerView(QGraphicsScene * scene, const IGestureFollower* gf)
	: VMappedShapeView( scene , new MouseEventAble<GFRect>(gf) )
{
	item()->setGF (gf);
}

//----------------------------------------------------------------------
void VGestureFollowerView::updateView( IGestureFollower * gf  )
{
    gf->cleanupSync();
    if(!gf->getParent()->getMaster(gf) && !gf->getParent()->getDeleted())
    {
        if(gf->getParent()->getTypeString() != IAppl::kApplType && gf->getParent()->getTypeString() != IScene::kSceneType)
            setParentItem(gf->getParent()->getView()?gf->getParent()->getView():0);
    }
	float h = relative2SceneHeight(gf->getHeight());
	float w = relative2SceneWidth(gf->getWidth());
	QRectF newRect( 0,0, w, h );
	item()->setRect( newRect );
	itemChanged();
	VShapeView::updateView( gf );
}

} // end namespoace
