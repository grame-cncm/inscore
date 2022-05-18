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

#ifndef __IPosition__
#define __IPosition__

#include <ostream>
#include <map>
#include <string>
#include <vector>

#include "IColor.h"
#include "IMessageHandlers.h"
#include "TIRect.h"

namespace inscore
{

class IMessage;

/*!
\addtogroup ITLModel Data Model
@{
*/

class IPosition;
class IObject;
typedef class libmapping::SMARTP<IObject>	SIObject;


//--------------------------------------------------------------------------
/*!
	\brief an object position data
*/
class IPosition
{
	private:
		float	fWidth, fHeight;		///< the object dimensions
		float	fXPos, fYPos;			///< the object coordinates

	protected:	
		float	fWHRatio = 0.f;			///< used by objects with proportional dimensions
		float	fXOrigin, fYOrigin;		///< the origin coordinates (range [-1,1] where 0,0 is the object center)
		int		fSceneRelativeDims = 0; ///< a set of flags to indicate scene relative dimensions
		int		fSceneRelativeXY = 0; 	///< a set of flags to indicate scene relative positions
		float	fZOrder;				///< the object Z-order
		bool	fVisible;				///< the object visibility
		float	fScale;					///< the object scaling factor
		bool	fModified;				///< the modification state

		float	fXAngle;				///< the object x rotation
		float	fYAngle;				///< the object y rotation
		float	fZAngle;				///< the object z rotation
    
        std::map<std::string, TFloatPoint> fPositions;			///< the slaved object positions for each master
        std::map<std::string, float> fHeights;                  ///< the slaved object heights for each master
        std::map<std::string, float> fWidths;                   ///< the slaved object widths for each master

		TFloatSize fShear;				///< the shear attributes

		// this constants indicates the relation between the object dimensions and the scene dimensions
		enum { kNone, kWidth2Width=1, kWidth2Height=2, kHeight2Height=4, kHeight2Width=8 };
		enum { kX2Width=1, kX2Height=2, kY2Height=4, kY2Width=8 };

	public:
				 IPosition();
		virtual ~IPosition() {}
	
		enum {	kDefaultX=0, kDefaultY=0 };

		virtual void setPos(const IPosition& p);

		virtual void 	setSize(float w, float h);

		/// \brief returns the object modification state
		virtual bool	modified () const			{ return fModified; }
		virtual	void	modify ()					{ fModified = true; }

		/// \brief cleanup stuff
		virtual void	cleanup ()					{ fModified = false; }

		/// \brief returns the \c x position of the object
		virtual float	getXPos () const;
				float	_getXPos () const			{ return fXPos; }

		/// \brief returns the \c y position of the object
		virtual float	getYPos () const;
				float	_getYPos () const			{ return fYPos; }

		/// \brief returns the \c x origin of the object
		virtual float	getXOrigin () const			{ return fXOrigin; }
		/// \brief returns the \c y origin of the object
		virtual float	getYOrigin () const			{ return fYOrigin; }
		/// \brief returns the object z order
		virtual float	getZOrder() const			{ return fZOrder; }
		/// \brief returns the object angle
		/// \brief returns the scaling factor of the object
		virtual float	getScale () const			{ return fScale; }
		/// \brief returns the object position as a TFloatPoint
		virtual TFloatPoint	getPos() const			{ return TFloatPoint( fXPos , fYPos ); }

		/// \brief returns the object x rotation
		virtual float	getRotateX() const			{ return fXAngle; }
		/// \brief returns the object y rotation
		virtual float	getRotateY() const			{ return fYAngle; }
		/// \brief returns the object z rotation
		virtual float	getRotateZ() const			{ return fZAngle; }

		/// \brief Returns the width
		virtual float	getWidth() const;
		/// \brief Returns the height
		virtual float	getHeight() const;
		/// \brief Returns the width
		virtual float	getRealWidth() const;
		/// \brief Returns the height
		virtual float	getRealHeight() const;
		/// \brief Returns the dimension
		virtual TFloatSize getDimension() const;
		/// \brief Returns the shear attributes
		virtual TFloatSize getShear() const			{ return fShear; }

		bool	widthRelative2SceneW () const 		{ return fSceneRelativeDims & kWidth2Width; }
		bool	widthRelative2SceneH () const 		{ return fSceneRelativeDims & kWidth2Height; }
		bool	heightRelative2SceneW () const 		{ return fSceneRelativeDims & kHeight2Width; }
		bool	heightRelative2SceneH () const 		{ return fSceneRelativeDims & kHeight2Height; }

		bool	xRelative2SceneW () const 		{ return fSceneRelativeXY & kX2Width; }
		bool	xRelative2SceneH () const 		{ return fSceneRelativeXY & kX2Height; }
		bool	yRelative2SceneW () const 		{ return fSceneRelativeXY & kY2Width; }
		bool	yRelative2SceneH () const 		{ return fSceneRelativeXY & kY2Height; }

		/// \brief returns the object visibility
		virtual bool	getVisible () const			{ return fVisible; }

		/// \brief print the object state \param out the output stream
		virtual void	print(std::ostream& out) const;

		/// \brief Sets the width
		virtual void	setWidth(float width, bool scenewidth, bool sceneheight);
		/// \brief Sets the height
		virtual void	setHeight(float height, bool scenewidth, bool sceneheight);
		/// \brief Sets the width without modifying the status
		virtual void	_setWidth(float width)		{ fWidth = width; }
				float	_getWidth() const			{ return fWidth; }
		/// \brief Sets the height without modifying the status
		virtual void	_setHeight(float height)	{ fHeight = height; }
				float	_getHeight() const			{ return fHeight; }
		/// \brief Sets flags for scene relative dimensions
		virtual void	setSceneRelativeWidth(bool scenewidth, bool sceneheight);
		virtual void	setSceneRelativeHeight(bool scenewidth, bool sceneheight);
		virtual void	setSceneRelativeX(bool scenewidth, bool sceneheight);
		virtual void	setSceneRelativeY(bool scenewidth, bool sceneheight);

		/*!
			\brief sets an object \c x position in its scene
			A scene coordinates system is between [-1, 1] for the \c x and \c y axis.
			[0,0] is the center of the scene, -1 is the leftmost position on the \c axis
			and 1 is the topmost position on the \c y axis.
			\param x the x position
		*/
		virtual void	setXPos (float x, bool scenewidth, bool sceneheight); //			{ fXPos = x; fModified = true; }
		virtual void	_setXPos (float x)			{ fXPos = x; fModified = true; }
		virtual void	addXPos (float x)			{ _setXPos (fXPos + x); }

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
		virtual void	setYPos (float y, bool scenewidth, bool sceneheight); //			{ fYPos = y; fModified = true; }
		virtual void	_setYPos (float y)			{ fYPos = y; fModified = true; }
		virtual void	addYPos (float y)			{ _setYPos (fYPos + y); }

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
		
		virtual void	addAngle(float angle)		{ setRotateZ(fZAngle + angle); }
		virtual void	addXAngle(float angle)		{ setRotateX(fXAngle + angle); }
		virtual void	addYAngle(float angle)		{ setRotateY(fYAngle + angle); }
		virtual void	addShear(const TFloatSize& s)	{ fShear += s; }
	
		/// \brief sets the object shear
		virtual void	setShear(const TFloatSize& s)		{ fShear = s; }		
		/// \brief sets the object x rotation
		virtual void	setRotateX(float a)					{ fXAngle = a; }
		/// \brief sets the object y rotation
		virtual void	setRotateY(float a)					{ fYAngle = a; }
		/// \brief sets the object z rotation
		virtual void	setRotateZ(float a)					{ fZAngle = a; }

        /// \brief sets the object height corresponding to one master (the string is the master's name)
		virtual void setSyncHeight(std::string m, float height);
        /// \brief sets the object width corresponding to one master
        virtual void setSyncWidth(std::string m, float width);
        /// \brief sets the object pos corresponding to one master
        virtual void setSyncPos(std::string m, TFloatPoint pos);
    
        /// \brief gets the object height corresponding to one master
        virtual float getSyncHeight (std::string m) const 	{ return fHeights.find(m)->second;}
        /// \brief gets the object width corresponding to one master
        virtual float getSyncWidth (std::string m) const 	{ return fWidths.find(m)->second;}
        /// \brief gets the object pos corresponding to one master
        virtual TFloatPoint getSyncPos (std::string m) const { return fPositions.find(m)->second;}

		/*! \brief Computes the bounding rect in Scene coordinates.
		
			Takes position, scale and rotation into account.
		*/
		TFloatRect		getBoundingRect() const;

};

/*! @} */

} // end namespoace

#endif
