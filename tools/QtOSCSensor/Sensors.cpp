
#include <vector>
#include <exception>
#include <iostream>

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>
#include <QSettings>

#include "Sensors.h"


using namespace std;

#define DEFAULT_ADDRESS "192.168.1.21"
//#define DEFAULT_ADDRESS "192.168.43.88"
#define DEFAULT_PORT 7001


//------------------------------------------------------------------------
void Sensors::timerEvent(QTimerEvent * )
{
	for (int i = Sensor::kSensorStart; i < Sensor::kSensorMax; i++) {
		Sensor* sensor = fSensors[i];
		if (sensor && sensor->active()) {
            int count = sensor->count();
            if (count) {
				OSCStream osc;
                osc.start( sensor->address());
                for (int i=0; i<count; i++)
                    osc << sensor->value(i);
                osc.end();
                fSocket->Send(osc.Data(), osc.Size());
            }
		}
	}
}

//------------------------------------------------------------------------
void Sensors::initSensors()
{
 	for (int i = Sensor::kSensorStart; i < Sensor::kSensorMax; i++) {
		fSensors[i] = new Sensor(i);
	}
}

//------------------------------------------------------------------------
Sensors::Sensors() : fTimerID(0)
{
	fUIRoot = 0;
	initSensors();
	fDestination = DEFAULT_ADDRESS;
	fPort = DEFAULT_PORT;
	try {
		fSocket = new UdpTransmitSocket( IpEndpointName( destination().toStdString().c_str() , port() ) );
		fTimerID = startTimer(10);
	}
	catch(std::exception e) {
		fSocket = 0;
	}
}

//------------------------------------------------------------------------
Sensors::~Sensors()
{
	QSettings settings;

    settings.setValue("port", port());
    settings.setValue("dest", destination());

	killTimer(fTimerID);
 	for (int i = Sensor::kSensorStart; i < Sensor::kSensorMax; i++) {
		delete fSensors[i];
	}
}

//------------------------------------------------------------------------
void Sensors::start(QObject* o)
{
	fUIRoot = o;

	QSettings settings;
	port(settings.value("port", DEFAULT_PORT).toString());
	destination (settings.value("dest", DEFAULT_ADDRESS).toString());
}

//------------------------------------------------------------------------
// Q_INVOKABLE methods
//------------------------------------------------------------------------
void Sensors::activate(int index, bool state)
{
	Sensor* s = fSensors[index];
	if (s) s->activate(state);
	else if (index == Sensor::kSensorMax)
		skipChge(state);
}

bool Sensors::available(int index)
{
	Sensor* s = fSensors[index];
	if (s) return s->available();
	return (index == Sensor::kSensorMax);
}

void Sensors::destination(QString dest)
{
	if (dest.length()) {
		fDestination = dest;
		destchge();
	}
}

void Sensors::port(QString port)
{
	bool converted = false;
	unsigned int p = port.toUInt (&converted);
	if (converted) {
		fPort = p;
		destchge();
	}
}

//------------------------------------------------------------------------
void Sensors::skipChge(int state)
{
 	for (int i = Sensor::kSensorStart; i < Sensor::kSensorMax; i++) {
		Sensor* s = fSensors[i];
		if (s) s->skipDuplicates (state);
    }
}

//------------------------------------------------------------------------
void Sensors::destchge()
{
	UdpTransmitSocket* socket = new UdpTransmitSocket( IpEndpointName( destination().toStdString().c_str() , port() ) );
	UdpTransmitSocket* tmp = fSocket;
	fSocket = socket;
	delete tmp;
	if (fUIRoot) {
		fUIRoot->setProperty("port", port());
		fUIRoot->setProperty("address", destination());
	}
}
