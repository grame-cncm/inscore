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

using namespace std;

namespace inscore
{

static const double gForce = 9.81;
const string IAccelerometer::kAccelerometerType = "accelerometer";

QAccelerometer*	IAccelerometer::fAccelerometer = 0;
int				IAccelerometer::fAccelerometerRefCount = 0;

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

//------------------------------------------------------------------------
void IAccelerometer::createVirtualNodes ()
{
	fXSig = TSignal::create ("accelerometer/x", 1);
	fYSig = TSignal::create ("accelerometer/y", 1);
	fZSig = TSignal::create ("accelerometer/z", 1);
	*this << TSignal::create( name(), 1);
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
void IAccelerometer::setSigSize (int size)
{
	fXSig->size(size);
	fYSig->size(size);
	fZSig->size(size);
	ParallelSignal::size( size );
}

//------------------------------------------------------------------------
void IAccelerometer::readData ()
{
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
			setModified();
			newData (true);

//INScore::MessagePtr msg = INScore::newMessage();
//INScore::add(msg, getXPos());
//INScore::postMessage("192.168.1.21:7000/accx", msg);
//
//msg = INScore::newMessage();
//INScore::add(msg, getYPos());
//INScore::postMessage("192.168.1.21:7000/accy", msg);
//
//msg = INScore::newMessage();
//INScore::add(msg, getZOrder());
//INScore::postMessage("192.168.1.21:7000/accz", msg);
		}
	}
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


