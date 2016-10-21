/*

  INScore Project

  Copyright (C) 2016  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>
#include <cmath>

#include <QAccelerometer>
#include <QAccelerometerReading>

#include "IAccelerometer.h"
#include "INScore.h"


#ifdef SENSORDEBUG
#include <stdlib.h>
#endif


using namespace std;

namespace inscore
{

static const double gForce = 9.81;
const string IAccelerometer::kAccelerometerType = "accelerometer";

QAccelerometer*	IAccelerometer::fAccelerometer = 0;
int				IAccelerometer::fAccelerometerRefCount = 0;
int				IAccelerometer::fActives = 0;

//------------------------------------------------------------------------
IAccelerometer::IAccelerometer(const std::string& name, IObject * parent)
	: ISensor (name, parent)
{
	fTypeString = kAccelerometerType;
	fCalibration = gForce;
	fCalibrating = false;
	if (!fAccelerometer)
		fAccelerometer = new QAccelerometer;
	fAccelerometerRefCount++;
	setSensor (fAccelerometer);
}

//------------------------------------------------------------------------
IAccelerometer::~IAccelerometer()
{
	fAccelerometerRefCount--;
	if (!fAccelerometerRefCount) {
		delete fAccelerometer;
		fAccelerometer = 0;
	}
}

//--------------------------------------------------------------------------
bool IAccelerometer::activate(bool val)
{
	fActives += val ? 1 : -1;
	if (val && !running())	return start(fActives);
	else if (running())		stop(fActives);
	return true;
}

//------------------------------------------------------------------------
void IAccelerometer::createVirtualNodes ()
{
	fXSig = TSignal::create ("accelerometer/x", 1);
	fYSig = TSignal::create ("accelerometer/y", 1);
	fZSig = TSignal::create ("accelerometer/z", 1);
	*this << fXSig;
	*this << fYSig;
	*this << fZSig;
}

//--------------------------------------------------------------------------
// accelerometer generates 3 signals, available at
// accelerometer/x, accelerometer/y and accelerometer/z
//--------------------------------------------------------------------------
bool IAccelerometer::findSubNode (std::string name, subnodes& outlist)
{
	STSignal sig;
	if (name == "x")		sig = fXSig;
	else if (name == "y")	sig = fYSig;
	else if (name == "z")	sig = fZSig;
	else	return false;
	
	string node = this->name() + "/" + name;
	SISignal s = ISignal::create(node, getParent());	// create a signal using the whole name
	*s << sig;											// put it into the parent node
	outlist.push_back(s);								// push the node to the output list
	return true;										// and set the return code to true
}

//------------------------------------------------------------------------
void IAccelerometer::cleanup ()
{
	IObject::cleanup();
	done();
}

//------------------------------------------------------------------------
void IAccelerometer::setSigSize (int size)
{
	ParallelSignal::size( size );
}

//------------------------------------------------------------------------
void IAccelerometer::readData ()
{
#ifdef SENSORDEBUG
	float x = (rand() / (RAND_MAX * 0.5) ) - 1;
	float y = (rand() / (RAND_MAX * 0.5) ) - 1;
	float z = (rand() / (RAND_MAX * 0.5) ) - 1;
	setXPos		( smooth (x, getXPos()) );
	setYPos		( smooth (y, getYPos()) );
	setZOrder	( smooth (z, getZOrder()) );
	if (fIsSignal) {
		*fXSig << getXPos();
		*fYSig << getYPos();
		*fZSig << getZOrder();
	}
	else newData (true);
	setModified();
#else
	QAccelerometerReading*	reader = fAccelerometer->reading();
	if (reader) {
		if (fCalibrating) {
			fCalibration = max(std::abs(reader->x()), std::abs(reader->y()), std::abs(reader->z()), (double)fCalibration);
		}
		else {
			setXPos		( smooth (reader->x()/fCalibration, getXPos()) );
			setYPos		( smooth (reader->y()/fCalibration, getYPos()) );
			setZOrder	( smooth (reader->z()/fCalibration, getZOrder()) );
			if (fIsSignal) {
				*fXSig << getXPos();
				*fYSig << getYPos();
				*fZSig << getZOrder();
			}
			else newData (true);
			setModified();
		}
	}
#endif
}

//------------------------------------------------------------------------
void IAccelerometer::calibrate (bool state)
{
	if (fCalibrating == state)	return;		// nothing to do, already in the requested mode
	fCalibrating = state;
	if (state) {
		fCalibration = gForce;
		fCalRunning = running();
		if (!fCalRunning) activate(true);
	}
	else {
		if (!fCalRunning) activate(false);
	}
}

//------------------------------------------------------------------------
void IAccelerometer::setHandlers()
{
	ISensor::setHandlers();
	
	fMsgHandlerMap[kcalibrate_SetMethod]	= TSetMethodMsgHandler<IAccelerometer,bool>::create(this, &IAccelerometer::calibrate);
	fMsgHandlerMap[kmax_GetSetMethod]		= TSetMethodMsgHandler<IAccelerometer,float>::create(this, &IAccelerometer::setMax);

	fGetMsgHandlerMap[kx_GetSetMethod]			= TGetParamMsgHandler<float>::create(fXPos);
	fGetMsgHandlerMap[ky_GetSetMethod]			= TGetParamMsgHandler<float>::create(fYPos);
	fGetMsgHandlerMap[kz_GetSetMethod]			= TGetParamMsgHandler<float>::create(fZOrder);
	fGetMsgHandlerMap[kmax_GetSetMethod]		= TGetParamMsgHandler<float>::create(fCalibration);
	fAltGetMsgHandlerMap[kcalibrate_SetMethod]	= TGetParamMsgHandler<bool>::create(fCalibrating);
}

} // end namespace


