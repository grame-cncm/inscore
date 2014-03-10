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


#ifndef __VGraphicsItemView__
#define __VGraphicsItemView__

#include <iostream>

#include "VObjectView.h"

#include "IModel.h"
#include "IText.h"
#include "ISync.h"
#include "TRefinedComposition.h"
#include "QStretchTilerItem.h"
#include "GraphicEffect.h"
#include "maptypes.h"

#include <QGraphicsItem>
#include <QGraphicsRectItem>

namespace inscore
{

/*!
\addtogroup ITLView 
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IObject that uses a QGraphicsItem to render.
*/
class VGraphicsItemView : public VObjectView
{
	public :
		virtual ~VGraphicsItemView();

		virtual void updateView(IObject * object);			// updates the object view
		virtual void updateObjectSize( IObject * object );	// updates the object size
		//virtual void setParentView (IObject * object);		// updates the object parent view
		virtual void setParentItem( VObjectView* parent )		{ setParentItem((VGraphicsItemView*)parent); }
		virtual void setParentItem( VGraphicsItemView* parent ){ fParent = parent ? parent->item() : 0;
                                                                fItem->setParentItem(parent ? parent->item() : 0);}
    
        virtual void setEffect (GraphicEffect& effect)		{ item()->setGraphicsEffect (effect.get()); }
		virtual GraphicEffect getEffect () const			{ return GraphicEffect ( item()->graphicsEffect()); }

		/// \brief Maps the IObject [-1,1] y coordinate to the referenceRect().
		double relative2SceneY(float y, QGraphicsItem * item = 0 ) const;
		/// \brief Maps the IObject [-1,1] x coordinate to the referenceRect().
		double relative2SceneX(float x, QGraphicsItem * item = 0 ) const;
		/// \brief Maps the IObject [0,2] width value to the corresponding referenceRect() value.
		double relative2SceneWidth(float width, QGraphicsItem * item = 0 ) const;
		/// \brief Maps the IObject [0,2] height value to the corresponding referenceRect() value.
		double relative2SceneHeight(float height, QGraphicsItem * item = 0 ) const;
		/// \brief Maps a rect expressed in [-1,1] scene coordinate to a QRectF expressed in referenceRect() coordinates.
//		QRectF relative2SceneRect( const TFloatRect& rect) const;

		/// \brief Maps the referenceRect() width value to the corresponding [0,2] value.
		double scene2RelativeWidth(float width, QGraphicsItem * item = 0 ) const;
		/// \brief Maps the referenceRect() height value to the corresponding [0,2] value.
		double scene2RelativeHeight(float height, QGraphicsItem * item = 0 ) const;
		/// \brief Maps the referenceRect() x value to the corresponding [-1,1] value.
		double scene2RelativeX(float x, QGraphicsItem * item = 0 ) const;
		/// \brief Maps the referenceRect() y value to the corresponding [-1,1] value.
		double scene2RelativeY(float y, QGraphicsItem * item = 0 ) const;
		
		static void buildDefaultMapping (IObject* object);
		
	protected:
		VGraphicsItemView( QGraphicsScene * scene , QGraphicsItem * item );
		
		virtual void drawMapping (IObject* o);
		virtual void drawNameAndBBox (IObject* o);
		virtual void updateTransform(IObject * object);		// updates the object transform matrix
		
		float getIObjectWidth() const { return scene2RelativeWidth( fItem->boundingRect().width() ); }		// Gives the object's width in interlude scene coordinates.
		float getIObjectHeight() const { return scene2RelativeHeight( fItem->boundingRect().height() ); }	// Gives the object's height in interlude scene coordinates.
		
		template <typename T, unsigned int D>
		static void setMapping( IObject* object ,
				const std::string& mapName , libmapping::SMARTP<libmapping::TMapping<float,2,T,D> > g2l_mapping ,
				libmapping::SMARTP<libmapping::TMapping<T,D, libmapping::rational,1> > local2time_mapping,
				bool refine=false)
		{
			// if refined, create the graphic to time composition using a refined composition
			if (refine) {
				typedef libmapping::TRefinedComposition <libmapping::rational,1,T,D, float,2> T2GComposition;
				SRelativeTime2GraphicMapping t2gr = T2GComposition::create( local2time_mapping->direct(), g2l_mapping->reverse() );
				object->setMapping( mapName , t2gr );
			}
			else {
				typedef libmapping::TComposition <libmapping::rational,1,T,D, float,2> T2GComposition;
				SRelativeTime2GraphicMapping t2gr = T2GComposition::create( local2time_mapping->reverse(), g2l_mapping->reverse() );
				object->setMapping( mapName , t2gr );
			}
		}
		
		/// \brief Returns the reference rectangle for the QGraphicsItem coordinate: the master QRect or the scene QRect (if there's no master).
		QRectF referenceRect(QGraphicsItem * item) const;

		/// \brief Maps a point in QGraphicsItem coordinate to a point in IObject internal coordinate. ( [-1,1], (0,0) is the center of the object, (-1,-1) is )
		///	the topLeft, (1,1) is the bottomright.
		TFloatPoint qGraphicsItem2IObject(const QPointF& point) const;
		/// \brief Similar to qGraphicsItem2IObject(const QPointF& point), but specifying the reference Qt rect.
		TFloatPoint qGraphicsItem2IObject(const QPointF& point, const QRectF& rect) const;
		/// \brief Maps a point in IObject internal coordinate to a point in QGraphicsItem coordinate.
		QPointF iObject2QGraphicsItem(const TFloatPoint& point) const;
		/// \brief Maps a rect in IObject internal coordinate to a rect in QGraphicsItem coordinate.
		QRectF iObject2QGraphicsItem(const TFloatRect& rect) const;
		/// \brief Maps a segment in IObject internal coordinate to a point in the specified QRectF.
		QRectF iObject2QGraphicsItem(const GraphicSegment& s) const;
		/// \brief Maps a point in IObject internal coordinate to a point in the specified QRectF.
		QPointF iObject2QGraphicsItem(const TFloatPoint& point, const QRectF& qrect) const;
		/// \brief Maps a segment in IObject internal coordinate to a point in the specified QRectF.
		QRectF iObject2QGraphicsItem(const GraphicSegment& rect, const QRectF& qrect) const;
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
    
        /// \brief Look in the fTilerItems map to see if we must add new pairs of slave-master (new representation)
		void findNewSync(SMaster master);
    
        /// \brief Look in the fTilerItems map if some pairs of slave-master (and so fTilerItems) are obsolete
		void findObsoleteSync(std::vector<SMaster> masters);
    
        /// \brief handles the fTilerItems to make them fit the model list of slave-master
		void setSlave(std::vector<SMaster> masters);
        
		/// \brief Returns the QGraphicsItem or the QTilerItem, whether the object is slaved or not
				QGraphicsItem * item(SMaster m = 0)	{return m ? fTilerItems.find(m)->second : fItem;}
		const	QGraphicsItem * item(SMaster m = 0) const    {return m ? fTilerItems.find(m)->second : fItem;}
		
		/// \brief Builds the QTilerItem to be used for stretching.
		virtual QStretchTilerItem* buildTiler();
		
        /// \brief Must be called when the QGraphicsItem has been modified in VGraphicsItemView subclasses.
		void itemChanged();
		
        /// \brief deletes the debug node items
		void deleteDebugItems();

        /// \brief updates the fTilerItem when it is h stretch (with mapping)
        void updateItemHStretch(QStretchTilerItem * item, const SGraphic2GraphicMapping& slave2Master);

        /// \brief updates the fTilerItem when it has no stretch
        void updateItemNoStretch(QStretchTilerItem* item, IObject* o, SMaster master);

        /// \brief updates the geometry (position, centering, scale) of the item
        void updateGeometry(QGraphicsItem* item, IObject* o, float x, float y, float scale);

        /// \brief updates the attributes of the QItem
        void updateItem(QGraphicsItem* item, IObject* o);

		QGraphicsItem * fItem;			/// \brief The QGraphicsItem used to render the IObject.
		std::map<SMaster, QStretchTilerItem *> fTilerItems; /// \brief The QTilerItem used when the object is a synchronized
        QList<QGraphicsItem*> fDebugItems;
		int fBrushColorStartIndex;

		QRectF fLastValidRect;
        int fNbMasters;
    
        QGraphicsItem* fParent;
        QGraphicsScene* fScene;
};
typedef class libmapping::SMARTP<VGraphicsItemView>	SVGraphicsItemView;

/*!@} */

} // end namespoace

#endif
