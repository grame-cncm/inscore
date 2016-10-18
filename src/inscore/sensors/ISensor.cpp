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

#include <QSensor>

#include "IObject.h"
#include "ITLError.h"
#include "ISensor.h"
#include "ISignalNode.h"
#include "INScore.h"

using namespace std;

namespace inscore
{

const string ISensor::kSensorType = "sensor";

class TEmptyParamMsgHandler;
typedef libmapping::SMARTP<TEmptyParamMsgHandler> SEmptyParamMsgHandler;
//------------------------------------------------------------------------
class TEmptyParamMsgHandler : public GetParamMsgHandler {
	public: 
		static SEmptyParamMsgHandler create() { return new TEmptyParamMsgHandler(); }

		virtual ~TEmptyParamMsgHandler() {}
		virtual SIMessage&  print(SIMessage& msg) const { return msg; };
};

//------------------------------------------------------------------------
ISensor::ISensor(const std::string& name, IObject * parent)
	: ISignal (name, parent), fSensor(0), fTimerID(0), fAlpha(1)
{
	fTypeString = kSensorType;
	fIsSignal = (parent->getTypeString() == ISignalNode::kSignalNodeType);
}

//------------------------------------------------------------------------
ISensor::~ISensor ()						{ activate (false);	}

//------------------------------------------------------------------------
bool ISensor::running () const				{ return fSensor->isActive(); }
void ISensor::timerEvent(QTimerEvent * )	{ readData(); }

//------------------------------------------------------------------------
void ISensor::setHandlers()
{
	fMsgHandlerMap[""]					= (void*)0;
	fMsgHandlerMap[krun_SetMethod]		= TMethodMsgHandler<ISensor>::create(this, &ISensor::run);
	fMsgHandlerMap[ksmooth_GetSetMethod]= TSetMethodMsgHandler<ISensor,float>::create(this, &ISensor::setSmooth);

	fGetMsgHandlerMap[""]					= TEmptyParamMsgHandler::create();
	fGetMsgHandlerMap[ksmooth_GetSetMethod]	= TGetParamMethodHandler<ISensor, float(ISensor::*)() const>::create(this, &ISensor::getSmooth);
	fAltGetMsgHandlerMap[krun_SetMethod]	= TGetParamMethodHandler<ISensor, bool(ISensor::*)() const>::create(this, &ISensor::running);
}


//------------------------------------------------------------------------
void ISensor::print (IMessage& out) const
{
	out.setMessage(ksize_GetSetMethod);
	out << signal(0)->size();
}

//------------------------------------------------------------------------
SIMessageList ISensor::getSetMsg() const
{
	if (fIsSignal) return ISignal::getSetMsg();
	return IObject::getSetMsg();
}

//------------------------------------------------------------------------
MsgHandler::msgStatus ISensor::run(const IMessage* msg)
{
	if (msg->size() != 1) return MsgHandler::kBadParameters;
	int val;
	if (!msg->param(0, val)) return MsgHandler::kBadParameters;
	if (!activate(val)) return MsgHandler::kCreateFailure;
	return MsgHandler::kProcessed;
}

//------------------------------------------------------------------------
MsgHandler::msgStatus ISensor::sizeMsg (const IMessage* msg)
{
	if (msg->size() != 1)		return MsgHandler::kBadParameters;
	int size;
	if (!msg->param(0, size))	return MsgHandler::kBadParameters;
	setSigSize (size);
	return MsgHandler::kProcessed;
}

//------------------------------------------------------------------------
MsgHandler::msgStatus ISensor::set (const IMessage* msg)
{
	string type;
	if (msg->size() != 1)		return MsgHandler::kBadParameters;
	if (!msg->param(0, type))	return MsgHandler::kBadParameters;
//	if (! fSensor->connectToBackend()) {
//		ITLErr << getOSCAddress() << type << "is not supported by your device." << ITLEndl;
//		return MsgHandler::kCreateFailure;
//	}
	return MsgHandler::kProcessed;
}

//------------------------------------------------------------------------
bool ISensor::setSensor(QSensor* sensor)
{
	fSensor = sensor;
	return fSensor->connectToBackend();
}

//------------------------------------------------------------------------
bool ISensor::activate(bool state)
{
	if (!fSensor->isConnectedToBackend())	return false;		// should not happen at this stage
	if (running() == state)					return true;		// nothing to do: already in the requested state

	fSensor->setActive(state);
	fSensor->setAlwaysOn (state);
	if (state) {
//INScore::postMessage("192.168.1.21:7001/ISensor", "activate", 1);
		if (fSensor->start()) {
			fTimerID = startTimer(10);		// start collecting sensor data every 10 mls
//INScore::postMessage("192.168.1.21:7001/ISensor", "fTimerID", fTimerID);
		}
		else return false;
	}
	else {
//INScore::postMessage("192.168.1.21:7001/ISensor", "activate", 0);
		killTimer(fTimerID);
		fTimerID = 0;
		fSensor->stop();
	}
	return true;
}

} // end namespace


