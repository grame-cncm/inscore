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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#include "Updater.h"
#include "IObject.h"
#include "ISync.h"

#include <iostream>
using namespace std;

namespace interlude
{

//--------------------------------------------------------------------------
void Updater::update (IObject* object)
{
	if (needupdate (object)) {
		object->accept(this);
	}
	if (object->getState() & IObject::kSubModified) {
		IObject::subnodes::const_iterator i = object->elements().begin();
		while (i != object->elements().end()) {
			update (*i);
			i++;
		}
	}
}

//--------------------------------------------------------------------------
bool ViewUpdater::needupdate (IObject* o)
{
	int state = o->getState();
	return (state & (IObject::kModified + IObject::kNewObject + IObject::kMasterModified));
}

//--------------------------------------------------------------------------
bool LocalMapUpdater::needupdate (IObject* o)
{
	return ( o->fAutoMap && o->durationModified()) || o->localMapModified() || o->newData();
}

//--------------------------------------------------------------------------
bool SlaveMapUpdater::needupdate (IObject* o)
{
	return true;

//	return o->localMapModified() || o->dateModified(); // || master->getMaster()->localMapModified() || master->modified();

//	int state = o->getState();
//	return (state & (IObject::kModified + IObject::kNewObject + IObject::kMasterModified));
}

} // end namespoace
