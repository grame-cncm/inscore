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


#ifndef __TMapMsgHandler__
#define __TMapMsgHandler__

#include "TLocalMapping.h"
#include "IMessage.h"
#include "IObject.h"
#include "segment2relativetimereader.h"
#include "IAppl.h"

namespace inscore
{

class IObject;

/*!
\addtogroup ITLModel
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief a class to handle map related messages
*/
template<typename S> class TMapMsgHandler
{
		static bool parseMsg (const IMessage* msg , std::string& mapname,  std::string& data)
		{
			switch (msg->params().size()) {
				case 2:
					if (!msg->param(0, mapname)) return false;
					if (!msg->param(1, data)) return false;
					break;
				case 1:
					if (!msg->param(0, data)) return false;
					mapname.clear();
					break;
				default: return false;
			}
			return data.size() > 0;
		}

	public:
	
		/// \brief the \c 'map' message handler
		static MsgHandler::msgStatus addMapMsg (const IMessage* msg , SMARTP<TLocalMapping<S> >& localMapping , IObject* object )
		{
			std::string mapName, map;
			if (parseMsg (msg, mapName, map)) {
				segment2relativetimereader<S> r;
				if (r.read(map)) {
					localMapping->addMapping( mapName , r.getMapping() );	// add the new localMapping without erasing the previous one.
					if (mapName.empty()) object->fAutoMap = false;
					return MsgHandler::kProcessed;
				}
			}
			return MsgHandler::kBadParameters;
		}
	
		/// \brief the \c 'map' message handler
		static MsgHandler::msgStatus mapMsg (const IMessage* msg , SMARTP<TLocalMapping<S> >& localMapping , IObject* object )
		{
			std::string mapName, map;
			if (parseMsg (msg, mapName, map)) {
				if ( map == "del" ) {
					localMapping->remove( mapName );
					object->removeMapping( mapName );
					return MsgHandler::kProcessed;
				}
				else
				{
					segment2relativetimereader<S> r;
					if (r.read(map)) {
						localMapping->setMapping( mapName , r.getMapping() );	// Set the new localMapping, also erasing the previous local<->graphic mapping.
																					// (which is no longer up-to-date)							
						if (mapName.empty()) object->fAutoMap = false;
						return MsgHandler::kProcessed;
					}
				}
			}
			return MsgHandler::kBadParameters;
		}

		/// \brief the \c 'mapf' message handler
		static MsgHandler::msgStatus mapFileMsg (const IMessage* msg , SMARTP<TLocalMapping<S> >& localMapping , IObject* object )
		{ 
			std::string mapName, file;
			if (parseMsg (msg, mapName, file)) {
				file = IAppl::absolutePath(file);
				segment2relativetimereader<S> r;
				if (r.readfile(file)) {
					localMapping->setMapping( mapName , r.getMapping() );	// Set the new localMapping, also erasing the previous local<->graphic mapping.
																				// (which is no longer up-to-date)
					if (mapName.empty()) object->fAutoMap = false;
					return MsgHandler::kProcessed;
				}
			}
			return MsgHandler::kBadParameters;
		}
		
		/// \brief Overrides IObject to handle 'get map' msg.
		static IMessageList getMapMsgs(const SMARTP<TLocalMapping<S> >& localMapping , const IObject* object )
		{ 
			IMessageList outMsgs;
			for ( typename TLocalMapping<S>::const_iterator iter = localMapping->namedMappings().begin() ; iter != localMapping->namedMappings().end() ; iter++ )
			{
				IMessage* msg = new IMessage(object->getOSCAddress(), "map");
				if ( iter->first.size() )
					*msg << iter->first;
//				*msg << iter->second.fLocal2Time->direct();
				*msg << iter->second->direct();
				outMsgs += msg;
			}
			return outMsgs;
		}
};

/*! @} */

} // end namespoace

#endif
