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

#include <sstream>

#include "IAppl.h"
#include "IGraphicBasedObject.h"
#include "IMessage.h"
#include "segment2relativetimereader.h"
#include "Updater.h"
#include "TComposition.h"

using namespace std;

namespace interlude
{

//--------------------------------------------------------------------------
IGraphicBasedObject::IGraphicBasedObject( const std::string& name, IObject * parent )
	: IObject(name, parent) 
{ 
	fLocalMappings = TLocalMapping<IntPointSegment>::create();

	fMsgHandlerMap["map"]		= TMethodMsgHandler<IGraphicBasedObject>::create(this, &IGraphicBasedObject::mapMsg);
	fMsgHandlerMap["mapf"]		= TMethodMsgHandler<IGraphicBasedObject>::create(this, &IGraphicBasedObject::mapFileMsg);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicBasedObject::mapFileMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<IntPointSegment>::mapFileMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGraphicBasedObject::mapMsg (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = TMapMsgHandler<IntPointSegment>::mapMsg( msg , localMappings() , this ); 
	if (status & MsgHandler::kProcessed) localMapModified(true);
	return status;
}

//--------------------------------------------------------------------------
void IGraphicBasedObject::accept (Updater* u)
{
	u->updateTo (SIGraphicBasedObject(this));
}

}
