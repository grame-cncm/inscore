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


#ifndef __VSVGView__
#define __VSVGView__

#include <QGraphicsItem>
#include <QSvgRenderer>

#include "VMappedShapeView.h"
#include "VIntPointObjectView.h"
#include "MouseEventAble.h"

namespace inscore
{

class ISVG;
class ISVGFile;

class EventsAble;
/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief an SVG file.
*/
class VSVGItem: public 	QAbstractGraphicsShapeItem 
{
	class AnimatedSvgRenderer : public QSvgRenderer {
		QGraphicsItem* fItem;
		public:
			AnimatedSvgRenderer (QGraphicsItem* container) : fItem(container) {};
		protected:
			void timerEvent(QTimerEvent *) {
				fItem->update (viewBoxF());
			}
	} fRenderer;
	int		fTimerID;
	bool	fAnimate;
	int		fFramesPerSecond;
	
	public :
				 VSVGItem() : fRenderer(this), fTimerID(0), fAnimate(false), fFramesPerSecond(0) {}
		virtual ~VSVGItem();
	
		void	setAnimate( bool state )	{ fAnimate = state; }
		bool	setFile( const char* file);
		bool	setText( const char* text);
		bool	getAnimated() const		{ return fRenderer.animated(); }
		QRectF	boundingRect() const	{ return fRenderer.viewBoxF(); }
		QSize	size() const			{ return fRenderer.defaultSize(); }
		void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
};

//--------------------------------------------------------------------------
/**
*	\brief the graphic view of a SVG file.
*/
class VSVGView: public VIntPointObjectView
{
	MouseEventAble<VSVGItem>*  item() const	{ return (MouseEventAble<VSVGItem>*)fItem; }
	
	public :
		using VIntPointObjectView::updateView;
		using VIntPointObjectView::updateLocalMapping;

				 VSVGView(QGraphicsScene * scene, const ISVG* svg);
				 VSVGView(QGraphicsScene * scene, const ISVGFile* svg);
		virtual ~VSVGView() {}
		virtual void updateView( ISVGFile * rect );
		virtual void updateView( ISVG * rect );
		virtual void updateLocalMapping (ISVG* img);
		virtual void updateLocalMapping (ISVGFile* img);
		virtual GraphicSegment getGraphicSegment( const IntPointSegment& intPointSegment , const IGraphicBasedObject * object , bool& mapOk ) const;
};

/*!@} */

} // end namespoace

#endif
