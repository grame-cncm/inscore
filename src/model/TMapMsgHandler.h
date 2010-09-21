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


#ifndef __TMapMsgHandler__
#define __TMapMsgHandler__

#include "TLocalMapping.h"
#include "IMessage.h"
#include "IObject.h"
#include "segment2relativetimereader.h"
#include "IAppl.h"

namespace interlude
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
	public:
	
		/// \brief the \c 'map' message handler
		static MsgHandler::msgStatus mapMsg (const IMessage* msg , SMARTP<TLocalMapping<S> >& localMapping , IObject* object )
		{
			if (msg->params().size() >= 1) {
				int i = 0;
				std::string mapName = "", map = "";
				if (msg->params().size() == 2)
				{
					msg->param(i, mapName);
					i++;
				}
				msg->param(i, map);

				if (map.size()) {
					if ( map == "del" )
					{
						localMapping->remove( mapName );
						object->removeMapping( mapName );
						return MsgHandler::kProcessed;
					}
					else
					{
						segment2relativetimereader<S> r;
						if (r.read(map)) {
							localMapping->setMapping( mapName , 0 , r.getMapping() );	// Set the new localMapping, also erasing the previous local<->graphic mapping.
																						// (which is no longer up-to-date)							
							object->setTimeSegmentation( mapName , r.getRelativeTimeSegmentation() );
							if (mapName.empty()) object->fAutoMap = false;
							return MsgHandler::kProcessed;
						}
					}
				}
			}
			return MsgHandler::kBadParameters;
		}

		/// \brief the \c 'mapf' message handler
		static MsgHandler::msgStatus mapFileMsg (const IMessage* msg , SMARTP<TLocalMapping<S> >& localMapping , IObject* object )
		{ 
			if (msg->params().size() >= 1) {
				int i = 0;
				std::string mapName = "", file = "";
				if (msg->params().size() == 2)
				{
					msg->param(i,mapName);
					i++;
				}
				msg->param(i,file);

				file = IAppl::absolutePath(file);
				if (file.size()) {
					segment2relativetimereader<S> r;
					if (r.readfile(file)) {
						localMapping->setMapping( mapName , 0 , r.getMapping() );	// Set the new localMapping, also erasing the previous local<->graphic mapping.
																					// (which is no longer up-to-date)
						object->setTimeSegmentation( mapName , r.getRelativeTimeSegmentation() );
						if (mapName.empty()) object->fAutoMap = false;
						return MsgHandler::kProcessed;
					}
				}
			}
			return MsgHandler::kBadParameters;
		}
		
		/// \brief Overrides IObject to handle 'get map' msg.
		static IMessageList getMsgs(const IMessage* msg , const SMARTP<TLocalMapping<S> >& localMapping , const IObject* object )
		{ 
			IMessageList outMsgs;
			for ( unsigned int i = 0 ; i < msg->params().size() ; i++ )
			{
				std::string val = "-";
				msg->param(i,val);
				if ( val == "map" )
				{
					for ( typename TLocalMapping<S>::const_iterator iter = localMapping->namedMappings().begin() ; iter != localMapping->namedMappings().end() ; iter++ )
					{
						IMessage* msg = new IMessage(object->getOSCAddress(), "map");
						if ( iter->first.size() )
							*msg << iter->first;
						*msg << iter->second.fLocal2Time->direct();
						outMsgs += msg;
					}
					break;
				}
			}
			outMsgs += object->IObject::getMsgs(msg);
			return outMsgs;
		}

};

/*! @} */

} // end namespoace

#endif
