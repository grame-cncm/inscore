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
#include "IScene.h"
#include "VExport.h"
#include "VSceneView.h"

#include "DataExchange.h"

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

// function pointer.
THttpdPlugin::TInitialize THttpdPlugin::fInitialize = 0;
THttpdPlugin::TDestroy THttpdPlugin::fDestroy = 0;
THttpdPlugin::TStart THttpdPlugin::fStart = 0;
THttpdPlugin::TStop THttpdPlugin::fStop = 0;
THttpdPlugin::TStatus THttpdPlugin::fStatus = 0;

/*!
 * \brief getData callback method used by the server.
 * \param args
 * \param aObject the Inscore server model object
 * \return
 */
struct responsedata * getData(struct requestarguments* args, void * aObject)
{
	THttpdPlugin * myPlugin = static_cast<THttpdPlugin*>(aObject);
	return myPlugin->getData(args);
}

struct responsedata * THttpdPlugin::getData(struct requestarguments* args) const
{
	if(fExportedObject->getDeleted())
		return 0;

	VObjectView * objectView = fExportedObject->getView();

	// Get data
	AbstractData data = objectView->getImage(args->format);
	if(data.data == 0)
		return 0;

	struct responsedata * resp = new struct responsedata;
	resp->data = new char[data.size];
	memcpy(resp->data, data.data, data.size);
	resp->size = data.size;

	return resp;
}

THttpdPlugin::THttpdPlugin(const IScene *exportedObject) : fExportedObject(exportedObject)
{
	// Load library and initialize function.
	if (load())
		fHttpdServer = fInitialize(&inscore::getData, this);
	else
		ITLErr << "cannot load http server plugin" << ITLEndl;
}

THttpdPlugin::~THttpdPlugin()
{
	if(isResolved())
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
	return 0;
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
