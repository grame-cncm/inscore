
#include <iostream>
#include <QString>

#include "OSCListener.h"
#include "MainWindow.h"

using namespace std;

#define kTimeInterval	250
//--------------------------------------------------------------------------
OSCListener::OSCListener(int port, ControllerWidget * controller)
		: QObject(0),
		  fSocket(IpEndpointName( IpEndpointName::ANY_ADDRESS, port ), this), fRunning(false), fReceived(0),
		  fCurrentMessageNumber(0), fPreviousMessageNumber(-1), fErrorCounter(0), fLastRefresh(0),
		  fController(controller)
{
	refresh.setInterval(kTimeInterval);
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
	fRunning = false;
}

//--------------------------------------------------------------------------
void OSCListener::ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& )
{
	if (!fRunning ) return;

	QString address = m.AddressPattern();
	if (address == fController->getAddress()) {
		osc::ReceivedMessageArgumentIterator i = m.ArgumentsBegin();
		if (i != m.ArgumentsEnd()) {
			if(i->IsInt32())
				fController->receive(float(i->AsInt32()));
			else if(i->IsFloat())
				fController->receive(i->AsFloat());
			else
				cerr << "osc error: message argument is not a number" << endl;
		}
	}
}

//------------------------------------------------------------------------
void OSCListener::refreshController()
{
	if (fReceived) {
//		fController->report (fReceived, fErrorCounter, ratio, fMsgPerSec);
	}
}
