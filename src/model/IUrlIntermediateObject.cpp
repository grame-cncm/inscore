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

#include "IUrlIntermediateObject.h"
#include "VUrlIntermediateObjectView.h"
#include "TFile.h"
#include "IObject.h"
#include "IScene.h"
#include "QFileDownloader.h"
#include "IObjectFactory.h"
#include "Updater.h"
#include "VObjectView.h"
#include "ISceneSync.h"
#include <QUrl>

#define useiterator 0

using namespace libmapping;

namespace inscore
{

const std::string IUrlIntermediateObject::kUrlIntermediateType("url");


//--------------------------------------------------------------------------
IUrlIntermediateObject::IUrlIntermediateObject( const std::string& name, IObject* parent ) : IShapeMap(name, parent), TFile(parent->getScene()), fDownloaderThread(0)
{
    fMsgHandlerMap[ksuccess_SetMethod] = TMethodMsgHandler<IUrlIntermediateObject, void (IUrlIntermediateObject::*)(void)>::create(this, &IUrlIntermediateObject::updateFileSucceded);
	fMsgHandlerMap[kerror_SetMethod]   = TMethodMsgHandler<IUrlIntermediateObject>::create(this, &IUrlIntermediateObject::updateFileFailed);
	//cancel ?
    //fMsgHandlerMap[]	= TMethodMsgHandler<ISceneSync>::create(this, &ISceneSync::syncMsg);
	
    fType = "";
    fWidth = 1.0;
    fHeight = 1.0;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IUrlIntermediateObject::set (const IMessage* msg )
{
	MsgHandler::msgStatus status = MsgHandler::kProcessed;
    
    if (msg->size() == 3) // case of direct declaration : .../urlname set url <type> <urlpath>
    {
        std::string type;
		if (!msg->param(1, type)) status = MsgHandler::kBadParameters;
        setType(type);
        
        std::string path;
		if (!msg->param(2, path)) status = MsgHandler::kBadParameters;
        fIsUrl = true;
        setFile(path);
    }
    else // case of indirect declaration : .../urlname set type <urlpath>
        status = TFile::set( msg );
	
    QUrl Url(getFile().c_str());
            
    if (fDownloaderThread) {
        fDownloaderThread->terminate();
        delete fDownloaderThread;
    }
    fDownloaderThread = new QFileDownloader(Url,getOSCAddress().c_str());
    if (fDownloaderThread) fDownloaderThread->start();
    
	return status;
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::updateFileSucceded()
{
    fData = fDownloaderThread->downloadedData();
    
    // creation of the real object
    SIObject obj = IObjectFactory::create(name(), fType, fParent);

    if(obj && fData.count())
    {
        // We pass all  the informations to the new object
        fParent->add(obj);
        transferAttributes(obj);
        obj->setState(IObject::kModified);
        
        TFile * file = dynamic_cast<TFile*>((IObject*)obj);
        if (file)
        {
            file->setFile(getFile());
            file->setData(fData);
            file->updateUrl();
        }
        
        // self destruction
        del();
    }
}


//--------------------------------------------------------------------------
MsgHandler::msgStatus IUrlIntermediateObject::updateFileFailed(const IMessage* msg )
{
    setR(200);
    if(msg->size() == 1)
    {
        std::string error;
		if (!msg->param(0, error)) return MsgHandler::kBadParameters;
        ITLErr << error << ITLEndl;
    }
    return MsgHandler::kProcessed;
}


//--------------------------------------------------------------------------
void IUrlIntermediateObject::accept (Updater* u)
{
	u->updateTo (SIUrlIntermediateObject(this));
}

}
