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
#include "TMessageEvaluator.h"
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
	fMsgHandlerMap[kcancel_SetMethod]	= TMethodMsgHandler<IUrlIntermediateObject, void (IUrlIntermediateObject::*)(void)>::create(this, &IUrlIntermediateObject::updateFileCanceled);
	
    fType = "";
    fTypeString = kUrlIntermediateType;
    fWidth = 1.0;
    fHeight = 1.0;
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
        fIsUrl = true;
        setFile(path);
        
        QUrl Url(getFile().c_str());
            
        if (fDownloaderThread) {
            updateFileCanceled();
        }
        
        fDownloaderThread = new QFileDownloader(Url,getOSCAddress().c_str());
        if (fDownloaderThread) fDownloaderThread->start();
        
        return MsgHandler::kProcessed;
    }
    
	return MsgHandler::kBadParameters;
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
    
    const IMessageList* msgs = eventsHandler()->getMessages (EventsAble::kSuccess);
	if (msgs && !msgs->list().empty())
        evalEventMsg(msgs);
    
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::updateFileCanceled()
{
    if (fDownloaderThread) {
        fDownloaderThread->terminate();
        delete fDownloaderThread;
    }
    
    const IMessageList* msgs = eventsHandler()->getMessages (EventsAble::kCancel);
	if (msgs && !msgs->list().empty())
        evalEventMsg(msgs);
    
    ITLErr << "URL download canceled" << ITLEndl;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IUrlIntermediateObject::updateFileFailed(const IMessage* msg )
{
    setR(200);
    
    const IMessageList* msgs = eventsHandler()->getMessages (EventsAble::kError);
	if (msgs && !msgs->list().empty())
        evalEventMsg(msgs);
    
    if(msg->size() == 1)
    {
        std::string error;
		if (!msg->param(0, error)) return MsgHandler::kBadParameters;
        ITLErr << error << ITLEndl;
    }
    return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::evalEventMsg(const IMessageList* list)
{
    MouseLocation mouse (0, 0, 0, 0, 0, 0);
	EventContext env(mouse, libmapping::rational(0,1), 0);
	TMessageEvaluator me;
	SIMessageList outmsgs = me.eval (list, env);
	if (outmsgs && outmsgs->list().size())
        outmsgs->send();
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IUrlIntermediateObject::_watchMsg(const IMessage* msg, bool add)
{ 
	MsgHandler::msgStatus status = IObject::_watchMsg (msg, add);
	if (status == MsgHandler::kProcessed) return status;

	std::string what;
	if (!msg->param (0, what))				// can't decode event to watch when not a string
		return MsgHandler::kBadParameters;	// exit with bad parameter
		
	EventsAble::eventype t = EventsAble::string2type (what);
	switch (t) {
		case EventsAble::kSuccess:
		case EventsAble::kError:
		case EventsAble::kCancel:
			if (msg->size() > 1) {
				SIMessageList watchMsg = msg->watchMsg2Msgs (1);
				if (!watchMsg) return MsgHandler::kBadParameters;

				if (add) eventsHandler()->addMsg (t, watchMsg);
				else eventsHandler()->setMsg (t, watchMsg);
			}
			else if (!add) eventsHandler()->setMsg (t, 0);
			status = MsgHandler::kProcessed;
			break;
		default: break;
	}
	return status;
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::accept (Updater* u)
{
	u->updateTo (SIUrlIntermediateObject(this));
}

}
