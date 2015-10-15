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
class SensorWidget : public QFrame, private Ui::Frame
{
	Q_OBJECT

//	SensorWatcher*	fWatcher;
	UdpTransmitSocket* fSocket;

	void initSensors ();
	void destchge ();
	void appendValue (osc::OutboundPacketStream& p, const char* value) const;
	void appendValue (osc::OutboundPacketStream& p, int value) const;
	void appendValue (osc::OutboundPacketStream& p, float value) const;
	
	public:
		typedef struct {
			Sensor*		sensor;
			QCheckBox*	controler;
		} TSensorUI;
		typedef std::vector<TSensorUI> TSensors;

				 SensorWidget(QWidget *parent = 0);
		virtual ~SensorWidget();

		int port () const;
		QString destination () const;
		void	sendAvailable ();

	template <typename T>	void send (const char * addr, T value)
	{
		OSCStream p;
		p.start( addr );
		p << value;
		p.end();
		fSocket->Send( p.Data(), p.Size() );
	}

	private:
		TSensors fSensors;
		int		 fTimerID;
	
	protected slots:
		void addressChge();
		void portChge(int i);
		void timerEvent(QTimerEvent * e);
};

//------------------------------------------------------------------------
class MainWindow: public QMainWindow
{
	public:
		MainWindow ( QWidget * parent = 0, Qt::WindowFlags flags = 0 );
		~MainWindow();

};

#endif
