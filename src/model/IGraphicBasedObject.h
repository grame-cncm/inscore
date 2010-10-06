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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __IGraphicBasedObject__
#define __IGraphicBasedObject__

#include "IObject.h"
#include "maptypes.h"
#include "TLocalMapping.h"
#include "TMapMsgHandler.h"

namespace interlude
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IGraphicBasedObject;
typedef class SMARTP<IGraphicBasedObject>	SIGraphicBasedObject;
//--------------------------------------------------------------------------
/*!
	\brief the base class for objects that supports "2-dimensions long int" segmentations
*/
class IGraphicBasedObject : public IObject
{
		typedef SMARTP<TLocalMapping<IntPointSegment> >	SLocalMapping;
		SLocalMapping	fLocalMappings;

	public:

		const	SLocalMapping& localMappings() const	{ return fLocalMappings; }
				SLocalMapping& localMappings()			{ return fLocalMappings; }

		virtual void		accept (Updater*);

	protected:
				 IGraphicBasedObject( const std::string& name, IObject * parent );
		virtual ~IGraphicBasedObject() {}

		/// \brief the \c 'mapf' message handler
		MsgHandler::msgStatus mapFileMsg (const IMessage* msg );
		/// \brief the \c 'map' message handler
		MsgHandler::msgStatus mapMsg (const IMessage* msg );
		
		/// \brief Overrides IObject to handle 'get map' msg.
		IMessageList getMsgs(const IMessage* msg) const	{ return TMapMsgHandler<IntPointSegment>::getMsgs( msg , localMappings() , this ); }
};

/*! @} */

} // end namespoace

#endif
