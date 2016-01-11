
#include "MainWindow.h"

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QTimer>

#include <iostream>

#define DEFAULT_ADDRESS "127.0.0.1"
#define DEFAULT_PORT 7000

#define OUTPUT_BUFFER_SIZE 32000

//------------------------------------------------------------------------
void SendThread::run()
{
	QString address = fController->destination();
	int port = fController->port();
	UdpTransmitSocket transmitSocket( IpEndpointName( address.toStdString().c_str() , port ) );
	transmitSocket.allowBroadcast();
    
    char buffer[OUTPUT_BUFFER_SIZE];
	fRun = true;
	while(fRun) {
		for (int i = 0 ; i < fController->getMessageSize(); i++) {
			osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
			p << osc::BeginMessage( "/test" ) << fController->nextMessage();
			p << osc::EndMessage;
			transmitSocket.Send( p.Data(), p.Size() );
		}
		msleep(fController->getWait());
	}
}

//------------------------------------------------------------------------
ControllerWidget::ControllerWidget(QWidget *parent)
	 : QWidget(parent), mSender(0), fMessageNumber(0)
{
	setupUi(this);
	connect( mStart, SIGNAL(clicked()) , this , SLOT(start()) );
	connect( mStop, SIGNAL(clicked()) , this , SLOT(stop()) );
	connect( mInit, SIGNAL(clicked()) , this , SLOT(initNumber()) );
	mStop->setEnabled (false);

	QSettings settings;
	mPortLineEdit->setValue(settings.value("port", DEFAULT_PORT).toInt());
	mAddressLineEdit->setText(settings.value("address", DEFAULT_ADDRESS).toString());
	mWait->setValue(settings.value("wait", 5).toInt());
	mMessageSize->setValue(settings.value("count", 10).toInt());
}

//------------------------------------------------------------------------
ControllerWidget::~ControllerWidget()
{
	QSettings settings;
    settings.setValue("port", mPortLineEdit->value());
    settings.setValue("address", destination());
    settings.setValue("wait", getWait());
    settings.setValue("count", getMessageSize());
}

//------------------------------------------------------------------------
QString ControllerWidget::destination () const
{
	QString address = mAddressLineEdit->text();
	if( address.isEmpty())
		address = DEFAULT_ADDRESS;
	return address;
}

//------------------------------------------------------------------------
int ControllerWidget::port () const
{
	return mPortLineEdit->value();
}

//------------------------------------------------------------------------
void ControllerWidget::start()
{
	mSender = new SendThread(this);
	mSender->start();
	mStart->setEnabled (false);
	mStop->setEnabled (true);
}

//------------------------------------------------------------------------
void ControllerWidget::stop()
{
	if(mSender) {
		mSender->stop();
		delete mSender;
		mSender = 0;
		mStart->setEnabled (true);
		mStop->setEnabled (false);
	}
}

//------------------------------------------------------------------------
void ControllerWidget::initNumber()		{ fMessageNumber = 0; }
int ControllerWidget::nextMessage()		{ return fMessageNumber++; }
int ControllerWidget::getWait()			{ return mWait->value(); }
int ControllerWidget::getMessageSize()	{ return mMessageSize->value(); }

//------------------------------------------------------------------------
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags ) 
	:	QMainWindow ( parent , flags )
{
	QCoreApplication::setOrganizationName("GRAME");
    QCoreApplication::setOrganizationDomain("QtOSCSender");
	
	QSettings settings;
	resize(settings.value("size", QSize(100, 100)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	
	ControllerWidget* widget = new ControllerWidget(this);
	setCentralWidget(widget);
}

//------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	QSettings settings;

    settings.setValue("size", size());
    settings.setValue("pos", pos());
}
