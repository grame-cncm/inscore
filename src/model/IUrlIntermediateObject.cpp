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


IUrlIntermediateObject::IUrlIntermediateObject( const std::string& name, IObject* parent ) : IShapeMap(name, parent), TFile(parent->getScene()), fDownloaderThread(0)
{ 
    fWidth = 1.0;
    fHeight = 1.0;
    setR(100);
    setG(100);
    setB(100);
    setA(100);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IUrlIntermediateObject::set (const IMessage* msg )
{
	MsgHandler::msgStatus status = TFile::set( msg );
	
    QUrl Url(getFile().c_str());
            
    if (fDownloaderThread) {
        fDownloaderThread->terminate();
        delete fDownloaderThread;
    }
    fDownloaderThread = new QFileDownloader(Url,this);
    if (fDownloaderThread) fDownloaderThread->start();
    
	return status;
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::updateFile()
{
    fData = fDownloaderThread->downloadedData();
    
    // creation of the real object
    SIObject obj = IObjectFactory::create(name(), fType, fParent);

    if(obj)
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
			
        obj->setDate (getDate());
        obj->setDuration (getDuration());

        *((EventsAble*)obj) = *((EventsAble*)this);
        
        fParent->add(obj);
        obj->setState(IObject::kModified);

        TFile * file = dynamic_cast<TFile*>((IObject*)obj);
        if (file)
        {
            file->setFile(getFile());
            file->setData(fData);
            file->updateUrl();
        }
    }
    // auto destruction
    del();
    VUrlIntermediateObjectView * urlView = dynamic_cast<VUrlIntermediateObjectView*>(fView);
    if(urlView) urlView->deleteFromScene();
}

//--------------------------------------------------------------------------
void IUrlIntermediateObject::accept (Updater* u)
{
	u->updateTo (SIUrlIntermediateObject(this));
}

}
