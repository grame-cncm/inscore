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


#ifndef __VGridView__
#define __VGridView__

#include <QGraphicsRectItem>

#include "VMappedShapeView.h"
#include "MouseEventAble.h"

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IGrid.
*/
class VGridView: public VMappedShapeView
{
	MouseEventAble<QGraphicsRectItem>*  item() const		{ return (MouseEventAble<QGraphicsRectItem>*)fItem; }

	public :
		using VMappedShapeView::updateView;

				 VGridView(QGraphicsScene * scene, const IGrid* h);
		virtual ~VGridView() {}

		virtual void	updateView( IGrid * rect );
		virtual void	updateObjectSize( IObject * object ) {}
		virtual void	updateLocalMapping (IGrid* object);
};

/*!@} */

} // end namespoace

#endif
