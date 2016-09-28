/*

  INScore Project

  Copyright (C) 2016  Grame

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

#include "IArc.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string IArc::kArcType("arc");

//--------------------------------------------------------------------------
IArc::IArc( const std::string& name, IObject* parent ) : IRectShape(name, parent)
{
	fTypeString = kArcType;
	fStartAngle = 0;
	fEndAngle = 360;
	fCloseArc = false;

	fMsgHandlerMap[kstart_GetSetMethod]		= TSetMethodMsgHandler<IArc, float>::create(this, &IArc::setStartAngle);
	fMsgHandlerMap[kend_GetSetMethod]		= TSetMethodMsgHandler<IArc, float>::create(this, &IArc::setEndAngle);
	fMsgHandlerMap[kdstart_SetMethod]		= TSetMethodMsgHandler<IArc, float>::create(this, &IArc::dStartAngle);
	fMsgHandlerMap[kdend_SetMethod]			= TSetMethodMsgHandler<IArc, float>::create(this, &IArc::dEndAngle);
	fMsgHandlerMap[kclose_GetSetMethod]		= TSetMethodMsgHandler<IArc, bool>::create(this, &IArc::setClosed);

	fGetMsgHandlerMap[kstart_GetSetMethod]		= TGetParamMsgHandler<float>::create(fStartAngle);
	fGetMsgHandlerMap[kend_GetSetMethod]		= TGetParamMsgHandler<float>::create(fEndAngle);
	fGetMsgHandlerMap[kclose_GetSetMethod]		= TGetParamMsgHandler<bool>::create(fCloseArc);

	setPenWidth (1.0);
	setBrushStyle ("none");
}

//--------------------------------------------------------------------------
void IArc::accept (Updater* u)
{
	u->updateTo (SIArc(this));
}

//--------------------------------------------------------------------------
void IArc::print (ostream& out) const
{
	IShape::print (out);
	out << " arc" << endl;
}

//--------------------------------------------------------------------------
// the 'get' form without parameter
SIMessageList IArc::getSetMsg() const
{
	SIMessageList outmsgs = IMessageList::create();
	SIMessage msg = IMessage::create(getOSCAddress(), kset_SetMethod);
	*msg << kArcType <<  getWidth() << getHeight() << getStartAngle() << getEndAngle();
	outmsgs->list().push_back (msg);
	return outmsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IArc::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	if (msg->size() == 5) {
		float width, height, startangle, endangle;
		if (!msg->cast_param(1, width) || !msg->cast_param(2, height) || !msg->cast_param(3, startangle) || !msg->cast_param(4, endangle))
			return MsgHandler::kBadParameters;

		if ( ( width != getWidth() ) || ( height != getHeight() )
			|| ( startangle != getStartAngle() ) || ( endangle != getEndAngle() ) )
		{
			setWidth( width );
			setHeight( height );
			setStartAngle( startangle );
			setEndAngle( endangle );
			newData(true);
			status = MsgHandler::kProcessed;
		}
		else status = MsgHandler::kProcessedNoChange;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}


}
