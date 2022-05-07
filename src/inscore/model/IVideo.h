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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/


#ifndef __IVideo__
#define __IVideo__

#include <string>
#include "IMedia.h"

#define VIDEO_MAP_TEMPO			"tempo"
#define VIDEO_MAP_START_SECOND	"startSecond"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IVideo;
typedef class libmapping::SMARTP<IVideo>	SIVideo;
//--------------------------------------------------------------------------
/*!
	\brief a video object.
*/
class IVideo : public IMedia
{
	bool	fUserWidth = false;
	int 	musicalTime2mls (float date) const;

	public:
		static const std::string kVideoType;
		static SIVideo create(const std::string& name, IObject * parent)	{ return new IVideo(name, parent); }
		virtual void	accept (Updater* u);
	
		/// \brief Returns the current video time in seconds, according to the object's date and videoMap.
		float	currentTime() const;
		bool	userWidth() const	{ return fUserWidth; }

		/// \brief set the object duration according to the video duration (tempo assumed to be 60).
		void	setVideoDuration( long mls)	{ setMediaDuration (mls); }

	protected:
				 IVideo( const std::string& name, IObject * parent);
		virtual ~IVideo() {}

		virtual void positionAble ();			///< \brief set the position message handlers

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg );

		/// \brief the \c 'videoMapf' message handler
		virtual MsgHandler::msgStatus videoMapFileMsg (const IMessage* msg );

		/// \brief the \c 'videoMap' message handler
		virtual MsgHandler::msgStatus videoMapMsg (const IMessage* msg );
	
		class Date2SecondConverter: public smartable
		{ 
			public:
				virtual ~Date2SecondConverter() {}
				virtual float convert(const libmapping::rational& r) const = 0;
				virtual SIMessage&  print(SIMessage& m) const = 0;
		};
		class Date2SecondMappingConverter: public Date2SecondConverter
		{ 
			SFloat2RelativeTimeMapping fMapping;
			
			protected:
				Date2SecondMappingConverter( SFloat2RelativeTimeMapping mapping );
			public:
				static libmapping::SMARTP<Date2SecondConverter> create( SFloat2RelativeTimeMapping mapping ) { return new Date2SecondMappingConverter(mapping); }
				virtual ~Date2SecondMappingConverter() {}
				float convert(const libmapping::rational& r) const;
				virtual SIMessage&  print(SIMessage& m) const	{ std::stringstream s; fMapping->direct().print(s); *m << s.str(); return m; }
		};
		class Date2SecondTempoConverter: public Date2SecondConverter
		{ 
			float fTempo, fStartSecond;
			
			protected:
				Date2SecondTempoConverter(float tempo , float startSecond) : fTempo(tempo) , fStartSecond(startSecond) {}
			public:
				static libmapping::SMARTP<Date2SecondConverter> create(float tempo , float startSecond) { return new Date2SecondTempoConverter(tempo,startSecond); }
				virtual ~Date2SecondTempoConverter()	{}
				float convert(const libmapping::rational& r) const	{ return fStartSecond + 240.0f * (float(r) / fTempo); }
				float tempo()							{ return fTempo; }
				float startSecond()						{ return fStartSecond; }
				virtual SIMessage&  print(SIMessage& m) const	{ *m << std::string(VIDEO_MAP_TEMPO) << fTempo << std::string(VIDEO_MAP_START_SECOND) << fStartSecond; return m; }
		};
					
		libmapping::SMARTP<Date2SecondConverter> fConverter;
		float fTempo, fStartSecond;
		
		//--------------------------------------------------------------------------
		class GetVideoMapMsgHandler : public GetParamMsgHandler {

			IVideo* fVideo;
			
			protected:
				GetVideoMapMsgHandler(IVideo* video) : fVideo(video) {}
			public: 
				static libmapping::SMARTP<GetVideoMapMsgHandler> create(IVideo* video) { return new GetVideoMapMsgHandler(video); }
				virtual ~GetVideoMapMsgHandler() {}
				virtual SIMessage&  print(SIMessage& m) const
				{
					return fVideo->fConverter->print( m );
				}
		};


};

/*! @} */

} // end namespoace

#endif
