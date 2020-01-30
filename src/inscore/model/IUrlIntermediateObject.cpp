/*

  INScore Project

  Copyright (C) 2009,2015  Grame

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

#include "IUrlIntermediateObject.h"
#include "IObjectFactory.h"
#include "TFile.h"
#include "IScene.h"
#include "Events.h"
#include "Updater.h"

#include "FileDownloader.h"
#if !defined(NOVIEW) && !defined(MODELONLY)
#include "QFileDownloader.h"
#endif

using namespace libmapping;

namespace inscore
{

const std::string IUrlIntermediateObject::kUrlIntermediateType("url");


//--------------------------------------------------------------------------
IUrlIntermediateObject::IUrlIntermediateObject( const std::string& name, IObject* parent ) : IShapeMap(name, parent), TFile(parent->getScene())
{
    fMsgHandlerMap[ksuccess_SetMethod] = TMethodMsgHandler<IUrlIntermediateObject, void (IUrlIntermediateObject::*)(void)>::create(this, &IUrlIntermediateObject::updateFileSucceded);
	fMsgHandlerMap[kerror_SetMethod]   = TMethodMsgHandler<IUrlIntermediateObject>::create(this, &IUrlIntermediateObject::updateFileFailed);
	fMsgHandlerMap[kcancel_SetMethod]	= TMethodMsgHandler<IUrlIntermediateObject, void (IUrlIntermediateObject::*)(void)>::create(this, &IUrlIntermediateObject::updateFileCanceled);
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<std::string>::create(getFile());
    
    fType = "";
    fTypeString = kUrlIntermediateType;
    fWidth = 1.0;
    fHeight = 1.0;
//	setColor( IColor(220,220,220) );
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IUrlIntermediateObject::set (const IMessage* msg )
{
	MsgHandler::msgStatus status = IObject::set(msg);
    if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange))
    {
        // this means that we have a change of type (not an url anymore) : we cancel the file download
        updateFileCanceled();
        return status;
    }
    if (msg->size() == 3) // we always use the declaration : .../urlname set url <type> <urlpath>
    {
        std::string type;
		if (!msg->param(1, type)) return MsgHandler::kBadParameters;
        setType(type);
        
        std::string path;
		if (!msg->param(2, path)) return MsgHandler::kBadParameters;
        setFile(path);
        
        // if the fDownloader exists, we are changing the path : we cancel the previous download.
        if (fDownloader)
            updateFileCanceled();
			
        fDownloader = createDownloader(getScene()->getRootPath().c_str());
        if (fDownloader) fDownloader->getAsync (path.c_str(), getOSCAddress().c_str());
		
        return MsgHandler::kProcessed;
    }
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
FileDownloader* IUrlIntermediateObject::createDownloader(const char* urlprefix ) const
{
#if !defined(NOVIEW) && !defined(MODELONLY)
	return new QFileDownloader (urlprefix);
#else
	return 0;
#endif
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::updateFileSucceded()
{
    // creation of the real object
    SIObject obj = IObjectFactory::create(name(), fType, fParent);
	int n = fDownloader->dataSize();

    if(obj && n)
    {
        // We pass all  the informations to the new object
        fParent->add(obj);
        transferAttributes(obj);
        obj->setModified();
        
        TFile * file = dynamic_cast<TFile*>((IObject*)obj);
        if (file)
        {
            file->setFile(getFile());
            file->setData(fDownloader->data(), fDownloader->dataSize());
            file->updateUrl();
        }
		else ITLErr << "Unexpected non file type" << fType << ITLEndl;
        
        // self destruction
        del();
        fParent->cleanupSync();
    }
	checkEvent(kSuccessEvent, rational(0,1), this);
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::updateFileCanceled()
{
    if (fDownloader) {
        delete fDownloader;
		fDownloader = 0;
    }
    
	checkEvent(kCancelEvent, rational(0,1), this);
    ITLErr << "URL download canceled" << ITLEndl;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IUrlIntermediateObject::updateFileFailed(const IMessage* msg )
{
    setR(200);
    
	checkEvent(kErrorEvent, rational(0,1), this);
    if(msg->size() == 1)
    {
        std::string error;
		if (!msg->param(0, error)) return MsgHandler::kBadParameters;
        ITLErr << error << ITLEndl;
    }
    return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
bool IUrlIntermediateObject::acceptSimpleEvent(EventsAble::eventype t) const
{
	std::string ev(t);
	if ( (ev == kSuccessEvent) || (ev == kErrorEvent) || (ev == kCancelEvent)) return true;
	return IObject::acceptSimpleEvent(t);
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::accept (Updater* u)
{
	u->updateTo (SIUrlIntermediateObject(this));

}
}
