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

#include <math.h>

#include "ILine.h"
#include "IMessage.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

const string ILine::kLineType("line");
//--------------------------------------------------------------------------
ILine::ILine( const std::string& name, IObject* parent ) : IShapeMap(name, parent), fView(0)
{ 
	fTypeString = kLineType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler< TFloatPoint >::create( getPoint() );
	
	fPenWidth = 1.0f;
}

//--------------------------------------------------------------------------
void ILine::accept (Updater* u)
{
	u->updateTo (SILine(this));
}

//--------------------------------------------------------------------------
void ILine::print (ostream& out) const
{
	IShapeMap::print (out);
	out << fPoint << endl;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ILine::set (const IMessage* msg)	
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	if (msg->params().size() == 3) {
		float x, y;
		if ((!msg->param(1, x)) || (!msg->param(2, y)))
			return MsgHandler::kBadParameters;
		setPoint( TFloatPoint(x,y) );
		status = MsgHandler::kProcessed;
		newData(true);
		oscerr << OSCWarn() << "set line without mode is deprecated" << OSCEnd();
	}
	else if (msg->params().size() == 4) {
		string mode; float a, b;
		if (!msg->param(1, mode) || (!msg->param(2, a)) || (!msg->param(3, b)))
			return MsgHandler::kBadParameters;

		if (mode == "xy") {
			setPoint( TFloatPoint(a,b) );
		}
		else if (mode == "wa") {
			float x = a * cos(M_PI * b / 180);
			float y = a * sin(M_PI * b / 180);
			setPoint( TFloatPoint(x,y) );
		}
		status = MsgHandler::kProcessed;
		newData(true);
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

}
