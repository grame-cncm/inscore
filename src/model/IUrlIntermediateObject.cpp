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
#include "TFile.h"
#include "IObject.h"
#include "IScene.h"
#include "QFileDownloader.h"
#include "IObjectFactory.h"
#include <QUrl>

#define useiterator 0

using namespace libmapping;

namespace inscore
{

const std::string IUrlIntermediateObject::kUrlIntermediateType("url");


IUrlIntermediateObject::IUrlIntermediateObject( const std::string& name, IObject* parent ) : IObject(name, parent), TFile(parent->getScene()), fDownloaderThread(0)
{ 
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IUrlIntermediateObject::set (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	status = TFile::set( msg );
	
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
    
    //creation du vrai objet
    SIObject obj = IObjectFactory::create(name(), fType, fParent);
	if (obj)
    {
        fParent->add(obj);
        obj->setState(IObject::kModified);
	}
    
    //auto destruction
}

}
