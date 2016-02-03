
#include "OSCListener.h"
#include "MainWindow.h"
#include <iostream>

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
}

//--------------------------------------------------------------------------
void OSCListener::ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& )
{
	osc::ReceivedMessageArgumentIterator i = m.ArgumentsBegin();
	if (i != m.ArgumentsEnd()) {
		if(i->IsInt32()) {
			fReceived++;
			fCurrentMessageNumber = i->AsInt32();
			int lost = fCurrentMessageNumber - fPreviousMessageNumber - 1;
			if((fPreviousMessageNumber >= 0) && lost) {
//				cerr << lost << " lost message(s)" << endl;
				fErrorCounter += lost;
			}
			fPreviousMessageNumber = fCurrentMessageNumber;
		}
		else if(i->IsString())
			cerr << "osc error: unexpected string argument" << endl;
		else
			cerr << "osc error: message argument is not a number" << endl;
	}
	else cerr << "osc error: message with no argument" << endl;
}

//------------------------------------------------------------------------
void OSCListener::refreshController()
{
	if (fReceived) {
		const float k = 0.7;
		if (fLastRefresh) {
			int flow = (fReceived - fLastRefresh) * (1000 / kTimeInterval);
			fMsgPerSec = fMsgPerSec ? int(k*flow + (1-k)*fMsgPerSec) : flow;
		}
		fLastRefresh = fReceived;
		long err = fErrorCounter*10000;
		long tot = fReceived + fErrorCounter;
        int iratio = fReceived ? err / tot : 0;
		float ratio = iratio / 100.f;
		fController->report (fReceived, fErrorCounter, ratio, fMsgPerSec);
	}
}
