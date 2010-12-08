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

#include "IGlue.h"
#include "VQtLocalMappingUpdater.h"
#include "VQtUpdater.h"
#include "VQtInit.h"
#include "VSceneView.h"

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


SIMessageStack gMsgStask;

#define kUPDPort 7000

//--------------------------------------------------------------------------
static IMessage* Message2IMessage (INScore::MessagePtr p)
{
	return (IMessage*)p;
}

//--------------------------------------------------------------------------
// Qt environment initiaization + INScore glue setup
// intended for theJava environment
//--------------------------------------------------------------------------
class OSApplication : public QApplication
{
	public :
			 OSApplication (int & argc, char ** argv) : QApplication(argc, argv) {}
	virtual ~OSApplication () {}
	bool	notify ( QObject * receiver, QEvent * event ) {
		if (event->type() == QEvent::Timer)
			return QApplication::notify (receiver, event);
		qDebug() << "QApplication notify called: " << event->type(); 
		return true;
	}
};

IGlue* INScore::init(int timeInterval, int udpport)
{
	int argc=0; char** argv=0;
	QApplication* appl = new QApplication(argc, argv);

	IGlue* glue = new IGlue (udpport, kUPDPort+1, kUPDPort+2);
	VQtInit::startQt();
	if (appl && glue && glue->start (timeInterval, true)) {
		appl->setApplicationName("INScoreViewer");	
		glue->setLocalMapUpdater(VQtLocalMappingUpdater::create() );
		glue->setViewUpdater	(VQtUpdater::create() );
//		JavaThread * thread = new JavaThread (appl);
//		thread->start();
		return glue;
	}
	std::cerr << "INScore initialization failed" << std::endl;
	delete glue;
	delete appl;
	return 0;
}

//--------------------------------------------------------------------------
bool INScore::getScene (IGlue* glue, unsigned int* bitmap, int w, int h)
{
	if (!glue || !bitmap) return false;
//	return glue->getSceneView()->copy(bitmap, w, h, false );
	return glue->getSceneView(bitmap, w, h, false );
}

//--------------------------------------------------------------------------
void INScore::setListener (IGlue* glue, GraphicUpdateListener* listener)
{
	if (glue) glue->setGraphicListener (listener);
}

//--------------------------------------------------------------------------
int INScore::version	()				{ return 62; }
const char* INScore::versionStr ()		{ return "0.62"; }

//--------------------------------------------------------------------------
void INScore::postMessage	(const char* address, MessagePtr msg)
{
	IMessage* m = Message2IMessage (msg);
	if (m) {
		m->setAddress(address);
		if (gMsgStask) gMsgStask->push(m);
	}
}

//--------------------------------------------------------------------------
INScore::MessagePtr INScore::newMessage (const char* msg)
{
	IMessage* m = new IMessage;
	m->setMessage(msg);
	return MessagePtr(m);
}

//--------------------------------------------------------------------------
INScore::MessagePtr INScore::newMessage ()
{
	IMessage* m = new IMessage;
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
