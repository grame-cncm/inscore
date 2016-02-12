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

#include "ISVGFile.h"
#include "IMessage.h"
#include "TComposition.h"
#include "IScene.h"
#include "Updater.h"
#include "VSVGView.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
const string ISVGFile::kSVGFileType("svgf");

//--------------------------------------------------------------------------
ISVGFile::ISVGFile( const std::string& name, IObject * parent )
	: IGraphicBasedObject(name, parent), TFile (parent->getScene()), IAnimated(this)
{ 
	fTypeString = kSVGFileType;
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<string>::create(getFile());

	fMsgHandlerMap[kanimate_GetSetMethod]		= TSetMethodMsgHandler<ISVGFile,bool>::create(this, &ISVGFile::setAnimate);
	fGetMsgHandlerMap[kanimate_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fAnimate);
	fGetMsgHandlerMap[kanimated_GetMethod]		= TGetParamMsgHandler<bool>::create(fAnimated);
}

//--------------------------------------------------------------------------
void ISVGFile::accept (Updater* u)
{
	u->updateTo (SISVGFile(this));
}


//--------------------------------------------------------------------------
void ISVGFile::print (ostream& out) const
{
	TFile::print(out);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISVGFile::set(const IMessage* msg )
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 
	
	status = TFile::set (msg);
	if (status & MsgHandler::kProcessed)
		newData(true);
	return status;
}

//--------------------------------------------------------------------------
void ISVGFile::updateUrl()
{
//    fIsUrl = true;
//    read(fData);
    changed(true);
    this->getView()->updateLocalMapping(this);

//    VSVGView * svgView = fView ? dynamic_cast<VSVGView*>(fView) : 0;
//    if(svgView)
//        svgView->updateLocalMapping(this);
}

}
