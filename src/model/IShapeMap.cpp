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

#include "IShapeMap.h"
#include "TMapMsgHandler.h"

namespace inscore
{

//--------------------------------------------------------------------------
IShapeMap::IShapeMap( const std::string& name, IObject* parent ) : IShape(name,parent)
{
	fLocalMappings = TLocalMapping<float,2>::create();

	fMsgHandlerMap["map"]		= TMethodMsgHandler<IShapeMap>::create(this, &IShapeMap::mapMsg);
	fMsgHandlerMap["map+"]		= TMethodMsgHandler<IShapeMap>::create(this, &IShapeMap::mapAddMsg);
	fMsgHandlerMap["mapf"]		= TMethodMsgHandler<IShapeMap>::create(this, &IShapeMap::mapFileMsg);
}

//--------------------------------------------------------------------------
IMessageList IShapeMap::__getMaps () const
{
	return TMapMsgHandler<float,2>::getMapMsgs( localMappings() , this );
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IShapeMap::mapFileMsg (const IMessage* msg )	
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<float,2>::mapFileMsg( msg , localMappings() , this );
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IShapeMap::mapMsg (const IMessage* msg )	
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<float,2>::mapMsg( msg , localMappings() , this); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IShapeMap::mapAddMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<float,2>::addMapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

} // end namespoace

