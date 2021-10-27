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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <stdexcept>
#include <iostream>
#include <condition_variable>

#include "EventsAble.h"
#include "GUIDOEngine.h"
#include "IAppl.h"
#include "IApplVNodes.h"
#include "IGlue.h"
#include "IMappingUpdater.h"
#include "IMessage.h"
#include "INScore.h"
#include "IScene.h"
#include "ISync.h"
#include "ITLError.h"
#include "Modules.h"
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

#ifdef EMCC
#define kDefaultRate	20
#else
#define kDefaultRate	10
#endif

//--------------------------------------------------------------------------
static void run (SINetListener listener)
{
	listener->run();
}

//--------------------------------------------------------------------------
void NetworkThread::start()
{
	if (fThread) stop();
	fThread = new std::thread (run, fListener);
}

//--------------------------------------------------------------------------
void NetworkThread::stop()
{
	if (fThread) {
		fListener->stop();
		fThread->join(); delete fThread; fThread = 0;
	}
}


//--------------------------------------------------------------------------
IGlue::IGlue(int udpport, int outport, int errport) 
	: fNetThread(0), fViewListener(0), fUDP(udpport, outport, errport)
{
	fLastTimeTask = 0;
}

IGlue::~IGlue()	{ clean(); }

//--------------------------------------------------------------------------
const IObject* IGlue::root () const  { return dynamic_cast<const IObject*>((IAppl*)fModel); }

//--------------------------------------------------------------------------
void IGlue::clean()
{
	delete fNetThread;
    fNetThread = 0;
#if HASOSCStream
	OSCStream::stop();
#endif
	fModel->getApplicatonGlue()->stopView();
}

//--------------------------------------------------------------------------
void IGlue::restart()
{
    try {
#if HASOSCStream
        if (!OSCStream::start())
            throw("Cannot initialize output udp streams");
#endif
        oscinit (fModel, fUDP);
        if (!fMsgStack || !fController || !fModel || !fNetThread)
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
#if HASOSCStream
			oscinit (udp.fInPort);
			oscinit (oscout, udp.fOutDstAddress, udp.fOutPort);
			oscinit (oscerr, udp.fErrDstAddress, udp.fErrPort);
#endif
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
	if (fNetThread) delete fNetThread;
	fNetThread = new NetworkThread(fMsgStack, fUDP.fInPort=port);
	if (fNetThread) fNetThread->start();
}

//--------------------------------------------------------------------------
void IGlue::oscinit (OSCStream& osc, const std::string& address, int port)
{
	osc.setPort(port);
	osc.setAddress(address);
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

#if QTView
	string address (fModel->getOSCAddress());
	address += "/scene";
	INScore::postMessage (address.c_str(), knew_SetMethod);
#endif

#ifdef __MOBILE__
	INScore::postMessage(address.c_str(), klock_GetSetMethod, 1);
#endif

	fTimeTask = fModel;
	if (!OSCStream::start())
		throw("Cannot initialize output udp streams");
	oscinit (fModel, fUDP);
	if (!fMsgStack || !fController || !fModel) // || !fNetThread)
		throw("Memory allocation failed!");
#if HASOSCStream
	oscerr.setLogWindow (fModel->getLogWindow());
	oscerr << "INScore v. " << INScore::versionStr() << " listening OSC on port " <<  fUDP.fInPort << OSCEnd();
	cout << "INScore v. " << INScore::versionStr() << " listening OSC on port " <<  fUDP.fInPort << endl;
#ifdef ANDROID
	qDebug() << "INSCORE v. " << INScore::versionStr().c_str() << " listening OSC on port " <<  fUDP.fInPort;
#endif
#elif defined(EMCC)
	string version ("INScore JS v. ");
	fModel->getLogWindow()->write (version + INScore::versionStr() + " beta");
#else
	cout << "INScore v. " << INScore::versionStr() << " compiled without OSC support" << endl;
#endif
	fModel->setRootPath ();

	// check Guido version
#ifndef EMCC
	if (GuidoCheckVersionNums(1, 6, 0) != guidoNoErr) {
#if HASOSCStream
		oscerr << OSCStart("Warning:") << "GUIDOEngine version >= 1.60 is required." << OSCEnd();
#endif
		cerr << "Warning: GUIDOEngine version >= 1.60 is required." << endl;
	}
#endif

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
//	if (fViewUpdater) {
//		fViewUpdater->update (fModel);	// force view update when updater changes
//									// otherwise the view won't be updated until the next incoming message
//									// see timerEvent method
//		fModel->cleanup();			// and clean the model
//	}
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
#if HASOSCStream
void IGlue::setOSCOut (int port) {	oscout.setPort(port); fUDP.fOutPort = port; }
void IGlue::setOSCOut (const std::string& a) { oscout.setAddress(a); fUDP.fOutDstAddress = a;  }
void IGlue::setOSCErr (int port) {	oscerr.setPort(port); fUDP.fErrPort = port; }
void IGlue::setOSCErr (const std::string& a) { oscerr.setAddress(a); fUDP.fErrDstAddress = a;  }
#else
void IGlue::setOSCOut (int port) 			 { }
void IGlue::setOSCOut (const std::string& a) { }
void IGlue::setOSCErr (int port) 			 { }
void IGlue::setOSCErr (const std::string& a) { }
#endif

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
#if HASOSCStream
	oscerr.activeConcatError(true);
#endif
	fController->processOn(fWebMsgStack, model);
#if HASOSCStream
	oscerr.activeConcatError(false);
#endif

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
//cerr << "delayed popped : " << *msgptr << endl;
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

