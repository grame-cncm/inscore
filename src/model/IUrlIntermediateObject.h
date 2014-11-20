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

#ifndef __INScore__IUrlIntermediateObject__
#define __INScore__IUrlIntermediateObject__

#include <iostream>
#include "TFile.h"
#include "IShapeMap.h"

namespace inscore
{

class IUrlIntermediateObject;
typedef class libmapping::SMARTP<IUrlIntermediateObject>	SIUrlIntermediateObject;

class IUrlIntermediateObject : public IShapeMap, public TFile
{
    public:
				 IUrlIntermediateObject( const std::string& name, IObject* parent );
		virtual ~IUrlIntermediateObject() {}
    
		static SIUrlIntermediateObject create(const std::string& name, IObject * parent)	{ return new IUrlIntermediateObject(name, parent); }
    
		static const std::string kUrlIntermediateType;
    
        virtual MsgHandler::msgStatus set (const IMessage* msg );
    
        virtual QByteArray  getData() { return fData; }
    
        void setType(std::string type) {fType = type; }
    
        std::string getType() { return fType; }
    
        virtual void updateFileSucceded();
    
        virtual MsgHandler::msgStatus updateFileFailed(const IMessage* msg );

		virtual void	accept (Updater*);
    
    protected:
        std::string fUrlPath;
        std::string fType;
        QFileDownloader *    fDownloaderThread;
        QByteArray fData;
    
        void updateAtrributes(SIObject &obj);
        void updateSync(SIObject &obj);
};
}

#endif
