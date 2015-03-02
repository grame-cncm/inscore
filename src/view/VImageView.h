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


#ifndef __VImageView__
#define __VImageView__

#include "VIntPointObjectView.h"
#include "MouseEventAble.h"

#ifdef PIXMAPBASED
# include <QGraphicsPixmapItem>
#else
# include <QGraphicsItem>
# include <QImage>
# include <QPainter>
#endif

namespace inscore
{

class EventsAble;

/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
class VGraphicsImageItem : public QGraphicsItem
{
	QImage fImage;
	public:
			     VGraphicsImageItem() {}
		virtual ~VGraphicsImageItem() {}
		
		QImage& image()					{ return fImage; }
		QRectF	boundingRect() const	{ return QRectF(0,0,fImage.width(), fImage.height()); }
		void paint(QPainter *painter, const QStyleOptionGraphicsItem *option, QWidget *widget = 0)
										{ painter->drawImage(QPoint(0,0), fImage); }
};

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IImage.
*/
class VImageView:  public VIntPointObjectView
{
	typedef MouseEventAble<VGraphicsImageItem> IQGraphicsImageItem;	
	IQGraphicsImageItem* fImageItem;

	public :
		using VIntPointObjectView::updateView;
		using VIntPointObjectView::updateLocalMapping;

		VImageView(QGraphicsScene * scene, const IImage*);
		virtual ~VImageView() {}
		
		virtual void updateLocalMapping (IImage* img);
		virtual void updateView ( IImage * img );
		virtual void setImage (QByteArray data);

		virtual void setImage (VObjectView* src);

	protected:
		GraphicSegment getGraphicSegment( const IntPointSegment& intPointSegment , const IGraphicBasedObject * object , bool& mapOk ) const;
		void setImage(const QString& fileName);
};

/*!@} */

} // end namespoace

#endif
