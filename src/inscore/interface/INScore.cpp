/*

  INScore Library
  Copyright (C) 2009,2010  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation.

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

#include "INScore.h"
#include "IMessage.h"
#include "IMessageStack.h"


#include <QApplication>
#include <QDir>
#include <QThread>
#include <QDebug>
#include <QWaitCondition>

#include <iostream>
#include <map>

#include "GUIDOEngine.h"

#include "IGlue.h"
#ifdef NOVIEW
#include "VoidUpdater.h"
#elif defined(__MOBILE__)
#include "VMobileQtInit.h"
#include "VMobileQtUpdater.h"
#include "VQtLocalMappingUpdater.h"
#else
#include "VQtInit.h"
#include "VQtLocalMappingUpdater.h"
#include "VQtUpdater.h"
#endif
#include "VSceneView.h"
#include "QGuidoImporter.h"

using namespace std;
namespace inscore 
{

IGlue* gGlue;
//_______________________________________________________________________
/*!
	\brief a specific thread for Java JNI
*/
class JavaThread : public QThread
{
	public:
		QApplication*	fAppl;
	
				 JavaThread(QApplication* appl) : fAppl(appl){}
		virtual ~JavaThread() {}
		void run()			 { fAppl->exec(); }
};


SIMessageStack				gMsgStack;			// the messages stack
SIMessageStack				gDelayStack;		// the delayed messages stack
SIMessageStack				gWebMsgStack;		// the messages stack for messages from the web
map<INScore::MessagePtr, SIMessage>	gMsgMemory;		// allocated messages are stored in a map for refcounting
QWaitCondition				gModelUpdateWaitCondition; // A wait condition on model update.
//--------------------------------------------------------------------------
static IMessage* Message2IMessage (INScore::MessagePtr p)
{
	return (IMessage*)p;
}

//--------------------------------------------------------------------------
// Qt environment initiaization + INScore glue setup
//--------------------------------------------------------------------------
IGlue* INScore::start(int timeInterval, int udpport, int outport, int errport, QApplication* appl, bool offscreen)
{
	IGlue* glue = new IGlue (udpport, outport, errport);
	if (glue && glue->start (timeInterval, offscreen, appl)) {
#ifdef NOVIEW
		glue->setLocalMapUpdater(VoidLocalMapUpdater::create() );
		glue->setViewUpdater	(VoidViewUpdater::create() );
#elif defined(__MOBILE__)
		VMobileQtInit::startQt();
		glue->setLocalMapUpdater(VQtLocalMappingUpdater::create() );
		// Initialize a view updater for mobile with a tab container
		glue->setViewUpdater	(VMobileQtUpdater::create() );
#else
		VQtInit::startQt();
		glue->setLocalMapUpdater(VQtLocalMappingUpdater::create() );
		glue->setViewUpdater	(VQtUpdater::create() );
#endif
		gGlue = glue;
		return glue;
	}
	std::cerr << "INScore initialization failed" << std::endl;
	delete glue;
	return 0;
}

//--------------------------------------------------------------------------
void INScore::stop(IGlue* glue)
{
#ifndef NOVIEW
	VQtInit::stopQt();
#endif
	gGlue = 0;
	delete glue;
}

//--------------------------------------------------------------------------
void INScore::restartNetwork()
{
    gGlue->restart();
}

//--------------------------------------------------------------------------
void INScore::stopNetwork()
{
    gGlue->clean();
}

//--------------------------------------------------------------------------
//bool INScore::getGraphicScore (IGlue* glue, unsigned int* bitmap, int w, int h)
//{
//	if (!glue || !bitmap) return false;
//	return glue->getSceneView(bitmap, w, h, false );
//}

//--------------------------------------------------------------------------
//void INScore::setListener (IGlue* glue, GraphicUpdateListener* listener)
//{
//	if (glue) glue->setGraphicListener (listener);
//}

//--------------------------------------------------------------------------
//void INScore::timeTask (IGlue* glue)
//{
//	if (glue) glue->timerEvent (0);
//}

//--------------------------------------------------------------------------
// versions 
//--------------------------------------------------------------------------
float INScore::version	()				{ return 1.17f; }
const char* INScore::versionStr ()		{ return "1.17"; }

//--------------------------------------------------------------------------
const char* INScore::guidoversion()
{
	int major, minor, sub;
	GuidoGetVersionNums(&major, &minor, &sub);
	stringstream s;
	s << major << '.' << minor << '.' << sub;
	
	static string version = s.str();
	return version.c_str();
}

//--------------------------------------------------------------------------
const char* INScore::musicxmlversion()
{
	if (QGuidoImporter::musicxmlSupported())
	{
		static string version;
		if (!version.size()) {
			version = QGuidoImporter::musicxmlVersion();
			version += " using the guido converter version ";
			version += QGuidoImporter::musicxml2guidoVersion();
		}
		return version.c_str();
	}
	return "not available";
}

//--------------------------------------------------------------------------
const char* INScore::qtversion()
{
	QString vers(qVersion());
	static string version = vers.toStdString();
	return version.c_str();
}


const unsigned long localhost = (127 << 24) + 1;

//--------------------------------------------------------------------------
// messages system 
//--------------------------------------------------------------------------
void INScore::postMessage	(const char* address, MessagePtr msg)
{
	IMessage* m = Message2IMessage (msg);
	if (m) {
		string oscAddress;
		IMessage::TUrl url;
		if (IMessage::decodeAddress (address, oscAddress, url)) {
			m->setAddress(oscAddress);
			m->setUrl(url);
		}
		else m->setAddress(address);
		if (gMsgStack) gMsgStack->push(new SIMessage(m));
		gMsgMemory[msg] = SIMessage(0);
	}
}

//--------------------------------------------------------------------------
void INScore::postMessage	(const char* address, const char* method)
{
	MessagePtr msg = newMessage (method);
	postMessage (address, msg);
}

//--------------------------------------------------------------------------
void INScore::postMessage	(const char* address, const char* method, int val)
{
	MessagePtr msg = newMessage (method);
	add (msg, val);
	postMessage (address, msg);
}

//--------------------------------------------------------------------------
void INScore::postMessage	(const char* address, const char* method, float val)
{
	MessagePtr msg = newMessage (method);
	add (msg, val);
	postMessage (address, msg);
}

//--------------------------------------------------------------------------
void INScore::postMessage	(const char* address, const char* method, const char* val)
{
	MessagePtr msg = newMessage (method);
	add (msg, val);
	postMessage (address, msg);
}

//--------------------------------------------------------------------------
void INScore::delayMessage	(const char* address, MessagePtr msg)
{
	IMessage* m = Message2IMessage (msg);
	if (m) {
		string oscAddress;
		IMessage::TUrl url;
		if (IMessage::decodeAddress (address, oscAddress, url)) {
			m->setAddress(oscAddress);
			m->setUrl(url);
		}
		else m->setAddress(address);
		if (gDelayStack) gDelayStack->push(new SIMessage(m));
	}
}

//--------------------------------------------------------------------------
INScore::MessagePtr INScore::newMessage (const char* msg)
{
	SIMessage m = IMessage::create();
	m->setSrcIP (localhost);
	m->setMessage(msg);
	gMsgMemory[MessagePtr(m)] = m;
	return MessagePtr(m);
}

//--------------------------------------------------------------------------
INScore::MessagePtr INScore::newMessage ()
{
	SIMessage m = IMessage::create();
	m->setSrcIP (localhost);
	gMsgMemory[MessagePtr(m)] = m;
	return MessagePtr(m);
}

//--------------------------------------------------------------------------
void INScore::delMessage(MessagePtr msg)
{
	map<INScore::MessagePtr, SIMessage>::iterator i = gMsgMemory.find(msg);
	if (i != gMsgMemory.end())
		gMsgMemory.erase (i);
//	gMsgMemory[msg] = SIMessage(0);
}

//--------------------------------------------------------------------------
void INScore::add (MessagePtr p, const char* s)
{
	IMessage* m = Message2IMessage (p);
	if (!m) return;
	
	if (!m->size() && m->message().empty()) m->setMessage(s);
	else m->add(s);
}

//--------------------------------------------------------------------------
void INScore::add (MessagePtr p, float f)
{
	IMessage* m = Message2IMessage (p);
	if (m) m->add(f);
}

//--------------------------------------------------------------------------
void INScore::add (MessagePtr p, int n)
{
	IMessage* m = Message2IMessage (p);
	if (m) m->add(n);
}

}
