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

#include "IApplVNodes.h"
#include "Updater.h"

using namespace std;

namespace INScore
{

//--------------------------------------------------------------------------
IApplDebug::IApplDebug(IObject * parent) : IObjectDebug(parent), fOSCDebug(false)
{
	fGetMsgHandlerMap["osc"]	= TGetParamMsgHandler<bool>::create(fOSCDebug);
	fMsgHandlerMap["osc"]		= TSetMethodMsgHandler<IApplDebug,bool>::create(this, &IApplDebug::setOSCDebug);
//	fMsgHandlerMap["osc"]		= TSetMsgHandler<bool>::create(fOSCDebug);
}

//--------------------------------------------------------------------------
void IApplDebug::accept (Updater* u)
{
	u->updateTo(this);
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
IMessageList IApplDebug::get () const
{
	IMessageList outMsgs = IObjectDebug::get();
	IMessage * msg = new IMessage (getOSCAddress(), "osc");
	*msg << fOSCDebug;
	outMsgs += msg;
	return outMsgs;
}

//--------------------------------------------------------------------------
// debugging facilities
//--------------------------------------------------------------------------
void IApplDebug::print (ostream& out) const
{
	IObjectDebug::print(out);
	out << "  debug osc: " << fOSCDebug;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const SIApplDebug& o)
{
	if (o) o->print(out);
	return out;
}

}
