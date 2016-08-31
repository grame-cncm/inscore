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


#ifndef __IVideo__
#define __IVideo__

#include <string>
#include <sstream>
#include "IRectShape.h"
#include "TFile.h"

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
class IVideo : public IRectShape,  public TFile
{
	public:
		static const std::string kVideoType;
		static SIVideo create(const std::string& name, IObject * parent)	{ return new IVideo(name, parent); }
		virtual void	accept (Updater* u);

		/// \brief set the path name \param path the new file path
		void			setFile(const std::string& path);
		
		/// \brief Returns the current video time in seconds, according to the object's date and videoMap.
		float	currentTime() const;
		bool	playing() const			{ return fPlaying; }
		bool	vdateModified() const	{ return fDateModified; }
		bool	rateModified() const	{ return fRateModified; }
		float	volume() const			{ return fVolume; }

		/// \brief set the object duration according to the video duration (tempo assumed to be 60).
		void	setVideoDuration( long mls);
		float	rate() const			{ return fRate; }
		int		vDate () const			{ return fCDate; }

		void	setIDate (long date);	// for internal update of the current date
		void	videoEnd ();			// called from view when the video reaches the end
		void	videoReady ();			// called from view when the video data are available

	protected:
		bool  fPlaying;			// the video playing state
		float fVolume;			// the video sound volume. Range: 0-1
		float fRate;			// the video playing rate. Nominal rate is 1.0
		int	  fVDuration;		// the video duration in mls
		int   fCDate;			// the video current date
		int   fVDate;			// the video requested date
		bool  fDateModified;	// to handle changes of the video date
		bool  fRateModified;	// to handle changes of the video rate
	
				 IVideo( const std::string& name, IObject * parent);
		virtual ~IVideo() {}

		virtual void	cleanup ();

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

		/// \brief the \c 'play' message handler
		virtual void setPlay (bool state);

		/// \brief the \c 'vdate' message handler
		virtual void setVDate (long date);

		/// \brief the \c 'volume' message handler
		virtual void setVolume (float volume);

		/// \brief the \c 'volume' message handler
		virtual void setRate (float rate);

		/// \brief the \c 'get vduration' message handler
		virtual libmapping::rational getVDuration () const;
	
		/// \brief the \c 'videoMapf' message handler
		virtual MsgHandler::msgStatus videoMapFileMsg (const IMessage* msg );

		/// \brief the \c 'videoMap' message handler
		virtual MsgHandler::msgStatus videoMapMsg (const IMessage* msg );

		/// \brief the \c 'watch' message handler
		virtual MsgHandler::msgStatus _watchMsg(const IMessage* msg, bool add);
	
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
