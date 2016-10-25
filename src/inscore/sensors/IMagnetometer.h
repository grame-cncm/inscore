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

#ifndef __IMagnetometer__
#define __IMagnetometer__

#include "I3DSensor.h"
#include "IQSensor.h"

class QMagnetometer;
class QMagnetometerReading;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class IMagnetometer;
typedef class libmapping::SMARTP<IMagnetometer>	SIMagnetometer;
//------------------------------------------------------------------------
class IMagnetometer : public IQSensor<QMagnetometer, I3DSensor>
{
	float			fCalibration;		// the calibration value (default to g)
	bool			fCalibrating;		// a flag to indicate a calibration in progress
	bool			fCalRunning;		// a flag to indicate whether the sensor was running before the calibration

	public:
		static const std::string kMagnetometerType;
		static SIMagnetometer create(const std::string& name, IObject * parent)	{ return new IMagnetometer(name, parent); }
	
	protected:
				 IMagnetometer(const std::string& name, IObject * parent);
		virtual ~IMagnetometer();

		virtual void calibrate (bool state);
		virtual float getMax () const		{ return fCalibration; }
		virtual void  setMax (float max)	{ fCalibration = max; }

		/// \brief called by the time task, intended to read the sensor data
		virtual bool read (float& x, float& y, float& z);

		/// \brief sets the message handlers.
		virtual void setHandlers ();
};

/*! @} */

} // end namespoace

#endif
