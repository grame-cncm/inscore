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

#ifndef __IAccelerometer__
#define __IAccelerometer__


#include "ISensor.h"


class QAccelerometer;
class QAccelerometerReading;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class IAccelerometer;
typedef class libmapping::SMARTP<IAccelerometer>	SIAccelerometer;
//------------------------------------------------------------------------
class IAccelerometer : public ISensor
{
	static QAccelerometer*	fAccelerometer;
	static int				fAccelerometerRefCount;
	
	float			fCalibration;		// the calibration value (default to g)
	bool			fCalibrating;		// a flag to indicate a calibration in progress
	bool			fCalRunning;		// a flag to indicate whether the sensor was running before the calibration
	STSignal		fXSig, fYSig, fZSig;

	public:
		static const std::string kAccelerometerType;
		static SIAccelerometer create(const std::string& name, IObject * parent)	{ return new IAccelerometer(name, parent); }
	
		/// \brief in sensor context, provides access x, y and z signals
		virtual bool	findSubNode (std::string node, subnodes& outlist);
	
	protected:
				 IAccelerometer(const std::string& name, IObject * parent);
		virtual ~IAccelerometer();

		virtual void calibrate (bool state);
		virtual float getMax () const		{ return fCalibration; }
		virtual void  setMax (float max)	{ fCalibration = max; }
		virtual void  createVirtualNodes ();
		virtual void setSigSize (int size);		///< set the signal size

		/// \brief called by the time task, intended to read the sensor data
		virtual void readData ();

		/// \brief sets the message handlers.
		virtual void setHandlers ();
};

/*! @} */

} // end namespoace

#endif
