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
#include "IMappingUpdater.h"
#include "VTextView.h"
#include "VGuidoItemView.h"
#include "INScore.h"
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
        updateAtrributes(obj);
        
        TFile * file = dynamic_cast<TFile*>((IObject*)obj);
        if (file)
        {
            file->setFile(getFile());
            file->setData(fData);
            file->updateUrl();
        }
        
        updateSync(obj);
        
        /*for(int i = 0; i < fParent->elements().size(); i++)
        {
            ISceneSync * sync = dynamic_cast<ISceneSync*>((IObject*)(fParent->elements()[i]));
            if(sync) // we found the syncnode, to get the informations about the synchronizations
            {
                IMessageList * list = sync->getAll();
                for(int j = 0; j < list->list().size(); j++)
                {
                    INScore::MessagePtr msg = INScore::newMessage(list->list()[j]->message().c_str());
                    std::string s;
                    std::string m;
                    if (list->list()[j]->param(0, s))
                        INScore::add (msg, s.c_str());
                    if(list->list()[j]->size()>1 && list->list()[j]->param(1,m))
                        INScore::add (msg, m.c_str());
                    std::cout << "sync message to send : " << msg << " : " << s << " " << m << std::endl;
                    //INScore::postMessage (sync->getOSCAddress().c_str(), msg);
                }
            }
        }
    */
        
        
        IText * text = dynamic_cast<IText*>((IObject*)obj);
        IGuidoCode * gmn = dynamic_cast<IGuidoCode*>((IObject*)obj);
        if(text)
        {
            VTextView * textView = dynamic_cast<VTextView*>(text->getView());
            textView->updateView(text);
        }
        else if(gmn)
        {
            VGuidoItemView * gmnView = dynamic_cast<VGuidoItemView*>(gmn->getView());
            gmnView->updateView(gmn);
        }
        else
            obj->getView()->updateView(obj);
        
        // self destruction
        del();
        VUrlIntermediateObjectView * urlView = dynamic_cast<VUrlIntermediateObjectView*>(fView);
        if(urlView)
            urlView->deleteFromScene();
    }
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::updateAtrributes(SIObject &obj)
{
    obj->setXPos (getXPos());
    obj->setYPos (getYPos());
    obj->setXOrigin (getXOrigin());
    obj->setYOrigin (getYOrigin());
    obj->setScale (getScale());
    obj->setVisible (getVisible());
    obj->setZOrder (getZOrder());
    obj->setShear (getShear());
    obj->setRotateX (getRotateX());
    obj->setRotateY (getRotateY());
    obj->setRotateZ (getRotateZ());
    obj->setR(getR());
    obj->setG(getG());
    obj->setB(getB());
    obj->setA(getA());
    
    obj->setDate (getDate());
    obj->setDuration (getDuration());

    *((EventsAble*)obj) = *((EventsAble*)this);
    
    fParent->add(obj);
    obj->setState(IObject::kModified);
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::updateSync(SIObject &obj)
{
    IMappingUpdater * updater = new IMappingUpdater();
        
    std::vector<SMaster> masters = fParent->getMasters(this);
    std::vector<SIObject> slaves = fParent->getSlaves(this);
        
    for(int i = 0; i < fParent->elements().size(); i++)
    {
        ISceneSync * sync = dynamic_cast<ISceneSync*>((IObject*)(fParent->elements()[i]));
        if(sync) // we found the syncnode, to get the informations about the synchronizations
        {
            // if the "proxy" object (this) was slaved, we have to re-create the sync relations for the new object
            for(int j = 0; j < masters.size(); j++)
                sync->sync(obj,masters[j]);
            
            // if it had slaves ...
            for(int j = 0; j < slaves.size(); j++)
            {
                std::vector<SMaster> mastersOfSlave = fParent->getMasters(slaves[j]);
                for(int k = 0 ; k < mastersOfSlave.size(); k++)
                {
                    if(mastersOfSlave[k]->getMaster() == this)
                    {
                        // we have to re-create a SMaster with same properties but with the new object
                        SMaster master = Master::create(obj, mastersOfSlave[k]->getAlignment(), mastersOfSlave[k]->getStretch(), mastersOfSlave[k]->getMode(), mastersOfSlave[k]->getMasterMapName() , mastersOfSlave[k]->getSlaveMapName() );
                        sync->sync(slaves[j], master);
                        // then we have to force the building of the delault mappings, and the updating of the mapping and the view...
                        slaves[j]->getView()->updateLocalMapping(slaves[j]);
                        updater->update(slaves[j]);
                        slaves[j]->getView()->updateView(slaves[j]);
                    }
                }
            }
        }
    }
        
    updater->update(obj);
    obj->getView()->updateView(obj);
        
    delete updater;
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
