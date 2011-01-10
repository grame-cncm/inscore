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
#include "MouseEventAble.h"

namespace inscore
{

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
	QSvgRenderer fRenderer;
	
	public :
				 VSVGItem() {}
		virtual ~VSVGItem() {}
		
		bool	setFile( const char* file);
		QRectF	boundingRect() const	{ return fRenderer.viewBoxF(); }
		QSize	size() const			{ return fRenderer.defaultSize(); }
		void	paint ( QPainter * painter, const QStyleOptionGraphicsItem * option, QWidget * widget = 0 );
};

//--------------------------------------------------------------------------
/**
*	\brief the graphic view of a SVG file.
*/
class VSVGView: public VMappedShapeView
{
	MouseEventAble<VSVGItem>*  item() const	{ return (MouseEventAble<VSVGItem>*)fItem; }
	
	public :
				 VSVGView(QGraphicsScene * scene, const ISVGFile* svg);
		virtual ~VSVGView() {}
		virtual void updateView( ISVGFile * rect );
};

/*!@} */

} // end namespoace

#endif
