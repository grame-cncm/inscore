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

#ifndef __IQSensor__
#define __IQSensor__

#include <map>


namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

//------------------------------------------------------------------------
// IQSensor combines a Qt sensor and an ISensor implementation
// It provides sharing of the Qt sensor between all the inscore objects
// (whether signal or regular node)
//------------------------------------------------------------------------
template<typename Q, typename S> class IQSensor : public S
{
	static Q*	fQSensor;				// device is shared between different instances
	static std::map<Q*, int>	fSensorsRefCount;		//
	static std::map<Q*, int>	fSensorsActives;		// number of client activations

	
	protected:
				 IQSensor(const std::string& name, IObject * parent) : S(name, parent) {
						if (!fQSensor) fQSensor = new Q;
						fSensorsRefCount[fQSensor]++;
						fSensorsActives[fQSensor] = 0;
						S::setSensor (fQSensor);
				 }
		virtual ~IQSensor() {
						activate(false);
						fSensorsRefCount[fQSensor]--;
						if (!fSensorsRefCount[fQSensor]) {
							delete fQSensor;
							S::setSensor (0);
							fQSensor = 0;
						}
				 }
	
		Q*			sensor()			{ return fQSensor; }
		const Q*	sensor() const		{ return fQSensor; }

	public:
		virtual	bool activate(bool val) {
			S::activate (val);
			fSensorsActives[fQSensor] += val ? 1 : -1;
			if (val && !S::running())	return S::start(fSensorsActives[fQSensor]);
			else if (S::running())		S::stop(fSensorsActives[fQSensor]);
			return true;
		}
};

template <typename C, typename S> C* IQSensor<C,S>::fQSensor;
template <typename C, typename S> std::map<C*, int>	IQSensor<C,S>::fSensorsRefCount;
template <typename C, typename S> std::map<C*, int>	IQSensor<C,S>::fSensorsActives;


/*! @} */

} // end namespoace

#endif
