/*

  INScore Project

  Copyright (C) 2009,2011  Grame

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


#ifndef __VDummyObjectView__
#define __VDummyObjectView__

#include "VObjectView.h"

namespace inscore
{

/*!
\addtogroup ITLView 
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a dummy graphic view of a IObject.
*/
class VDummyObjectView : public VObjectView
{
	public :
		virtual ~VDummyObjectView()	{}

		virtual void updateView(IObject * object)			{}
		virtual void updateObjectSize( IObject * object )	{}
		virtual void setParentView (IObject * object)		{}
		virtual void setParentItem( VObjectView* parent )	{}
		virtual void addMasterItem( VObjectView* master )	{}
		virtual void deleteMasterItem( VObjectView* master )	{}

		virtual void setEffect (GraphicEffect& effect)		{}
		virtual GraphicEffect getEffect () const			{ return GraphicEffect(); }

		/// \brief Maps the IObject [-1,1] y coordinate to the referenceRect().
		virtual double relative2SceneY(float y) const						{ return y; }
		/// \brief Maps the IObject [-1,1] x coordinate to the referenceRect().
		virtual double relative2SceneX(float x) const						{ return x; }
		/// \brief Maps the IObject [0,2] width value to the corresponding referenceRect() value.
		virtual double relative2SceneWidth(float width) const				{ return width; }
		/// \brief Maps the IObject [0,2] height value to the corresponding referenceRect() value.
		virtual double relative2SceneHeight(float height) const				{ return height; }
		/// \brief Maps a rect expressed in [-1,1] scene coordinate to a QRectF expressed in referenceRect() coordinates.
//		virtual QRectF relative2SceneRect( const TFloatRect& rect) const	= 0;

		/// \brief Maps the referenceRect() width value to the corresponding [0,2] value.
		virtual double scene2RelativeWidth(float width) const				{ return width; }
		/// \brief Maps the referenceRect() height value to the corresponding [0,2] value.
		virtual double scene2RelativeHeight(float height) const				{ return height; }
		/// \brief Maps the referenceRect() x value to the corresponding [-1,1] value.
		virtual double scene2RelativeX(float x) const						{ return x; }
		/// \brief Maps the referenceRect() y value to the corresponding [-1,1] value.
		virtual double scene2RelativeY(float y) const						{ return y; }
};

/*!@} */

} // end namespoace

#endif
