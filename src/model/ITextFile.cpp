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

#include "ITextFile.h"
#include "IMessage.h"
#include "TComposition.h"
#include "IScene.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
const string ITextFile::kTextFileType("txtf");

//--------------------------------------------------------------------------
ITextFile::ITextFile( const std::string& name, IObject * parent )
	: IText(name, parent), TFile (parent->getScene()) 
{ 
	fTypeString = kTextFileType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<string>::create(getFile());
}

//--------------------------------------------------------------------------
void ITextFile::accept (Updater* u)
{
	u->updateTo (SITextFile(this));
}


//--------------------------------------------------------------------------
void ITextFile::print (ostream& out) const
{
	IText::print(out);
	TFile::print(out);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ITextFile::set(const IMessage* msg )
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	status = TFile::set (msg) ;
	if (status & MsgHandler::kProcessed) {
		if (!read(fText))
			status = MsgHandler::kCreateFailure;
		else newData(true);
	}
	return status;
}

}
