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

#include <iostream>

#include "GUIDOEngine.h"

#include "IGlue.h"
#include "VQtLocalMappingUpdater.h"
#include "VQtUpdater.h"
#include "VQtInit.h"
#include "VSceneView.h"
#include "QGuidoImporter.h"

using namespace std;
namespace inscore 
{

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


SIMessageStack gMsgStack;

#define kUPDPort 7000

//--------------------------------------------------------------------------
static IMessage* Message2IMessage (INScore::MessagePtr p)
{
	return (IMessage*)p;
}

//--------------------------------------------------------------------------
// Qt environment initiaization + INScore glue setup
//--------------------------------------------------------------------------
IGlue* INScore::start(int timeInterval, int udpport, int outport, int errport, bool offscreen)
{
	IGlue* glue = new IGlue (udpport, outport, errport);
	VQtInit::startQt();
	if (glue && glue->start (timeInterval, offscreen)) {
		glue->setLocalMapUpdater(VQtLocalMappingUpdater::create() );
		glue->setViewUpdater	(VQtUpdater::create() );
		return glue;
	}
	std::cerr << "INScore initialization failed" << std::endl;
	delete glue;
	return 0;
}

//--------------------------------------------------------------------------
void INScore::stop(IGlue* glue)
{
	delete glue;
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
float INScore::version	()				{ return 0.92; }
const char* INScore::versionStr ()		{ return "0.92"; }

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
		static string version = QGuidoImporter::musicxmlVersion();
		version += " using the guido converter version ";
		version += QGuidoImporter::musicxml2guidoVersion();
		return version.c_str();
	}
	return "not available";
}


const unsigned long localhost = (127 << 24) + 1;

//--------------------------------------------------------------------------
// messages system 
//--------------------------------------------------------------------------
void INScore::postMessage	(const char* address, MessagePtr msg)
{
	IMessage* m = Message2IMessage (msg);
	if (m) {
		m->setAddress(address);
		if (gMsgStack) gMsgStack->push(m);
	}
}

//--------------------------------------------------------------------------
INScore::MessagePtr INScore::newMessage (const char* msg)
{
	IMessage* m = new IMessage;
	m->setSrcIP (localhost);
	m->setMessage(msg);
	return MessagePtr(m);
}

//--------------------------------------------------------------------------
INScore::MessagePtr INScore::newMessage ()
{
	IMessage* m = new IMessage;
	m->setSrcIP (localhost);
	return MessagePtr(m);
}

//--------------------------------------------------------------------------
void INScore::delMessage(MessagePtr msg)
{
	IMessage* m = Message2IMessage (msg);
	if (m) delete m;
}

//--------------------------------------------------------------------------
void INScore::add (MessagePtr p, const char* s)
{
	IMessage* m = Message2IMessage (p);
	if (m) m->add<string>(s);
}

//--------------------------------------------------------------------------
void INScore::add (MessagePtr p, float f)
{
	IMessage* m = Message2IMessage (p);
	if (m) m->add<float>(f);
}

//--------------------------------------------------------------------------
void INScore::add (MessagePtr p, int n)
{
	IMessage* m = Message2IMessage (p);
	if (m) m->add<int>(n);
}

}
