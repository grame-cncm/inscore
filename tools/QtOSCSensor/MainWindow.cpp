
#include "MainWindow.h"

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>

#include <QAccelerometerReading>


#define DEFAULT_ADDRESS "192.168.1.21"
#define DEFAULT_PORT 7001



void SensorWatcher::timerEvent(QTimerEvent * )
{
//	if (fSensors->fAccel->isActive()) {
//		QAccelerometerReading *	r = fSensors->fAccel->reading();
//		float x =  (float)r->x();
//		float y =  (float)r->y();
//		float z =  (float)r->z();
//		if ((x != fLastAx) || (y != fLastAy) || (z != fLastAz)) {
//			fSensors->send(kAccelAddress, "x", fLastAx = x);
//			fSensors->send(kAccelAddress, "y", fLastAy = y);
//			fSensors->send(kAccelAddress, "z", fLastAz = z);
//		}
//	}
//
//	if (fSensors->fGyro->isActive()) {
//	}
//
//	if (fSensors->fLight->isActive()) {
//		QLightReading* r = fSensors->fLight->reading();
//		float val =  (float)r->lux();
//		if (val != fLastLight)
//			fSensors->send(kLightAddress, "lux", fLastLight=val);
//	}
//
//	if (fSensors->fAmbientLight->isActive()) {
//		QAmbientLightReading* r = fSensors->fAmbientLight->reading();
//		int val =  (float)r->lightLevel();
//		if (val != fLastALight)
//			fSensors->send(kLightAddress, "level", fLastALight=val);
//	}
//
//	if (fSensors->fMagnet->isActive()) {
//	}
//
//	if (fSensors->fOrient->isActive()) {
//		QOrientationReading * r = fSensors->fOrient->reading();
//		int val = r->orientation();
//		if (val != flastOrientation)
//			fSensors->send(kOrientAddress, "orientation", flastOrientation = val);
//	}
//
//	if (fSensors->fDistance->isActive()) {
//	}
//
//	if (fSensors->fRotate->isActive()) {
//	}
}


//------------------------------------------------------------------------
void SensorWidget::initSensors()
{
	int avail = 0;
	for (int t = Sensor::kSensorStart; t < Sensor::kSensorMax; t++) {
		TSensorUI ui;
		ui.sensor = new Sensor(t);
		if (ui.sensor->available()) {
			QCheckBox* ctrl = new QCheckBox(verticalLayoutWidget);
			ctrl->setObjectName(ui.sensor->name());
			QSizePolicy sizePolicy(QSizePolicy::Minimum, QSizePolicy::Expanding);
			sizePolicy.setHorizontalStretch(0);
			sizePolicy.setVerticalStretch(0);
			sizePolicy.setHeightForWidth(ctrl->sizePolicy().hasHeightForWidth());
			ctrl->setSizePolicy(sizePolicy);
			verticalLayout->addWidget(ctrl, 0, Qt::AlignVCenter);
//			ctrl->setText(QApplication::translate("Frame", ui.sensor->name(), 0));
			ctrl->setText(ui.sensor->name());
			ui.controler = ctrl;
			avail++;
		}
		else ui.controler = 0;
		fSensors.push_back(ui);
	}
	if (!avail) {
		QMessageBox alert(QMessageBox::Information, "Sensors", "No sensor available", QMessageBox::Ok, this);
		alert.exec();
	}
}

//------------------------------------------------------------------------
SensorWidget::SensorWidget(QWidget *parent) : QFrame(parent)
{
	setupUi(this);
	initSensors();

//	fAccel			= new QAccelerometer();
//	fAltimeter		= new QAltimeter();
//	fAmbientLight	= new QAmbientLightSensor();
//	fAmbientTemp	= new QAmbientTemperatureSensor();
//	fCompass		= new QCompass();
//	fDistance		= new QDistanceSensor();
//	fGyro			= new QGyroscope();
//	fHolster		= new QHolsterSensor();
//	fIRProx			= new QIRProximitySensor();
//	fLight			= new QLightSensor();
//	fMagnet			= new QMagnetometer();
//	fOrient			= new QOrientationSensor();
//	fPressure		= new QPressureSensor();
//	fProximity		= new QProximitySensor();
//	fRotate			= new QRotationSensor();
//	fTap			= new QTapSensor();
//	fTilt			= new QTiltSensor();
//
//	fSensors[fAccel]		= kAccelAddress;
//	fSensors[fAltimeter]	= kAltiAddress;
//	fSensors[fAmbientLight]	= kALightAddress;
//	fSensors[fAmbientTemp]	= kATempAddress;
//	fSensors[fCompass]		= kCompassAddress;
//	fSensors[fDistance]		= kDistAddress;
//	fSensors[fGyro]			= kGyroAddress;
//	fSensors[fHolster]		= kHolsterAddress;
//	fSensors[fIRProx]		= kIRProxAddress;
//	fSensors[fLight]		= kLightAddress;
//	fSensors[fMagnet]		= kMagnetAddress;
//	fSensors[fOrient]		= kOrientAddress;
//	fSensors[fPressure]		= kPressAddress;
//	fSensors[fProximity]	= kProxAddress;
//	fSensors[fRotate]		= kRotateAddress;
//	fSensors[fTap]			= kTapAddress;
//	fSensors[fTilt]			= kTiltAddress;

	
	fWatcher = new SensorWatcher (this);
	fWatcher->start(100);

//	connect( fAccelState,	SIGNAL(clicked()) , this , SLOT(accel()) );
//	connect( fLightState,	SIGNAL(clicked()) , this , SLOT(light()) );
//	connect( fRotState,		SIGNAL(clicked()) ,	this , SLOT(rotate()) );
//	connect( fOrientState,	SIGNAL(clicked()) , this , SLOT(orient()) );
//	connect( fGyroState,	SIGNAL(clicked()) , this , SLOT(gyro()) );
//	connect( fMagnetState,	SIGNAL(clicked()) , this , SLOT(magneto()) );
//	connect( fDistState,	SIGNAL(clicked()) , this , SLOT(distance()) );
//	connect( fALightState,	SIGNAL(clicked()) , this , SLOT(alight()) );

	connect( mAddressLineEdit,	SIGNAL(editingFinished()) , this , SLOT(addressChge()) );
	connect( mPortLineEdit,	SIGNAL(valueChanged(int)) , this , SLOT(portChge(int)) );

	fSocket = new UdpTransmitSocket( IpEndpointName( destination().toStdString().c_str() , port() ) );
	QSettings settings;
	mPortLineEdit->setValue(settings.value("port", DEFAULT_PORT).toInt());
	mAddressLineEdit->setText(settings.value("address", DEFAULT_ADDRESS).toString());
	sendAvailable();
}

//------------------------------------------------------------------------
void SensorWidget::sendAvailable ()
{
	for (TSensors::const_iterator i = fSensors.begin(); i != fSensors.end(); i++) {
		if (i->sensor->available())
			send(i->sensor->address(), "available");
	}
}

//------------------------------------------------------------------------
SensorWidget::~SensorWidget()
{
	for (size_t i = 0; i < fSensors.size(); i++)
		delete fSensors[i].sensor;
	QSettings settings;
    settings.setValue("port", mPortLineEdit->value());
    settings.setValue("address", destination());
	fWatcher->stop();
}

//------------------------------------------------------------------------
QString SensorWidget::destination () const
{
	QString address = mAddressLineEdit->text();
	if( address.isEmpty())
		address = DEFAULT_ADDRESS;
	return address;
}

//------------------------------------------------------------------------
void SensorWidget::appendValue (osc::OutboundPacketStream& p, const char* value) const	{ p << value; }
void SensorWidget::appendValue (osc::OutboundPacketStream& p, int value) const			{ p << value; }
void SensorWidget::appendValue (osc::OutboundPacketStream& p, float value) const		{ p << value; }

//------------------------------------------------------------------------
void SensorWidget::destchge()
{
	UdpTransmitSocket* socket = new UdpTransmitSocket( IpEndpointName( destination().toStdString().c_str() , port() ) );
	UdpTransmitSocket* tmp = fSocket;
	fSocket = socket;
	delete tmp;
}

//------------------------------------------------------------------------
void SensorWidget::addressChge()	{ destchge(); }
void SensorWidget::portChge(int)	{ destchge(); }

//------------------------------------------------------------------------
int SensorWidget::port () const
{
	return mPortLineEdit->value();
}

//------------------------------------------------------------------------
//void SensorWidget::accel()		{ activate(fAccel, kAccelAddress, fAccelState->checkState() ? true : false); }
//void SensorWidget::gyro()		{ activate(fGyro, kGyroAddress, fGyroState->checkState() ? true : false); }
//void SensorWidget::magneto()	{ activate(fMagnet, kMagnetAddress, fMagnetState->checkState() ? true : false);}
//void SensorWidget::orient()		{ activate(fOrient, kOrientAddress, fOrientState->checkState() ? true : false); }
//void SensorWidget::rotate()		{ activate(fRotate, kRotateAddress, fRotState->checkState() ? true : false); }
//void SensorWidget::light()		{ activate(fLight, kLightAddress, fLightState->checkState() ? true : false); }
//void SensorWidget::alight()		{ activate(fAmbientLight, kALightAddress, fALightState->checkState() ? true : false); }
//void SensorWidget::distance()	{ activate(fDistance, kDistAddress, fDistState->checkState() ? true : false); }


//------------------------------------------------------------------------
MainWindow::MainWindow(QWidget * parent, Qt::WindowFlags flags ) 
	:	QMainWindow ( parent , flags )
{
	QCoreApplication::setOrganizationName("GRAME");
    QCoreApplication::setOrganizationDomain("QtOSCSensor");
	
	QSettings settings;
	resize(settings.value("size", QSize(100, 100)).toSize());
	move(settings.value("pos", QPoint(200, 200)).toPoint());
	
	SensorWidget* widget = new SensorWidget(this);
	setCentralWidget(widget);
}

//------------------------------------------------------------------------
MainWindow::~MainWindow()
{
	QSettings settings;

    settings.setValue("size", size());
    settings.setValue("pos", pos());
}
