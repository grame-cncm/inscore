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


#pragma once

#include <iostream>

#include "VObjectView.h"

class QGraphicsItem;

namespace inscore
{

class IObject;

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

		virtual void updateView(IObject * object)			{}
		virtual void updateObjectSize( IObject * object )	{}
		virtual void setParentItem( VObjectView* parent )		{}
		virtual void setParentItem( VGraphicsItemView* parent )	{}
    
        virtual void setEffect (const IEffect* effect)		{}

		float relative2SceneY(float y, QGraphicsItem * item = 0 ) const				{ return y; }
		float relative2SceneX(float x, QGraphicsItem * item = 0 ) const				{ return x; }
		float relative2SceneWidth(float width, QGraphicsItem * item = 0 ) const		{ return width; }
		float relative2SceneHeight(float height, QGraphicsItem * item = 0 ) const	{ return height; }

		float scene2RelativeWidth(float width, QGraphicsItem * item = 0 ) const		{ return width; }
		float scene2RelativeHeight(float height, QGraphicsItem * item = 0 ) const	{ return height; }
		float scene2RelativeX(float x, QGraphicsItem * item = 0 ) const				{ return x; }
		float scene2RelativeY(float y, QGraphicsItem * item = 0 ) const				{ return y; }

		void	getFrame (const IObject* , std::vector<float>&)		{}
		virtual void setMouseEventSensibility(bool mouseSensible)	{}
	
		static void buildDefaultMapping (IObject* object)	{}
        void refreshSyncCache() 							{}
	
				QGraphicsItem * item(SMaster m = 0)			{return 0;}
		const	QGraphicsItem * item(SMaster m = 0) const   {return 0;}
	
};

/*!@} */

} // end namespoace
