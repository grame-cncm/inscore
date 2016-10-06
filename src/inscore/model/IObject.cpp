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


#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>

#include <algorithm>
#include <iostream>
#include <fstream>

#include "EventsAble.h"
#include "IAppl.h"
#include "IApplVNodes.h"
#include "IGlue.h"
#include "IMessage.h"
#include "IMessageTranslator.h"
#include "IMessageStream.h"
#include "IObject.h"
#include "IObjectVNodes.h"
#include "IProxy.h"
#include "IScene.h"
#include "IVNode.h"
#include "GraphicEffect.h"
#include "OSCAddress.h"
#include "OSCRegexp.h"
#include "OSCStream.h"
#include "Updater.h"
#include "ISync.h"
#include "Tools.h"
#include "ISceneSync.h"
#include "TMessageEvaluator.h"
#include "ISignalNode.h"
#include "INScore.h"
#include "Events.h"

#include "VObjectView.h"


using namespace std;
using namespace libmapping;

namespace inscore
{

bool isDirectory( std::string path )
{
	DIR *dp = opendir ( path.c_str() );
	bool result = (dp != NULL);
	if ( result )
		closedir(dp);
	return result;
}

//--------------------------------------------------------------------------
OSCStream& operator <<(OSCStream& s, const TFloatPoint& val)
{
	s << float(val.x()) << float(val.y());
	return s;
}


//--------------------------------------------------------------------------
// IObject implementation
//--------------------------------------------------------------------------
IObject::IObject(const std::string& name, IObject* parent) : IDate(this),
					fName(name), fDispStart(0), fDispEnd(1),
					fDelete (false), fLock(false), fState(kNewObject), fNewData(true), fEdit(false), fView(0), fParent(parent)
{
	fTypeString = "obj";

	fMsgHandlerMap[kalias_GetSetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::aliasMsg);
	fMsgHandlerMap[kset_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::set);
	fMsgHandlerMap[kget_SetMethod]		= TMethodMsgHandler<IObject, MsgHandler::msgStatus (IObject::*)(const IMessage*) const >::create(this, &IObject::get);
	fMsgHandlerMap[kdel_SetMethod]		= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::del);
	fMsgHandlerMap[kexport_SetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::exportMsg);
	fMsgHandlerMap[kexportAll_SetMethod]= TMethodMsgHandler<IObject>::create(this, &IObject::exportAllMsg);
//	fMsgHandlerMap["rename"]			= TMethodMsgHandler<IObject>::create(this, &IObject::renameMsg);
	fMsgHandlerMap[ksave_SetMethod]		= TMethodMsgHandler<IObject, MsgHandler::msgStatus (IObject::*)(const IMessage*) const>::create(this, &IObject::saveMsg);
	fMsgHandlerMap[klock_GetSetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::lockMsg);
	fMsgHandlerMap[kwatch_GetSetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::watchMsg);
	fMsgHandlerMap[keval_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::evalMsg);
	
	fMsgHandlerMap[kwatchplus_SetMethod]= TMethodMsgHandler<IObject>::create(this, &IObject::watchMsgAdd);
	fMsgHandlerMap[kevent_SetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::eventMsg);
	fMsgHandlerMap[kedit_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::editMsg);

	fMsgHandlerMap[kpush_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::pushMsg);
	fMsgHandlerMap[kpop_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::popMsg);

	fGetMultiMsgHandlerMap[kwatch_GetSetMethod]	= TGetParamMultiMethodHandler<IObject, SIMessageList (IObject::*)() const>::create(this, &IObject::getWatch);
	fGetMultiMsgHandlerMap[kmap_GetSetMethod]	= TGetParamMultiMethodHandler<IObject, SIMessageList (IObject::*)() const>::create(this, &IObject::getMaps);
	fGetMultiMsgHandlerMap[kalias_GetSetMethod]	= TGetParamMultiMethodHandler<IObject, SIMessageList (IObject::*)() const>::create(this, &IObject::getAliases);
    fGetMultiMsgHandlerMap[kstack_GetMethod]	= TGetParamMultiMethodHandler<IObject, SIMessageList (IObject::*)() const>::create(this, &IObject::getStack);


	fGetMsgHandlerMap[klock_GetSetMethod]	= TGetParamMethodHandler<IObject, bool(IObject::*)() const>::create(this, &IObject::getLocked);
	fGetMsgHandlerMap[kcount_GetMethod]		= TGetParamMethodHandler<IObject, int (IObject::*)() const>::create(this, &IObject::getSize);
	fGetMsgHandlerMap[krcount_GetMethod]	= TGetParamMethodHandler<IObject, int (IObject::*)() const>::create(this, &IObject::getRSize);
}


//--------------------------------------------------------------------------
void IObject::setHandlers()
{
	colorAble();
	positionAble();
	shapeAble();
	timeAble();
}

//--------------------------------------------------------------------------
void IObject::colorAble()
{
	fMsgHandlerMap[kcolor_GetSetMethod]		= TMethodMsgHandler<IColor>::create(this, &IColor::set);
	fMsgHandlerMap[khsb_SetMethod]			= TMethodMsgHandler<IColor>::create(this, &IColor::setHSV);

	fMsgHandlerMap[kred_GetSetMethod]		= IColor::SetColorMsgHandler::create(this, &IObject::setR, &IObject::setR);
	fMsgHandlerMap[kgreen_GetSetMethod]		= IColor::SetColorMsgHandler::create(this, &IObject::setG, &IObject::setG);
	fMsgHandlerMap[kblue_GetSetMethod]		= IColor::SetColorMsgHandler::create(this, &IObject::setB, &IObject::setB);
	fMsgHandlerMap[kalpha_GetSetMethod]		= IColor::SetColorMsgHandler::create(this, &IObject::setA, &IObject::setA);
	fMsgHandlerMap[khue_GetSetMethod]		= IColor::SetColorMsgHandler::create(this, &IObject::setH, &IObject::setH);
	fMsgHandlerMap[ksaturation_GetSetMethod]= IColor::SetColorMsgHandler::create(this, &IObject::setS, &IObject::setS);
	fMsgHandlerMap[kbrightness_GetSetMethod]= IColor::SetColorMsgHandler::create(this, &IObject::setV, &IObject::setV);

	fMsgHandlerMap[kdcolor_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::dcolorMsg);
	fMsgHandlerMap[kdhsb_SetMethod]			= TMethodMsgHandler<IObject>::create(this, &IObject::dhsvMsg);

	fMsgHandlerMap[kdred_SetMethod]			= IColor::SetColorMsgHandler::create(this, &IObject::dR, &IObject::dR);
	fMsgHandlerMap[kdgreen_SetMethod]		= IColor::SetColorMsgHandler::create(this, &IObject::dG, &IObject::dG);
	fMsgHandlerMap[kdblue_SetMethod]		= IColor::SetColorMsgHandler::create(this, &IObject::dB, &IObject::dB);
	fMsgHandlerMap[kdalpha_SetMethod]		= IColor::SetColorMsgHandler::create(this, &IObject::dA, &IObject::dA);
	fMsgHandlerMap[kdhue_SetMethod]			= IColor::SetColorMsgHandler::create(this, &IObject::dH, &IObject::dH);
	fMsgHandlerMap[kdsaturation_SetMethod]	= IColor::SetColorMsgHandler::create(this, &IObject::dS, &IObject::dS);
	fMsgHandlerMap[kdbrightness_SetMethod]	= IColor::SetColorMsgHandler::create(this, &IObject::dV, &IObject::dV);

	fGetMsgHandlerMap[kcolor_GetSetMethod]			= TGetParamMsgHandler<IColor>::create(*(IColor*)this);
	fAltGetMsgHandlerMap[kred_GetSetMethod]			= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getR);
	fAltGetMsgHandlerMap[kgreen_GetSetMethod]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getG);
	fAltGetMsgHandlerMap[kblue_GetSetMethod]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getB);
	fAltGetMsgHandlerMap[kalpha_GetSetMethod]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getA);
	fAltGetMsgHandlerMap[khue_GetSetMethod]			= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getH);
	fAltGetMsgHandlerMap[ksaturation_GetSetMethod]	= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getS);
	fAltGetMsgHandlerMap[kbrightness_GetSetMethod]	= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getV);
	
    fSigHandlerMap[kred_GetSetMethod]		= IColor::SetColorSigHandler::create(this, &IObject::setR, &IObject::setR);
	fSigHandlerMap[kgreen_GetSetMethod]		= IColor::SetColorSigHandler::create(this, &IObject::setG, &IObject::setG);
	fSigHandlerMap[kblue_GetSetMethod]		= IColor::SetColorSigHandler::create(this, &IObject::setB, &IObject::setB);
	fSigHandlerMap[kalpha_GetSetMethod]		= IColor::SetColorSigHandler::create(this, &IObject::setA, &IObject::setA);
	fSigHandlerMap[khue_GetSetMethod]		= IColor::SetColorSigHandler::create(this, &IObject::setH, &IObject::setH);
	fSigHandlerMap[ksaturation_GetSetMethod]= IColor::SetColorSigHandler::create(this, &IObject::setS, &IObject::setS);
	fSigHandlerMap[kbrightness_GetSetMethod]= IColor::SetColorSigHandler::create(this, &IObject::setV, &IObject::setV);
    
	fSigHandlerMap[kdred_SetMethod]			= IColor::SetColorSigHandler::create(this, &IObject::dR, &IObject::dR);
	fSigHandlerMap[kdgreen_SetMethod]		= IColor::SetColorSigHandler::create(this, &IObject::dG, &IObject::dG);
	fSigHandlerMap[kdblue_SetMethod]		= IColor::SetColorSigHandler::create(this, &IObject::dB, &IObject::dB);
	fSigHandlerMap[kdalpha_SetMethod]		= IColor::SetColorSigHandler::create(this, &IObject::dA, &IObject::dA);
	fSigHandlerMap[kdhue_SetMethod]			= IColor::SetColorSigHandler::create(this, &IObject::dH, &IObject::dH);
	fSigHandlerMap[kdsaturation_SetMethod]	= IColor::SetColorSigHandler::create(this, &IObject::dS, &IObject::dS);
	fSigHandlerMap[kdbrightness_SetMethod]	= IColor::SetColorSigHandler::create(this, &IObject::dV, &IObject::dV);
}

//--------------------------------------------------------------------------
void IObject::positionAble()
{
	fGetMsgHandlerMap[kx_GetSetMethod]		= TGetParamMsgHandler<float>::create(fXPos);
	fGetMsgHandlerMap[ky_GetSetMethod]		= TGetParamMsgHandler<float>::create(fYPos);
	fGetMsgHandlerMap[kxorigin_GetSetMethod]= TGetParamMsgHandler<float>::create(fXOrigin);
	fGetMsgHandlerMap[kyorigin_GetSetMethod]= TGetParamMsgHandler<float>::create(fYOrigin);
	fGetMsgHandlerMap[kz_GetSetMethod]		= TGetParamMsgHandler<float>::create(fZOrder);
	fAltGetMsgHandlerMap[kangle_GetSetMethod]	= TGetParamMsgHandler<float>::create(fZAngle);
	fGetMsgHandlerMap[kscale_GetSetMethod]	= TGetParamMsgHandler<float>::create(fScale);
	fGetMsgHandlerMap[kshow_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fVisible);
	fGetMsgHandlerMap[kwidth_GetSetMethod]	= TGetParamMsgHandler<float>::create(fWidth);
	fGetMsgHandlerMap[kheight_GetSetMethod] = TGetParamMsgHandler<float>::create(fHeight);
	fGetMsgHandlerMap[kshear_GetSetMethod]	= TGetParamMsgHandler<TFloatSize>::create(fShear);
	fGetMsgHandlerMap[krotatex_GetSetMethod]= TGetParamMsgHandler<float>::create(fXAngle);
	fGetMsgHandlerMap[krotatey_GetSetMethod]= TGetParamMsgHandler<float>::create(fYAngle);
	fGetMsgHandlerMap[krotatez_GetSetMethod]= TGetParamMsgHandler<float>::create(fZAngle);
	fGetMsgHandlerMap[keffect_GetSetMethod]	= TGetParamMethodHandler<IObject, GraphicEffect (IObject::*)() const>::create(this, &IObject::getEffect);
	fGetMsgHandlerMap[kframe_GetMethod]		= TGetParamMethodHandler<IObject, vector<float> (IObject::*)() const>::create(this, &IObject::getFrame);

	fMsgHandlerMap[kx_GetSetMethod]			= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setXPos);
	fMsgHandlerMap[ky_GetSetMethod]			= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setYPos);
	fMsgHandlerMap[kxorigin_GetSetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setXOrigin);
	fMsgHandlerMap[kyorigin_GetSetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setYOrigin);
	fMsgHandlerMap[kz_GetSetMethod]			= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setZOrder);
	fMsgHandlerMap[kangle_GetSetMethod]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setRotateZ);
	fMsgHandlerMap[kscale_GetSetMethod]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setScale);
	fMsgHandlerMap[kshear_GetSetMethod]		= TSetMethodMsgHandler<IObject,TFloatSize>::create(this, &IObject::setShear);
	fMsgHandlerMap[krotatex_GetSetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setRotateX);
	fMsgHandlerMap[krotatey_GetSetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setRotateY);
	fMsgHandlerMap[krotatez_GetSetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setRotateZ);
	fMsgHandlerMap[kshow_GetSetMethod]		= TSetMethodMsgHandler<IObject,bool>::create(this, &IObject::setVisible);
	fMsgHandlerMap[keffect_GetSetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::effectMsg);
    
	fMsgHandlerMap[kdx_SetMethod]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addXPos);
	fMsgHandlerMap[kdy_SetMethod]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYPos);
	fMsgHandlerMap[kdxorigin_SetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addXOrigin);
	fMsgHandlerMap[kdyorigin_SetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYOrigin);
	fMsgHandlerMap[kdz_SetMethod]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addZOrder);
	fMsgHandlerMap[kdangle_SetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addAngle);
	fMsgHandlerMap[kdscale_SetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::multScale);

	fSigHandlerMap[kx_GetSetMethod]			= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setXPos);
	fSigHandlerMap[ky_GetSetMethod]			= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setYPos);
	fSigHandlerMap[kxorigin_GetSetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setXOrigin);
	fSigHandlerMap[kyorigin_GetSetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setYOrigin);
	fSigHandlerMap[kz_GetSetMethod]			= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setZOrder);
	fSigHandlerMap[kangle_GetSetMethod]		= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setRotateZ);
	fSigHandlerMap[kscale_GetSetMethod]		= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setScale);
	fSigHandlerMap[krotatex_GetSetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setRotateX);
	fSigHandlerMap[krotatey_GetSetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setRotateY);
	fSigHandlerMap[krotatez_GetSetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::setRotateZ);
    
	fSigHandlerMap[kdx_SetMethod]		= TSetMethodSigHandler<IObject,float>::create(this, &IObject::addXPos);
	fSigHandlerMap[kdy_SetMethod]		= TSetMethodSigHandler<IObject,float>::create(this, &IObject::addYPos);
	fSigHandlerMap[kdxorigin_SetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::addXOrigin);
	fSigHandlerMap[kdyorigin_SetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::addYOrigin);
	fSigHandlerMap[kdz_SetMethod]		= TSetMethodSigHandler<IObject,float>::create(this, &IObject::addZOrder);
	fSigHandlerMap[kdangle_SetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::addAngle);
	fSigHandlerMap[kdscale_SetMethod]	= TSetMethodSigHandler<IObject,float>::create(this, &IObject::multScale);
	fMsgHandlerMap[kdrotatex_SetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addXAngle);
	fMsgHandlerMap[kdrotatey_SetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYAngle);
	fMsgHandlerMap[kdrotatez_SetMethod]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addAngle);

}

//--------------------------------------------------------------------------
void IObject::shapeAble()
{
	fMsgHandlerMap[kpenColor_GetSetMethod]	= TMethodMsgHandler<IColor>::create(&fPenColor, &IColor::set);
	fMsgHandlerMap[kpenAlpha_GetSetMethod]	= IColor::SetColorMsgHandler::create(&fPenColor, &IColor::setA, &IColor::setA);
	fMsgHandlerMap[kpendAlpha_SetMethod]	= IColor::SetColorMsgHandler::create(&fPenColor, &IColor::dA, &IColor::dA);
	fMsgHandlerMap[kpenWidth_GetSetMethod]	= TSetMethodMsgHandler<IObject, float>::create(this, &IObject::setPenWidth);
	fMsgHandlerMap[kpenStyle_GetSetMethod]  = TSetMethodMsgHandler<IObject, string>::create(this, &IObject::setPenStyle);
    fMsgHandlerMap[kbrushStyle_GetSetMethod]  = TSetMethodMsgHandler<IObject, string>::create(this, &IObject::setBrushStyle);
	
	fGetMsgHandlerMap[kpenWidth_GetSetMethod]	= TGetParamMsgHandler<float>::create(fPenWidth);
	fGetMsgHandlerMap[kpenColor_GetSetMethod]	= TGetParamMsgHandler<IColor>::create(fPenColor);
	fAltGetMsgHandlerMap[kpenAlpha_GetSetMethod]	= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(&fPenColor, &IColor::getA);
	fGetMsgHandlerMap[kpenStyle_GetSetMethod]	= TGetParamMsgHandler<std::string>::create(fPenStyle);
	fGetMsgHandlerMap[kbrushStyle_GetSetMethod]	= TGetParamMsgHandler<std::string>::create(fBrushStyle);

    fSigHandlerMap[kpenAlpha_GetSetMethod]	= IColor::SetColorSigHandler::create(&fPenColor, &IColor::setA, &IColor::setA);
	fSigHandlerMap[kpendAlpha_SetMethod]	= IColor::SetColorSigHandler::create(&fPenColor, &IColor::dA, &IColor::dA);
	fSigHandlerMap[kpenWidth_GetSetMethod]	= TSetMethodSigHandler<IObject, float>::create(this, &IObject::setPenWidth);
}

//--------------------------------------------------------------------------
void IObject::setMouseEventSensibility(bool mouseSensible)
{
	if(fView)
		fView->setMouseEventSensibility(mouseSensible);
}

//--------------------------------------------------------------------------
void IObject::setdyMsgHandler ()
{ 
	fMsgHandlerMap[kdy_SetMethod] = TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYPos);
}

//--------------------------------------------------------------------------
void IObject::setSyncDY (float dy)
{
	vector<SMaster> mlist = getParent()->getMasters(this);
	for (size_t i = 0; i < mlist.size(); i++) {
		mlist[i]->setDy(dy);
	}
}

//--------------------------------------------------------------------------
void IObject::setdyMsgHandler (Master* m)
{ 
	fMsgHandlerMap[kdy_SetMethod] = TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setSyncDY);
//	fMsgHandlerMap[kdy_SetMethod] = TSetMethodMsgHandler<Master,void (Master::*)(float)>::create(this, m, &Master::setDy); 
}

//--------------------------------------------------------------------------
void IObject::timeAble()
{
	fGetMsgHandlerMap[kdate_GetSetMethod]		= TGetParamMsgHandler<rational>::create(fDate);
	fGetMsgHandlerMap[kduration_GetSetMethod]	= TGetParamMsgHandler<rational>::create(fDuration);
	fGetMsgHandlerMap[kdate_GetSetMethod]		= TGetParamMsgHandler<rational>::create(fDate);
	fGetMsgHandlerMap[ktempo_GetSetMethod]		= TGetParamMsgHandler<int>::create(fTempo);

	fMsgHandlerMap[kdate_GetSetMethod]		= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::setDate);
	fMsgHandlerMap[kduration_GetSetMethod]	= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::setDuration);
	fMsgHandlerMap[ktempo_GetSetMethod]		= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::setTempo);
	fMsgHandlerMap[kddate_SetMethod]		= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::addDate);
	fMsgHandlerMap[kdduration_SetMethod]	= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::addDuration);
	fMsgHandlerMap[kdtempo_SetMethod]		= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::addTempo);
	
	fMsgHandlerMap[kclock_SetMethod]		= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::clock);
	fMsgHandlerMap[kdurClock_SetMethod]	= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::durclock);

	fSigHandlerMap[kdate_GetSetMethod]		= TSetMethodSigHandler<IObject,rational>::create(this, &IObject::setDate);
	fSigHandlerMap[kduration_GetSetMethod]	= TSetMethodSigHandler<IObject,rational>::create(this, &IObject::setDuration);
	fSigHandlerMap[kddate_SetMethod]		= TSetMethodSigHandler<IObject,rational>::create(this, &IObject::addDate);
	fSigHandlerMap[kdduration_SetMethod]	= TSetMethodSigHandler<IObject,rational>::create(this, &IObject::addDuration);
}

//--------------------------------------------------------------------------
void IObject::delsubnodes()
{
	for (unsigned int i=0; i < elements().size(); i++) {
		elements()[i]->del();
		elements()[i]->setModified();
	}
}

//--------------------------------------------------------------------------
IObject::~IObject() 
{
	// removes all the child objects refs to me
	for (int i=0; i < size(); i++)
    {
		elements()[i]->fParent = fParent;
    }
	delete fView;
}

void IObject::del()		{ _del(true); }
void IObject::_del(bool delsigcnx)
{
	if(fLock){
		ITLErr<<"Impossible to delete "<<getOSCAddress()<<", the object is locked."<<ITLEndl;
		return;
	}
    // we set the delte flag to 1
    fDelete = true;
	IAppl::delAliases (getOSCAddress());

	// cleanup signal connections
	if (delsigcnx)
		getParent()->signalsNode()->cleanupTarget(name());
}

//--------------------------------------------------------------------------
void IObject::newData (bool state) {
	fNewData = state;
	triggerEvent(kNewDataEvent, true);
}

//--------------------------------------------------------------------------
void IObject::createVirtualNodes()
{
    fDebug = IObjectDebug::create(this);
    add ( fDebug );
    fSync = ISceneSync::create(this);
    fSignals = ISignalNode::create(this);
	fSignals->createVirtualNodes();
	add ( fSignals );
    add(fSync);
	
}

//--------------------------------------------------------------------------
SISignalNode IObject::signalsNode () const			{ return fSignals; }

//--------------------------------------------------------------------------
void IObject::propagateSignalsState ()
{
	SigModified visitor;
	for (unsigned int i = 0; i < elements().size(); i++) {
		elements()[i]->accept(&visitor);
	}
}

//--------------------------------------------------------------------------
SMaster IObject::getMaster(SIObject o) const					{ return fSync ? fSync->getMaster(o) : 0; }
vector<SMaster>  IObject::getMasters(SIObject o, const string& master, const string& map) const
																{ return fSync->getMasters(o, master, map); }
vector<SMaster>  IObject::getMasters(SIObject o) const			{ return fSync ? fSync->getMasters(o) : vector<SMaster>(); }
vector<SIObject> IObject::getSlaves(const SIObject o) const		{ return fSync ? fSync->getSlaves(o) : vector<SIObject>(); }
void IObject::cleanupSync ()										{ if (fSync) fSync->cleanup(); }

//--------------------------------------------------------------------------
IObject::subnodes IObject::sort ()
{
	// topological sort of the scene elements
	if (fSync)
        return fSync->sort(elements());
    else
        return elements();
}

//--------------------------------------------------------------------------
IObject::subnodes IObject::invertedSort ()
{
	// topological sort of the scene elements
	if (fSync)
        return fSync->invertedSort(elements());
    else
        return elements();
}

//--------------------------------------------------------------------------
string IObject::getOSCAddress() const
{
	return fParent ? fParent->getOSCAddress() + '/' + name() : '/' + name(); 
}

//--------------------------------------------------------------------------
void IObject::ptask ()
{ 
	if (fSync) fSync->ptask();
	if (signalsNode() && signalsNode()->getState()) propagateSignalsState();
    
	for (unsigned int i = 0; i < elements().size(); i++) {
        elements()[i]->ptask();
    }
}

//--------------------------------------------------------------------------
void IObject::accept (Updater* u)		{ u->updateTo(this); }

//--------------------------------------------------------------------------
SIScene			IObject::getScene()			{ return fParent ? fParent->getScene() : 0; }
const IScene*	IObject::getScene() const	{ return fParent ? fParent->getScene() : 0; }
//--------------------------------------------------------------------------
SIAppl			IObject::getAppl()			{ return fParent ? fParent->getAppl() : 0; }
const IAppl*	IObject::getAppl() const	{ return fParent ? fParent->getAppl() : 0; }

//--------------------------------------------------------------------------
const IObject * IObject::getRoot()	const	{ return fParent ? fParent->getRoot() : this; }
IObject * IObject::getRoot()				{ return fParent ? fParent->getRoot() : this; }

//--------------------------------------------------------------------------
void IObject::setState (state s)			{ fState |= s; }
void IObject::setModified ()				{ setState(kModified); propagateSubModified(); }

//--------------------------------------------------------------------------
void IObject::propagateSubModified ()	{
	if (fParent) {
		fParent->setState(kSubModified);
		fParent->propagateSubModified();
	}
};

//--------------------------------------------------------------------------
void IObject::cleanup ()
{
	IPosition::cleanup();
	IDate::cleanup();
	IColor::cleanup();
	fNewData = false;
	localMapModified (false);
	fExportFlag.clear();
 	if (getState() & kSubModified) {     // todo: could be optimised - to be checked
		subnodes::iterator i = elements().begin();
		while (i!=elements().end()) {
			if ((*i)->fDelete) {
				i = elements().erase(i);
			}
			else { 
				(*i)->cleanup();
				i++;
			}
		}
	}
	fState= kClean;
}

//--------------------------------------------------------------------------
bool IObject::match(const std::string& regexp) const
{
	OSCRegexp r (regexp.c_str());
	return r.match(name().c_str());
}

//--------------------------------------------------------------------------
bool IObject::accept(const std::string& addr, const IMessage *)
{
	return match(addr);
}

//--------------------------------------------------------------------------
const IObject* IObject::findnode(const string& node, const string& pathtail) const
{
	string next, nexttail;
	std::size_t pos = pathtail.find_first_of('/');
	if (pos != string::npos) {
		next		= pathtail.substr(0, pos);
		nexttail	= pathtail.substr(pos+1);
	}
	else {
		next		= pathtail;
		nexttail	= "";
	}

	if (node == ".")
		return findnode (next, nexttail);
	if (node == "..")
		return fParent ? fParent->findnode (next, nexttail) : 0;

	subnodes objs;
	if (exactfind (node, objs) && objs.size()) {
		const IObject* obj = objs[0];
		if (next.empty())
			return obj;

		return obj->findnode (next, nexttail);
	}
	return 0;
}

//--------------------------------------------------------------------------
const IObject* IObject::findnode(const string& objpath) const
{
	if (objpath[0] == '/') {				// absolute addresses are forwarded to the root node
		std::size_t pos = objpath.find_first_of('/', 1);
		if (pos != string::npos) {
			const IObject* root = getRoot();
			string next		= objpath.substr(1, pos-1);
			string nexttail	= objpath.substr(pos+1);
			if (next == root->name()) {
				return root->findnode(".", nexttail);
			}
		}
		return 0;
	}
	return findnode ("..", objpath);
}

//--------------------------------------------------------------------------
bool IObject::find(const std::string& expr, subnodes& outlist) const
{
	if (!Tools::regexp(expr)) {
		return exactfind(expr, outlist);
	}
	else {
		size_t size = outlist.size();

		size_t n = elements().size();
		for (size_t i = 0; i < n; i++) {
			IObject * elt = elements()[i];
			if (elt->match(expr) && !elt->getDeleted())
				outlist.push_back(elt);
		}
		return outlist.size() > size;
	}
}

//--------------------------------------------------------------------------
bool IObject::exactfind(const std::string& name, subnodes& outlist) const
{
	size_t n = elements().size();
	bool ret = false;
	for (size_t i = 0; i < n; i++) {
		IObject * elt = elements()[i];
		if ((!elt->getDeleted()) && (elt->name() == name)) {
			outlist.push_back(elt);
			ret = true;
		}
	}
	return ret;
}

//--------------------------------------------------------------------------
int IObject::execute (const IMessage* msg)
{
	SMsgHandler handler = messageHandler(msg->message());
	if ( handler ) {
		int ret = (*handler)(msg);
		if (ret == MsgHandler::msgStatus::kProcessed) {
			// check if there is any associated event
			const string method = msg->message();
			MouseLocation pos (getXPos(), getYPos(), 0, 0, 0, 0);	// object position and
			EventContext env (pos, 0, this);				// date are available from the environment
			checkEvent(method.c_str(), env);
		}
		return ret;
	}

#ifndef WIN32
	#warning qui utilise le match true dans IObject::execute ?
#endif
	// no basic handler , try to find if there is a match
	handler = messageHandler(msg->message(), true);
	if ( handler ) {
cout << "IObject::execute regexp match for " << msg->message() << endl;
		return (*handler)(msg);
	}

	// try to find a default handler
	handler = messageHandler("*");
	if ( handler ) return (*handler)(msg);
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
int IObject::executeSignal (const std::string method, const std::pair<float,float> range, const ParallelSignal* sig)
{
	SSigHandler handler = signalHandler(method);
	if ( handler ) return (*handler)(sig, range);

	// no basic handler , try to find if there is a match
	handler = signalHandler(method, true);
	if ( handler ) return (*handler)(sig, range);

	// try to find a default handler
	handler = signalHandler("*");
	if ( handler ) return (*handler)(sig, range);
	return SigHandler::kBadParameters;
}

//--------------------------------------------------------------------------
int IObject::executeSignal (const std::string method, const std::pair<int,int> range, const ParallelSignal* sig)
{
	SSigHandler handler = signalHandler(method);
	if ( handler ) return (*handler)(sig, range);

	// no basic handler , try to find if there is a match
	handler = signalHandler(method, true);
	if ( handler ) return (*handler)(sig, range);

	// try to find a default handler
	handler = signalHandler("*");
	if ( handler ) return (*handler)(sig, range);
	return SigHandler::kBadParameters;
}

//--------------------------------------------------------------------------
int IObject::mapDebug() const			{ return fDebug->getMapDebug(); }
bool IObject::nameDebug() const			{ return fDebug->getNameDebug(); }
//bool IObject::signalDebug() const		{ return fDebug->getSignalDebug(); }
bool IObject::clickDebug() const		{ return fDebug->getClickDebug(); }

//--------------------------------------------------------------------------
void IObject::getObjects(const string& address, vector<const IObject*>& outv) const
{
	string beg  = OSCAddress::addressFirst(address);
	string tail = OSCAddress::addressTail(address);
	if (match(beg)) {				// first make sure that the object is part of the address
		if (tail.size()) {
			size_t n = elements().size();
			for (size_t i = 0; i < n; i++)
				elements()[i]->getObjects(tail, outv);
		}
		else if (!getDeleted()) outv.push_back(this);
	}
}
 
//--------------------------------------------------------------------------
// frame sync mode support
// gives the location corresponding to a date
// this location is expressed as a ratio on x and y axis starting from top left
//--------------------------------------------------------------------------
bool IObject::date2FramePoint(const libmapping::rational& date, TFloatPoint& p) const
{
	const libmapping::rational dur = getDuration();
	if ((date < 0.) || (date > dur))	return false;

	float w	= getWidth();
	float h = getHeight();
	float objlen	= (w + h) * 2;
	float datelen	= objlen * float(date) / float(dur);
	
	// start from top left corner, clockwise
	if (datelen <= w) {			// location is on the top segment
		p.fX = datelen / w;
		p.fY = 0;
		return true;			// done
	}
	datelen -= w;
	if (datelen <= h) {			// location is on the right segment
		p.fX = 1;
		p.fY = datelen / h;
		return true;			// done
	}
	datelen -= h;
	if (datelen <= w) {			// location is on the bottom segment
		p.fX = 1- (datelen / w);
		p.fY = 1;
		return true;			// done
	}
	datelen -= w;				// location is on the left segment
	p.fX = 0;
	p.fY = 1 - (datelen / h);
	return true;
}

//--------------------------------------------------------------------------
// events processing
//--------------------------------------------------------------------------
bool IObject::checkEvent (EventsAble::eventype event, EventContext& context) const
{
	const IMessageList*	msgs = getMessages(event);
	if (msgs) {
		TMessageEvaluator me;
		SIMessageList outmsgs = me.eval (msgs, context);
		if (outmsgs && outmsgs->list().size()) outmsgs->send(true);
		return true;
	}
	return false;
}

bool IObject::checkEvent (EventsAble::eventype event, const IMessage::argslist& args) const
{
	const IMessageList*	msgs = getMessages(event);
	if (msgs) {
		EventContext env(getDate(), this);
		TMessageEvaluator me;
		SIMessageList outmsgs = me.eval (msgs, env, args);
		if (outmsgs && outmsgs->list().size()) outmsgs->send(true);
		return true;
	}
	return false;
}

bool IObject::checkEvent (EventsAble::eventype event, libmapping::rational date, const IObject* obj) const
{
	EventContext env(date, obj);
	return checkEvent( event, env);
}

//--------------------------------------------------------------------------
// messages processing
//--------------------------------------------------------------------------
int IObject::processMsg (const string& address, const string& addressTail, const IMessage* msg)
{
	int result = MsgHandler::kBadAddress;
	if (accept(address, msg)) {				// first make sure that the object is part of the address
		string beg  = OSCAddress::addressFirst(addressTail);	// next takes the next destination object
		string tail = OSCAddress::addressTail(addressTail);		// and possible remaining address part
		
		if (tail.size()) {			// we're not processing the end of the address, process the address one step down
			size_t n = elements().size();
			for (size_t i = 0; i < n; i++) {
				result |= elements()[i]->processMsg (beg, tail, msg);
			}
		}
		else {										// addressTail indicates a terminal node
			IMessageTranslator translator;
			SIMessage translated = translator.translate(msg);
			subnodes targets;
			if (find (beg, targets)) {				// looks for subnodes matching addressTail
				size_t n = targets.size();
				for (size_t i = 0; i< n; i++) {
					IObject * target = targets[i];
					result |= target->execute(translated ? translated : msg);	// asks the subnode to execute the message
					if (result & MsgHandler::kProcessed) {
						target->setModified();									// sets the modified state of the subnode
					}
				}
			}
			// can't find the target node but name is a regular expression: ignore 
			else if (Tools::regexp(beg)) result = MsgHandler::kProcessedNoChange;
			// can't find the target node: try to create it
			else result = IProxy::execute (translated ? translated : msg, beg, this);
		}
	}
    return result;
}

//--------------------------------------------------------------------------
// signals processing
//--------------------------------------------------------------------------
int IObject::processSig ()
{
	int result = 0;
    for(int i = 0; i<size(); i++)
    {
		 if (elements()[i]->getDeleted()) continue;
		// looks for the object elements()[i] in all the signal connections
        std::vector<ISignalConnection*> connections;
        if(fSignals) connections = fSignals->getConnectionsOf(elements()[i]->name());
        if(!connections.empty())
        {
            // if found, we call the method executeSignal to link the attribute and the signal.
			for(unsigned int it = 0; it < connections.size(); it++)
            {
                int status = 0;
                if(connections[it]->getRangeType() == "float")
                    status = elements()[i]->executeSignal(connections[it]->getMethod(), connections[it]->getFloatRange(), connections[it]->getSignal());
                else if(connections[it]->getRangeType() == "int")
                    status = elements()[i]->executeSignal(connections[it]->getMethod(), connections[it]->getIntRange(), connections[it]->getSignal());
                else
                    status = elements()[i]->executeSignal(connections[it]->getMethod(), std::pair<float, float>(-1.f,1.f), connections[it]->getSignal());
                result |= status;
            }
        }
        elements()[i]->processSig();
    }
    return result;
}


//--------------------------------------------------------------------------
// the 'get' to retrieve an object parameters
SIMessageList IObject::getParams(const std::vector<std::string>& attributes) const
{
	SIMessageList outMsgs = IMessageList::create();
	
	for (unsigned int i=0; i<attributes.size(); i++) {
		map<std::string, SGetParamMsgHandler>::const_iterator e = fGetMsgHandlerMap.find(attributes[i]);
		if (e != fGetMsgHandlerMap.end()) {							// attribute found in msg map
			SIMessage msg = getParam(e->first, e->second);
			outMsgs->list().push_back (msg);
		}
		else {			// attribute not found: look in alternate get message handlers map
			map<std::string, SGetParamMsgHandler>::const_iterator e = fAltGetMsgHandlerMap.find(attributes[i]);
			if (e != fAltGetMsgHandlerMap.end()) {					// attribute found in msg map
				SIMessage msg = getParam(e->first, e->second);
				outMsgs->list().push_back (msg);
			}
			else {		// attribute not found: look in MultiMsgHandlerMap
				map<std::string, SGetParamMultiMsgHandler>::const_iterator e = fGetMultiMsgHandlerMap.find(attributes[i]);
				if (e != fGetMultiMsgHandlerMap.end()) {			// attribute found in msg map
					SIMessageList mlist = IMessageList::create();
					outMsgs->list().push_back(e->second->print(mlist)->list());
				}
			}
		}
	}
	return outMsgs;
}


//--------------------------------------------------------------------------
// the 'get' to retrieve an object parameters
SIMessageList IObject::getParams() const
{
	SIMessageList outMsgs = IMessageList::create();
	
	map<std::string, SGetParamMsgHandler>::const_iterator i = fGetMsgHandlerMap.begin();
	while (i != fGetMsgHandlerMap.end()) {
		const string& what = i->first;
		const SGetParamMsgHandler& handler = what.size() ? i->second : 0;
		if (handler && fMsgHandlerMap.find(what) != fMsgHandlerMap.end())  {
			SIMessage msg = getParam(i->first, i->second);
			outMsgs->list().push_back (msg);
		}
		i++;
	}

	map<std::string, SGetParamMultiMsgHandler>::const_iterator j = fGetMultiMsgHandlerMap.begin();
	while (j != fGetMultiMsgHandlerMap.end()) {
		const string& what = j->first;
		const SGetParamMultiMsgHandler& handler = what.size() ? j->second : 0;
		if (handler && (fMsgHandlerMap.find(what) != fMsgHandlerMap.end() || what == kstack_GetMethod))  {
			SIMessageList mlist = IMessageList::create();
			outMsgs->list().push_back(handler->print(mlist)->list());
		}
		j++;
	}
	return outMsgs;
}

//--------------------------------------------------------------------------
// the 'get' to retrieve the specified objects parameters
SIMessageList IObject::getAllParams(const std::vector<std::string>& attributes) const
{
	SIMessageList outMsgs = getParams(attributes);
	// and distribute the message to subnodes
	for (unsigned int i = 0; i < elements().size(); i++) {
		nodePtr elt = elements()[i];
		if (!elt->getDeleted())
			outMsgs->list().push_back (elt->getAllParams(attributes)->list());
	}
	return outMsgs;
}

//--------------------------------------------------------------------------
// the 'get' to retrieve all the objects parameters
SIMessageList IObject::getAllParams() const
{
	SIMessageList outMsgs = getParams();
	// and distribute the message to subnodes
	for (unsigned int i = 0; i < elements().size(); i++) {
		nodePtr elt = elements()[i];
		if (!elt->getDeleted())
			outMsgs->list().push_back (elt->getAllParams()->list());
	}
	return outMsgs;
}

//--------------------------------------------------------------------------
// the 'get' to retrieve all objects full state
// note that getSetMsg() and getAllParams() are both recursive
// this design is intended to retrieve all the objects first
// in order to avoid dependencies with the messages order
SIMessageList IObject::getAttributes(const vector<string>& attributes) const
{
	SIMessageList outMsgs = IMessageList::create();
	outMsgs->list().push_back (getAllParams(attributes)->list());		// next get the objects parameters
	return outMsgs;
}


//--------------------------------------------------------------------------
// the 'get' to retrieve an object full state
SIMessageList IObject::nonRecursiveGetAll () const
{
	SIMessageList outMsgs = IMessageList::create();
	SIMessageList setMsgs = getSetMsg();
	outMsgs->list().push_back(setMsgs->list()[0]);		// getSetMsg is recursive: push only the first msg
	outMsgs->list().push_back(getParams()->list());
	return outMsgs;
}

//--------------------------------------------------------------------------
// the 'get' to retrieve all objects full state
// note that getSetMsg() and getAllParams() are both recursive
// this design is intended to retrieve all the objects first
// in order to avoid dependencies with the messages order
SIMessageList IObject::getAll() const
{
	SIMessageList outMsgs = IMessageList::create();
	outMsgs->list().push_back (getSetMsg()->list());		// first get all objects state
	outMsgs->list().push_back (getAllParams()->list());		// next get the objects parameters
	return outMsgs;
}

//--------------------------------------------------------------------------
// the 'get' form without parameter
SIMessageList IObject::getSetMsg() const
{
	SIMessageList outMsgs = IMessageList::create();
	string address = getOSCAddress();
	
	// check first if there is an existing message handler
	SGetParamMsgHandler handler = getMessageHandler("");
	if (handler) {
		SIMessage msg = IMessage::create(address, kset_SetMethod);
		*msg << getTypeString();
		handler->print(msg);
		outMsgs->list().push_back (msg);
	}

	// always distributes the message to subnodes (new with version 1.03)
    address += "/";
    for (unsigned int i = 0; i < elements().size(); i++) {
        nodePtr elt = elements()[i];
        if (!elt->getDeleted() && elt->name() != "sync") {
            SIMessage msg = IMessage::create(address + elt->name(), kget_SetMethod);
            outMsgs->list().push_back (elt->getMsgs(msg)->list());
        }
    }
	return outMsgs;
}

//--------------------------------------------------------------------------
SIMessage IObject::getParam(const string& what, const SGetParamMsgHandler& h) const
{
	SIMessage msg = IMessage::create(getOSCAddress(), what);
	h->print(msg);
	return msg;
}

//--------------------------------------------------------------------------
SIMessageList IObject::getMsgs(const IMessage* msg) const
{ 
	SIMessageList outMsgs = IMessageList::create();

	if (msg->size() == 0) {
		outMsgs = getSetMsg();
	}
	else for (int i=0; i<msg->size(); i++) {
		string what;
		if (msg->param(i, what)) {
			SGetParamMsgHandler handler = getMessageHandler(what);
			SGetParamMultiMsgHandler multihandler = getMultiMessageHandler(what);
			if (handler) {
				SIMessage outmsg = getParam(what, handler);
				if (outmsg) outMsgs->list().push_back(outmsg);
				else break;
			}
			else if (multihandler) {
				SIMessageList mlist = IMessageList::create();
				outMsgs->list().push_back( multihandler->print(mlist)->list() );
			}
			else if (what == "*")
				outMsgs = getAll();
		}
		else break;
	}
	return outMsgs;
}


//--------------------------------------------------------------------------
int IObject::size (bool recursive) const
{
	int n = int(fSubNodes.size());
	int subn = 0;
	if (recursive) {
		for (int i=0; i<n; i++)
			subn += fSubNodes[i]->size(recursive);
	}
	return n + subn;
}


//--------------------------------------------------------------------------
SIMessageList IObject::getMaps() const		{ return __getMaps(); }
SIMessageList IObject::__getMaps() const	{ return IMessageList::create(); }

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::get(const IMessage* msg) const
{ 
	SIMessageList msgs = getMsgs (msg);
	if (msgs->list().size()) {
		try {
			oscout << msgs;
			IAppl* appl = (IAppl*) getAppl();
			if (appl) {
				IApplLog* log = appl->getLogWindow();
				if (log && log->acceptMsgs()) {
					msgs->list().set ("", "\n");
					stringstream sstr;
					sstr <<  msgs->list();			// and print it to the string stream
					log->print (sstr.str().c_str());
				}
			}
		}
		catch (exception& e) {
			ITLErr << "while sending osc msg: " << e.what() << ITLEndl;
		}
	}
	return MsgHandler::kProcessedNoChange;
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
struct msgMatchPredicat {
	const char* msg;
			 msgMatchPredicat(const string& s) : msg(s.c_str()) {}
	bool operator() (const pair<string, SMsgHandler>& elt) const { 
		if (elt.first.empty() ||(elt.first == "*") ) return false;
		CRegexpT<char> regexp(elt.first.c_str(), EXTENDED);
		return regexp.MatchExact(msg);
	}
};

struct sigMatchPredicat {
	const char* method;
			 sigMatchPredicat(const string& s) : method(s.c_str()) {}
	bool operator() (const pair<string, SSigHandler>& elt) const {
		if (elt.first.empty() ||(elt.first == "*") ) return false;
		CRegexpT<char> regexp(elt.first.c_str(), EXTENDED);
		return regexp.MatchExact(method);
	}
};

//--------------------------------------------------------------------------
SMsgHandler IObject::messageHandler(const string& msg, bool match) const
{
	SMsgHandler handler;
	if (!match) {
		map<string, SMsgHandler>::const_iterator h = fMsgHandlerMap.find(msg);
		if (h != fMsgHandlerMap.end()) handler = h->second;
//		else handler = setMessageHandler (msg);
	}
	else {
		msgMatchPredicat p(msg);
		map<string, SMsgHandler>::const_iterator h = find_if(fMsgHandlerMap.begin(), fMsgHandlerMap.end(), p);
		if (h != fMsgHandlerMap.end()) handler = h->second;
	}
	return handler;
}

//--------------------------------------------------------------------------
SSigHandler IObject::signalHandler(const string& method, bool match) const
{
	SSigHandler handler;
	if (!match) {
		map<string, SSigHandler>::const_iterator h = fSigHandlerMap.find(method);
		if (h != fSigHandlerMap.end()) handler = h->second;
	}
	else {
		sigMatchPredicat p(method);
		map<string, SSigHandler>::const_iterator h = find_if(fSigHandlerMap.begin(), fSigHandlerMap.end(), p);
		if (h != fSigHandlerMap.end()) handler = h->second;
	}
	return handler;
}

//--------------------------------------------------------------------------
SGetParamMsgHandler IObject::getMessageHandler(const std::string& param) const
{
	map<string, SGetParamMsgHandler>::const_iterator h = fGetMsgHandlerMap.find(param);
	if ( h == fGetMsgHandlerMap.end()) {
		h = fAltGetMsgHandlerMap.find(param);
		return h == fAltGetMsgHandlerMap.end() ? 0 : h->second;
	}
	else return h->second;
}

//--------------------------------------------------------------------------
SGetParamMultiMsgHandler IObject::getMultiMessageHandler(const std::string& param) const
{
	map<string, SGetParamMultiMsgHandler>::const_iterator h = fGetMultiMsgHandlerMap.find(param);
	return h == fGetMultiMsgHandlerMap.end() ? 0 : h->second;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::pushMsg(const IMessage* msg)
{
	if (msg->size()) return MsgHandler::kBadParameters;
	EventsAble::pushWatch();
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::popMsg(const IMessage* msg)
{
	if (msg->size()) return MsgHandler::kBadParameters;
	EventsAble::popWatch();
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
void IObject::transferAttributes(SIObject dest)
{
    //transfer of the attributes of the current object to another object
    dest->setXPos (getXPos());
    dest->setYPos (getYPos());
    dest->setXOrigin (getXOrigin());
    dest->setYOrigin (getYOrigin());
    dest->setScale (getScale());
    dest->setVisible (getVisible());
    dest->setZOrder (getZOrder());
    dest->setShear (getShear());

    dest->setRotateX (getRotateX());
    dest->setRotateY (getRotateY());
    dest->setRotateZ (getRotateZ());

    dest->setR(getR());
    dest->setG(getG());
    dest->setB(getB());
    dest->setA(getA());

    dest->setPenWidth(getPenWidth());
    dest->setPenColor(getPenColor());
    dest->setPenStyle(getPenStyle());
	
    dest->setDate (getDate());
    dest->setDuration (getDuration());

    *((EventsAble*)dest) = *((EventsAble*)this);
    
    // transfer of the sync informations
	for(unsigned int i = 0; i < fParent->elements().size(); i++)
    {
        ISceneSync * sync = dynamic_cast<ISceneSync*>((IObject*)(fParent->elements()[i]));
        if(sync) // we found the syncnode, to get the informations about the synchronizations
        {
            SIMessageList list = sync->getAll();
			for(unsigned int j = 0; j < list->list().size(); j++)
            {
                INScore::MessagePtr msg = list->list()[j];
                std::string slave, master;
                if(list->list()[j]->size() != 2)
                    continue;
                if(!list->list()[j]->param(0, slave) || !list->list()[j]->param(1,master))
                    continue;
                if(slave == name())
                    INScore::postMessage (sync->getOSCAddress().c_str(), msg);
                else if(master == name())
                    INScore::delayMessage(sync->getOSCAddress().c_str(), msg);
            }
        }
    }
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::set(const IMessage* msg)	
{
	string type;
	if (!msg->param(0, type)) return MsgHandler::kBadParameters;
	if (type != getTypeString()) {
		// types don't match
		// try to re-create the object with the new type
		IObject* newobj;
		int status = IProxy::execute (msg, name(), fParent, &newobj, this);
		if (status & MsgHandler::kProcessed) {
            SIObject obj = newobj;
            newobj = obj;
			del();								// and delete the object
			fParent->cleanupSync();
			return MsgHandler::kProcessed;		// message has been handled at IObject level
		}
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::effectMsg(const IMessage* msg)
{ 
	GraphicEffect effect;
	MsgHandler::msgStatus status = effect.set (msg);
	if (status == MsgHandler::kProcessed) {
		VObjectView* view = getView();
		if (view) view->setEffect (effect);
	}
	return status;
}

#if 0
//--------------------------------------------------------------------------
static void showpoint (int i, float x, float y)
{
	stringstream address("/ITL/scene/p");
	address << "/ITL/scene/p" << i;
	
	INScore::MessagePtr msg = INScore::newMessage ("set");
	INScore::add (msg, "ellipse");
	INScore::add (msg, 0.03f);
	INScore::add (msg, 0.03f);
	INScore::postMessage (address.str().c_str(), msg);

	msg = INScore::newMessage ("x");
	INScore::add (msg, x);
	INScore::postMessage (address.str().c_str(), msg);
	
	msg = INScore::newMessage ("y");
	INScore::add (msg, y);
	INScore::postMessage (address.str().c_str(), msg);
	
	msg = INScore::newMessage ("color");
	INScore::add (msg, 250);
	INScore::add (msg, 100);
	INScore::add (msg, 100);
	INScore::add (msg, 150);
	INScore::postMessage (address.str().c_str(), msg);
	
}

//--------------------------------------------------------------------------
static void showframe (const vector<float>& p)
{
	for (size_t i=0; i < p.size(); i+=2) {
		showpoint (i, p[i], p[i+1]);
	}
}
#endif

//--------------------------------------------------------------------------
// gives the object frame under the form of 4 points (top-left, top-right, bottom-right, bottom-left)
vector<float> IObject::getFrame ()	const
{ 
	vector<float> frame;
	getView()->getFrame(this, frame);
//	showframe (frame);
	return frame;
}

//--------------------------------------------------------------------------
GraphicEffect IObject::getEffect ()	const
{ 
	return getView() ? getView()->getEffect() : GraphicEffect(); 
}

//--------------------------------------------------------------------------
SIMessageList IObject::getWatch() const
{
	return EventsAble::getWatch (getOSCAddress().c_str());
}

//--------------------------------------------------------------------------
SIMessageList IObject::getStack() const
{
	return EventsAble::getStack (getOSCAddress().c_str());
}

//--------------------------------------------------------------------------
SIMessageList IObject::getAliases() const
{
	SIMessageList list = IMessageList::create();
	vector<pair<string, string> > aliases;
	IAppl::getAliases (getOSCAddress(), aliases);
	size_t n = aliases.size();
	for (size_t i = 0; i < n; i++) {
		SIMessage msg = IMessage::create (getOSCAddress(), kalias_GetSetMethod);
		msg->add (aliases[i].first);
		if (aliases[i].second.size()) msg->add (aliases[i].second);
		list->list().push_back (msg);
	}
	if (list->list().empty()) {
		list->list().push_back (IMessage::create (getOSCAddress(), kalias_GetSetMethod));
	}
	return list;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::aliasMsg(const IMessage* msg)
{ 
	unsigned int n = msg->size();
	if (n == 0) {
		IAppl::delAliases (getOSCAddress());
		return MsgHandler::kProcessed;
	}
	
	else if ( n <= 2 ) {
		string alias, msgstr;
		if (( n == 2 ) && !msg->param(1, msgstr)) return MsgHandler::kBadParameters;
		if (msg->param(0, alias)) {
			IAppl::addAlias (alias, getOSCAddress(), msgstr);
			return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::renameMsg(const IMessage* msg)
{ 
	if (msg->size() == 1) {
		string newname;
		if (msg->param(0, newname)) {
			setName (newname);
			return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::genericExport(const IMessage* msg, bool drawChildren)
{
	if (msg->size() == 0) {	//No argument : export to "objectName".
			addExportFlag( getScene()->absolutePath(name()), drawChildren);
			return MsgHandler::kProcessed;
	} else {
		for (int i = 0; i < msg->size(); i++) {
			std::string fileName;
			if (!msg->param(i, fileName)) return MsgHandler::kBadParameters;
			if (fileName.length()) {
				SIScene scene = getScene();
				std::string absolutePath = scene ? scene->absolutePath(fileName) : IAppl::absolutePath(fileName);
				if ( isDirectory(absolutePath) )	//Argument is a directory: export to "directory/objectName".
				{
#ifdef WIN32
					const char* sep = "\\";
#else
					const char* sep = "/";
#endif
					const char* tmp = ( absolutePath[ absolutePath.length() - 1 ] != *sep ) ? sep : "";
					addExportFlag( absolutePath + tmp + name(), drawChildren);
				}
				else								//Argument is a file: export to this file.
					addExportFlag( absolutePath, drawChildren);
			}
		}
        return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::exportMsg(const IMessage* msg)
{
	return genericExport(msg, false);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::exportAllMsg(const IMessage* msg)
{
	return genericExport(msg, true);
}

//--------------------------------------------------------------------------
// user events must be in capital letters or numbers
bool IObject::checkUserEvent(EventsAble::eventype t) const
{
	const char * ptr = t;
	if (!*ptr)
		return false;

	int c = *ptr++;
	if (!isupper(c) && !isdigit(c))
		return false;
	while (*ptr) {
		c = *ptr++;
		if ( !isupper(c) && !isdigit(c) )
			return false;
	}
	return true;
}

//--------------------------------------------------------------------------
bool IObject::acceptSimpleEvent(EventsAble::eventype t) const
{
	if (EventsAble::isMouseEvent(t)) return true;
	if (string(t) == kNewDataEvent)	 return true;

	// look if there is a handler for the message
	SMsgHandler h  = messageHandler(t, true);
	if (h) return EventsAble::hash(t);
	
	// check if the event is candidate for a user defined event
	// user defined event must be all in capital letters
	if (!checkUserEvent(t)) return false;
	return EventsAble::hash(t);		// user defined event is accepted
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::_watchMsg(const IMessage* msg, bool add)
{ 
	if (!msg->size()) {					// no param to watch message
		EventsAble::reset();			// clear every watched events
		return MsgHandler::kProcessed;	// and exit
	}

	string what;
	if (!msg->param (0, what))				// can't decode event to watch when not a string
		return MsgHandler::kBadParameters;	// exit with bad parameter
		
	const char* event = what.c_str();
	if (acceptSimpleEvent (event)) {
		if (msg->size() > 1) {
			SIMessageList watchMsg = msg->watchMsg2Msgs (1);
			if (!watchMsg) return MsgHandler::kBadParameters;

			if (add)
				eventsHandler()->addMsg (event, watchMsg);
			else
				eventsHandler()->setMsg (event, watchMsg);
		}
		else if (!add) eventsHandler()->setMsg (event, 0);
	}
	else if (EventsAble::isTimeEvent(event)) {
		// time events messages can have the following forms :
		// a) watch timevent					=> the messages related to timevent are cleared
		// b) watch timevent timeInterval		=> all the messages related to timevent and timeInterval are cleared
		// c) watch timevent timeInterval msg	=> sets the associated messages related to timevent and timeInterval
		// note also that timeInterval can be expressed as
		//		- 4 integer values (actually 2 rationals)
		//		- 2 integer values (i.e. 2 rationals with an implicit 1 denominator)
		//		- 2 float values 
		//		- 2 strings in the form 'n/d'
		// thus the number of expected parameters are:
		// a) 1 param: the time event
		// b) 3 or 5 params depending on how the time interval is expressed
		// b) >3 or >5 params depending on how the time interval is expressed
		{
			if (msg->size() == 1) {
				if (!add) {
					clearList(event);
					eventsHandler()->clearTimeMsg(event);
				}
				else return MsgHandler::kBadParameters;
			}

			RationalInterval time(0, 0);
			int msgindex;
			if(msg->size() >= 5) {
				time = Tools::readRationalInterval(msg, true, 1);
				msgindex = 5;
			} else if(msg->size() >= 3) {
				time = Tools::readRationalInterval(msg, false, 1);
				msgindex = 3;
			}
			if(time.first().getDenominator() == 0 || time.second().getDenominator() == 0 ) {
				return MsgHandler::kBadParameters;
			}

			if (msg->size() > msgindex) {
				SIMessageList watchMsg = msg->watchMsg2Msgs (msgindex);
				if (!watchMsg) return MsgHandler::kBadParameters;
				if (!add) eventsHandler()->setTimeMsg (event, time, watchMsg);
				else eventsHandler()->addTimeMsg (event, time, watchMsg);
				watchInterval(event, time);
			}
			else if (!add) {
				delInterval (event, time);
				eventsHandler()->setTimeMsg (event, time, 0);
			}
		}
	}
	else return MsgHandler::kBadParameters;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::lockMsg(const IMessage *msg)
{
	if (!msg->size()) return MsgHandler::kBadParameters;
	int lock;
	if(!msg->param(0,lock))
		return MsgHandler::kBadParameters;

	fLock = lock;
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::evalMsg(const IMessage* msg)
{ 
	int n =msg->size();
	if (!n) return MsgHandler::kBadParameters;

	SIMessageList watchMsg = msg->watchMsg2Msgs (0);
	if (watchMsg) {
		size_t n = watchMsg->list().size();
		if (!n) return MsgHandler::kBadParameters;


		for (unsigned int i=0; i < n; i++) {
			SIMessage msg = watchMsg->list()[i];
			string address;
			if (msg->relativeAddress())
				address = msg->relative2absoluteAddress (getOSCAddress());
			else
				address = msg->address();
			string beg  = OSCAddress::addressFirst(address);
			string tail = OSCAddress::addressTail(address);
			int ret = getRoot()->processMsg(beg, tail, msg);
			IGlue::trace(msg, ret);
		}
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
void IObject::save(ostream& out, const vector<string>& attributes) const
{
	SIMessageList msgs = attributes.size() ? getAttributes(attributes) : getAll();
	msgs->list().set("", "\n");
	if (msgs->list().size())
		out <<  msgs->list();
	else cout << "IObject::save : empty msg list" << endl;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::saveMsg (const IMessage* msg) const
{ 
	int n = msg->size();
	if (n > 0) {
		vector<string> attributes;
		string destfile;
		ios_base::openmode mode = ios_base::out;
		for (int i=n-1; i>=0; i--) {
			string str;
			if (! msg->param(i, str))	return MsgHandler::kBadParameters;	// error: incorrect parameter type
			if (str == "+")
				mode |= ios_base::app;
			else if (destfile.empty()) destfile = str;
			else attributes.push_back(str);
		}
		if (destfile.empty())			return MsgHandler::kBadParameters;	// error: no destination file
		string path = getScene() ? getScene()->absolutePath(destfile) : IAppl::absolutePath(destfile);
		ofstream out (path.c_str(), mode);
		save (out, attributes);
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::eventMsg (const IMessage* msg)
{
	int n = msg->size();
	if (n >= 1) {
		string event;
		if (!msg->param(0, event)) return MsgHandler::kBadParameters;
		
		if (EventsAble::isMouseEvent(event.c_str())) {		// this is a mouse related event
			if (n == 3) {									// x and  y parameters are expected
				int x, y;
				if (msg->param(1, x) && msg->param(2, y)) {
					VObjectView	* view = getView();
					if (view)
						view->handleEvent (this, x, y, event.c_str());
					return MsgHandler::kProcessed;
				}
			}
		}
		else if (checkUserEvent (event.c_str())) {			// this is a use defined event
			IMessage::argslist args;						// supports arbitrary args count
			for (int i=1; i<n; i++) args.push_back(msg->param(i));
			if (checkEvent(event.c_str(), args))
				return MsgHandler::kProcessed;
		}
		else if (n == 1) {									// this is a simple event
			if (checkEvent(event.c_str(), getDate(), this))
				return MsgHandler::kProcessed;
		}
	}
	return MsgHandler::kBadParameters;

//	if (n == 3) {			// this is a mouse related event
//		string event; int x, y;
//		if (msg->param(0, event) && msg->param(1, x) && msg->param(2, y)) {
//			VObjectView	* view = getView();
//			if (view) {
//				view->handleEvent (this, x, y, event.c_str());
//			}
//			return MsgHandler::kProcessed;
//		}
//	}
//	else if (n == 1) {			// this is a simple event
//		string event;
//		if (msg->param(0, event)) {
//			if (checkEvent(event.c_str(), getDate(), this))
//				return MsgHandler::kProcessed;
//		}
//	}
//	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::editMsg (const IMessage* msg)
{
	if (getEditString().empty()) {		// check first if there is a previous edition, in case yes, preserves the content
		size_t n = msg->size();
		if (n) {							// check if there is a set of attributes to be edited from the msg
			vector<string> attributes;
			for (size_t i=0; i<n; i++) {	// in case yes, retrieve these attributes
				string str;
				if (!msg->param(i, str))
					return MsgHandler::kBadParameters;
				attributes.push_back(str);
			}
			stringstream sstr;
			save(sstr, attributes);			// and ask the object to save them to a string stream
			setEditString(sstr.str());		// finally fill the edit string (will appear in the dialog box)
		}
		else {								// otherwise get all the attributes (including the set msg)
			SIMessageList msgs = nonRecursiveGetAll();
			msgs->list().set("", "\n");
			stringstream sstr;
			sstr <<  msgs->list();			// and print it to the string stream
			setEditString(sstr.str());		// finally fill the edit string (will appear in the dialog box)
		}
	}
	fEdit = true;						// a flag to trigger the edit dialog from the view
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
// OSCStream support
//--------------------------------------------------------------------------
SIMessage& operator << (SIMessage& out, const SGetParamMsgHandler& h)
{
	return h->print(out);
}
//--------------------------------------------------------------------------
IMessage& operator << (IMessage& out, const IObject::subnodes& l)
{
	for (IObject::subnodes::const_iterator i = l.begin(); i != l.end(); i++) {
		if (!(*i)->getDeleted())
			out << (*i)->name();
	}
	return out;
}

//--------------------------------------------------------------------------
// debugging facilities
//--------------------------------------------------------------------------
void IObject::print (ostream& out) const
{
	out << "'" << getTypeString() << "'" << " name: \"" << name() << "\"";
	if (getDeleted()) out << " [deleted]";
	out << endl;
	IPosition::print(out);
	IColor::print(out);
	IShape::print(out);
	IDate::print(out);
	out << " - display range [" << getDispStart() << "," << getDispEnd() << "]" << endl;
	out << "  elements count: " << size() << endl;
	out << fDebug << endl;
}

//--------------------------------------------------------------------------
ostream& operator << (ostream& out, const SIObject& o)
{
	o->print(out);
	return out;
}

}
