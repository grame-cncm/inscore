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

#include <iostream>
#include "deelx.h"

#include "IAppl.h"
#include "IGlue.h"
#include "IGraphicSignal.h"
#include "IMessage.h"
#include "IObjectFactory.h"
#include "ISignalNode.h"
#include "IScene.h"
#include "ISceneSync.h"
#include "ITLparser.h"
#include "OSCAddress.h"
#include "QFileWatcher.h"
#include "Updater.h"

#include "VSceneView.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
const string IScene::kSceneType("scene");

//--------------------------------------------------------------------------
IScene::~IScene() { delete fView; }
IScene::IScene(const std::string& name, IObject * parent) : IRectShape(name, parent), fFullScreen(false), fView(0)
{
	fTypeString = kSceneType;
	setColor( IColor(255,255,255,255) );
	setWidth(1.0f);
	setHeight(1.0f);
	
	fMsgHandlerMap["new"]			= TMethodMsgHandler<IScene, void (IScene::*)(void)>::create(this, &IScene::newScene);
	fMsgHandlerMap["del"]			= TMethodMsgHandler<IScene, void (IScene::*)(void)>::create(this, &IScene::del);
	fMsgHandlerMap["reset"]			= TMethodMsgHandler<IScene, void (IScene::*)(void)>::create(this, &IScene::reset);
	fMsgHandlerMap["foreground"]	= TMethodMsgHandler<IScene, void (IScene::*)(void)>::create(this, &IScene::foreground);
	fMsgHandlerMap["fullscreen"]	= TSetMethodMsgHandler<IScene,bool>::create(this,&IScene::setFullScreen);
	fMsgHandlerMap["load"]			= TMethodMsgHandler<IScene>::create(this, &IScene::loadMsg);

	fGetMsgHandlerMap["fullscreen"] = TGetParamMsgHandler<bool>::create(fFullScreen);
	fGetMsgHandlerMap[""]			= 0;	// force standard propagation of the get message
	fGetMsgHandlerMap["effect"]		= 0;	// no effects at scene level
	fGetMsgHandlerMap["watch"]		= TGetParamMethodHandler<IScene, IMessageList (IScene::*)() const>::create(this, &IScene::getWatch);
}

//--------------------------------------------------------------------------
QGraphicsScene * IScene::getGraphicScene () const			{ return getView()->scene(); }

//--------------------------------------------------------------------------
void IScene::newScene ()	{}
void IScene::del ()			{ IObject::del(); }
void IScene::foreground()	{ getView()->foreground(); }

//--------------------------------------------------------------------------
void IScene::reset ()
{
	setColor( IColor(255,255,255,255) );
	setXPos(0.f);
	setYPos(0.f);
	setWidth(1.0f);
	setHeight(1.0f);
	signalsNode()->delsubnodes();
	delsubnodes();
	fFileWatcher->clear();
}

#define useiterator 0
//--------------------------------------------------------------------------
void IScene::propagateSignalsState ()
{
	SigModified visitor;
#if useiterator
	for (subnodes::iterator i = elements().begin(); i != elements().end(); i++) {
		(*i)->accept(&visitor);
	}
#else
	for (unsigned int i = 0; i < elements().size(); i++) {
		elements()[i]->accept(&visitor);
	}
#endif
}

//--------------------------------------------------------------------------
void IScene::createVirtualNodes()
{
	IRectShape::createVirtualNodes();

	fSync = ISceneSync::create(this);
	fFileWatcher = QFileWatcher::create(this);
	fSignals = ISignalNode::create(this);
	fSignals->createVirtualNodes();
	add ( fSignals );
	add ( fFileWatcher );
	add ( fSync );
}

//--------------------------------------------------------------------------
SISignalNode IScene::signalsNode () const			{ return fSignals; }

//--------------------------------------------------------------------------
void IScene::accept (Updater* u)
{
	u->updateTo (SIScene(this));
}

//--------------------------------------------------------------------------
SMaster IScene::getMaster(SIObject o) const		
{ 
	return fSync ? fSync->getMaster(o) : 0;
}

//--------------------------------------------------------------------------
void IScene::cleanupSync ()		{ if (fSync) fSync->cleanup(); }

void IScene::sort () 
{ 
	// topological sort of the scene elements
	if (fSync) fSync->sort(elements()); 
}

//--------------------------------------------------------------------------
string IScene::address2scene (const char* addr) const
{
	CRegexpT<char> regexp("/ITL/[^\\/]*", EXTENDED);
	char * replaced = regexp.Replace (addr, getOSCAddress().c_str());
	string sceneAddress (replaced);
	regexp.ReleaseString (replaced);
	return sceneAddress;
}

extern SIMessageStack gMsgStack;
//--------------------------------------------------------------------------
MsgHandler::msgStatus IScene::loadMsg(const IMessage* msg)
{
	if (msg->size() == 1) {
		string srcfile = msg->params()[0]->value<string>("");
		if (srcfile.size()) {
			ITLparser p;
			IMessageList* msgs = p.readfile(IAppl::absolutePath(srcfile).c_str());
			if (msgs) {
				for (IMessageList::const_iterator i = msgs->begin(); i != msgs->end(); i++) {
					IMessage * msg = *i;
					string address = address2scene (msg->address().c_str());
					string beg  = OSCAddress::addressFirst(address);
					string tail = OSCAddress::addressTail(address);
					bool ret = getRoot()->processMsg(beg, tail, *i);
//					if (oscDebug()) IGlue::trace(*i, ret);

//					IMessage * msg = *i;
//					string address = address2scene (msg->address().c_str());
//					msg->setAddress (address);
//					gMsgStack->push(msg);
				}
				msgs->clear();
				delete msgs;
				return MsgHandler::kProcessed;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
void IScene::add (const nodePtr& node)
{ 
	IObject::add (node);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IScene::_watchMsg(const IMessage* msg, bool add)
{ 
	if (msg->params().size()) {
		string what;
		if (msg->param (0, what)) {
			EventsAble::eventype t = EventsAble::string2type (what);
			switch (t) {
				case EventsAble::kNewElement:
					if (msg->params().size() > 1)
						if (add) eventsHandler()->addMsg (t, EventMessage::create (name(), getScene()->name(), msg, 1));
						else eventsHandler()->setMsg (t, EventMessage::create (name(), getScene()->name(),msg, 1));
					else if (!add) eventsHandler()->setMsg (t, 0);
					return MsgHandler::kProcessed;
					break;

				default:
					break;
			}
		}
	}
	return IObject::_watchMsg(msg, add);
}

//--------------------------------------------------------------------------
// propagates modification state from masters to slaves
//--------------------------------------------------------------------------
void IScene::ptask ()
{ 
	if (fSync) fSync->ptask(); 
	if (signalsNode()->getState()) propagateSignalsState();
}

//--------------------------------------------------------------------------
void IScene::print (ostream& out) const
{
	IRectShape::print (out);
	out << "  mode : " << (getFullScreen() ? "normal" : "full") << "screen" << endl;
	out << "  nodes synchronization :" << endl << fSync->getSync();
	out << "  file watcher :" << endl;
	fFileWatcher->print(out);
}


}
