#ifndef __Sensor__
#define __Sensor__

#include <map>
#include <vector>

class QSensor;
class QSensorReading;

//------------------------------------------------------------------------
class Sensor
{
	private:
		QSensor*		fSensor;
		int				fType;
		QSensorReading*	fReader;

		void			init();
		QSensor*		create(int type) const;
	
		static std::map<int, const char*>	fOSC;
		static std::map<int, const char*>	fNames;
	
	public:
		enum  { kSensorStart, kAccelerometer=0, kAltimeter, kAmbientLight, kAmbientTemperature, kCompass, kDistance, kGyroscope, kHolster, kIRProximity, kLight, kMagnetometer, kOrientation, kPressure, kProximity, kRotation, kTap, kTilt, kSensorMax };

				 Sensor(int type);
		virtual ~Sensor();

		const char*		name() const		{ return fNames[fType]; }
		const char*		address() const		{ return fOSC[fType]; }
		QSensor*		sensor()			{ return fSensor; }
		bool			available() const	{ return fSensor->isConnectedToBackend(); }
		bool			active() const		{ return fSensor->isActive(); }
		void			activate(bool state);
		int				count() const		{ return fReader ? fReader->valueCount() : 0; }
		float			value(int i) const	{ return fReader->value(i).value<float>(); }
		void			skipDuplicates(bool state)	{ fSensor->setSkipDuplicates(state); }
};


#endif
