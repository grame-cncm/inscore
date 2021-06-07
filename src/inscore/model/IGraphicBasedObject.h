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


#ifndef __IGraphicBasedObject__
#define __IGraphicBasedObject__

#include "IObject.h"
#include "IProportionalAsyncDims.h"
#include "maptypes.h"
#include "TLocalMapping.h"
#include "TMapMsgHandler.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IGraphicBasedObject;
typedef class libmapping::SMARTP<IGraphicBasedObject>	SIGraphicBasedObject;
//--------------------------------------------------------------------------
/*!
	\brief the base class for objects that supports "2-dimensions long int" segmentations
*/
class IGraphicBasedObject : public IObject, public IProportionalAsyncDims
{
		typedef libmapping::SMARTP<TLocalMapping<long,2> >	SLocalMapping;
		SLocalMapping	fLocalMappings;
		TLongRect 	fBoundingRect;

		/// \brief get an object maps
		virtual SIMessageList __getMaps () const	{ return TMapMsgHandler<long,2>::getMapMsgs( localMappings() , this ); }

	public:

		const	SLocalMapping& localMappings() const	{ return fLocalMappings; }
				SLocalMapping& localMappings()			{ return fLocalMappings; }
		
		void 	updateLocalMapping ();
		void 	setBoundingRect(long x, long y, long w, long h);
		const TLongRect getBoundingRect() const { return fBoundingRect; }

		virtual void		accept (Updater*);

		/// \brief Sets the width with height adjustment
		virtual void	setPWidth(float width);
		/// \brief Sets the height with width adjustment
		virtual void	setPHeight(float height);
		/// \brief clear the pending state of an object
		virtual void	ready();
		/// \brief Returns the real width
		virtual float	getRealWidth() const		{ return fRealWidth; }
		/// \brief Returns the real height
		virtual float	getRealHeight() const		{ return fRealHeight; }

	protected:
				 IGraphicBasedObject( const std::string& name, IObject * parent );
		virtual ~IGraphicBasedObject() {}

		bool 		getGraphicSegment( const IntPointSegment& segment, GraphicSegment& outSegment ) const;
		TFloatPoint view2ItemPoint(const TLongPoint& point) const;

		/// \brief the \c 'set' message handler
		void setCalled ();
		
		/// \brief the \c 'mapf' message handler
		MsgHandler::msgStatus mapFileMsg (const IMessage* msg );
		/// \brief the \c 'map' message handler
		MsgHandler::msgStatus mapMsg (const IMessage* msg );
		/// \brief the \c 'map+' message handler
		MsgHandler::msgStatus mapAddMsg (const IMessage* msg );
};

/*! @} */

} // end namespoace

#endif
