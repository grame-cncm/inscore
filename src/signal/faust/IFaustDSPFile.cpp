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

#include "IFaustDSPFile.h"
#include "IScene.h"
#include "Updater.h"
#include <iostream>

using namespace std;

namespace inscore
{
//--------------------------------------------------------------------------
const string IFaustDSPFile::kFaustDSPFileType("faustdspf");

//--------------------------------------------------------------------------
IFaustDSPFile::IFaustDSPFile( const std::string& name, IObject * parent )
	: IFaustDSP (name, parent), TFile (parent->getScene())
{ 
	fTypeString = kFaustDSPFileType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<string>::create(getFile());
}

//--------------------------------------------------------------------------
void IFaustDSPFile::accept (Updater* u)
{
	u->updateTo (SIFaustDSPFile(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustDSPFile::set (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) 
        return status; 

	status = TFile::set( msg );
    
    fSetParam = TFile::getFile();
    
    string content;
    
	if (status & MsgHandler::kProcessed) {
		if (!read(content) )
			return MsgHandler::kCreateFailure;
		else{ 
           newData(true);
          if(createFaustDSP (content)){
				init();        
				createVirtualNodes();
			}
       }
	}
	return status;   
}
//--------------------------------------------------------------------------
void IFaustDSPFile::print (IMessage& out) const
{
    out.setMessage(kset_SetMethod);
    out << kFaustDSPFileType << fSetParam;
}
    
    
}
