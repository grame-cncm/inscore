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

#include "IGuidoPianoRollStream.h"
//#include "IScene.h"
#include "Updater.h"
//#include "VGuidoItemView.h"

using namespace std;

namespace inscore
{
//--------------------------------------------------------------------------
const string IGuidoPianoRollStream::kGuidoPianoRollStreamType("pianorollstream");

//--------------------------------------------------------------------------
IGuidoPianoRollStream::IGuidoPianoRollStream( const std::string& name, IObject * parent )
	: IGuidoCode(name, parent), IGuidoStream (name, parent), IGuidoPianoRoll (name, parent)
{
    fTypeString = kGuidoPianoRollStreamType;
}

IGuidoPianoRollStream::~IGuidoPianoRollStream()
{
//    GuidoDestroyPianoRoll(fPianoRoll);
}

//--------------------------------------------------------------------------
void IGuidoPianoRollStream::accept (Updater* u)
{
	u->updateTo (SIGuidoPianoRollStream(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRollStream::set (const IMessage* msg )
{
	MsgHandler::msgStatus status = IGuidoStream::set(msg);
    if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return IGuidoPianoRoll::set(msg);
    else return status;
}

//--------------------------------------------------------------------------
void IGuidoPianoRollStream::clear()
{
    IGuidoStream::clear();
    IGuidoPianoRoll::updatePianoRoll();
}


//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRollStream::write (const IMessage* msg )
{
	MsgHandler::msgStatus status = IGuidoStream::write(msg);
    IGuidoPianoRoll::updatePianoRoll();
	return status;
}

}
