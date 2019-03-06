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
#include <fstream>
#include "deelx.h"

#include "IAppl.h"
#include "IGlue.h"
#include "IGraphicSignal.h"
#include "IMessage.h"
#include "IObjectFactory.h"
#include "ISignalNode.h"
#include "IScene.h"
#include "ISceneSync.h"
#include "ITLError.h"
#include "ITLparser.h"
#include "OSCAddress.h"
#include "QFileWatcher.h"
#include "rational.h"
#include "Updater.h"
#include "IJavascript.h"
#include "IFilterForward.h"
#include "Events.h"

#include "VSceneView.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
const string IScene::kSceneType("scene");

//--------------------------------------------------------------------------
IScene::~IScene() 
{
    fSync->cleanup();
    elements().clear();		// this is required to avoid orphan QGraphicsItem (and crash after that)
}

IScene::IScene(const std::string& name, IObject * parent)
		: IRectShape(name, parent), fOpenGl(false), fFullScreen(false), fFrameless(false), fAbsoluteCoordinates(false),
		fWindowOpacity(false), fUpdateVersion(false), fJavascript(getAppl()->getJSEngine())
{
	fTypeString = kSceneType;
	setColor( IColor(255,255,255,255) );
	setWidth(1.0f);
	setHeight(1.0f);
	
	fMsgHandlerMap[knew_SetMethod]				= TMethodMsgHandler<IScene, void (IScene::*)(void)>::create(this, &IScene::newScene);
	fMsgHandlerMap[kreset_SetMethod]			= TMethodMsgHandler<IScene, void (IScene::*)(void)>::create(this, &IScene::reset);
	fMsgHandlerMap[kforeground_SetMethod]		= TMethodMsgHandler<IScene, void (IScene::*)(void)>::create(this, &IScene::foreground);
	fMsgHandlerMap[kfullscreen_GetSetMethod]	= TSetMethodMsgHandler<IScene,bool>::create(this,&IScene::setFullScreen);
	fMsgHandlerMap[kopengl_GetSetMethod]		= TSetMethodMsgHandler<IScene,bool>::create(this,&IScene::setOpenGl);
	fMsgHandlerMap[kframeless_GetSetMethod]		= TSetMethodMsgHandler<IScene,bool>::create(this,&IScene::setFrameless);
	fMsgHandlerMap[kabsolutexy_GetSetMethod]	= TSetMethodMsgHandler<IScene,bool>::create(this,&IScene::setAbsoluteCoordinates);
	fMsgHandlerMap[kwindowOpacity_GetSetMethod]	= TSetMethodMsgHandler<IScene,bool>::create(this,&IScene::setWindowOpacity);
	fMsgHandlerMap[kload_SetMethod]				= TMethodMsgHandler<IScene>::create(this, &IScene::loadMsg);
	fMsgHandlerMap[kpreprocess_SetMethod]		= TMethodMsgHandler<IScene>::create(this, &IScene::preProcessMsg);
	fMsgHandlerMap[krootPath_GetSetMethod]		= TMethodMsgHandler<IScene>::create(this, &IScene::setRootPath);
	fMsgHandlerMap[kforward_GetSetMethod]		= TMethodMsgHandler<IScene>::create(this, &IScene::forward);
	fMsgHandlerMap[kparse_GetSetMethod]			= TMethodMsgHandler<IScene>::create(this, &IScene::setParseVersion);

	fGetMsgHandlerMap[kopengl_GetSetMethod]		= TGetParamMsgHandler<bool>::create(fOpenGl);
	fGetMsgHandlerMap[kfullscreen_GetSetMethod] = TGetParamMsgHandler<bool>::create(fFullScreen);
	fGetMsgHandlerMap[kframeless_GetSetMethod]	= TGetParamMsgHandler<bool>::create(fFrameless);
	fGetMsgHandlerMap[kabsolutexy_GetSetMethod] = TGetParamMsgHandler<bool>::create(fAbsoluteCoordinates);
	fGetMsgHandlerMap[kwindowOpacity_GetSetMethod] = TGetParamMsgHandler<bool>::create(fWindowOpacity);
	fGetMsgHandlerMap[krootPath_GetSetMethod]	= TGetParamMsgHandler<string>::create(fRootPath);
	fGetMsgHandlerMap[kforward_GetSetMethod]	= TGetParamMethodHandler<IScene, const vector<IMessage::TUrl> (IScene::*)() const>::create(this, &IScene::getForwardList);
	fGetMsgHandlerMap[kparse_GetSetMethod]		= TGetParamMethodHandler<IScene, const std::string& (IScene::*)() const>::create(this, &IScene::parseVersion);
}

//--------------------------------------------------------------------------
QGraphicsScene * IScene::getGraphicScene () const			{ return fView ? static_cast<VSceneView*>(fView)->scene() : 0; }

//--------------------------------------------------------------------------
void IScene::setHandlers ()
{
	colorAble();
	positionAble();
	fGetMsgHandlerMap[""]			= (void*)0;	// force standard propagation of the get message
	fMsgHandlerMap[keffect_GetSetMethod]		= (void*)0;	// no effects at scene level
	fGetMsgHandlerMap[keffect_GetSetMethod]		= (void*)0;	// no effects at scene level
}

//--------------------------------------------------------------------------
void IScene::newScene ()						{}
void IScene::foreground()						{ getSceneView()->foreground(); }
void IScene::setRootPath(const std::string& s)  { fRootPath = IAppl::checkRootPath(s);}
//--------------------------------------------------------------------------
int IScene::getParseVersion () const
{
	if (fParseVersion.empty()) return IAppl::getParseVersion();
	if (fParseVersion == "v2") return 2;
	return 1;
}

const string& IScene::parseVersion () const
{
	return (fParseVersion.empty()) ? IAppl::parseVersion() : fParseVersion;
}

void IScene::del()
{
	for(int i=0; i<size(); i++)
        elements()[i]->del();
	_del(false);
}
VSceneView*	IScene::getSceneView() const		{ return static_cast<VSceneView *>(fView); }

//--------------------------------------------------------------------------
void IScene::reset ()
{
	setColor( IColor(255,255,255,255) );
	setXPos(0.f);
	setYPos(0.f);
	setScale(1.0f);
	setXOrigin(0.0f);
	setYOrigin(0.0f);
	setWidth(1.0f);
	setHeight(1.0f);
	signalsNode()->delsubnodes();
	delsubnodes();
	fFileWatcher->clear();
	fRootPath.clear();
	fFullScreen = false; 
	fFrameless = false;
}

//--------------------------------------------------------------------------
void IScene::setOpenGl(bool state)
{
#ifdef __MOBILE__
	if (state)
		ITLErr << "OpenGL is not (yet) supported on mobile platforms" << ITLEndl;
#else
	fOpenGl = state;
#endif
}

//--------------------------------------------------------------------------
SIMessageList IScene::getAll () const
{
	SIMessageList outMsgs = IMessageList::create();
	SIMessage msg = IMessage::create( getOSCAddress(), "new");
	outMsgs->list().push_back (IMessage::create( getOSCAddress(), "new"));
	outMsgs->list().push_back (IObject::getAll()->list());
	return outMsgs;
}

//--------------------------------------------------------------------------
void IScene::createVirtualNodes()
{
	IRectShape::createVirtualNodes();

	fFileWatcher = QFileWatcher::create(this);
	fJSObject = IJavascript::create(this);
	fFilterForward = IFilterForward::create(this);
	fForwarder.setFilter(fFilterForward);
	add ( fFileWatcher );
	add ( fJSObject );
	add ( fFilterForward );
}

//--------------------------------------------------------------------------
string IScene::getRootPath() const
{
	return fRootPath.size() ? fRootPath : IAppl::getRootPath();
}

//--------------------------------------------------------------------------
string IScene::absolutePath(const std::string& path) const
{
	return IAppl::makeAbsolutePath (getRootPath(), path);
}

//--------------------------------------------------------------------------
void IScene::accept (Updater* u)
{
	u->updateTo (SIScene(this));
}

//--------------------------------------------------------------------------
bool IScene::accept(const std::string& regexp, const IMessage *msg)
{
	bool result = IObject::match(regexp);
	if (result)
		fForwarder.forward(msg);
	return result;
}

//--------------------------------------------------------------------------
int	IScene::execute (const IMessage* msg)
{
	fForwarder.forward(msg);
	return IObject::execute(msg);
}

//--------------------------------------------------------------------------
// a message addressed to /ITL/scene that is dropped to another scene is converted
// to the other scene address.
// in a given way, the address /ITL/scene match any scene address
string IScene::address2scene (const char* addr) const
{
//	CRegexpT<char> regexp("/ITL/[^\\/]*", EXTENDED);
	CRegexpT<char> regexp("/ITL/scene", EXTENDED);
	char * replaced = regexp.Replace (addr, getOSCAddress().c_str());
	string sceneAddress (replaced);
	regexp.ReleaseString (replaced);
	return sceneAddress;
}
//--------------------------------------------------------------------------
MsgHandler::msgStatus IScene::preProcessMsg(const IMessage* msg)
{
	return preprocess (msg, getAppl(), getRootPath(), getParseVersion());
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IScene::loadMsg(const IMessage* msg)
{
	return load (msg, this, getRootPath(), getParseVersion());
}

//--------------------------------------------------------------------------
void IScene::endPaint () const
{
	checkEvent (kEndPaintEvent, libmapping::rational(0,1), this);
}

//--------------------------------------------------------------------------
void IScene::add (const nodePtr& node)
{
	IObject::add (node);
	checkEvent (kNewElementEvent, libmapping::rational(0,1), node);
}

//--------------------------------------------------------------------------
void IScene::setState (state s)
{
	IObject::setState(s);
	if (getState() & (IObject::kModified | IObject::kSubModified))
		setUpdateVersion(true);
}

//--------------------------------------------------------------------------
bool IScene::acceptSimpleEvent(EventsAble::eventype t) const
{
	string ev(t);
	if ( (ev == kNewElementEvent) || (ev == kEndPaintEvent)) return true;
	return IObject::acceptSimpleEvent(t);
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

//--------------------------------------------------------------------------
MsgHandler::msgStatus IScene::setRootPath(const IMessage* msg)
{
	MsgHandler::msgStatus status = MsgHandler::kProcessedNoChange;
	size_t n = msg->size();
	if (!n) {
		fRootPath.clear();
	}
	else if (n == 1) {
		string path;
		if (msg->param(0, path)) {
			fRootPath = IAppl::checkRootPath(path);
		}
		else status = MsgHandler::kBadParameters;
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IScene::forward(const IMessage* msg)
{
	return fForwarder.processForwardMsg(msg);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IScene::setParseVersion(const IMessage* msg)
{
	MsgHandler::msgStatus status = MsgHandler::kProcessedNoChange;
	size_t n = msg->size();
	if (!n) {
		fParseVersion.clear();
		return status;
	}

	string v;
	if ((n == 1) && msg->param(0, v)) {
		if (v == "v1") 		fParseVersion = v;
		else if (v == "v2") fParseVersion = v;
		else {
			ITLErr << "unknown parse version '" << v << "'" << ITLEndl;
			status = MsgHandler::kBadParameters;
		}
	}
	else status = MsgHandler::kBadParameters;
	return status;
}

}
