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

#include <algorithm>
#include <iostream>
#include <fstream>

#include "EventsAble.h"
#include "IAppl.h"
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

#include "VObjectView.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>


#define useiterator 0

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
					fDelete (false), fState(kNewObject), fNewData(true), fView(0), fParent(parent)
{
	fTypeString = "obj";

	fMsgHandlerMap[kalias_GetSetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::aliasMsg);
	fMsgHandlerMap[kset_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::set);
	fMsgHandlerMap[kget_SetMethod]		= TMethodMsgHandler<IObject, MsgHandler::msgStatus (IObject::*)(const IMessage*) const >::create(this, &IObject::get);
	fMsgHandlerMap[kdel_SetMethod]		= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::del);
	fMsgHandlerMap[kexport_SetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::exportMsg);
//	fMsgHandlerMap["rename"]			= TMethodMsgHandler<IObject>::create(this, &IObject::renameMsg);
	fMsgHandlerMap[ksave_SetMethod]		= TMethodMsgHandler<IObject, MsgHandler::msgStatus (IObject::*)(const IMessage*) const>::create(this, &IObject::saveMsg);
	fMsgHandlerMap[kwatch_GetSetMethod]	= TMethodMsgHandler<IObject>::create(this, &IObject::watchMsg);
	fMsgHandlerMap[kwatchplus_SetMethod]= TMethodMsgHandler<IObject>::create(this, &IObject::watchMsgAdd);
	fMsgHandlerMap[kpush_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::pushMsg);
	fMsgHandlerMap[kpop_SetMethod]		= TMethodMsgHandler<IObject>::create(this, &IObject::popMsg);

	fGetMultiMsgHandlerMap[kwatch_GetSetMethod]	= TGetParamMultiMethodHandler<IObject, SIMessageList (IObject::*)() const>::create(this, &IObject::getWatch);
	fGetMultiMsgHandlerMap[kmap_GetSetMethod]	= TGetParamMultiMethodHandler<IObject, SIMessageList (IObject::*)() const>::create(this, &IObject::getMaps);
	fGetMultiMsgHandlerMap[kalias_GetSetMethod]	= TGetParamMultiMethodHandler<IObject, SIMessageList (IObject::*)() const>::create(this, &IObject::getAliases);
}


//--------------------------------------------------------------------------
void IObject::setHandlers()
{
	colorAble();
	positionAble();
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

	fGetMsgHandlerMap[kcolor_GetSetMethod]		= TGetParamMsgHandler<IColor>::create(*(IColor*)this);
	fGetMsgHandlerMap[kred_GetSetMethod]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getR);
	fGetMsgHandlerMap[kgreen_GetSetMethod]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getG);
	fGetMsgHandlerMap[kblue_GetSetMethod]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getB);
	fGetMsgHandlerMap[kalpha_GetSetMethod]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getA);
	fGetMsgHandlerMap[khue_GetSetMethod]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getH);
	fGetMsgHandlerMap[ksaturation_GetSetMethod] = TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getS);
	fGetMsgHandlerMap[kbrightness_GetSetMethod]	= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getV);
}

//--------------------------------------------------------------------------
void IObject::positionAble()
{
	fGetMsgHandlerMap[kx_GetSetMethod]		= TGetParamMsgHandler<float>::create(fXPos);
	fGetMsgHandlerMap[ky_GetSetMethod]		= TGetParamMsgHandler<float>::create(fYPos);
	fGetMsgHandlerMap[kxorigin_GetSetMethod]= TGetParamMsgHandler<float>::create(fXOrigin);
	fGetMsgHandlerMap[kyorigin_GetSetMethod]= TGetParamMsgHandler<float>::create(fYOrigin);
	fGetMsgHandlerMap[kz_GetSetMethod]		= TGetParamMsgHandler<float>::create(fZOrder);
	fGetMsgHandlerMap[kangle_GetSetMethod]	= TGetParamMsgHandler<float>::create(fZAngle);
	fGetMsgHandlerMap[kscale_GetSetMethod]	= TGetParamMsgHandler<float>::create(fScale);
	fGetMsgHandlerMap[kshow_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fVisible);
	fGetMsgHandlerMap[kwidth_GetSetMethod]	= TGetParamMsgHandler<float>::create(fWidth);
	fGetMsgHandlerMap[kheight_GetSetMethod] = TGetParamMsgHandler<float>::create(fHeight);
	fGetMsgHandlerMap[kshear_GetSetMethod]	= TGetParamMsgHandler<TFloatSize>::create(fShear);
	fGetMsgHandlerMap[krotatex_GetSetMethod]= TGetParamMsgHandler<float>::create(fXAngle);
	fGetMsgHandlerMap[krotatey_GetSetMethod]= TGetParamMsgHandler<float>::create(fYAngle);
	fGetMsgHandlerMap[krotatez_GetSetMethod]= TGetParamMsgHandler<float>::create(fZAngle);
	fGetMsgHandlerMap[keffect_GetSetMethod]	= TGetParamMethodHandler<IObject, GraphicEffect (IObject::*)() const>::create(this, &IObject::getEffect);

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
}

//--------------------------------------------------------------------------
void IObject::setdyMsgHandler ()
{ 
	fMsgHandlerMap[kdy_SetMethod] = TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYPos);
}

//--------------------------------------------------------------------------
void IObject::setdyMsgHandler (Master* m)
{ 
	fMsgHandlerMap[kdy_SetMethod] = TSetMethodMsgHandler<Master,void (Master::*)(float)>::create(this, m, &Master::setDy); 
}

//--------------------------------------------------------------------------
void IObject::timeAble()
{
	fGetMsgHandlerMap[kdate_GetSetMethod]		= TGetParamMsgHandler<rational>::create(fDate);
	fGetMsgHandlerMap[kduration_GetSetMethod]	= TGetParamMsgHandler<rational>::create(fDuration);

	fMsgHandlerMap[kdate_GetSetMethod]		= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::setDate);
	fMsgHandlerMap[kduration_GetSetMethod]	= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::setDuration);
	fMsgHandlerMap[kddate_SetMethod]		= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::addDate);
	fMsgHandlerMap[kdduration_SetMethod]	= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::addDuration);

	fMsgHandlerMap[kclock_SetMethod]		= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::clock);
	fMsgHandlerMap[kdurClock_SetMethod]	= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::durclock);
}

//--------------------------------------------------------------------------
void IObject::delsubnodes()
{
	setState(kSubModified);
#if useiterator
	for (subnodes::iterator i = elements().begin(); i != elements().end(); i++) {
		(*i)->del();
		(*i)->setState(kModified);
	}
#else
	for (unsigned int i=0; i < elements().size(); i++) {
		elements()[i]->del();
		elements()[i]->setState(kModified);
	}
#endif
}

//--------------------------------------------------------------------------
IObject::~IObject() 
{
	// removes all the child objects refs to me
	for (int i=0; i < size(); i++)
		elements()[i]->fParent = 0;
	delete fView;
}

//--------------------------------------------------------------------------
void IObject::createVirtualNodes()
{
	fSync = ISceneSync::create(this);
	fDebug = IObjectDebug::create(this);
    add(fSync);
    add ( fDebug );
}

//--------------------------------------------------------------------------
SMaster IObject::getMaster(SIObject o) const
{ 
	return fSync ? fSync->getMaster(o) : 0;
}

//--------------------------------------------------------------------------
void IObject::cleanupSync ()		{ if (fSync) fSync->cleanup(); }

//void IObject::sort ()
//{
	// topological sort of the scene elements
//	if (fSync) fSync->sort(elements());
//}

//--------------------------------------------------------------------------
string IObject::getOSCAddress() const
{
	return fParent ? fParent->getOSCAddress() + '/' + name() : '/' + name(); 
}

//--------------------------------------------------------------------------
void IObject::accept (Updater* u)		{ u->updateTo(this); }

//--------------------------------------------------------------------------
SIScene	IObject::getScene()					{ return fParent ? fParent->getScene() : 0; }
const IScene*	IObject::getScene() const	{ return fParent ? fParent->getScene() : 0; }

//--------------------------------------------------------------------------
const IObject * IObject::getRoot()	const	{ return fParent ? fParent->getRoot() : this; }
IObject * IObject::getRoot()				{ return fParent ? fParent->getRoot() : this; }

//--------------------------------------------------------------------------
void IObject::cleanup ()
{
	IPosition::cleanup();
	IDate::cleanup();
	IColor::cleanup();
	fNewData = false;
	localMapModified (false);
	fExportFlag = "";
	fState= kClean;
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

//--------------------------------------------------------------------------
bool IObject::match(const std::string& regexp) const
{
	OSCRegexp r (regexp.c_str());
	return r.match(name().c_str());
}

//--------------------------------------------------------------------------
bool IObject::find(const std::string& expr, subnodes& outlist) const
{
	if (!Tools::regexp(expr)) {
		return exactfind(expr, outlist);
	}
	else {
		unsigned int size = outlist.size();

	#if useiterator
		subnodes::const_iterator i = elements().begin();
		while (i!=elements().end()) {
			if ((*i)->match(expr) && !(*i)->getDeleted())
				outlist.push_back(*i);
			i++;
		}
	#else
		unsigned int n = elements().size();
		for (unsigned int i = 0; i < n; i++) {
			IObject * elt = elements()[i];
			if (elt->match(expr) && !elt->getDeleted())
				outlist.push_back(elt);
		}
	#endif
		return outlist.size() > size;
	}
}

//--------------------------------------------------------------------------
bool IObject::exactfind(const std::string& name, subnodes& outlist) const
{
	unsigned int n = elements().size();
	bool ret = false;
	for (unsigned int i = 0; i < n; i++) {
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
	if ( handler ) return (*handler)(msg);

	// no basic handler , try to find if there is a match
	handler = messageHandler(msg->message(), true);
	if ( handler ) return (*handler)(msg);

	// try to find a default handler
	handler = messageHandler("*");
	if ( handler ) return (*handler)(msg);
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
bool IObject::mapDebug() const			{ return fDebug->getMapDebug(); }
bool IObject::nameDebug() const			{ return fDebug->getNameDebug(); }
bool IObject::signalDebug() const		{ return fDebug->getSignalDebug(); }
bool IObject::clickDebug() const		{ return fDebug->getClickDebug(); }

//--------------------------------------------------------------------------
void IObject::getObjects(const string& address, vector<const IObject*>& outv) const
{
	string beg  = OSCAddress::addressFirst(address);
	string tail = OSCAddress::addressTail(address);
	if (match(beg)) {				// first make sure that the object is part of the address
		if (tail.size()) {
			unsigned int n = elements().size();
			for (unsigned int i = 0; i < n; i++)
				elements()[i]->getObjects(tail, outv);
		}
		else outv.push_back(this);
	}
}


//--------------------------------------------------------------------------
// messages processing
//--------------------------------------------------------------------------
int IObject::processMsg (const string& address, const string& addressTail, const IMessage* msg)
{
//	bool result = false;
	int result = MsgHandler::kBadAddress;
	if (match(address)) {				// first make sure that the object is part of the address
		string beg  = OSCAddress::addressFirst(addressTail);	// next takes the next destination object
		string tail = OSCAddress::addressTail(addressTail);		// and possible remaining address part
		
		if (tail.size()) {			// we're not processing the end of the address, process the address one step down
			unsigned int n = elements().size();
			for (unsigned int i = 0; i < n; i++) {
				result |= elements()[i]->processMsg (beg, tail, msg);
			}
		}
		else {										// addressTail indicates a terminal node
			IMessageTranslator translator;
			SIMessage translated = translator.translate(msg);
			subnodes targets;		
			if (find (beg, targets)) {				// looks for subnodes matching addressTail
				unsigned int n = targets.size();
				for (unsigned int i = 0; i< n; i++) {
					IObject * target = targets[i];
					result |= target->execute(translated ? translated : msg);	// asks the subnode to execute the message
					if (result & MsgHandler::kProcessed) {
						target->setState(IObject::kModified);		// sets the modified state of the subnode
					}
				}
			}
			// can't find the target node: try to create it
			else result = IProxy::execute (translated ? translated : msg, beg, this);
		}
	}
	if (result & MsgHandler::kProcessed) 
		setState(IObject::kSubModified);
	return result;
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
		if (handler)  {
			SIMessage msg = getParam(i->first, i->second);
			outMsgs->list().push_back (msg);
		}
		i++;
	}

	map<std::string, SGetParamMultiMsgHandler>::const_iterator j = fGetMultiMsgHandlerMap.begin();
	while (j != fGetMultiMsgHandlerMap.end()) {
		const string& what = j->first;
		const SGetParamMultiMsgHandler& handler = what.size() ? j->second : 0;
		if (handler)  {
			SIMessageList mlist = IMessageList::create();
			outMsgs->list().push_back(handler->print(mlist)->list());
		}
		j++;
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
        if (!elt->getDeleted()) {
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
SIMessageList IObject::getMaps() const		{ return __getMaps(); }
SIMessageList IObject::__getMaps() const	{ return IMessageList::create(); }

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::get(const IMessage* msg) const
{ 
	SIMessageList msgs = getMsgs (msg);
	if (msgs->list().size()) {
		oscout << msgs;
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
		bool ret = regexp.Match(msg);
		return ret;
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
SGetParamMsgHandler IObject::getMessageHandler(const std::string& param) const
{
	map<string, SGetParamMsgHandler>::const_iterator h = fGetMsgHandlerMap.find(param);
	return h == fGetMsgHandlerMap.end() ? 0 : h->second;
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
	return EventsAble::popWatch() ? MsgHandler::kProcessed : MsgHandler::kBadParameters;
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
		int status = IProxy::execute (msg, name(), fParent, &newobj);
		if (status & MsgHandler::kProcessed) {
			newobj->setXPos (getXPos());
			newobj->setYPos (getYPos());
			newobj->setXOrigin (getXOrigin());
			newobj->setYOrigin (getYOrigin());
			newobj->setScale (getScale());
			newobj->setVisible (getVisible());
			newobj->setZOrder (getZOrder());
			newobj->setShear (getShear());
			newobj->setRotateX (getRotateX());
			newobj->setRotateY (getRotateY());
			newobj->setRotateZ (getRotateZ());
			
			newobj->setDate (getDate());
			newobj->setDuration (getDuration());

			*((EventsAble*)newobj) = *((EventsAble*)this);
			del();								// and delete the object
			return MsgHandler::kProcessed;		// message has been handled at IObject level
		}
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
SIMessageList IObject::getAliases() const
{
	SIMessageList list = IMessageList::create();
	vector<pair<string, string> > aliases;
	IAppl::getAliases (getOSCAddress(), aliases);
	unsigned int n = aliases.size();
	for (unsigned i = 0; i < n; i++) {
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
	if (n == 0)
		IAppl::delAliases (getOSCAddress());
	
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
MsgHandler::msgStatus IObject::exportMsg(const IMessage* msg)
{
	if (msg->size() == 1) {
		std::string fileName;
		if (!msg->param(0, fileName)) return MsgHandler::kBadParameters;
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
				setExportFlag( absolutePath + tmp + name() );
			}
			else								//Argument is a file: export to this file.
				setExportFlag( absolutePath );
			return MsgHandler::kProcessed;
		}
	}
	else if (msg->size() == 0) {	//No argument : export to "objectName".
		setExportFlag( getScene()->absolutePath(name() ) );
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
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
		
	EventsAble::eventype t = EventsAble::string2type (what);
	switch (t) {
		case EventsAble::kMouseMove:
		case EventsAble::kMouseDown:
		case EventsAble::kMouseUp:
		case EventsAble::kMouseDoubleClick:
		case EventsAble::kMouseEnter:
		case EventsAble::kMouseLeave:
		case EventsAble::kExport:
			if (msg->size() > 1) {
				SIMessageList watchMsg = msg->watchMsg2Msgs (1);
				if (!watchMsg) return MsgHandler::kBadParameters;

				if (add) eventsHandler()->addMsg (t, watchMsg);
				else eventsHandler()->setMsg (t, watchMsg);
			}
			else if (!add) eventsHandler()->setMsg (t, 0);
			break;

		case EventsAble::kTimeEnter:
		case EventsAble::kTimeLeave:
		case EventsAble::kDurEnter:
		case EventsAble::kDurLeave:
			if (msg->size() >= 3) {
				int msgindex = 3;
				rational start, end;
				if (!msg->param(1,start) || !msg->param(3, end)) {			// try to read rational values
					int istart, iend;
					float fstart, fend;
					if (msg->param(1,istart) && msg->param(2, iend)) {		// try to read int values (with implicit denominator = 1)
						start = rational (istart, 1);
						end = rational (iend, 1);
					}
					else if (msg->param(1,fstart) && msg->param(2, fend)) { // try to read float values
						start = rational (fstart);
						end = rational (fend);
					}
					else return MsgHandler::kBadParameters;
				}
				else msgindex = 5;

				RationalInterval time(start,end);
				if (msg->size() > msgindex) {
					SIMessageList watchMsg = msg->watchMsg2Msgs (msgindex);
					if (!watchMsg) return MsgHandler::kBadParameters;
					if (!add) eventsHandler()->setTimeMsg (t, time, watchMsg);
					else eventsHandler()->addTimeMsg (t, time, watchMsg);
					watchInterval(t, time);
				}
				else if (!add) {
					delInterval (t, time);
					eventsHandler()->setTimeMsg (t, time, 0);
				}
			}
			else if (msg->size() == 1) {
				if (!add) {
					clearList(t);
					eventsHandler()->clearTimeMsg(t);
				}
			}
			else return MsgHandler::kBadParameters;
			break;

		default:			// unknown event to watch
			return MsgHandler::kBadParameters;
	}
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
void IObject::save(ostream& out) const
{
	SIMessageList msgs = getAll();
	msgs->list().set("", "\n");
	out <<  msgs->list();
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::saveMsg (const IMessage* msg) const
{ 
	if ((msg->size() > 0) && (msg->size() < 3)) {
		string destfile = msg->param(0)->value<string>("");
		if (destfile.size()) {
			ios_base::openmode mode = ios_base::out;
			if (msg->size() == 2) {
				string mstr = msg->param(1)->value<string>("");
				if (mstr == "+")
					mode |= ios_base::app;
				else return MsgHandler::kBadParameters;
			}
			string path = getScene() ? getScene()->absolutePath(destfile) : IAppl::absolutePath(destfile);
			ofstream out (path.c_str(), mode);
			save (out);
			return MsgHandler::kProcessedNoChange;
		}
	}
	return MsgHandler::kBadParameters;
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
