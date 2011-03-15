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


#ifndef __IShapeMap__
#define __IShapeMap__

#include "TLocalMapping.h"
#include "TMapMsgHandler.h"
#include "IShape.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief local maps of a basic geometric shape.
*/
class IShapeMap: public IShape
{
	protected:
		typedef SMARTP<TLocalMapping<GraphicSegment> >	SLocalMapping;
		SLocalMapping	fLocalMappings;

	public:
				 IShapeMap( const std::string& name, IObject* parent );
		virtual ~IShapeMap() {}

		const	SLocalMapping& localMappings() const	{ return fLocalMappings; }
				SLocalMapping& localMappings()			{ return fLocalMappings; }

		/// \brief the \c 'mapf' message handler
		MsgHandler::msgStatus mapFileMsg (const IMessage* msg );
		/// \brief the \c 'map' message handler
		MsgHandler::msgStatus mapMsg (const IMessage* msg );
		/// \brief the \c 'map+' message handler
		MsgHandler::msgStatus mapAddMsg (const IMessage* msg );
		
		/// \brief Overrides IObject to handle 'get map' msg.
		IMessageList getMsgs(const IMessage* msg) const	{ return TMapMsgHandler<GraphicSegment>::getMsgs( msg , localMappings() , this ); }

};

/*! @} */

} // end namespoace

#endif
