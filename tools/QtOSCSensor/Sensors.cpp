
#include <vector>

#include <QPushButton>
#include <QSettings>
#include <QCoreApplication>
#include <QVBoxLayout>
#include <QTimer>
#include <QMessageBox>

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
Sensors::Sensors()
{
	initSensors();
	fDestination = DEFAULT_ADDRESS;
	fPort = DEFAULT_PORT;
	fSocket = new UdpTransmitSocket( IpEndpointName( destination().toStdString().c_str() , port() ) );
	fTimerID = startTimer(10);
}

//------------------------------------------------------------------------
Sensors::~Sensors()
{
	killTimer(fTimerID);
 	for (int i = Sensor::kSensorStart; i < Sensor::kSensorMax; i++) {
		delete fSensors[i];
	}
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
	if (dest.length()) fDestination = dest;
}

void Sensors::port(QString port)
{
	bool converted = false;
	unsigned int p = port.toUInt (&converted);
	if (converted) fPort = p;
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
}
