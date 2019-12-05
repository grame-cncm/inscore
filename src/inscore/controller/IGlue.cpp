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

#include <stdexcept>
#include <iostream>
#include <condition_variable>

#include "GUIDOEngine.h"

#include "EventsAble.h"
#include "IAppl.h"
#include "IGlue.h"
#include "IMappingUpdater.h"
#include "IMessage.h"
#include "INScore.h"
#include "IScene.h"
#include "ITLError.h"
#include "ISync.h"
#include "OSCStream.h"
#include "TWallClock.h"
#include "ViewFactory.h"

#include "benchtools.h"

using namespace std;

namespace inscore
{

extern SIMessageStack gMsgStack;
extern SIMessageStack gDelayStack;
extern SIMessageStack gWebMsgStack;
extern std::condition_variable gModelUpdateWaitCondition;

#define kDefaultRate	10

//--------------------------------------------------------------------------
static void run (SIOSCListener listener)
{
	listener->run();
}

//--------------------------------------------------------------------------
void OscThread::start()
{
	if (fThread) stop();
	fThread = new std::thread (run, fListener);
//	fThread = new std::thread (fListener->run);
}

//--------------------------------------------------------------------------
void OscThread::stop()
{
	if (fThread) {
		fListener->stop();
		fThread->join(); delete fThread; fThread = 0;
	}
}


//--------------------------------------------------------------------------
IGlue::IGlue(int udpport, int outport, int errport) 
	: fOscThread(0), fViewListener(0), fUDP(udpport, outport, errport)
{
	fLastTimeTask = 0;
}

IGlue::~IGlue()	{ clean(); }

//--------------------------------------------------------------------------
const IObject* IGlue::root () const  { return dynamic_cast<const IObject*>((IAppl*)fModel); }

//--------------------------------------------------------------------------
void IGlue::clean()
{
	delete fOscThread;
    fOscThread = 0;
	OSCStream::stop();
	fModel->getApplicatonGlue()->stopView();
}

//--------------------------------------------------------------------------
void IGlue::restart()
{
    try {
        if (!OSCStream::start())
            throw("Cannot initialize output udp streams");
        oscinit (fModel, fUDP);
        if (!fMsgStack || !fController || !fModel || !fOscThread)
            throw("Memory allocation failed!");
    }
    catch (std::runtime_error e) {
        clean();
		ITLErr << "Unexpected error: " << e.what() << ITLEndl;
    }
    catch (const char* e) {
        clean();
		ITLErr << "Unexpected error: " << e << ITLEndl;
    }
}

//--------------------------------------------------------------------------
// try to open the udp ports
// listening port number (which binding may fail) is allocated dynamically
// actually, tries to bind the next available port until success
// output port numbers remain as set by default
void IGlue::oscinit (SIAppl appl, udpinfo& udp)
{
	int port = udp.fErrPort;
	bool done = false;
	do {
		try {
			oscinit (udp.fInPort);
			oscinit (oscout, udp.fOutDstAddress, udp.fOutPort);
			oscinit (oscerr, udp.fErrDstAddress, udp.fErrPort);
			appl->setUDPInPort (udp.fInPort);
			done = true;
		}
		catch (std::runtime_error e) {
			if ( port - udp.fErrPort > 1000) throw ("Cannot bind udp communication ports");
			udp.fInPort = ++port;
		}
	} while (!done);
}

//--------------------------------------------------------------------------
void IGlue::oscinit (int port)
{
	if (fOscThread) delete fOscThread;
	fOscThread = new OscThread(fMsgStack, fUDP.fInPort=port);
	if (fOscThread) fOscThread->start();
}

//--------------------------------------------------------------------------
void IGlue::oscinit (OSCStream& osc, const std::string& address, int port)
{
	osc.setPort(port);
	osc.setAddress(address);
}

//--------------------------------------------------------------------------
bool IGlue::getSceneView(unsigned int* , int , int , bool )
{ 
//	QRect r = QApplication::desktop()->screenGeometry();
//	float lowestDimension = qMin( r.width(), r.height() );
//	fScene->setWidth((2*w) / lowestDimension);
//	fScene->setHeight((2*h) / lowestDimension);

	return false;
//	return getSceneView()->copy(dest, w, h, smooth );
}

//--------------------------------------------------------------------------
void IGlue::initialize (bool offscreen, INScoreApplicationGlue* ag)
{
	ag->startView();
	Master::initMap();
	EventsAble::init();

	fMsgStack = IMessageStack::create();
	gMsgStack = fMsgStack;
	fDelayStack = IMessageStack::create();
	gDelayStack = fDelayStack;
	fWebMsgStack = IMessageStack::create();
	gWebMsgStack = fWebMsgStack;
	fController = IController::create();

	fModel = IAppl::create(fUDP.fInPort, fUDP.fOutPort, fUDP.fErrPort, ag, offscreen);
	fModel->createVirtualNodes();
	fModel->setView (ViewFactory::create(fModel));

	string address (fModel->getOSCAddress());
	address += "/scene";
	INScore::postMessage (address.c_str(), knew_SetMethod);

#ifdef __MOBILE__
	INScore::postMessage(address.c_str(), klock_GetSetMethod, 1);
#endif

	fTimeTask = fModel;
	if (!OSCStream::start())
		throw("Cannot initialize output udp streams");
	oscinit (fModel, fUDP);
	if (!fMsgStack || !fController || !fModel || !fOscThread)
		throw("Memory allocation failed!");
	string listen(" listening OSC on port ");
	oscerr.setLogWindow (fModel->getLogWindow());
	oscerr << OSCStart("INScore") << "v" << INScore::versionStr() << listen <<  fUDP.fInPort << OSCEnd();
	cout << "INScore v " << INScore::versionStr() << listen <<  fUDP.fInPort << endl;
	fModel->setRootPath ();

	// check Guido version
	if (GuidoCheckVersionNums(1, 6, 0) != guidoNoErr) {
		oscerr << OSCStart("Warning:") << "GUIDOEngine version >= 1.60 is required." << OSCEnd();
		cerr << "Warning: GUIDOEngine version >= 1.60 is required." << endl;
	}
	
	// creates a mapping updater - note that it may send error messages and thus should not be
	// set before the osc streams are ready
	setSlaveMapUpdater(new IMappingUpdater);

	fModel->startTime();

#if defined(RUNBENCH) || defined(TIMEBENCH)
	fModel->resetBench();
#endif
}

//--------------------------------------------------------------------------
int IGlue::getRate () const	{ return fModel->getRate(); }

//--------------------------------------------------------------------------
bool IGlue::start (bool offscreen, INScoreApplicationGlue* ag)
{
	try {
		initialize(offscreen, ag);
	}
	catch (std::runtime_error e) {
		clean();
		ITLErr << "Unexpected error: " << e.what() << ITLEndl;
		return false;
	}
	catch (const char* e) {
		clean();
		ITLErr << "Unexpected error: " << e << ITLEndl;
		return false;
	}
	return true;
}

//--------------------------------------------------------------------------
void IGlue::setViewUpdater(SUpdater updater)
{
	fViewUpdater = updater;
	if (fViewUpdater) {
		fViewUpdater->update (fModel);	// force view update when updater changes
									// otherwise the view won't be updated until the next incoming message
									// see timerEvent method
		fModel->cleanup();			// and clean the model
	}
}

//--------------------------------------------------------------------------
void IGlue::setSlaveMapUpdater(SUpdater updater)
{
	fSlaveMapUpdater = updater;
	if (fSlaveMapUpdater) {
		fSlaveMapUpdater->update (fModel);	// force map update when updater changes
	}
}

//--------------------------------------------------------------------------
void IGlue::setLocalMapUpdater(SUpdater updater)
{
	fLocalMapUpdater = updater;
	if (fLocalMapUpdater) {
		fLocalMapUpdater->update (fModel);	// force map update when updater changes
	}
}

//--------------------------------------------------------------------------
void IGlue::setOSCOut (int port) {	oscout.setPort(port); fUDP.fOutPort = port; }
void IGlue::setOSCOut (const std::string& a) { oscout.setAddress(a); fUDP.fOutDstAddress = a;  }
void IGlue::setOSCErr (int port) {	oscerr.setPort(port); fUDP.fErrPort = port; }
void IGlue::setOSCErr (const std::string& a) { oscerr.setAddress(a); fUDP.fErrDstAddress = a;  }

//--------------------------------------------------------------------------
void IGlue::checkUDPChange()
{
	if (IAppl::getUDPInPort() != fUDP.fInPort)					// check for udp port number changes
		oscinit (IAppl::getUDPInPort());
	if (IAppl::getUDPOutPort() != fUDP.fOutPort)				// check for udp out port number changes
		setOSCOut(IAppl::getUDPOutPort());
	if (IAppl::getUDPErrPort() != fUDP.fErrPort)				// check for udp err port number changes
		setOSCErr(IAppl::getUDPErrPort());
}

//--------------------------------------------------------------------------
void IGlue::modelUpdate()
{
	SIObject model(fModel);
	fController->processOn(fMsgStack, model);

	// Process web message stack
	oscerr.activeConcatError(true);
	fController->processOn(fWebMsgStack, model);
	oscerr.activeConcatError(false);

	// Wake up thread waiting for a model update.
	gModelUpdateWaitCondition.notify_all();
}

//--------------------------------------------------------------------------
void IGlue::localMapUpdate()	{ if (fLocalMapUpdater) fLocalMapUpdater->update (fModel); }
void IGlue::slaveMapUpdate()	{ if (fSlaveMapUpdater) fSlaveMapUpdater->update (fModel); }
void IGlue::viewUpdate()		{ if (fViewUpdater) fViewUpdater->update (fModel); }

#ifdef TIMEBENCH
//--------------------------------------------------------------------------
static void sendTimeSig ()
{
	static const char * timesig = "/ITL/scene/signal/ttask";
	static bool first = true;
	if (!first) {
		float elapsed = IAppl::getRealRate();
		bench::put("time", elapsed);
		float rate = elapsed / IAppl::getRate();
		SIMessage msg = IMessage::create(timesig);
		msg->add(rate - 1.f);
		msg->send();
	}
	else {
		SIMessage msg = IMessage::create(timesig, "size");
		msg->add(400);
		msg->send();
		first = false;
//cout << "IGlue::timerEvent create sig: " << msg << endl;
	}
}
#endif

//--------------------------------------------------------------------------
void IGlue::sorterTask ()
{
	fModel->timeTask();
}

//--------------------------------------------------------------------------
void IGlue::timeTask ()
{
	double current = TWallClock::time();
	if (fLastTimeTask)
		fModel->setRealRate(current - fLastTimeTask);
	else fModel->setRealRate(kDefaultRate);
	fLastTimeTask = current;

#ifdef TIMEBENCH
	sendTimeSig ();
#endif

#ifdef RUNBENCH
	static double prevtime = 0;
	double time = getTime();
	bench::put ("time", prevtime ? (time - prevtime)/1000 : 0);
	prevtime = time;
#endif

	fModel->clock();
	if (fMsgStack->size() || fWebMsgStack->size()) {
		timebench ("model", modelUpdate());
	}

	fModel->processSig();
	if (fModel->getState() & IObject::kModified + IObject::kSubModified) {

		if (fTimeTask) fTimeTask->ptask();

		timebench ("lmap", localMapUpdate());
		timebench ("smap", slaveMapUpdate());
		timebench ("view", viewUpdate());

		if (fModel->getState() & IObject::kModified) {
			checkUDPChange();
			if (fModel->getUDPInPort() != fUDP.fInPort)					// check for udp port number changes
				oscinit (fModel->getUDPInPort());
		}

		if (fModel->getState() & IObject::kSubModified) {
			fController->setListener (fModel->oscDebug() ? this : 0);	// check for debug flag changes
			if (fViewListener) fViewListener->update();
		}		
		fModel->cleanup();
	}

#ifdef RUNBENCH
	else {
		bench::put ("model", 0);
		bench::put ("lmap", 0);
		bench::put ("smap", 0);
		bench::put ("view", 0);
	}
	bench::put ("total", getTime() - time);
#endif

	// check delayed messages and transfer them to the messages stack
	if (fDelayStack->size()) {
		SIMessage* msgptr = fDelayStack->pop();
		while (msgptr) {
			fMsgStack->push (msgptr);
			msgptr = fDelayStack->pop();
		}
	}
}

//--------------------------------------------------------------------------
void IGlue::trace( const IMessage* msg, int status )
{
	if (status == MsgHandler::kBadAddress) 
		ITLErr << "incorrect OSC address:" << msg->address() << ITLEndl;
	else if (status == MsgHandler::kBadParameters)
		ITLErr << "incorrect parameters:"<< msg << ITLEndl;
}

//--------------------------------------------------------------------------
void IGlue::msgReceived( const IMessage* msg, int status )
{
	trace(msg, status);
}


} // end namespoace

