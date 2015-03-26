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

#include "IGuidoPianoRoll.h"
#include "IGuidoStream.h"
#include "IScene.h"
#include "Updater.h"
#include "VGuidoItemView.h"

using namespace std;

namespace inscore
{
//--------------------------------------------------------------------------
const string IGuidoPianoRoll::kGuidoPianoRollType("pianoroll");

//--------------------------------------------------------------------------
IGuidoPianoRoll::IGuidoPianoRoll( const std::string& name, IObject * parent )
	: IGuidoCode (name, parent)
{
	fTypeString = kGuidoPianoRollType;
    fType = kSimplePianoRoll;
}

IGuidoPianoRoll::~IGuidoPianoRoll()
{
    GuidoDestroyPianoRoll(fPianoRoll);
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::accept (Updater* u)
{
	u->updateTo (SIGuidoPianoRoll(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRoll::set (const IMessage* msg )
{
	MsgHandler::msgStatus status = IGuidoCode::set(msg);

    updatePianoRoll();
	return status;
}

//--------------------------------------------------------------------------
void IGuidoPianoRoll::updatePianoRoll()
{
    GuidoParser * parser = GuidoOpenParser ();
	ARHandler handler;
    IGuidoStream * stream = dynamic_cast<IGuidoStream*>(this);
    if(stream)
        handler = GuidoStream2AR(parser, stream->getGuidoStream());
    else
        handler = GuidoString2AR(parser, fGMN.c_str());
    fPianoRoll = GuidoAR2PianoRoll(fType, handler);
    
}

}
