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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <condition_variable>
#include <iostream>
#include <map>
#include <sstream>

#include "GUIDOEngine.h"
#include "IAppl.h"
#include "IGlue.h"
#include "IMessage.h"
#include "IMessageStack.h"
#include "INScore.h"
#include "Modules.h"
#include "TILoader.h"
#include "TSorter.h"
#include "TWallClock.h"
#include "XMLImporter.h"

#if QTVIEW
#  include <QFontDatabase>
#  include "QGuidoPainter.h"
#  include "VQtLocalMappingUpdater.h"
#  include "VQtUpdater.h"

#if defined(__MOBILE__)
#  include "VMobileQtInit.h"
#  include "VMobileQtUpdater.h"
#  include "VQtLocalMappingUpdater.h"
#endif

#elif defined(NOVIEW) || defined(MODELONLY)
# include "VoidUpdater.h"

#elif defined(HTMLVIEW)
# include "HTMLUpdater.h"
#endif


#ifdef EMCC
#include "JSCall.h"
#endif

using namespace std;
namespace inscore 
{

IGlue* gGlue;


SIMessageStack				gMsgStack;			// the messages stack
SIMessageStack				gDelayStack;		// the delayed messages stack
SIMessageStack				gWebMsgStack;		// the messages stack for messages from the web
map<INScore::MessagePtr, SIMessage>	gMsgMemory;		// allocated messages are stored in a map for refcounting
std::condition_variable		gModelUpdateWaitCondition; // A wait condition on model update.

//--------------------------------------------------------------------------
static IMessage* Message2IMessage (INScore::MessagePtr p)
{
	return (IMessage*)p;
}

#if QTVIEW
#define GUIDO_FONT_FILE ":/guido2.ttf"
//-----------------------------------------------------------------------
static void startQtView ()
{
	QFontDatabase::addApplicationFont (GUIDO_FONT_FILE);
	QGuidoPainter::startGuidoEngine();
}

//-----------------------------------------------------------------------
void stopQtView  ()
{
	QGuidoPainter::stopGuidoEngine();
}
#endif

//--------------------------------------------------------------------------
// Qt environment initiaization + INScore glue setup
//--------------------------------------------------------------------------
INScoreGlue* INScore::start(int udpport, int outport, int errport, INScoreApplicationGlue* ag, bool offscreen)
{
#if QTVIEW
	startQtView ();
#endif
	IGlue* glue = new IGlue (udpport, outport, errport);
	if (glue && glue->start (offscreen, ag)) {
#if defined(NOVIEW)
	glue->setLocalMapUpdater(VoidLocalMapUpdater::create() );
	glue->setViewUpdater	(VoidViewUpdater::create() );
#elif defined(HTMLVIEW)
	glue->setLocalMapUpdater(HTMLLocalMapUpdater::create() );
	glue->setViewUpdater	(HTMLViewUpdater::create() );
#elif defined(MODELONLY)
		glue->setLocalMapUpdater( 0 );
		glue->setViewUpdater	( 0 );
#elif defined(__MOBILE__)
		VMobileQtInit::startQt();
		glue->setLocalMapUpdater(VQtLocalMappingUpdater::create() );
		// Initialize a view updater for mobile with a tab container
		glue->setViewUpdater	(VMobileQtUpdater::create() );
#else
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
void INScore::stop(INScoreGlue* glue)
{
#if QTVIEW
	stopQtView ();
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
bool INScore::loadInscore(const char *script, bool autoparse)
{
	IAppl* appl = gGlue->getAppl();
	if (autoparse && (appl->parseVersion() == "v2"))
		return loadInscore2(script);

	stringstream stream(script);
	return TILoader::parse(&stream, 0, appl, 1);
}

//--------------------------------------------------------------------------
bool INScore::loadInscore2(const char *script)
{
	stringstream stream(script);
	return TILoader::parse(&stream, 0, gGlue->getAppl(), 2);
}

//--------------------------------------------------------------------------
// versions 
//--------------------------------------------------------------------------
string INScore::guidoversion()
{
#ifdef EMCC
	return jscall::getGuidoVersion();
#else
	return GuidoGetVersionStr();
#endif
}

//--------------------------------------------------------------------------
string INScore::musicxmlversion()
{
#ifdef EMCC
	return jscall::getMusicXmlVersion();
#else
	if (XMLImporter::musicxmlSupported())
	{
		string version = XMLImporter::musicxmlVersion();
		version += " using the guido converter version ";
		version += XMLImporter::musicxml2guidoVersion();
		return version;
	}
	return "not available";
#endif
}

string INScore::faustversion()
{
#ifdef EMCC
	return jscall::getFaustVersion();
#else
	return "not available";
#endif
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
