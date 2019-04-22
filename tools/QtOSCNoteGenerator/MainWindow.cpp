
#ifdef WIN32
#include <windows.h>
#else
#include <unistd.h>
#endif // win32

#include <iostream>
#include <algorithm>

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QDebug>
#include <QTimer>

#include "MainWindow.h"
#include "OscException.h"
#include "OSCListener.h"
#include "TWallClock.h"
#include "OscOutboundPacketStream.h"


#define kDefaultPort	7400
#define kDefaultMin		-500
#define kDefaultMax		500
#define kDefaultRange	20
#define kDefaultTempo	60
#define kDefaultTimeout	1000
#define kDefaultAddress	"/orientation/roll"
#define kDefaultScore	"\\clef<\"g\"> "

using namespace std;

//------------------------------------------------------------------------
ControllerWidget::ControllerWidget(QWidget *parent)
	 : QWidget(parent)
{
	fOscThread = 0;
	setupUi(this);
	restore();
	init();
	restart();
	connect( mRestart , SIGNAL(clicked()) , this , SLOT(restart()) );
	connect( mState , SIGNAL(clicked()) , this , SLOT(chgeState()) );
	connect( mMin , SIGNAL(valueChanged(int)) , this , SLOT(chgeMin()) );
	connect( mMax , SIGNAL(valueChanged(int)) , this , SLOT(chgeMax()) );
	connect( mTempo , SIGNAL(valueChanged(int)) , this , SLOT(chgeTempo()) );
	connect( mTimeout , SIGNAL(valueChanged(int)) , this , SLOT(chgeTimeout()) );
	connect( mRange , SIGNAL(valueChanged(int)) , this , SLOT(chgeRange()) );
	fNotes[0] = "c";
	fNotes[1] = "c#";
	fNotes[2] = "d";
	fNotes[3] = "d#";
	fNotes[4] = "e";
	fNotes[5] = "f";
	fNotes[6] = "f#";
	fNotes[7] = "g";
	fNotes[8] = "g#";
	fNotes[9] = "a";
	fNotes[10] = "a#";
	fNotes[11] = "b";
}

//------------------------------------------------------------------------
void ControllerWidget::init ()
{
	fMin	= getMin();
	fMax	= getMax();
	fTempo	= getTempo();
	fRange	= getRange();
	fTimeout=getTimeout();
}

//------------------------------------------------------------------------
void ControllerWidget::restore ()
{
	QSettings settings;

	mPort->setValue(settings.value("port", kDefaultPort).toInt());
	mAddress->setText(settings.value("address", kDefaultAddress).toString());
	mScore->setPlainText(settings.value("score", kDefaultScore).toString());

	mMin->setValue(settings.value("min", kDefaultMin).toInt());
	mMax->setValue(settings.value("max", kDefaultMax).toInt());
	mAutoMin->setCheckState(settings.value("automin", false).toBool() ? Qt::Checked : Qt::Unchecked);
	mAutoMax->setCheckState(settings.value("automax", false).toBool() ? Qt::Checked : Qt::Unchecked);

	mRange->setValue(settings.value("range", kDefaultRange).toInt());
	mTempo->setValue(settings.value("tempo", kDefaultTempo).toInt());
	mTimeout->setValue(settings.value("timeout", kDefaultTimeout).toInt());
}

//------------------------------------------------------------------------
void ControllerWidget::save ()
{
	QSettings settings;

    settings.setValue("port", getPort());
    settings.setValue("address", getAddress());
    settings.setValue("score", getScore());
    settings.setValue("min", getMin());
    settings.setValue("max", getMax());
    settings.setValue("automin", getAutoMin());
    settings.setValue("automax", getAutoMax());
    settings.setValue("range", getRange());
    settings.setValue("tempo", getTempo());
    settings.setValue("timeout", getTimeout());
}

//------------------------------------------------------------------------
void ControllerWidget::restart()
{
	try {
		if (fOscThread) {
			fOscThread->stop();
			delete fOscThread;
			fOscThread = 0;
		}
		fOscThread = new OscThread(getPort(), this);
		fOscThread->start();
		mMsg->setText ("");
		setScore();
	}
	catch (osc::Exception e) {
		cerr << "Error: " << e.what() << endl;
		mMsg->setText (e.what());
	}
	catch (std::runtime_error e) {
		cerr << "Error: " << e.what() << endl;
		mMsg->setText (e.what());
	}
}

//------------------------------------------------------------------------
int ControllerWidget::getPort() const			{ return mPort->value(); }
QString ControllerWidget::getScore() const		{ return mScore->toPlainText(); }
QString ControllerWidget::getAddress() const	{ return mAddress->text(); }
int ControllerWidget::getMin() const			{ return mMin->value(); }
int ControllerWidget::getMax() const			{ return mMax->value(); }
int ControllerWidget::getTempo() const			{ return mTempo->value(); }
int ControllerWidget::getRange() const			{ return mRange->value(); }
int ControllerWidget::getTimeout() const		{ return mTimeout->value(); }

bool ControllerWidget::getAutoMin() const		{ return mAutoMin->isChecked(); }
bool ControllerWidget::getAutoMax() const		{ return mAutoMax->isChecked(); }

//------------------------------------------------------------------------
void ControllerWidget::chgeState()
{
	fRunning = mState->isChecked();
	if (!fRunning) fLastTime = 0;
}

#define mabs(v)	(( (v) >= 0) ? (v) : -(v))
//------------------------------------------------------------------------
string ControllerWidget::pitch2note (int pitch)
{
	int deg = pitch % 12;
	int oct = pitch / 12;
	return fNotes[deg] + to_string(oct-3);
}

//------------------------------------------------------------------------
string ControllerWidget::dur2symdur (float duration)
{
	int unit = 60000 / fTempo;
	int n = (duration / unit) * 8; 		// 32th notes
	n = std::max (1, std::min(128, n));
	return to_string( n) + "/32";
}


#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 7000

#define OUTPUT_BUFFER_SIZE 32000
const char* score = "/ITL/scene/score";

//------------------------------------------------------------------------
void ControllerWidget::setScore()	{ send (score, "set", "gmnstream", getScore().toStdString().c_str()); }

//------------------------------------------------------------------------
void ControllerWidget::send(const char* to, const char *msg, const char* type, const char* value)
{
	UdpTransmitSocket transmitSocket( IpEndpointName( DEFAULT_ADDRESS , DEFAULT_PORT ) );
    char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
	p << osc::BeginMessage( to ) << msg << type << value;
	p << osc::EndMessage;
	transmitSocket.Send( p.Data(), p.Size() );
}

//------------------------------------------------------------------------
void ControllerWidget::send(const char* to, const char *msg, const char* value)
{
	UdpTransmitSocket transmitSocket( IpEndpointName( DEFAULT_ADDRESS , DEFAULT_PORT ) );
    char buffer[OUTPUT_BUFFER_SIZE];
	osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
	p << osc::BeginMessage( to ) << msg << value;
	p << osc::EndMessage;
	transmitSocket.Send( p.Data(), p.Size() );
}

//------------------------------------------------------------------------
int ControllerWidget::val2midipitch (float value)
{
	int centerNote = 60;
	float norm = (value / mabs(float(fMax - fMin))) * fRange;
	return norm + centerNote;
}

//------------------------------------------------------------------------
void ControllerWidget::accept (float value, float duration)
{
	int midipitch = val2midipitch(value);
	cerr << "ControllerWidget::accept " << value << " dur " << duration << " => " << midipitch  << endl;

//	if (mabs(midipitch - fLastPitch) > 7) return;
	string note = pitch2note(midipitch) + "*" + dur2symdur(duration * 2);
	if (duration > fTimeout) setScore();
	send (score, "write", note.c_str());
	mMsg->setText (note.c_str());
}

//------------------------------------------------------------------------
void ControllerWidget::receive (float value)
{
	if (fRunning) {
		if (fLastTime) {
			if (mAutoMin->isChecked() &&  (value < fMin))
				mMin->setValue (fMin = (int)value);
			if (mAutoMax->isChecked() &&  (value > fMax))
				mMax->setValue (fMax = (int)value);
			float step = mabs(float(fMax - fMin) / fRange);
			float gap = mabs(value - fLastAccepted);
			if (gap >= step) {
				fLastAccepted = value;
				double now = TWallClock::time();
				accept (-value, now - fLastTime);
				fLastTime = now;
			}
		}
		else {
			fLastTime = TWallClock::time();
			fLastAccepted = value;
			fLastPitch = val2midipitch(value);
		}
	}
}

//------------------------------------------------------------------------
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags ) 
	:	QMainWindow ( parent , flags )
{
	QCoreApplication::setOrganizationName("GRAME");
    QCoreApplication::setOrganizationDomain("QtOSCNoteGenerator");
	
	QSettings settings;
	resize(settings.value("size", QSize(100, 100)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	 
	ControllerWidget * centralW = new ControllerWidget(this);
	setCentralWidget(centralW);
}

//------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	QSettings settings;

    settings.setValue("size", size());
    settings.setValue("pos", pos());
}
