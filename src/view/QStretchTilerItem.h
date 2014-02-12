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


#ifndef __QStretchTilerItem__
#define __QStretchTilerItem__

#include <QGraphicsRectItem>
#include <QImage>
#include <QPair>
#include <VExport.h>

//#define PIXMAPBASED

namespace inscore
{

class QStretchTilerItem: public QGraphicsRectItem
{
	QGraphicsItem * fOriginItem;

#ifdef PIXMAPBASED
	QPixmap fCache;
#else
	QImage fCache;
	QImage fExtendedCache;
	QImage fSimpleCache;
#endif
	typedef QPair<QRectF,QRectF> QRectFPair;
	QList<QRectFPair> fMapping;

    bool fNeedCacheUpdate;
    bool fIsStretch;

	public:

		QStretchTilerItem( QGraphicsItem* tiledItem, QGraphicsItem* parent = 0)
		: QGraphicsRectItem( QRect() , parent ) , fOriginItem(tiledItem), fNeedCacheUpdate(true), fIsStretch(false) {}
		
		virtual ~QStretchTilerItem() {}
		
		/*! 
		*	\brief QGraphicsItem::paint implementation.
		*		- Updates 'just-in-time' the cache rendering of the fTiledItem if updateCache() has been called.
		*		- then draws parts of this cache to their destination (set with addSegment)
		*/
		virtual void paint ( QPainter * painter , const QStyleOptionGraphicsItem * , QWidget * );

		virtual void clearSegments() {fMapping.clear();}

		virtual void addSegment( const QRectF& sourceRect , const QRectF& destRect);
		
		/// \brief	setting of the new image
		void setStretch(bool stretch) {fIsStretch = stretch;}
    
        void needUpdate(bool needCacheUpdate){fNeedCacheUpdate = needCacheUpdate;}

        void updateCache(){
            float xscale = 1.f;
            float yscale = 1.f;
            // the first boolean means that we draw also the children
            // the second boolean means that we extend or not the bounding rect to the children.
            fSimpleCache = VExport::itemToImage( fOriginItem , xscale , yscale, QColor(255, 255, 255, 0), true, false );
            fExtendedCache = VExport::itemToImage( fOriginItem , xscale , yscale, QColor(255, 255, 255, 0), true, true );
        }
    
        void chooseCache(){fCache = fIsStretch ? fSimpleCache : fExtendedCache;}

		/// \brief QGraphicsItem implementation (a QGraphicsItem must not draw outside of its boundingRect()).
		QRectF boundingRect() const { return rect(); }

};

}

#endif // #ifndef __QStretchTilerItem__