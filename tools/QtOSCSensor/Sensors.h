#ifndef __Sensors__
#define __Sensors__

#include <QMainWindow>

#include <QVariant>
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
#include <string>


#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"

#include "Sensor.h"


#define OUTPUT_BUFFER_SIZE 1024

//------------------------------------------------------------------------
class OSCStream : public osc::OutboundPacketStream
{
	char fBuffer[OUTPUT_BUFFER_SIZE];
	
	public:
				 OSCStream() : osc::OutboundPacketStream(fBuffer, OUTPUT_BUFFER_SIZE) {}
		virtual ~OSCStream() {}
	
		void start(const char * addr)	{ *this << osc::BeginMessage( addr ); }
		void end()						{ *this << osc::EndMessage; }
};

//------------------------------------------------------------------------
class Sensors : public QObject
{
	Q_OBJECT
	UdpTransmitSocket* fSocket;

	void initSensors ();
	void destchge ();
	
	public:
		typedef std::map<int, Sensor*> TSensors;

		Q_INVOKABLE void activate(int index, bool state);
		Q_INVOKABLE bool available(int index);
		Q_INVOKABLE void destination(QString dest);
		Q_INVOKABLE void port(QString port);

				 Sensors();
		virtual ~Sensors();

		int port () const				{ return fPort; }
		QString destination () const	{ return fDestination; }
		void skipChge(int state);

	template <typename T>	void send (const char * addr, T value)
	{
		OSCStream p;
		p.start( addr );
		p << value;
		p.end();
		fSocket->Send( p.Data(), p.Size() );
	}

	protected:
		void timerEvent(QTimerEvent * );

	private:
		TSensors fSensors;
		int		 fTimerID;
		QString	 fDestination;
		int		 fPort;
};


#endif
