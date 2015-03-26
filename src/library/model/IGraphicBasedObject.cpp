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

#include <sstream>

#include "IAppl.h"
#include "IGraphicBasedObject.h"
#include "IMessage.h"
//#include "segment2relativetimereader.h"
#include "Updater.h"
#include "TComposition.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
IGraphicBasedObject::IGraphicBasedObject( const std::string& name, IObject * parent )
	: IObject(name, parent) 
{ 
	fLocalMappings = TLocalMapping<long,2>::create();

	fMsgHandlerMap[kmap_GetSetMethod]		= TMethodMsgHandler<IGraphicBasedObject>::create(this, &IGraphicBasedObject::mapMsg);
	fMsgHandlerMap[kmapplus_SetMethod]		= TMethodMsgHandler<IGraphicBasedObject>::create(this, &IGraphicBasedObject::mapAddMsg);
	fMsgHandlerMap[kmapf_SetMethod]			= TMethodMsgHandler<IGraphicBasedObject>::create(this, &IGraphicBasedObject::mapFileMsg);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicBasedObject::mapFileMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,2>::mapFileMsg( msg , localMappings() , this );
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicBasedObject::mapAddMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,2>::addMapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicBasedObject::mapMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<long,2>::mapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
void IGraphicBasedObject::accept (Updater* u)
{
	u->updateTo (SIGraphicBasedObject(this));
}

}
