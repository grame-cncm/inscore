/*

  INScore Project

  Copyright (C) 2009,2021  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include "AudioIO.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
const string AudioIO::kAudioIOType("audioio");

//--------------------------------------------------------------------------
AudioIO::AudioIO (const std::string& name, IObject * parent) : IRectShape(name, parent)
{
	fTypeString = kAudioIOType;
	fGetMsgHandlerMap[""]				= TGetParamMethodHandler<AudioIO, std::vector<int> (AudioIO::*)() const>::create(this, &AudioIO::getInOut);
	fGetMsgHandlerMap[kin_GetMethod]	= TGetParamMsgHandler<int>::create(fNumInputs);
	fGetMsgHandlerMap[kout_GetMethod]	= TGetParamMsgHandler<int>::create(fNumOutputs);
	fGetMsgHandlerMap[kconnect_GetSetMethod]= TGetParamMethodHandler<AudioNode, vector<string> (AudioNode::*)() const>::create(this, &AudioIO::getconnect);

	fMsgHandlerMap[kconnect_GetSetMethod]	= TMethodMsgHandler<AudioIO>::create(this, &AudioIO::connect);
	fMsgHandlerMap[kdisconnect_SetMethod]	= TMethodMsgHandler<AudioIO>::create(this, &AudioIO::disconnect);
}

//--------------------------------------------------------------------------
void AudioIO::accept (Updater* u)
{
	u->updateTo (SAudioIO(this));
}

//--------------------------------------------------------------------------
vector<int> AudioIO::getInOut() const
{
	vector<int> out;
	out.push_back (fNumInputs);
	out.push_back (fNumOutputs);
	return out;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus AudioIO::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	int n = msg->size();
	if (n != 3) return MsgHandler::kBadParameters;
	int in, out;
	if (!msg->param(1, in) || !msg->param(2, out)) return MsgHandler::kBadParameters;
	setIONums (in, out);
	newData(true);
	setVisible (false);
	return MsgHandler::kProcessed;
}

} // end namespoace
