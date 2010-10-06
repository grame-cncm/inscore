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


#ifndef __QStretchTilerItem__
#define __QStretchTilerItem__

#include <QGraphicsRectItem>
#include <QPair>

namespace interlude
{

class QStretchTilerItem: public QGraphicsRectItem
{
	QGraphicsItem * fStretchTiledItem;

	QPixmap fCache;
	float fCacheFactor;
	typedef QPair<QRectF,QRectF> QRectFPair;
	QList<QRectFPair> fMapping;
	bool fNeedCacheUpdate;

	public:

		QStretchTilerItem( QGraphicsItem* tiledItem , QGraphicsItem* parent = 0 )
		: QGraphicsRectItem( QRect() , parent ) , fStretchTiledItem(tiledItem) , fCacheFactor(1.0) , fNeedCacheUpdate(true) {}
		
		virtual ~QStretchTilerItem() {}
		
		/*! 
		*	\brief QGraphicsItem::paint implementation.
		*		- Updates 'just-in-time' the cache rendering of the fTiledItem if updateCache() has been called.
		*		- then draws parts of this cache to their destination (set with addSegment)
		*/
		void paint ( QPainter * painter , const QStyleOptionGraphicsItem * , QWidget * );

		virtual void clearSegments() { fMapping.clear(); }

		virtual void addSegment( const QRectF& sourceRect , const QRectF& destRect );
		
		/// \brief	To be called when the tiled-Item appearance has changed.
		void updateCache() { fNeedCacheUpdate = true; }

		/// \brief QGraphicsItem implementation (a QGraphicsItem must not draw outside of its boundingRect()).
		QRectF boundingRect() const { return rect(); }
};

}

#endif // #ifndef __QStretchTilerItem__