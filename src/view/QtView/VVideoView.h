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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/


#ifndef __VVideoView__
#define __VVideoView__

#include <string>

#include "VMediaPlayer.h"

#include <QMediaPlayer>
#include <QGraphicsVideoItem>

#include "VGraphicsItemView.h"
#include "VMappedShapeView.h"
#include "MouseEventAble.h"


namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

class IVideo;
//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IVide.
*/
class VVideoView: public VGraphicsItemView, public VMediaPlayer
{
	public :
		using VGraphicsItemView::updateView;
		using VGraphicsItemView::updateLocalMapping;

				 VVideoView(QGraphicsScene * scene, const IVideo* h);
		virtual ~VVideoView() {}

		virtual bool initView  ( IObject* obj);
				bool initialize( IVideo * video );

		virtual void updateView ( IVideo * video );
		virtual void updateLocalMapping (IShapeMap* shapeMap)	{ VMappedShapeView::updateGraphic2GraphicMapping(shapeMap); }
		virtual void updateObjectSize(IObject* o) {} // overrides
		// overrides default: a video must be visible to trigger the size change signal, which makes the object ready
        virtual bool getVisible (const IObject* o) const	{ return o->getPending() ? true : o->getVisible(); }

		virtual void mediaReady();
		virtual void mediaEnd();
		virtual void posChanged(qint64 pos);
		virtual void sizeChanged(const QSizeF & size);
		virtual void error(QString msg);

	protected:
		virtual bool ready() const;

	private:
	typedef MouseEventAble<QGraphicsVideoItem> IQGraphicsVideoItem;
	QGraphicsVideoItem*		fVideoItem;
	IVideo *				fVideo;
};


/*!@} */

} // end namespoace

#endif
