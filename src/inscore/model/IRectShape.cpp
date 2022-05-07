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

#include <iostream>

#include "IRectShape.h"
#include "IMessage.h"
#include "Updater.h"
#include "VObjectView.h"

using namespace std;

namespace inscore
{

const string IRectShape::kRectShapeType("rshape");

//--------------------------------------------------------------------------
IRectShape::IRectShape( const std::string& name, IObject* parent ) : IShapeMap(name, parent)
{ 
	fTypeString = kRectShapeType;
	fGetMsgHandlerMap[""]					= TGetParamMethodHandler<IRectShape, TFloatSize (IRectShape::*)() const>::create(this, &IRectShape::getDimension);
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
	
	int n = msg->size();
	if (n == 3) {
		float width, height;
		bool wscenewidth, wsceneheight;
		bool hscenewidth, hsceneheight;
		if (!getDimParameter (msg, 1, width, wscenewidth, wsceneheight)) return MsgHandler::kBadParameters;
		if (!getDimParameter (msg, 2, height, hscenewidth, hsceneheight)) return MsgHandler::kBadParameters;
		setWidth (width, wscenewidth, wsceneheight);
		setHeight (height, hscenewidth, hsceneheight);
	}
	else return MsgHandler::kBadParameters;
	getView()->initView (this);
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
SIMessage IRectShape::getSetMsg(const std::string& address) const
{
	SIMessage msg = IMessage::create(address, kset_SetMethod);
	*msg << getTypeString();
	if (fSceneRelativeDims != IPosition::kNone) {
		stringstream s;
		if (widthRelative2SceneW()) {
			s << _getWidth() << "sw";
			*msg << s.str();
		}
		else if (widthRelative2SceneH()) {
			s << _getWidth() << "sh";
			*msg << s.str();
		}
		else *msg << _getWidth();

		s.str(std::string());
		if (heightRelative2SceneW()) {
			s << _getHeight() << "sw";
			*msg << s.str();
		}
		else if (heightRelative2SceneH()) {
			s << _getHeight() << "sh";
			*msg << s.str();
		}
		else *msg << _getHeight();
	}
	else *msg << _getWidth() << _getHeight();
	return msg;
}


}
