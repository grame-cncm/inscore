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

#define OUTPUT_BUFFER_SIZE 2048

#define DEBUG

//------------------------------------------------------------------------
void OSCMessage::send( const std::string& str , int port ) const
{
	UdpTransmitSocket transmitSocket( IpEndpointName( str.c_str() , port ) );
    
    char buffer[OUTPUT_BUFFER_SIZE];
    osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );

#if 1
//	p << osc::BeginBundleImmediate
//		<< osc::BeginMessage( mAddress.c_str() ) << mCommand.c_str();
	p << osc::BeginMessage( mAddress.c_str() ) << mCommand.c_str();

	for ( int i = 0 ; i < mValues.size() ; i++ )
	{
		QVariant::Type t = mValues[i].type();
		if ( t == QVariant::Int )
			p << mValues[i].toInt();
		else if ( t == QVariant::Double )
			p << float(mValues[i].toDouble());
		else
			p << mValues[i].toString().toAscii().data();
	}
	p << osc::EndMessage;
//	p << osc::EndMessage << osc::EndBundle;
#else
	std::cout << "Sending: " << mAddress << " " << mCommand;

	p << osc::BeginBundleImmediate
		<< osc::BeginMessage( mAddress.c_str() ) << mCommand.c_str();

	for ( int i = 0 ; i < mValues.size() ; i++ )
	{
		QVariant::Type t = mValues[i].type();
		if ( t == QVariant::Int )
		{
			p << mValues[i].toInt();
			std::cout << " " << mValues[i].toInt();
		}
		else if ( t == QVariant::Double )
		{
			p << float(mValues[i].toDouble());
			std::cout << " " << mValues[i].toDouble();
		}
		else if ( t == QVariant::String )
		{
			p << mValues[i].toString().toAscii().data();
			std::cout << " " << mValues[i].toString().toAscii().data();
		}
		else std::cout << " ===> type inconnu !! " ;

	}
	p << osc::EndMessage << osc::EndBundle;
	
	std::cout << std::endl;
#endif
    transmitSocket.Send( p.Data(), p.Size() );

}

//------------------------------------------------------------------------
ControllerWidget::ControllerWidget(QWidget *parent)
     : QWidget(parent), mAddress(DEFAULT_ADDRESS), mPort(DEFAULT_PORT)
{
	setupUi(this);
	
	mRotateAllTimer = new QTimer(this);
	mRotateAllTimer->setInterval( 20 );
    connect(mRotateAllTimer, SIGNAL(timeout()), this, SLOT(rotateAll()));
	connect( mRotateAll , SIGNAL(toggled(bool)) , this , SLOT(rotateAllToggled(bool)) );
	
	connect( mQuit , SIGNAL(clicked()) , this , SLOT(ITLQuit()) );
	connect( mReset , SIGNAL(clicked()) , this , SLOT(ITLReset()) );
	connect( mScene1 , SIGNAL(clicked()) , this , SLOT(scene1()) );
}

//------------------------------------------------------------------------
void ControllerWidget::ITLQuit()
{
	send( OSCMessage("/ITL").setCommand("quit") );
}

//------------------------------------------------------------------------
void ControllerWidget::ITLReset()
{
	send( OSCMessage("/ITL/scene").setCommand("reset") );
}

#define RECT_NUM 10
//------------------------------------------------------------------------
void ControllerWidget::scene1()
{
	int size = mScene1Int->value();
	if (!size) return;

	float fsize = float(size);
	const float base = 1.5;
	float rsize = base / fsize;
	float step = rsize + 0.5/fsize;
	float x = 0 - (step * (size-1))/2;
	float x0 =x, y = x;
	for ( int i = 0 ; i < size ; i++ )
	{
		for ( int j = 0 ; j < size ; j++ )
		{
			std::string rectName = QString( "/ITL/scene/rect" + QVariant( i*size + j ).toString() ).toStdString();
			send( OSCMessage( rectName ).setCommand("set").addString("rect").addFloat(rsize).addFloat(rsize) );
//			send( OSCMessage( rectName ).setCommand("x").addFloat( 2*i/float(size) - (1.f/size) ) );
//			send( OSCMessage( rectName ).setCommand("y").addFloat( 2*j/float(size) - (1.f/size) ) );
			send( OSCMessage( rectName ).setCommand("x").addFloat( x ) );
			send( OSCMessage( rectName ).setCommand("y").addFloat( y ) );
			x += step;
		}
		x = x0;
		y += step;
	}	
}

//------------------------------------------------------------------------
void ControllerWidget::rotateAll()
{
	send( OSCMessage( QString("/ITL/scene/" + fRotateEdit->text()).toAscii().data()  ).setCommand("dangle").addFloat( 1 ) );
}

//------------------------------------------------------------------------
void ControllerWidget::rotateAllToggled(bool toggled)
{
	if ( toggled )
		mRotateAllTimer->start();
	else
		mRotateAllTimer->stop();
}

//------------------------------------------------------------------------
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags ) 
	:	QMainWindow ( parent , flags )
{
	QCoreApplication::setOrganizationName("GRAME");
    QCoreApplication::setOrganizationDomain("QtController");
	
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
