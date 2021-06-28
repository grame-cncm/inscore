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

#include "IFaustwProcessor.h"
#include "Updater.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
const string IFaustwProcessor::kFaustwProcessorfType("faustw");

//--------------------------------------------------------------------------
IFaustwProcessor::IFaustwProcessor( const std::string& name, IObject * parent) : IFaustProcessor(name, parent)
{
	fTypeString = kFaustwProcessorfType;
}

//--------------------------------------------------------------------------
void IFaustwProcessor::accept (Updater* u)
{
	u->updateTo (SIFaustwProcessor(this));
}

//--------------------------------------------------------------------------
void IFaustwProcessor::print (IMessage& out) const
{
//cerr << "IFaustwProcessor::print" << endl;
	out.setMessage(kset_SetMethod);
	out << kFaustwProcessorfType;
	if (getVoices()) out << getVoices();
	out << fDspCode << fJsonFile;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustwProcessor::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	int n = msg->size();
	string wasm;
	string json;
	int voices;
	switch (n) {
		case 3:
			if (msg->param(1, wasm) && msg->param(2, json)) {
				fDspCode = wasm;
				fJsonFile = json;
				newData(true);
				return MsgHandler::kProcessed;
			}

		case 4:
			if (msg->param(1, voices) && msg->param(2, wasm) && msg->param(3, json)) {
				fVoices = voices;
				fDspCode = wasm;
				fJsonFile = json;
				status = MsgHandler::kProcessed;
				newData(true);
				return MsgHandler::kProcessed;
			}
	}
	return MsgHandler::kBadParameters;
}

}
