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

#include <QMagnetometer>
#include <QMagnetometerReading>

#include "IMagnetometer.h"
#include "ITLError.h"

using namespace std;

namespace inscore
{

const string IMagnetometer::kMagnetometerType = "magnetometer";

static const string kGeoMode	("geomagnetic");
static const string kRawMode	("raw");

//------------------------------------------------------------------------
IMagnetometer::IMagnetometer(const std::string& name, IObject * parent)
	: IQSensor (name, parent)
{
	fTypeString = kMagnetometerType;
	if (isSignal()) fDefaultScale = 10000;
	setScale ( fDefaultScale );
}

//------------------------------------------------------------------------
IMagnetometer::~IMagnetometer()	{}

//------------------------------------------------------------------------
bool IMagnetometer::read (float& x, float& y, float& z)
{
	QMagnetometerReading*	reader = sensor()->reading();
	if (reader) {
		x = reader->x();
		y = reader->y();
		z = reader->z();
		return true;
	}
	else return false;
}


//------------------------------------------------------------------------
void IMagnetometer::setMode (const std::string& mode)
{
	if (mode == kGeoMode)
		sensor()->setReturnGeoValues (true);
	else if (mode == kRawMode)
		sensor()->setReturnGeoValues (false);
	else
		ITLErr << getOSCAddress() <<  kmode_GetSetMethod << mode << ": invalid mode." << ITLEndl;
}

//------------------------------------------------------------------------
std::string IMagnetometer::getMode () const
{
	return sensor()->returnGeoValues() ? kGeoMode : kRawMode;
}


//------------------------------------------------------------------------
void IMagnetometer::setHandlers()
{
	ISensor::setHandlers();
	fGetMsgHandlerMap[kmode_GetSetMethod]	= TGetParamMethodHandler<IMagnetometer, string (IMagnetometer::*)() const>::create(this, &IMagnetometer::getMode);
	fMsgHandlerMap[kmode_GetSetMethod]		= TSetMethodMsgHandler<IMagnetometer, string>::create(this, &IMagnetometer::setMode);
}

} // end namespace


