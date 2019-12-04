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


#ifndef __VoidUpdaters__
#define __VoidUpdaters__

#include "export.h"
#include "IModelTypes.h"
#include "Updater.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief A class intended to update the view
*/
class inscore_export VoidUpdater : public Updater
{
	protected:
				 VoidUpdater() {}
		virtual ~VoidUpdater() {}

	public:		
		virtual void update (IObject*);
		virtual const char* name()	{ return "VoidUpdater"; }
};
typedef class libmapping::SMARTP<VoidUpdater>	SVoidUpdater;


class inscore_export VoidViewUpdater : public VoidUpdater {
	public:	
		virtual bool needupdate (IObject*);
		virtual const char* name()	{ return "VoidViewUpdater"; }
	static libmapping::SMARTP<VoidViewUpdater> create()	{ return new VoidViewUpdater(); }
};

class inscore_export VoidLocalMapUpdater : public VoidUpdater {
	public:	
		virtual bool needupdate (IObject*);
		virtual const char* name()	{ return "VoidLocalMapUpdater"; }
	static libmapping::SMARTP<VoidLocalMapUpdater> create()	{ return new VoidLocalMapUpdater(); }
};

class inscore_export VoidSlaveMapUpdater : public VoidUpdater {
	public:	
		virtual bool needupdate (IObject*);
		virtual const char* name()	{ return "VoidSlaveMapUpdater"; }
	static libmapping::SMARTP<VoidSlaveMapUpdater> create()	{ return new VoidSlaveMapUpdater(); }
};


/*!@} */

} // end namespoace

#endif
