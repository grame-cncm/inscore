/*
  Copyright (c) Grame 2015

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr

*/

#include "THttpdPlugin.h"
#include "ITLError.h"

namespace inscore
{
	// Library name.
static const char* httpdlibName = "Httpd";

// function name.
static const char* fctInitialize = "initialize";
static const char* fctDestroy = "destroy";
static const char* fctStart = "start";
static const char* fctStop = "stop";
static const char* fctStatus = "status";

// function pointer.
THttpdPlugin::TInitialize THttpdPlugin::fInitialize = 0;
THttpdPlugin::TDestroy THttpdPlugin::fDestroy = 0;
THttpdPlugin::TStart THttpdPlugin::fStart = 0;
THttpdPlugin::TStop THttpdPlugin::fStop = 0;
THttpdPlugin::TStatus THttpdPlugin::fStatus = 0;

THttpdPlugin::THttpdPlugin()
{
	if (load())
		fHttpdServer = fInitialize();
	else
		ITLErr << "cannot load http server plugin" << ITLEndl;
}

THttpdPlugin::~THttpdPlugin()
{
	fDestroy(fHttpdServer);
}

bool THttpdPlugin::start(int port)
{
	if(isResolved())
		return fStart(fHttpdServer, port);
	return false;
}

bool THttpdPlugin::stop()
{
	if(isResolved())
		return fStop(fHttpdServer);
	return false;
}

int THttpdPlugin::status()
{
	if(isResolved())
		return fStatus(fHttpdServer);
	return false;
}

//----------------------------------------------------------------------------
bool THttpdPlugin::isResolved ()
{
	return	fInitialize && fDestroy && fStart && fStop && fStatus;
}

//----------------------------------------------------------------------------
bool THttpdPlugin::load ()
{
	if (isLoaded()) return isResolved();

	if (TPlugin::load(httpdlibName)) {
		fInitialize = resolve<TInitialize> (fctInitialize);
		if (fInitialize == 0) return false;
		fDestroy = resolve<TDestroy> (fctDestroy);
		if (fDestroy == 0) return false;
		fStart = resolve<TStart> (fctStart);
		if (fStart == 0) return false;
		fStop = resolve<TStop> (fctStop);
		if (fStop == 0) return false;
		fStatus = resolve<TStatus> (fctStatus);
		if (fStatus == 0) return false;
	} else return false;
	return true;
}


}
