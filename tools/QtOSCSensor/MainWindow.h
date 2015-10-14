#ifndef __MainWindow__
#define __MainWindow__

#include <QMainWindow>

#include <QList>
#include <QVariant>
#include <QCheckBox>
#include <QTimer>

#include <QAccelerometer>
#include <QAltimeter>
#include <QAmbientLightSensor>
#include <QAmbientTemperatureSensor>
#include <QCompass>
#include <QDistanceSensor>
#include <QGyroscope>
#include <QHolsterSensor>
#include <QIRProximitySensor>
#include <QLightSensor>
#include <QMagnetometer>
#include <QOrientationSensor>
#include <QPressureSensor>
#include <QProximitySensor>
#include <QRotationSensor>
#include <QTapSensor>
#include <QTiltSensor>

#include <map>


#include "ui_sensorsWidget.h"
#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include "Sensor.h"


#define OUTPUT_BUFFER_SIZE 1024

class SensorWidget;
//------------------------------------------------------------------------
class SensorWatcher : public QTimer
{
	SensorWidget* fSensors;
//	int		flastOrientation, fLastALight;
//	float	fLastLight;
//	float	fLastAx, fLastAy, fLastAz;

	protected:
		virtual void	timerEvent(QTimerEvent * e);
	public:
				 SensorWatcher(SensorWidget* s) : fSensors(s) {}
		virtual ~SensorWatcher() {}
};


//------------------------------------------------------------------------
class SensorWidget : public QFrame, private Ui::Frame
{
     Q_OBJECT

	typedef struct {
		Sensor*		sensor;
		QCheckBox*	controler;
	} TSensorUI;
	typedef std::vector<TSensorUI> TSensors;

	SensorWatcher*	fWatcher;
	TSensors		fSensors;
	
	UdpTransmitSocket* fSocket;
	void initSensors ();
	void destchge ();
	void appendValue (osc::OutboundPacketStream& p, const char* value) const;
	void appendValue (osc::OutboundPacketStream& p, int value) const;
	void appendValue (osc::OutboundPacketStream& p, float value) const;
	
	public:
//		QAccelerometer*		fAccel;
//		QAltimeter *		fAltimeter;
//		QAmbientLightSensor* fAmbientLight;
//		QAmbientTemperatureSensor* fAmbientTemp;
//		QCompass *			fCompass;
//		QDistanceSensor*	fDistance;
//		QGyroscope*			fGyro;
//		QHolsterSensor*		fHolster;
//		QIRProximitySensor*	fIRProx;
//		QLightSensor*		fLight;
//		QMagnetometer*		fMagnet;
//		QOrientationSensor*	fOrient;
//		QPressureSensor*	fPressure;
//		QProximitySensor*	fProximity;
//		QRotationSensor*	fRotate;
//		QTapSensor *		fTap;
//		QTiltSensor *		fTilt;

				 SensorWidget(QWidget *parent = 0);
		virtual ~SensorWidget();

		int port () const;
		QString destination () const;
		void	sendAvailable ();

	template <typename T>	void send (const char * addr, T value)
	{
		char buffer[OUTPUT_BUFFER_SIZE];
		osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
		p << osc::BeginMessage( addr );
		appendValue (p, value);
		p << osc::EndMessage;
		fSocket->Send( p.Data(), p.Size() );
	}

	template <typename T>	void send (const char * addr, const char * msg, T value)
	{
		char buffer[OUTPUT_BUFFER_SIZE];
		osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
		p << osc::BeginMessage( addr ) << msg;
		appendValue (p, value);
		p << osc::EndMessage;
		fSocket->Send( p.Data(), p.Size() );
	}

	template <typename T>	void activate (T* sensor, const char * address, bool state) {
		if (state) {
			sensor->setActive(true);
			send(address, "on");
//			send(address, (int)sensor->connectToBackend());
			send(address, sensor->description().toStdString().c_str());
//			send(address, "range", sensor->outputRange());
		}
		else {
			sensor->setActive(false);
			send(address, "off");
		}
	}
	
	protected slots:
//		void distance();
//		void accel();
//		void gyro();
//		void magneto();
//		void orient();
//		void rotate();
//		void light();
//		void alight();
		void addressChge();
		void portChge(int i);
};


//------------------------------------------------------------------------
class MainWindow: public QMainWindow
{
	public:
		MainWindow ( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
		~MainWindow();

};

#endif
