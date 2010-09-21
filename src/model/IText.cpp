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

//#include "graphic2relativetimereader.h"
#include "IAppl.h"
#include "IText.h"
#include "IMessage.h"
#include "segment2relativetimereader.h"
#include "TComposition.h"
#include "Updater.h"

using namespace std;

namespace interlude
{

//--------------------------------------------------------------------------
const string IText::kTextType("txt");
//--------------------------------------------------------------------------
IText::IText( const std::string& name, IObject * parent )
	: IGraphicBasedObject(name, parent), fView(0)
{ 
	fTypeString = kTextType;
	setColor( IColor(0,0,0,255) );
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<string>::create(fText);
}

//--------------------------------------------------------------------------
void IText::accept (Updater* u)
{
	u->updateTo (SIText(this));
}

//--------------------------------------------------------------------------
void IText::print (ostream& out) const
{
	IObject::print (out);
	out << "  \"" << getText() << "\"";
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
MsgHandler::msgStatus IText::set( const IMessage* msg )	
{ 
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	if (msg->params().size() == 2) {
		string text;
		if (msg->param(1, text)) {
			setText( text );
			newData(true);
			status = MsgHandler::kProcessed;
		}
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

}
