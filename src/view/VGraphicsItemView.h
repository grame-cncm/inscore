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


#ifndef __VGraphicsItemView__
#define __VGraphicsItemView__

#include <iostream>

#include "IModel.h"
#include "IText.h"
#include "ISync.h"
#include "TVirtualRelation.h"
#include "TComposition.h"
#include "TMappingComposer.h"
#include "QStretchTilerItem.h"

#include <QGraphicsItem>
#include <QGraphicsRectItem>

namespace interlude
{

/*!
\addtogroup ITLView 
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IObject that uses a QGraphicsItem to render.
*/
class VGraphicsItemView
{
	public :
		virtual ~VGraphicsItemView();
		
		virtual void drawMapping (IObject* o);
		virtual void drawNameAndBBox (IObject* o);

		virtual void updateView(IObject * object);			// updates the object view
		virtual void setParentView (IObject * object);		// updates the object parent view
		virtual void updateObjectSize( IObject * object );	// updates the object size
		virtual void setParentItem( VGraphicsItemView* master )	{ item()->setParentItem( master ? master->item() : 0); }
		
		float getIObjectWidth() const { return scene2RelativeWidth( fItem->boundingRect().width() ); }		// Gives the object's width in interlude scene coordinates.
		float getIObjectHeight() const { return scene2RelativeHeight( fItem->boundingRect().height() ); }	// Gives the object's height in interlude scene coordinates.

		
		static void buildDefaultMapping (IObject* object);
		
	protected:
		VGraphicsItemView( QGraphicsScene * scene , QGraphicsItem * item );
		
		template <typename L>
		static void setMapping( IObject* object , const std::string& mapName , SMARTP<TMapping<GraphicSegment, L> > g2l_mapping , SMARTP<TMapping<L, RelativeTimeSegment> > l2t_mapping)
		{
			// create the graphic to time composition
			// composition reduction to a simple mapping
			typedef TComposition <RelativeTimeSegment, L, GraphicSegment>		T2GComposition;
			SRelativeTime2GraphicMapping t2gr = T2GComposition::create( l2t_mapping->reverse(), g2l_mapping->reverse() );
			object->setMapping( mapName , t2gr );
		}
		
		/// \brief Returns the reference rectangle for the QGraphicsItem coordinate: the master QRect or the scene QRect (if there's no master).
		QRectF referenceRect() const;

		/// \brief Maps the IObject [-1,1] y coordinate to the referenceRect().
		float relative2SceneY(float y) const;
		/// \brief Maps the IObject [-1,1] x coordinate to the referenceRect().
		float relative2SceneX(float x) const;
		/// \brief Maps the IObject [0,2] width value to the corresponding referenceRect() value.
		float relative2SceneWidth(float width) const;
		/// \brief Maps the IObject [0,2] height value to the corresponding referenceRect() value.
		float relative2SceneHeight(float height) const;
		/// \brief Maps a rect expressed in [-1,1] scene coordinate to a QRectF expressed in referenceRect() coordinates.
		QRectF relative2SceneRect( const TFloatRect& rect) const;
		/// \brief Maps the referenceRect() width value to the corresponding [0,2] value.
		float scene2RelativeWidth(float width) const;
		/// \brief Maps the referenceRect() height value to the corresponding [0,2] value.
		float scene2RelativeHeight(float height) const;
		/// \brief Maps the referenceRect() x value to the corresponding [-1,1] value.
		float scene2RelativeX(float x) const;
		/// \brief Maps the referenceRect() y value to the corresponding [-1,1] value.
		float scene2RelativeY(float y) const;

		/// \brief Maps a point in QGraphicsItem coordinate to a point in IObject internal coordinate. ( [-1,1], (0,0) is the center of the object, (-1,-1) is )
		///	the topLeft, (1,1) is the bottomright.
		TFloatPoint qGraphicsItem2IObject(const QPointF& point) const;
		/// \brief Similar to qGraphicsItem2IObject(const QPointF& point), but specifying the reference Qt rect.
		TFloatPoint qGraphicsItem2IObject(const QPointF& point, const QRectF& rect) const;
		/// \brief Maps a point in IObject internal coordinate to a point in QGraphicsItem coordinate.
		QPointF iObject2QGraphicsItem(const TFloatPoint& point) const;
		/// \brief Maps a rect in IObject internal coordinate to a rect in QGraphicsItem coordinate.
		QRectF iObject2QGraphicsItem(const TFloatRect& rect) const;
		/// \brief Maps a point in IObject internal coordinate to a point in the specified QRectF.
		QPointF iObject2QGraphicsItem(const TFloatPoint& point, const QRectF& qrect) const;
		/// \brief Maps a rect in IObject internal coordinate to a rect in the specified QRectF.
		QRectF iObject2QGraphicsItem(const TFloatRect& rect, const QRectF& qrect) const;

		/// \brief QPoint to TLongPoint converter.
		static TLongPoint qPointToLongPoint(const QPoint& p)		{ return TLongPoint(p.x(),p.y());}
		/// \brief TLongPoint to QPoint converter.
		static QPoint longPointToQPoint(const TLongPoint& p)		{ return QPoint(p.x(),p.y());}
		/// \brief QPointF to TFloatPoint converter.
		static TFloatPoint qPointFToFloatPoint(const QPointF& p)	{ return TFloatPoint(p.x(),p.y());}
		/// \brief TFloatPoint to QPointF converter.
		static QPointF floatPointToQPointF(const TFloatPoint& p)	{ return QPointF(p.x(),p.y());}

		/// \brief Activate/desactivate stretch.
		void setStretch( bool isStretchOn );

		/// \brief Returns the QGraphicsItem or the QTilerItem, whether stretch-mode is on or off.
				QGraphicsItem * item()			{ return fIsStretchOn ? fTilerItem : fItem; }
		const	QGraphicsItem * item() const	{ return fIsStretchOn ? fTilerItem : fItem; }

		bool isStretchOn() const { return fIsStretchOn; }
		
		/// \brief Builds the QTilerItem to be used for stretching.
		virtual QStretchTilerItem* buildTiler();
		/// \brief Must be called when the QGraphicsItem has been modified in VGraphicsItemView subclasses.
		void itemChanged();
		
		void deleteDebugItems();		/// \brief deletes the debug node items

		QGraphicsItem * fItem;			/// \brief The QGraphicsItem used to render the IObject.
		QStretchTilerItem * fTilerItem;	/// \brief The QTilerItem used when stretching a slave item
		QList<QGraphicsItem*> fDebugItems;
		int fBrushColorStartIndex;

		QRectF fLastValidRect;
		bool fIsStretchOn;
};
typedef class SMARTP<VGraphicsItemView>	SVGraphicsItemView;

/*!@} */

} // end namespoace

#endif
