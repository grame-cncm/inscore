/*

  INScore Project

  Copyright (C) 2009,2020  Grame

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


#pragma once

#include <iostream>
#include <vector>

#include "abstractdata.h"
#include "EventsAble.h"
#include "Modules.h"
#include "TIRect.h"

class QGraphicsItem;

namespace inscore
{

/*!
\addtogroup ITLView 
@{
*/

class IObject;
class IEffect;

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IObject that uses a QGraphicsItem to render.
*/
class VObjectView
{
	VObjectView* fParent;

	public :
		virtual ~VObjectView() {}

		virtual void updateView(IObject * object)			{}
		virtual void updateObjectSize( IObject * object )	{}
		virtual void setParentItem( VObjectView* parent )	{}

		virtual void setEffect (const IEffect* effect)		{}

		/// \brief Maps the IObject [-1,1] y coordinate to the referenceRect().
		virtual float relative2SceneY(float y, VObjectContext item = 0 ) const;
		/// \brief Maps the IObject [-1,1] x coordinate to the referenceRect().
		virtual float relative2SceneX(float x, VObjectContext item = 0 ) const;
		/// \brief Maps the IObject [0,2] width value to the corresponding referenceRect() value.
		virtual float relative2SceneWidth(float width, VObjectContext item = 0 ) const;
		/// \brief Maps the IObject [0,2] height value to the corresponding referenceRect() value.
		virtual float relative2SceneHeight(float height, VObjectContext item = 0 ) const;

		/// \brief Maps the referenceRect() width value to the corresponding [0,2] value.
		virtual float scene2RelativeWidth(float width, VObjectContext item = 0 ) const;
		/// \brief Maps the referenceRect() height value to the corresponding [0,2] value.
		virtual float scene2RelativeHeight(float height, VObjectContext item = 0 ) const;
		/// \brief Maps the referenceRect() x value to the corresponding [-1,1] value.
		virtual float scene2RelativeX(float x, VObjectContext item = 0 ) const;
		/// \brief Maps the referenceRect() y value to the corresponding [-1,1] value.
		virtual float scene2RelativeY(float y, VObjectContext item = 0 ) const;

		/// \brief Returns the reference rectangle for the object: the master rect or the scene rect (if there's no master).
		virtual TFloatRect referenceRect(VObjectContext item) const	= 0;

		/// \brief updates the local mapping (do nothing at IObject level) 
		virtual void	updateLocalMapping (IObject* )					{}
		
		/// \brief initialize an object view (do nothing at IObject level)
		virtual void	initialize (IObject* )							{}
		
		/// \brief apply the current transform matrix to an object rect
		virtual void	getFrame (const IObject* , std::vector<float>&)	{}

		/*!
			\brief set the object view image using another view
			\param src the src view
		*/
		virtual void	setImage (VObjectView* )						{}

		/*!
			\brief set the object view image using another view
			\param src the src view
		*/
		virtual void	setImage (const unsigned char* , int )	{}
	
		/*!
		 * \brief getImage get image data of the object view at specified format.
		 * \param format Image format of the data.
		 * \return data of the image
		 */
		virtual const AbstractData		getImage(const char *);

		/*!
		 * \brief getVersion get the score version.
		 * \return
		 */
		virtual unsigned long	getVersion() const { return 0; }

		/// \brief simulate UI mouse events
		virtual void handleEvent (const IObject* obj, float x, float y, EventsAble::eventype type);

		/// \brief Enable or disable mouse and touch event on this object
		virtual void setMouseEventSensibility(bool){}

        virtual void refreshSyncCache(){}
};

/*!@} */

} // end namespoace
