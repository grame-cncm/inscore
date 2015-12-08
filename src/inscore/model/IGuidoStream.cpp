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

#include "IGuidoStream.h"
#include "IScene.h"
#include "Updater.h"
#include "VGuidoItemView.h"
#include "GUIDOParse.h"

using namespace std;

namespace inscore
{
//--------------------------------------------------------------------------
const string IGuidoStream::kGuidoStreamType("gmnstream");

//--------------------------------------------------------------------------
IGuidoStream::IGuidoStream( const std::string& name, IObject * parent )
	: IGuidoCode (name, parent)
{
	fTypeString = kGuidoStreamType;
    fGuidoStream = GuidoOpenStream();
    
	fMsgHandlerMap[kclear_SetMethod] = TMethodMsgHandler<IGuidoStream, void (IGuidoStream::*)()>::create(this, &IGuidoStream::clear);
    fMsgHandlerMap[kwrite_SetMethod]		= TMethodMsgHandler<IGuidoStream>::create(this, &IGuidoStream::write);
}

IGuidoStream::~IGuidoStream()
{
	GuidoCloseStream(fGuidoStream);
}

//--------------------------------------------------------------------------
const string IGuidoStream::getCleanGMN() const
{
	const char* str = GuidoStream2GuidoString(fGuidoStream);
	string r(str);
	GuidoFreeStreamString(str);
	return r;
}

//--------------------------------------------------------------------------
void IGuidoStream::print (ostream& out) const
{
	IGuidoCode::print(out);
}

//--------------------------------------------------------------------------
void IGuidoStream::accept (Updater* u)
{
	u->updateTo (SIGuidoStream(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoStream::set (const IMessage* msg )
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

    string t;
	if ((msg->size() == 2) && msg->param(1, t)) {
		if(t!=fGMN){
			GuidoResetStream(fGuidoStream);
			writeStream(t);
			status = MsgHandler::kProcessed;
		}else status = MsgHandler::kProcessedNoChange;
	}
	else status = MsgHandler::kBadParameters;

	return status;
}

//--------------------------------------------------------------------------
void IGuidoStream::clear()
{
	if(fGMN=="") return;

	GuidoResetStream(fGuidoStream);
	setGMN("");
	newData(true);
}


//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoStream::write (const IMessage* msg )
{
	MsgHandler::msgStatus status; 

	string t;
	if ((msg->size() == 1) && msg->param(0, t)) {
        status = MsgHandler::kProcessed;
        writeStream(t);
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

//--------------------------------------------------------------------------
void IGuidoStream::writeStream (std::string t)
{
	const char * newchar = t.c_str();
    GuidoWriteStream(fGuidoStream, newchar);
    const char * str = GuidoGetStream(fGuidoStream);
    setGMN(str);
	GuidoFreeStreamString (str);
    newData(true);
}

}
