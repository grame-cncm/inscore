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

#ifndef __IAmbientLight__
#define __IAmbientLight__

#include "I1DSensor.h"
#include "IQSensor.h"

class QAmbientLightSensor;

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class IAmbientLight;
typedef class libmapping::SMARTP<IAmbientLight>	SIAmbientLight;
//------------------------------------------------------------------------
class IAmbientLight : public IQSensor<QAmbientLightSensor, I1DSensor>
{
	public:
		static const std::string kAmbientLightType;
		static SIAmbientLight create(const std::string& name, IObject * parent)	{ return new IAmbientLight(name, parent); }
	
	protected:
				 IAmbientLight(const std::string& name, IObject * parent);
		virtual ~IAmbientLight();

		/// \brief called by the time task, intended to read the sensor data
		virtual float read ();
		virtual float sigvalue (float value) const		{ return (value + 1) / 4 - 0.75; }

		/// \brief sets the message handlers.
		virtual void setHandlers ();
};

/*! @} */

} // end namespoace

#endif
