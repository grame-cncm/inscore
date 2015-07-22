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
#include "HTTPServer.h"
#include "ITLError.h"
#include "IScene.h"
#include "VExport.h"
#include "VSceneView.h"
#include "WebApi.h"

using namespace std;

namespace inscore
{
	// Library name.
static const char* httpdlibName = "inscorehttpd";

// function name.
static const char* fctInitialize = "initialize";
static const char* fctDestroy = "destroy";
static const char* fctStart = "start";
static const char* fctStop = "stop";
static const char* fctStatus = "status";
static const char* fctVersion = "version";

// function pointer.
THttpdPlugin::TInitialize THttpdPlugin::fInitialize = 0;
THttpdPlugin::TDestroy THttpdPlugin::fDestroy = 0;
THttpdPlugin::TStart THttpdPlugin::fStart = 0;
THttpdPlugin::TStop THttpdPlugin::fStop = 0;
THttpdPlugin::TStatus THttpdPlugin::fStatus = 0;
THttpdPlugin::TVersion THttpdPlugin::fVersion = 0;

THttpdPlugin::THttpdPlugin(IScene *exportedObject) : fExportedObject(exportedObject)
{
	
	// Load library and initialize function.
	
	fApi = new WebApi(fExportedObject->getView(), fExportedObject->getJSEngine(), fExportedObject->getLUAEngine());
	fHttpdServer = new HTTPDServer(fApi, 0, 0);

//	if (load()) {
//		// Create Api object
//		fApi = new WebApi(fExportedObject->getView(), fExportedObject->getJSEngine(), fExportedObject->getLUAEngine());
//		// Initialize server
//		fHttpdServer = fInitialize(fApi);
//	} else {
//		ITLErr << "cannot load http server plugin" << ITLEndl;
//	}
}

THttpdPlugin::~THttpdPlugin()
{
	delete fHttpdServer;
//	if(isResolved())
//		fDestroy(fHttpdServer);
}

bool THttpdPlugin::start(int port)
{
	return fHttpdServer->start(port);
//	if(isResolved())
//		return fStart(fHttpdServer, port);
//	return false;
}

bool THttpdPlugin::stop()
{
	fHttpdServer->stop();
	return true;

//	if(isResolved())
//		return fStop(fHttpdServer);
//	return false;
}

int THttpdPlugin::status()
{
	return fHttpdServer->status();
//	if(isResolved())
//		return fStatus(fHttpdServer);
	return 0;
}

//----------------------------------------------------------------------------
bool THttpdPlugin::isResolved ()
{
	return	fInitialize && fDestroy && fStart && fStop && fStatus && fVersion;
}

//----------------------------------------------------------------------------
bool THttpdPlugin::load ()
{
	return true;
	
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
		fVersion = resolve<TVersion> (fctVersion);
		if (fVersion == 0) return false;
	} else return false;
	oscerr << OSCStart("INScore Http server version ") << fVersion() << "loaded" << OSCEnd();
	return true;
}

}
