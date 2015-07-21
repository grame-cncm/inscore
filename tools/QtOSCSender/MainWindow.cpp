
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

#define OUTPUT_BUFFER_SIZE 16384

//------------------------------------------------------------------------
void OSCMessage::send( const std::string& str , int port ) const
{
	UdpTransmitSocket transmitSocket( IpEndpointName( str.c_str() , port ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

	p << osc::BeginMessage( mAddress.c_str() ) << mCommand.c_str();

	for ( int i = 0 ; i < mValues.size() ; i++ )
	{
		QVariant::Type t = mValues[i].type();
		if ( t == QVariant::Int )
			p << int(mValues[i].toInt());
		else if ( t == QVariant::Double )
			p << float(mValues[i].toDouble());
		else
			p << mValues[i].toString().toUtf8().data();
	}
	p << osc::EndMessage;
    transmitSocket.Send( p.Data(), p.Size() );
}

//------------------------------------------------------------------------
void SendThread::run()
{
	QString address = fController->destination();
	int port = fController->port();
	UdpTransmitSocket transmitSocket( IpEndpointName( address.toStdString().c_str() , port ) );
    
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
	mAddressLineEdit->setText(DEFAULT_ADDRESS);
	mPortLineEdit->setValue(DEFAULT_PORT);
}

//------------------------------------------------------------------------
void ControllerWidget::send( const OSCMessage& msg ) const
{
	QString address = mAddressLineEdit->text();
	if( address.isEmpty())
		address = DEFAULT_ADDRESS;

	msg.send( address.toStdString() , mPortLineEdit->value() );
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
}

//------------------------------------------------------------------------
void ControllerWidget::stop()
{
	if(mSender) {
		mSender->stop();
		delete mSender;
		mSender = 0;
	}
}

//------------------------------------------------------------------------
void ControllerWidget::initNumber()
{
	fMessageNumber = 0;
}

//------------------------------------------------------------------------
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
