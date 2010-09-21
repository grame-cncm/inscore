/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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

#ifndef __IPosition__
#define __IPosition__

#include <ostream>
#include <map>
#include <string>
#include <vector>

#include "IColor.h"
#include "IMessageHandlers.h"
#include "TRect.h"

namespace interlude
{

class IMessage;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IPosition;
class IObject;
typedef class SMARTP<IObject>	SIObject;


//--------------------------------------------------------------------------
/*!
	\brief an object position data
*/
class Position
{
	protected:	
		float	fXPos, fYPos;			///< the object coordinates
		float	fXOrigin, fYOrigin;		///< the origin coordinates (range [-1,1] where 0,0 is the object center)
		float	fWidth, fHeight;		///< the object dimensions
		float	fZOrder;				///< the object Z-order
		float	fAngle;					///< the object angle
		bool	fVisible;				///< the object visibility
		float	fScale;					///< the object scaling factor
		bool	fModified;				///< the modification state

	public:
				 Position();
		virtual ~Position() {}
	
		enum {	kDefaultX=0, kDefaultY=0 };

		virtual void set(const Position& p);

		/// \brief returns the object modification state
		virtual bool	modified () const			{ return fModified; }
		virtual	void	modify ()					{ fModified = true; }

		/// \brief cleanup stuff
		virtual void	cleanup ()					{ fModified = false; }

		/// \brief returns the \c x position of the object
		virtual float	getXPos () const			{ return fXPos; }
		/// \brief returns the \c y position of the object
		virtual float	getYPos () const			{ return fYPos; }
		/// \brief returns the \c x position of the object
		virtual float	getXOrigin () const			{ return fXOrigin; }
		/// \brief returns the \c y position of the object
		virtual float	getYOrigin () const			{ return fYOrigin; }
		/// \brief returns the object z order
		virtual float	getZOrder() const			{ return fZOrder; }
		/// \brief returns the object z order
		virtual float	getAngle() const			{ return fAngle; }
		/// \brief returns the scaling factor of the object
		virtual float	getScale () const			{ return fScale; }
		/// \brief returns the object position as a TFloatPoint
		virtual TFloatPoint	getPos() const			{ return TFloatPoint( fXPos , fYPos ); }

		/// \brief Returns the width
		virtual float	getWidth() const			{ return fWidth; }
		/// \brief Returns the height
		virtual float	getHeight() const			{ return fHeight; }
		/// \brief Returns the dimension
		virtual TFloatSize getDimension() const		{ return TFloatSize( fWidth , fHeight ); }

		/// \brief returns the object visibility
		virtual bool	getVisible () const			{ return fVisible; }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& out) const;

		/// \brief Sets the width
		void			setWidth(float width)		{ fWidth = width; }
		/// \brief Sets the height
		void			setHeight(float height)		{ fHeight = height; }

		/*!
			\brief sets an object \c x position in its scene			
			A scene coordinates system is between [-1, 1] for the \c x and \c y axis.
			[0,0] is the center of the scene, -1 is the leftmost position on the \c axis
			and 1 is the topmost position on the \c y axis.
			\param x the x position
		*/
		virtual void	setXPos (float x)			{ fXPos = x; fModified = true; }
		virtual void	addXPos (float x)			{ setXPos (fXPos + x); }

		/*!
			\brief sets an object \c x origin
			\param x the x origin in the range -1,1 where -1 is the left border and 1 the right border
		*/
		virtual void	setXOrigin (float x)		{ fXOrigin = x; fModified = true; }
		virtual void	addXOrigin (float x)		{ setXOrigin (fXOrigin + x); }

		/*!
			\brief sets an object \c y origin
			\param x the x origin in the range -1,1 where -1 is the left border and 1 the right border
		*/
		virtual void	setYOrigin (float y)		{ fYOrigin = y; fModified = true; }
		virtual void	addYOrigin (float y)		{ setYOrigin (fYOrigin + y); }

		/*!
			\brief sets an object \c y position in its scene			
			A scene coordinates system is between [-1, 1] for the \c x and \c y axis.
			[0,0] is the center of the scene, -1 is the leftmost position on the \c axis
			and 1 is the topmost position on the \c y axis.
			\param y the y position
		*/
		virtual void	setYPos (float y)			{ fYPos = y; fModified = true; }
		virtual void	addYPos (float y)			{ setYPos (fYPos + y); }

		/*!
			\brief sets an object scaling factor
			An object is created with a scaling factor equal to 1, i.e. it has its natural size.
			\param scale the scaling factor
		*/
		virtual void	setScale (float scale)		{ fScale = scale; fModified = true; }
		virtual void	multScale (float scale)		{ setScale(fScale * scale); }
		
		/// \brief sets the object visibility \param vis a boolean value to show/hide the object
		virtual void	setVisible (bool vis)		{ fVisible = vis; fModified = true; }

		/*!
		*	\brief sets the object Z-Order.
		*	
		*	The Z Order (or the elevation) decides the stacking order of items. 
		*	An item of high Z-Order will be drawn on top of an item with a lower Z-Order
		*
		*	\param z the Z order
		*/
		virtual void	setZOrder(float z)			{ fZOrder = z; fModified = true; }
		virtual void	addZOrder(float z)			{ setZOrder(fZOrder + z); }
		
		/*!
		*	\brief sets the object rotation, in degrees.
		*
		*	The object will be rotated around its origin 
		*	(top-left corner in most of the cases).
		*/
		virtual void	setAngle(float angle)		{ fAngle = angle; fModified = true; }
		virtual void	addAngle(float angle)		{ setAngle(fAngle + angle); }

		/*! \brief Computes the bounding rect in Scene coordinates. 
		
			Takes position, scale and rotation into account.
		*/
		TFloatRect		getBoundingRect() const;

};

//--------------------------------------------------------------------------
/*!
	\brief an object position data with message handlers.
*/
class IPosition: public Position
{
	protected:
				 IPosition() {}
		virtual ~IPosition() {}

		/*!
			\brief selects a list of components under the object position.
			\param msg the message
			\param parent the parent object of the current object
			\param outlist on output, a components list
			\return true when the message has been correctly processed
		*/
		virtual bool	click (const IMessage* msg, IObject * parent, std::vector<SIObject>& outlist) const;

		/*!
			\brief selects a list of components that intersect or are included in the object bounding rect.
			\param msg the message
			\param parent the parent object of the current object
			\param outlist on output, a components list
			\return true when the message has been correctly processed
		*/
		virtual bool	select (const IMessage* msg, IObject * parent, std::vector<SIObject>& outlist) const;
};


/*! @} */

} // end namespoace

#endif
