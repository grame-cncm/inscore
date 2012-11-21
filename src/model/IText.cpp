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
#include "IText.h"
#include "IMessage.h"
//#include "segment2relativetimereader.h"
#include "TComposition.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
const string IText::kTextType("txt");
//--------------------------------------------------------------------------
IText::IText( const std::string& name, IObject * parent ) : IGraphicBasedObject(name, parent)
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

	int n = msg->size();
	if (n >= 2) {
		stringstream stream;
		const char * sep = "";
		for (int i = 1; i < n ; i++) {
			string text; int itext; float ftext;
			stream << sep;
			if (msg->param(i, itext))			stream << itext;
			else if (msg->param(i, ftext))		stream << ftext;
			else if (msg->param(i, text))		stream << text;
			sep = " ";
		}
		setText( stream.str() );
		newData(true);
		status = MsgHandler::kProcessed;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

}
