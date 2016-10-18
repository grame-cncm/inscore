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

#include "IVideo.h"
#include "Updater.h"
#include "IMessage.h"
#include "MapTools.h"
#include "IScene.h"
#include "VObjectView.h"
#include "TMapMsgHandler.h"
#include "TVariety.h"
#include "Events.h"

#include "imapreader.h"
#include "long_to_rational_reader.h"
#include "long2D_to_rational_reader.h"
#include "float_to_rational_reader.h"
#include "float2D_to_rational_reader.h"

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
const string IVideo::kVideoType("video");

//--------------------------------------------------------------------------
IVideo::IVideo( const std::string& name, IObject * parent ) 
	: IMedia (name, parent)
{	
	fTypeString = kVideoType;

	fMsgHandlerMap[kvideoMap_GetSetMethod]		= TMethodMsgHandler<IVideo>::create(this, &IVideo::videoMapMsg);
	fMsgHandlerMap[kvideoMapf_SetMethod]		= TMethodMsgHandler<IVideo>::create(this, &IVideo::videoMapFileMsg);
	
	fGetMsgHandlerMap[kvideoMap_GetSetMethod]	= GetVideoMapMsgHandler::create(this);
	
	fTempo = 60.0f;
	fStartSecond = 0.0f;
	fConverter = Date2SecondTempoConverter::create( fTempo , fStartSecond );
}

//--------------------------------------------------------------------------
void IVideo::accept (Updater* u)
{
	u->updateTo (SIVideo(this));
}

//----------------------------------------------------------------------
float IVideo::currentTime() const
{
	return fConverter->convert( getDate() );
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IVideo::videoMapMsg (const IMessage* msg )	
{ 
	if (msg->size() == 1) {
		string map = msg->param(0)->value<std::string>("");

		if (map.size()) {
			_imapreader<float,1> reader; std::istringstream s(map);
			imapreader r (&reader, &s);
			if (r.parse()) {
				fConverter = Date2SecondMappingConverter::create(reader.mapping());
				return MsgHandler::kProcessed;
			}
		}
	}
	else if (msg->size() >= 2) {
		int i = 0;
		while ( (i < msg->size()) && (i < 4) )
		{
			string keyWord = msg->param(i)->value<std::string>("");
			if ( !msg->param(i+1)->isType<float>() )
				return MsgHandler::kBadParameters;
			float value = msg->param(i+1)->value<float>(0);

			if ( keyWord == VIDEO_MAP_TEMPO )
				fTempo = value;
			else if ( keyWord == VIDEO_MAP_START_SECOND )
				fStartSecond = value;
			else
				return MsgHandler::kBadParameters;
			
			i+=2;
		}
		fConverter = Date2SecondTempoConverter::create( fTempo , fStartSecond );
	}
	return MsgHandler::kBadParameters;
}

//---------------------------------------------------------------------------
MsgHandler::msgStatus IVideo::videoMapFileMsg (const IMessage* msg )	
{ 
	if (msg->size() == 1) {
		string file = msg->param(0)->value<std::string>("");
		
		file = getScene()->absolutePath(file);
		if (file.size()) {
			_imapreader<float,1> reader; std::ifstream s(file.c_str());
			imapreader r (&reader, &s);
			if (r.parse()) {
				fConverter = Date2SecondMappingConverter::create(reader.mapping());
				return MsgHandler::kProcessed;
			}
		}
	}
	return MsgHandler::kBadParameters;
}

//----------------------------------------------------------------------
IVideo::Date2SecondMappingConverter::Date2SecondMappingConverter( SFloat2RelativeTimeMapping map )
{
	fMapping = map;
}

//----------------------------------------------------------------------
float IVideo::Date2SecondMappingConverter::convert(const rational& r) const
{
	RelativeTimeSegment t = MapTools::find (r, fMapping->reverse());// get the time segment containing the date r
	std::set<FloatSegment> dates = fMapping->reverse().get(t);
	float date = -1;
	if (dates.size()) {
		RationalInterval pos(r, r);
		TAXBFunction<rational> f(t.interval(), pos);		// computes the linear interpolation function that goes from t to pos
		TSegmentVariety<float,1> v (*dates.begin(), &f);	// create a variety of this segment using the previous linear interpolation function
		date = v.get( f(r) );								// x is now the variety x pos et date relative pos regarding f
	}
	return date;
}

}

