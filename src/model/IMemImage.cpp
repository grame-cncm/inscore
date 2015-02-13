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

#include "IMemImage.h"
#include "IMessage.h"
#include "ITLError.h"
#include "IScene.h"
#include "Updater.h"
#include "VImageView.h"

using namespace std;

namespace inscore
{
//--------------------------------------------------------------------------
const string IMemImage::kMemImageType("memimg");

//--------------------------------------------------------------------------
IMemImage::IMemImage( const std::string& name, IObject * parent )
	: IImage (name, parent)
{	
	fTypeString = kMemImageType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<string>::create(getFile());
}

//--------------------------------------------------------------------------
void IMemImage::accept (Updater* u)
{
	u->updateTo (SIMemImage(this));
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IMemImage::set (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	if (msg->size() != 2) return MsgHandler::kBadParameters;
	string opath;
	if (msg->param(1,opath)) {
		const IObject* obj = findnode (opath);
		if (obj) {
cout << "IMemImage::set " << obj->name() << endl;
			return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;
}

}
