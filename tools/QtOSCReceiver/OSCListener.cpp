#include "OSCListener.h"
#include "MainWindow.h"
#include <iostream>

using namespace std;

//--------------------------------------------------------------------------
OSCListener::OSCListener(int port, ControllerWidget * controller)
		: QObject(0),
		  fSocket(IpEndpointName( IpEndpointName::ANY_ADDRESS, port ), this), fRunning(false),
		  fCurrentMessageNumber(0), fPreviousMessageNumber(-1), fErrorCounter(0),
		  fController(controller)
{
	refresh.setInterval(1000);
	connect(&refresh, SIGNAL(timeout()), this, SLOT(refreshController()));
	refresh.start();
}

//--------------------------------------------------------------------------
OSCListener::~OSCListener()	{ stop(); }

//--------------------------------------------------------------------------
void OSCListener::run()
{
	fRunning = true;
	try {
			fSocket.Run();
		}
		catch (osc::Exception e) {
			cerr << "osc error: " << e.what() << endl;
		}
	fRunning = false;
}

//--------------------------------------------------------------------------
void OSCListener::stop()
{
	fSocket.AsynchronousBreak();
}

//--------------------------------------------------------------------------
void OSCListener::ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& )
{
	osc::ReceivedMessageArgumentIterator i = m.ArgumentsBegin();
	if (i != m.ArgumentsEnd()) {
		if(i->IsString()) {
			QString str(i->AsStringUnchecked());
			fCurrentMessageNumber = str.toULong();
			//fCurrentMessageNumber = i->AsInt32Unchecked();
			if(fCurrentMessageNumber != fPreviousMessageNumber + 1) {
				cerr << "osc error: message number is not previous number  + 1" << endl;
				// Increment error
				fErrorCounter++;
			}
			fPreviousMessageNumber = fCurrentMessageNumber;
		} else {
			cerr << "osc error: message argument is not a number" << endl;
			// Increment error
			fErrorCounter++;
		}
	} else {
		cerr << "osc error: message with no argument" << endl;
		// Increment error
		fErrorCounter++;
	}
}

//------------------------------------------------------------------------
void OSCListener::refreshController()
{
	fController->setLastMessage(fCurrentMessageNumber);
	fController->setError(fErrorCounter);
}
