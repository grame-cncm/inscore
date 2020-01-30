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
#include "ITLError.h"

using namespace std;

namespace inscore
{

static const double gForce = 9.81;
const string IAccelerometer::kAccelerometerType = "accelerometer";

static const string kCombinedMode	("combined");
static const string kGravityMode	("gravity");
static const string kUserMode		("user");

//------------------------------------------------------------------------
IAccelerometer::IAccelerometer(const std::string& name, IObject * parent)
	: IQSensor (name, parent)
{
	fTypeString = kAccelerometerType;
	if (isSignal()) fDefaultScale =  1 / gForce;
	setScale ( fDefaultScale );
}
IAccelerometer::~IAccelerometer()	{}

//------------------------------------------------------------------------
bool IAccelerometer::read (float& x, float& y, float& z)
{
	QAccelerometerReading*	reader = sensor()->reading();
	if (reader) {
		x = reader->x();
		y = reader->y();
		z = reader->z();
		return true;
	}
	else return false;
}

//------------------------------------------------------------------------
void IAccelerometer::setMode (const std::string& mode)
{
	if (mode == kCombinedMode)
		sensor()->setAccelerationMode (QAccelerometer::Combined);
	else if (mode == kGravityMode)
		sensor()->setAccelerationMode (QAccelerometer::Gravity);
	else if (mode == kUserMode)
		sensor()->setAccelerationMode (QAccelerometer::User);
	else
		ITLErr << getOSCAddress() <<  kmode_GetSetMethod << mode << ": invalid mode." << ITLEndl;
}

//------------------------------------------------------------------------
std::string IAccelerometer::getMode () const
{
	QAccelerometer::AccelerationMode mode = sensor()->accelerationMode();
	switch (mode) {
		case QAccelerometer::Combined:
			return kCombinedMode;
		case QAccelerometer::Gravity:
			return kGravityMode;
		case QAccelerometer::User:
			return kUserMode;
		default:
			return "unknown";
	}
}

//------------------------------------------------------------------------
void IAccelerometer::setHandlers()
{
	ISensor::setHandlers();
	fGetMsgHandlerMap[kmode_GetSetMethod]	= TGetParamMethodHandler<IAccelerometer, string (IAccelerometer::*)() const>::create(this, &IAccelerometer::getMode);
	fMsgHandlerMap[kmode_GetSetMethod]		= TSetMethodMsgHandler<IAccelerometer, string>::create(this, &IAccelerometer::setMode);
}

} // end namespace

