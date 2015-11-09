/*

  INScore Project

  Copyright (C) 2015  Grame

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

#include "IGuidoPianoRollFile.h"
#include "IGuidoFile.h"
#include "IScene.h"
#include "Updater.h"
#include "VGuidoItemView.h"

using namespace std;

namespace inscore
{
//--------------------------------------------------------------------------
const string IGuidoPianoRollFile::kGuidoPianoRollFileType("pianorollf");

//--------------------------------------------------------------------------
IGuidoPianoRollFile::IGuidoPianoRollFile( const std::string& name, IObject * parent )
		: IGuidoCode(name, parent), IGuidoPianoRoll (name, parent), TFile (parent->getScene())
{
		fTypeString = kGuidoPianoRollFileType;
		fGetMsgHandlerMap[""] = TGetParamMsgHandler<string>::create(getFile());
}

//--------------------------------------------------------------------------
void IGuidoPianoRollFile::accept (Updater* u)
{
		u->updateTo (SIGuidoPianoRollFile(this));
}

//--------------------------------------------------------------------------
void IGuidoPianoRollFile::print (ostream& out) const
{
	IGuidoCode::print(out);
	TFile::print(out);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IGuidoPianoRollFile::set (const IMessage* msg )
{
		MsgHandler::msgStatus status = IObject::set(msg);
		if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

		status = TFile::set( msg );
		if (status & MsgHandler::kProcessed) {
			if(!hasData())
			{
				string file = getFile();
				string::size_type pos = file.rfind(".");
				string extension;
				if(pos != string::npos) {
					extension = file.substr(pos + 1);
				}
				if(extension == "gmn") {
					if (!read(fGMN))
						return MsgHandler::kCreateFailure;
					//updatePianoRoll();	//Useless called by newData
				} else
				if(extension == "mid") {
					fMidiFile = file;
					//updatePianoRoll(fMidiFile);	//Useless called by newData
				} else
					return MsgHandler::kCreateFailure;
				newData(true);

			}
		}
		return status;
}

//--------------------------------------------------------------------------
void IGuidoPianoRollFile::updateUrl()
{
	if (dataSize())	fGMN = data();
	this->getView()->updateLocalMapping(this);
}

void IGuidoPianoRollFile::newData(bool state)
{
	if(isMidiFile()){
		if(state)
			updatePianoRoll(fMidiFile);
		IGuidoCode::newData(true);
	}else{
		IGuidoPianoRoll::newData(true); //auto call updatePianoRoll() which fail in case of midi file
	}
}

}
