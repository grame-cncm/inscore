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

#include <iostream>

#include "IRectShape.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace interlude
{

const string IRectShape::kRectShapeType("rshape");

//--------------------------------------------------------------------------
IRectShape::IRectShape( const std::string& name, IObject* parent ) : IShapeMap(name, parent)
{ 
	fTypeString = kRectShapeType;
	fGetMsgHandlerMap[""]		= TGetParamMethodHandler<IRectShape, TFloatSize (IRectShape::*)() const>::create(this, &IRectShape::getDimension);
	fMsgHandlerMap["width"]		= TSetMethodMsgHandler<IObject, float>::create(this, &IObject::setWidth);
	fMsgHandlerMap["height"]	= TSetMethodMsgHandler<IObject, float>::create(this, &IObject::setHeight);
//	fMsgHandlerMap["width"]		= TSetMsgHandler<float>::create(fWidth);
//	fMsgHandlerMap["height"]	= TSetMsgHandler<float>::create(fHeight);
}

//--------------------------------------------------------------------------
void IRectShape::accept (Updater* u)
{
	u->updateTo (SIRectShape(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IRectShape::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	if (msg->params().size() == 3) {
		const float err = -1;
		float width = msg->params()[1]->value<float>(err);
		float height = msg->params()[2]->value<float>(err);

		if ( (width != err) && (height != err) && ( ( width != getWidth() ) || ( height != getHeight() ) ) )
		{
			setWidth( width );
			setHeight( height );
			newData(true);
			status = MsgHandler::kProcessed;
		}
		else status = MsgHandler::kProcessedNoChange;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}
		
}
