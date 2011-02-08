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
#include "EventMessage.h"
#include "IAppl.h"
#include "IMessage.h"
#include "IMessageTranslator.h"
#include "IObject.h"
#include "IObjectVNodes.h"
#include "IProxy.h"
#include "IScene.h"
#include "IVNode.h"
#include "GraphicEffect.h"
#include "OSCAddress.h"
#include "OSCRegexp.h"
#include "Updater.h"
#include "ISync.h"
#include "Tools.h"

#include "VGraphicsItemView.h"

#include <stdio.h>
#include <sys/types.h>
#include <dirent.h>
#include <math.h>


#define useiterator 0

using namespace std;

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
	s << val.x() << val.y();
	return s;
}


//--------------------------------------------------------------------------
// IObject implementation
//--------------------------------------------------------------------------
IObject::IObject(const std::string& name, IObject* parent) : IDate(this),
					fName(name), fDispStart(0), fDispEnd(1),
					fDelete (false), fState(kNewObject), fNewData(true), fParent(parent)
{
	fTypeString = "obj";

	fMsgHandlerMap["set"]		= TMethodMsgHandler<IObject>::create(this, &IObject::set);
	fMsgHandlerMap["get"]		= TMethodMsgHandler<IObject, MsgHandler::msgStatus (IObject::*)(const IMessage*) const >::create(this, &IObject::get);
	fMsgHandlerMap["del"]		= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::del);
	fMsgHandlerMap["effect"]	= TMethodMsgHandler<IObject>::create(this, &IObject::effectMsg);
	fMsgHandlerMap["export"]	= TMethodMsgHandler<IObject>::create(this, &IObject::exportMsg);
	fMsgHandlerMap["click"]		= TMethodMsgHandler<IObject,MsgHandler::msgStatus (IObject::*)(const IMessage*) const>::create(this, &IObject::clickMsg);
	fMsgHandlerMap["select"]	= TMethodMsgHandler<IObject, MsgHandler::msgStatus (IObject::*)(const IMessage*) const>::create(this, &IObject::selectMsg);
	fMsgHandlerMap["save"]		= TMethodMsgHandler<IObject, MsgHandler::msgStatus (IObject::*)(const IMessage*) const>::create(this, &IObject::saveMsg);
	fMsgHandlerMap["watch"]		= TMethodMsgHandler<IObject>::create(this, &IObject::watchMsg);
	fMsgHandlerMap["watch+"]	= TMethodMsgHandler<IObject>::create(this, &IObject::watchMsgAdd);
	
	colorAble();
	positionAble();
	timeAble();

	fGetMsgHandlerMap["effect"]	= TGetParamMethodHandler<IObject, GraphicEffect (IObject::*)() const>::create(this, &IObject::getEffect);
	fGetMsgHandlerMap["watch"]	= TGetParamMethodHandler<IObject, IMessageList (IObject::*)() const>::create(this, &IObject::getWatch);
}

//--------------------------------------------------------------------------
void IObject::colorAble()
{
	fMsgHandlerMap["color"]		= TMethodMsgHandler<IColor>::create(this, &IColor::set);
	fMsgHandlerMap["hsb"]		= TMethodMsgHandler<IColor>::create(this, &IColor::setHSV);

	fMsgHandlerMap["red"]		= TSetMethodMsgHandler<IObject, int>::create(this,&IObject::setR);
	fMsgHandlerMap["green"]		= TSetMethodMsgHandler<IObject, int>::create(this,&IObject::setG);
	fMsgHandlerMap["blue"]		= TSetMethodMsgHandler<IObject, int>::create(this,&IObject::setB);
	fMsgHandlerMap["alpha"]		= TSetMethodMsgHandler<IObject, int>::create(this,&IObject::setA);
	fMsgHandlerMap["hue"]		= TSetMethodMsgHandler<IObject, int>::create(this,&IObject::setH);
	fMsgHandlerMap["saturation"]= TSetMethodMsgHandler<IObject, int>::create(this,&IObject::setS);
	fMsgHandlerMap["brightness"]= TSetMethodMsgHandler<IObject, int>::create(this,&IObject::setV);

	fMsgHandlerMap["dcolor"]	= TMethodMsgHandler<IObject>::create(this, &IObject::dcolorMsg);
	fMsgHandlerMap["dhsb"]		= TMethodMsgHandler<IObject>::create(this, &IObject::dhsvMsg);

	fMsgHandlerMap["dred"]			= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::dR);
	fMsgHandlerMap["dgreen"]		= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::dG);
	fMsgHandlerMap["dblue"]			= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::dB);
	fMsgHandlerMap["dalpha"]		= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::dA);
	fMsgHandlerMap["dhue"]			= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::dH);
	fMsgHandlerMap["dsaturation"]	= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::dS);
	fMsgHandlerMap["dbrightness"]	= TSetMethodMsgHandler<IObject,int>::create(this, &IObject::dV);

	fGetMsgHandlerMap["color"]		= TGetParamMsgHandler<IColor>::create(*(IColor*)this);
	fGetMsgHandlerMap["red"]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getR);
	fGetMsgHandlerMap["green"]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getG);
	fGetMsgHandlerMap["blue"]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getB);
	fGetMsgHandlerMap["alpha"]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getA);
	fGetMsgHandlerMap["hue"]		= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getH);
	fGetMsgHandlerMap["saturation"] = TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getS);
	fGetMsgHandlerMap["brightness"]	= TGetParamMethodHandler<IColor, int (IColor::*)() const>::create(this, &IColor::getV);
}

//--------------------------------------------------------------------------
void IObject::positionAble()
{
	fGetMsgHandlerMap["x"]		= TGetParamMsgHandler<float>::create(fXPos);
	fGetMsgHandlerMap["y"]		= TGetParamMsgHandler<float>::create(fYPos);
	fGetMsgHandlerMap["xorigin"]= TGetParamMsgHandler<float>::create(fXOrigin);
	fGetMsgHandlerMap["yorigin"]= TGetParamMsgHandler<float>::create(fYOrigin);
	fGetMsgHandlerMap["z"]		= TGetParamMsgHandler<float>::create(fZOrder);
	fGetMsgHandlerMap["angle"]	= TGetParamMsgHandler<float>::create(fAngle);
	fGetMsgHandlerMap["scale"]	= TGetParamMsgHandler<float>::create(fScale);
	fGetMsgHandlerMap["show"]	= TGetParamMsgHandler<bool>::create(fVisible);
	fGetMsgHandlerMap["width"]	= TGetParamMsgHandler<float>::create(fWidth);
	fGetMsgHandlerMap["height"] = TGetParamMsgHandler<float>::create(fHeight);

	fMsgHandlerMap["x"]			= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setXPos);
	fMsgHandlerMap["y"]			= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setYPos);
	fMsgHandlerMap["xorigin"]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setXOrigin);
	fMsgHandlerMap["yorigin"]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setYOrigin);
	fMsgHandlerMap["z"]			= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setZOrder);
	fMsgHandlerMap["angle"]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setAngle);
	fMsgHandlerMap["scale"]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::setScale);
	fMsgHandlerMap["show"]		= TSetMethodMsgHandler<IObject,bool>::create(this, &IObject::setVisible);

	fMsgHandlerMap["dx"]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addXPos);
	fMsgHandlerMap["dy"]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYPos);
	fMsgHandlerMap["dxorigin"]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addXOrigin);
	fMsgHandlerMap["dyorigin"]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYOrigin);
	fMsgHandlerMap["dz"]		= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addZOrder);
	fMsgHandlerMap["dangle"]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addAngle);
	fMsgHandlerMap["dscale"]	= TSetMethodMsgHandler<IObject,float>::create(this, &IObject::multScale);
}

//--------------------------------------------------------------------------
void IObject::setdyMsgHandler ()
{ 
	fMsgHandlerMap["dy"] = TSetMethodMsgHandler<IObject,float>::create(this, &IObject::addYPos); 
}

//--------------------------------------------------------------------------
void IObject::setdyMsgHandler (Master* m)
{ 
	fMsgHandlerMap["dy"] = TSetMethodMsgHandler<Master,void (Master::*)(float)>::create(this, m, &Master::setDy); 
}

//--------------------------------------------------------------------------
void IObject::timeAble()
{
	fGetMsgHandlerMap["date"]		= TGetParamMsgHandler<rational>::create(fDate);
	fGetMsgHandlerMap["duration"]	= TGetParamMsgHandler<rational>::create(fDuration);

	fMsgHandlerMap["date"]		= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::setDate);
	fMsgHandlerMap["duration"]	= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::setDuration);
	fMsgHandlerMap["ddate"]		= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::addDate);
	fMsgHandlerMap["dduration"]	= TSetMethodMsgHandler<IObject,rational>::create(this, &IObject::addDuration);

	fMsgHandlerMap["clock"]		= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::clock);
	fMsgHandlerMap["durClock"]	= TMethodMsgHandler<IObject, void (IObject::*)(void)>::create(this, &IObject::durclock);
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
#if useiterator
	for (subnodes::iterator i = elements().begin(); i != elements().end(); i++) {
		(*i)->fParent = 0;
	}
#else
	for (int i=0; i < size(); i++)
		elements()[i]->fParent = 0;
#endif
}

//--------------------------------------------------------------------------
void IObject::createVirtualNodes()
{
	fDebug = IObjectDebug::create(this);
	add ( fDebug );
}

//--------------------------------------------------------------------------
string IObject::getOSCAddress() const
{
	return fParent ? fParent->getOSCAddress() + '/' + name() : '/' + name(); 
}

//--------------------------------------------------------------------------
void IObject::accept (Updater* u)		{ u->updateTo(this); }

//--------------------------------------------------------------------------
SIScene	IObject::getScene()				{ return fParent ? fParent->getScene() : 0; }

//--------------------------------------------------------------------------
void IObject::cleanup ()
{
	IPosition::cleanup();
	IDate::cleanup();
	IColor::cleanup();
//	fModified = false;
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
		SIObject elt = exactfind(expr);
		if (elt) {
			outlist.push_back(elt);
			return true;
		}
		return false;
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
SIObject IObject::exactfind(const std::string& name) const
{
#if useiterator
	subnodes::const_iterator i = elements().begin();
	while (i!=elements().end()) {
		if ((!(*i)->getDeleted()) && ((*i)->name() == name))
			return *i;
		i++;
	}
#else
	unsigned int n = elements().size();
	for (unsigned int i = 0; i < n; i++) {
		IObject * elt = elements()[i];
		if ((!elt->getDeleted()) && (elt->name() == name))
			return elt;
	}
#endif
	return 0;
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
			IMessage* translated = translator.translate(msg);
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
			delete translated;
		}
	}
	if (result & MsgHandler::kProcessed) 
		setState(IObject::kSubModified);
	return result;
}

//--------------------------------------------------------------------------
// the 'get' to retrieve an object parameters
IMessageList IObject::getParams() const
{
	IMessageList outMsgs;
	map<string, SGetParamMsgHandler>::const_iterator i = fGetMsgHandlerMap.begin();
	while (i != fGetMsgHandlerMap.end()) {
		const string& what = i->first;
		if (what == "watch")
			outMsgs = getWatch();
		else {
			const SGetParamMsgHandler& handler = what.size() ? i->second : 0;
			if (handler) outMsgs += getParam(i->first, i->second);
		}
		i++;
	}
	return outMsgs;
}

//--------------------------------------------------------------------------
// the 'get' to retrieve all the objects parameters
IMessageList IObject::getAllParams() const
{
	IMessageList outMsgs = 	getParams();
	// and distribute the message to subnodes
#if useiterator
	for (subnodes::const_iterator i = elements().begin(); i != elements().end(); i++) {
		if (!(*i)->getDeleted())
			outMsgs += (*i)->getAllParams();
	}
#else
	for (unsigned int i = 0; i < elements().size(); i++) {
		nodePtr elt = elements()[i];
		if (!elt->getDeleted())
			outMsgs += elt->getAllParams();
	}
#endif
	return outMsgs;
}

//--------------------------------------------------------------------------
// the 'get' to retrieve all objects full state
// note that getSetMsg() and getAllParams() are both recursive
// this design is intended to retrieve all the objects first
// in order to avoid dependencies with the messages order
IMessageList IObject::getAll() const
{
	IMessageList outMsgs;
	outMsgs += getSetMsg();			// first get all objects state
	outMsgs += getAllParams();		// next get the objects parameters
	return outMsgs;
}

//--------------------------------------------------------------------------
// the 'get' form without parameter
IMessageList IObject::getSetMsg() const
{
	IMessageList outMsgs;
	string address = getOSCAddress();
	
	// check first if there is an existing message handler
	SGetParamMsgHandler handler = getMessageHandler("");
	if (handler) {
		IMessage* msg = new IMessage(address, "set");
		*msg << getTypeString();
		handler->print(*msg);	
		outMsgs += msg;
	}

	// else distributes the message to subnodes
	else {
		address += "/";
#if useiterator
		for (subnodes::const_iterator i = elements().begin(); i != elements().end(); i++) {
			nodePtr elt = *i;
			if (!elt->getDeleted()) {
				IMessage msg(address + elt->name(), "get");
				outMsgs += elt->getMsgs(&msg);
			}
		}
#else
		for (unsigned int i = 0; i < elements().size(); i++) {
			nodePtr elt = elements()[i];
			if (!elt->getDeleted()) {
				IMessage msg(address + elt->name(), "get");
				outMsgs += elt->getMsgs(&msg);
			}
		}
#endif
	}
	return outMsgs;
}

//--------------------------------------------------------------------------
IMessage* IObject::getParam(const string& what, const SGetParamMsgHandler& h) const
{
	IMessage* msg = new IMessage(getOSCAddress(), what);
	h->print(*msg); 
	return msg;
}

//--------------------------------------------------------------------------
IMessageList IObject::getMsgs(const IMessage* msg) const
{ 
	SGetParamMsgHandler handler;
	IMessageList outMsgs;
	string what;
	if (msg->params().size() == 0) {
		outMsgs = getSetMsg();
	}
	else for (unsigned int i=0; i<msg->params().size(); i++) {
		what = msg->params()[i]->value<string>("-");
		if (what.size()) {
			handler = getMessageHandler(what);
			if (handler) {
				if (what == "watch")
					outMsgs = getWatch();
				else {
					IMessage * msg = getParam(what, handler);
					if (msg) outMsgs += msg;
					else break;
				}
			}
			else if (what == "*")
				outMsgs = getAll();
		}
		else break;
	}
	return outMsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::get(const IMessage* msg) const
{ 
	IMessageList msgs = getMsgs (msg);
	if (msgs.size()) {
		oscout << msgs;
		msgs.clear();
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
		if (elt.first == "*") return false;
		OSCRegexp regexp (elt.first.c_str());	
		return regexp.match(msg);
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
//SMsgHandler IObject::setMessageHandler(const std::string& param) const
//{
//	map<string, SMsgHandler>::const_iterator h = fSetMsgHandlerMap.find(param);
//	return h == fSetMsgHandlerMap.end() ? 0 : h->second;
//}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::set(const IMessage* msg)	
{
	string type = msg->params()[0]->value<std::string>("");
//	if ((type != getTypeString()) && !virtualNode()) {
	if (type != getTypeString()) {
		// types don't match
		// try to re-create the object with the new type
		int status = IProxy::execute (msg, name(), fParent);
		if (status & MsgHandler::kProcessed) {
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
		VGraphicsItemView* view = graphicView();
		if (view) view->setEffect (effect);
	}
	return status;
}

//--------------------------------------------------------------------------
GraphicEffect IObject::getEffect ()	const
{ 
	return graphicView() ? graphicView()->getEffect() : GraphicEffect(); 
}

//--------------------------------------------------------------------------
IMessageList IObject::getWatch() const
{
	return EventsAble::getWatch (getOSCAddress().c_str());
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::exportMsg(const IMessage* msg)
{ 
	if (msg->params().size() == 1) {
		const std::string err = "";
		std::string fileName = msg->params()[0]->value<std::string>(err);
		if ( (fileName != err) && (fileName.length()) ) {
			std::string absolutePath = IAppl::absolutePath(fileName);
			if ( isDirectory(absolutePath) )	//Argument is a directory: export to "directory/objectName".
			{
#ifdef WIN32
				const char sep = '\\';
#else
				const char sep = '/';
#endif
				std::string addedSeparator = ( absolutePath[ absolutePath.length() - 1 ] != sep ) ? std::string(&sep) : "";
				setExportFlag( absolutePath + addedSeparator + name() );
			}
			else								//Argument is a file: export to this file.
				setExportFlag( absolutePath );
			return MsgHandler::kProcessed;
		}
	}
	else if (msg->params().size() == 0) {	//No argument : export to "objectName".
		setExportFlag( IAppl::absolutePath(name() ) );
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::_watchMsg(const IMessage* msg, bool add)
{ 
	if (msg->params().size()) {
		string what;
		if (msg->param (0, what)) {
			EventsAble::eventype t = EventsAble::string2type (what);
			switch (t) {
				case EventsAble::kMouseMove:
				case EventsAble::kMouseDown:
				case EventsAble::kMouseUp:
				case EventsAble::kMouseDoubleClick:
				case EventsAble::kMouseEnter:
				case EventsAble::kMouseLeave:
					if (msg->params().size() > 1)
						if (add) eventsHandler()->addMsg (t, EventMessage::create (name(), getScene()->name(), msg, 1));
						else eventsHandler()->setMsg (t, EventMessage::create (name(), getScene()->name(),msg, 1));
					else if (!add) eventsHandler()->setMsg (t, 0);
					break;
				case EventsAble::kFile:
					break;
				case EventsAble::kTimeEnter:
				case EventsAble::kTimeLeave:
					if (msg->params().size() >= 5) {
						rational start, end;
						if (!msg->param(1,start) || !msg->param(3, end))
							return MsgHandler::kBadParameters;
						RationalInterval time(start,end);
						if (msg->params().size() > 5) {
							if (!add) eventsHandler()->setTimeMsg (t, time, EventMessage::create (name(), getScene()->name(), msg, 5));
							else eventsHandler()->addTimeMsg (t, time, EventMessage::create (name(), getScene()->name(), msg, 5));
							watchTime(time);
						}
						else if (!add) {
							delTime (time);
							eventsHandler()->setTimeMsg (t, time, 0);
						}
					}
					else if (msg->params().size() == 1) {
						if (!add) {
							clearTime();
							eventsHandler()->clearTimeMsg(t);
						}
					}
					else return MsgHandler::kBadParameters;
					break;
				default:
					return MsgHandler::kBadParameters;
			}
			return MsgHandler::kProcessed;
		}
	}
	else {
		EventsAble::reset();
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::clickMsg (const IMessage* msg) const
{ 
	IMessage * outmsg = click(msg);
	if (outmsg) {
		outmsg->print(oscout);
		delete outmsg;
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::selectMsg (const IMessage* msg) const
{ 
	IMessage * outmsg = select(msg);
	if (outmsg) {
		outmsg->print(oscout);
		delete outmsg;
		return MsgHandler::kProcessedNoChange;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
void IObject::save(ostream& out) const
{
	IMessageList outMsgs = getAll();
	out << outMsgs;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::saveMsg (const IMessage* msg) const
{ 
	if ((msg->size() > 0) && (msg->size() < 3)) {
		string destfile = msg->params()[0]->value<string>("");
		if (destfile.size()) {
			ios_base::openmode mode = ios_base::out;
			if (msg->size() == 2) {
				string mstr = msg->params()[1]->value<string>("");
				if (mstr == "+")
					mode |= ios_base::app;
				else return MsgHandler::kBadParameters;
			}
			ofstream out (IAppl::absolutePath(destfile).c_str(), mode);
			save (out);
			return MsgHandler::kProcessedNoChange;
		}
	}
	return MsgHandler::kBadParameters;
}


//--------------------------------------------------------------------------
IMessage * IObject::select (const IMessage* msg) const
{ 
	IMessage * outmsg = 0;
	vector<SIObject> list;
	string mode = "intersect";	// default value
	if (msg->params().size() == 1)
		mode = msg->params()[0]->value<string>("");

	if (IPosition::select (msg, fParent, list)) {
		outmsg = new IMessage(getOSCAddress(), mode);
		for (unsigned i=0; i<list.size(); i++)
			*outmsg << list[i]->name();
	}
	return outmsg;
}

//--------------------------------------------------------------------------
IMessage * IObject::click (const IMessage* msg) const
{ 
	IMessage * outmsg = 0;
	vector<SIObject> list;
	string mode = "topleft";	// default values
	if (msg->params().size() == 1)
		mode = msg->params()[0]->value<string>("");

	if (IPosition::click(msg, SIObject(fParent), list)) {
		outmsg = new IMessage(getOSCAddress(), mode);
		for (unsigned i=0; i<list.size(); i++)
			*outmsg << list[i]->name();
	}
	return outmsg;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::dcolorMsg(const IMessage* msg)
{
	if ( ( msg->params().size() == 3 ) || ( msg->params().size() == 4 ) )
	{
		int r,g,b,a;
		r = msg->params()[0]->value<int>(0);
		g = msg->params()[1]->value<int>(0);
		b = msg->params()[2]->value<int>(0);
		a = ( msg->params().size() == 4 ) ? msg->params()[3]->value<int>(0) : 0;

//		IColor c( getColor() );
		IColor c( *this );
		c.dR( r );
		c.dG( g );
		c.dB( b );
		c.dA( a );
		setColor( c );
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IObject::dhsvMsg(const IMessage* msg)
{
	if ( ( msg->params().size() == 3 ) || ( msg->params().size() == 4 ) )
	{
		int h,s,v,a;
		h = msg->params()[0]->value<int>(0);
		s = msg->params()[1]->value<int>(0);
		v = msg->params()[2]->value<int>(0);
		a = ( msg->params().size() == 4 ) ? msg->params()[3]->value<int>(0) : 0;

		IColor c( *this );
		c.dH(h);
		c.dS(s);		
		c.dV(v);
		c.dA(a);
		setColor( c );
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
// OSCStream support
//--------------------------------------------------------------------------
IMessage& operator << (IMessage& out, const SGetParamMsgHandler& h)
{
	return h->print(out);
}
//--------------------------------------------------------------------------
IMessage& operator << (IMessage& out, const IObject::subnodes& l)
{
	for (IObject::subnodes::const_iterator i = l.begin(); i != l.end(); i++) {
//		if (!(*i)->getDeleted() && ((*i)->getTypeString()!=IVNode::fTypeString)) 
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
