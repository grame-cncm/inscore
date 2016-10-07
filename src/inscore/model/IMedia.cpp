/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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

#include <fstream>

#include "IMedia.h"
#include "IMessage.h"
#include "IScene.h"
#include "Events.h"
#include "VObjectView.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
IMedia::IMedia( const std::string& name, IObject * parent )
	: IRectShape (name, parent), TFile (parent->getScene())
{	
	fGetMsgHandlerMap[""] = TGetParamMsgHandler<string>::create(getFile());
	
	fMsgHandlerMap[kplay_GetSetMethod]			= TSetMethodMsgHandler<IMedia,bool>::create(this, &IMedia::setPlay);
	fMsgHandlerMap[kvolume_GetSetMethod]		= TSetMethodMsgHandler<IMedia,float>::create(this, &IMedia::setVolume);
	fMsgHandlerMap[krate_GetSetMethod]			= TSetMethodMsgHandler<IMedia,float>::create(this, &IMedia::setRate);
	fMsgHandlerMap[kvdate_GetSetMethod]			= TMethodMsgHandler<IMedia, MsgHandler::msgStatus (IMedia::*)(const IMessage*)>::create(this, &IMedia::vdateMsg);
	
	fGetMsgHandlerMap[kplay_GetSetMethod]		= TGetParamMsgHandler<bool>::create(fPlaying);
	fGetMsgHandlerMap[kvolume_GetSetMethod]		= TGetParamMsgHandler<float>::create(fVolume);
	fGetMsgHandlerMap[krate_GetSetMethod]		= TGetParamMsgHandler<float>::create(fRate);
	fGetMsgHandlerMap[kvdate_GetSetMethod]		= TGetParamMsgHandler<int>::create(fCDate);
	fGetMsgHandlerMap[kmls_GetMethod]			= TGetParamMsgHandler<int>::create(fVDuration);
	fGetMsgHandlerMap[kvduration_GetMethod]		= TGetParamMethodHandler<IMedia, rational (IMedia::*)() const>::create(this, &IMedia::getMediaDuration);
	
	fPlaying = false;
	fVolume = 1.f;						// QMediaPlayer max value
	fRate = 1.f;						// QMediaPlayer default value
	fVDate = 0;							// the media current date
	fVDuration = 0;						// unknown at object initialisation
	fRateModified = fDateModified = false;
}

//--------------------------------------------------------------------------
void IMedia::setPlay (bool state)		{ fPlaying = state;  }
void IMedia::setVolume (float vol)		{ fVolume = vol;  }
void IMedia::setRate (float rate)		{ fRate = rate; fRateModified = true;  }
void IMedia::setVDate (long date)		{ fCDate = fVDate = int(date); fDateModified=true;  }
void IMedia::setIDate (long date)		{ fCDate = int(date); }

void IMedia::cleanup ()
{
	fRateModified = fDateModified = false;
	IObject::cleanup();
}

//--------------------------------------------------------------------------
void IMedia::mediaReady ()
{
	fPlaying = false;
	checkEvent (kReadyEvent, rational(0,1), this);
}

//--------------------------------------------------------------------------
void IMedia::mediaEnd ()
{
	fPlaying = false;
	checkEvent (kEndEvent, rational(0,1), this);
}


//--------------------------------------------------------------------------
bool IMedia::acceptSimpleEvent(EventsAble::eventype t) const
{
	string ev(t);
	if ( (ev == kEndEvent) || (ev == kReadyEvent)) return true;
	return IObject::acceptSimpleEvent(t);
}

//--------------------------------------------------------------------------
// set the object duration
void IMedia::setMediaDuration( long mls)	{ fVDuration = int(mls); }
rational IMedia::getMediaDuration () const	{ return rational((fVDuration * fRate) / 4000.f); }

//--------------------------------------------------------------------------
void IMedia::setFile(const std::string& path)
{
	TFile::setFile(path);

	ifstream file;
	file.open (path.c_str(), ifstream::in);
	if (file.is_open())
		file.close();
	else
	{
		const char* msg = "can't open media file :";
		cerr << msg << path << endl;
		oscerr << OSCErr() << msg << path << OSCEnd();
	}
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IMedia::set (const IMessage* msg )
{ 
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status; 

	status = TFile::set( msg );
	if (status & MsgHandler::kProcessed) {
		newData(true);
		getView()->initialize(this);
	}
	return status;
}

//--------------------------------------------------------------------------
int IMedia::musicalTime2mls (float date) const
{
	// converts the date in float and in quarter notes count
	// assumes the tempo is 60 and converts the quarter notes count in milliseconds
	return int(date * 4000);
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IMedia::vdateMsg (const IMessage* msg )
{
	MsgHandler::msgStatus ret = MsgHandler::kBadParameters;
	size_t n = msg->size();
	if (n == 1) {
		int mlsdate;
		float floatdate;
		if (msg->param(0, mlsdate)) {
			setVDate (mlsdate);
			ret = MsgHandler::kProcessed;
		}
		else if (msg->param(0, floatdate)) {
			setVDate (musicalTime2mls(floatdate));
			ret = MsgHandler::kProcessed;
		}
	}
	else if (n == 2) {
		int num, denum;
		if (msg->param(0, num) && msg->param(1, denum)) {
			int vdate = musicalTime2mls(rational(num, denum));
			setVDate (vdate);
			ret = MsgHandler::kProcessed;
		}
	}
	return ret;
}

}

