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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include "IAudio.h"
#include "Updater.h"
#include "IMessage.h"
#include "IScene.h"
#include "VObjectView.h"
#include "Events.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
const string IAudio::kAudioType("audio");

//--------------------------------------------------------------------------
IAudio::IAudio( const std::string& name, IObject * parent )
	: IMedia (name, parent)
{	
	fTypeString = kAudioType;
	setWidth(1, false, false);
	setHeight(0.5, false, false);
	setPenWidth (1.0);
	setBrushStyle ("none");
	setPending();
}

//--------------------------------------------------------------------------
void IAudio::accept (Updater* u)
{
	u->updateTo (SIAudio(this));
}

}

