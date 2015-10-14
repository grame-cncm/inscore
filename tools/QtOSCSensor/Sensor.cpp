
#include <iostream>

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

#include "Sensor.h"

using namespace std;

const char * kAccelAddress	= "/accelerometer";
const char * kAltiAddress	= "/altimeter";
const char * kALightAddress	= "/ambientlight";
const char * kCompassAddress= "/compass";
const char * kATempAddress	= "/ambienttemperature";
const char * kDistAddress	= "/distance";
const char * kGyroAddress	= "/gyroscope";
const char * kHolsterAddress= "/holster";
const char * kIRProxAddress = "/irproximity";
const char * kLightAddress	= "/light";
const char * kMagnetAddress	= "/magnetometer";
const char * kOrientAddress	= "/orientation";
const char * kPressAddress	= "/pressure";
const char * kProxAddress	= "/proximity";
const char * kRotateAddress	= "/rotation";
const char * kTapAddress	= "/tap";
const char * kTiltAddress	= "/tilt";

map<int, const char*>	Sensor::fOSC;
map<int, const char*>	Sensor::fNames;


//------------------------------------------------------------------------
Sensor::Sensor (int type)
{
	init();
	fSensor = create (type);
	fType = type;
	fSensor->connectToBackend();
}

//------------------------------------------------------------------------
Sensor::~Sensor ()
{
	delete fSensor;
}

//------------------------------------------------------------------------
void Sensor::init ()
{
	if (fOSC.empty()) {
		fOSC[kAccelerometer]		= kAccelAddress;
		fOSC[kAltimeter]			= kAltiAddress;
		fOSC[kAmbientLight]			= kALightAddress;
		fOSC[kAmbientTemperature]	= kATempAddress;
		fOSC[kCompass]				= kCompassAddress;
		fOSC[kDistance]				= kDistAddress;
		fOSC[kGyroscope]			= kGyroAddress;
		fOSC[kHolster]				= kHolsterAddress;
		fOSC[kIRProximity]			= kIRProxAddress;
		fOSC[kLight]				= kLightAddress;
		fOSC[kMagnetometer]			= kMagnetAddress;
		fOSC[kOrientation]			= kOrientAddress;
		fOSC[kPressure]				= kPressAddress;
		fOSC[kProximity]			= kProxAddress;
		fOSC[kRotation]				= kRotateAddress;
		fOSC[kTap]					= kTapAddress;
		fOSC[kTilt]					= kTiltAddress;
	}
//	if (fNames.empty()) {
//		fNames[kAccelerometer]			= "Accelerometer;
//		fNames[kAltimeter]		= "Atlimeter";
//		fNames[kAmbientLight]	= "Ambient Light";
//		fNames[kAmbientTemperature]	= "Ambient temp.";
//		fNames[kCompass]		= "Compass";
//		fNames[kDistance]		= "Distance";
//		fNames[kGyro]			= "Gyroscope";
//		fNames[kHolster]		= "Holster;
//		fNames[kIRProx]			= "IR Proximity";
//		fNames[kLight]			= "Light";
//		fNames[kMagnet]			= "Magnetometer";
//		fNames[kOrient]			= "Orientation";
//		fNames[kPressure]		= "Pressure";
//		fNames[kProximity]		= "Proximity";
//		fNames[kRotate]			= "Rotation";
//		fNames[kTap]			= "Tap";
//		fNames[kTilt]			= "Tilt";
//	}
}

//------------------------------------------------------------------------
QSensor* Sensor::create (int type) const
{
	switch (type) {
		case kAccelerometer:		return new QAccelerometer();
		case kAltimeter:			return new QAltimeter();
		case kAmbientLight:			return new QAmbientLightSensor();
		case kAmbientTemperature:	return new QAmbientTemperatureSensor();
		case kCompass:				return new QCompass();
		case kDistance:				return new QDistanceSensor();
		case kGyroscope:			return new QGyroscope();
		case kHolster:				return new QHolsterSensor();
		case kIRProximity:			return new QIRProximitySensor();
		case kLight:				return new QLightSensor();
		case kMagnetometer:			return new QMagnetometer();
		case kOrientation:			return new QOrientationSensor();
		case kPressure:				return new QPressureSensor();
		case kProximity:			return new QProximitySensor();
		case kRotation:				return new QRotationSensor();
		case kTap:					return new QTapSensor();
		case kTilt:					return new QTiltSensor();
		default:
			cerr << "unknown sensor type " << type << endl;
			return 0;
	}
}
