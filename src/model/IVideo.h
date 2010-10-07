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
#include "IRectShape.h"
#include "TFile.h"

#define VIDEO_MAP_TEMPO			"tempo"
#define VIDEO_MAP_START_SECOND	"startSecond"

namespace interlude
{

/*!
\addtogroup ITLModel
@{
*/

class VVideoView;
class Updater;
class IVideo;
typedef class SMARTP<IVideo>	SIVideo;
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
		float currentTime() const;
		
		VVideoView *	getView () const				{ return fView; }
		void			setView (VVideoView * view) 	{ fView = view; }
		VGraphicsItemView*	graphicView() const			{ return (VGraphicsItemView*)fView; }

	protected:
		VVideoView * fView;
		
				 IVideo( const std::string& name, IObject * parent);
		virtual ~IVideo() {}

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
		
		/// \brief the \c 'videoMapf' message handler
		virtual MsgHandler::msgStatus videoMapFileMsg (const IMessage* msg );

		/// \brief the \c 'videoMap' message handler
		virtual MsgHandler::msgStatus videoMapMsg (const IMessage* msg );
				
		class Date2SecondConverter: public smartable
		{ 
			public:
				virtual ~Date2SecondConverter() {}
				virtual float convert(const rational& r) const = 0;
				virtual IMessage&  print(IMessage& m) const = 0;
		};
		class Date2SecondMappingConverter: public Date2SecondConverter
		{ 
			SFloat2RelativeTimeMapping fMapping;
			
			protected:
				Date2SecondMappingConverter( SFloat2RelativeTimeMapping mapping );
			public:
				static SMARTP<Date2SecondConverter> create( SFloat2RelativeTimeMapping mapping ) { return new Date2SecondMappingConverter(mapping); }
				virtual ~Date2SecondMappingConverter() {}
				float convert(const rational& r) const;
				virtual IMessage&  print(IMessage& m) const	{ m << fMapping; return m; }
		};
		class Date2SecondTempoConverter: public Date2SecondConverter
		{ 
			float fTempo, fStartSecond;
			
			protected:
				Date2SecondTempoConverter(float tempo , float startSecond) : fTempo(tempo) , fStartSecond(startSecond) {}
			public:
				static SMARTP<Date2SecondConverter> create(float tempo , float startSecond) { return new Date2SecondTempoConverter(tempo,startSecond); }
				virtual ~Date2SecondTempoConverter()	{}
				float convert(const rational& r) const	{ return fStartSecond + 240.0f * (float(r) / fTempo); }
				float tempo()							{ return fTempo; }
				float startSecond()						{ return fStartSecond; }
				virtual IMessage&  print(IMessage& m) const	{ m << std::string(VIDEO_MAP_TEMPO) << fTempo << std::string(VIDEO_MAP_START_SECOND) << fStartSecond; return m; }
		};
					
		SMARTP<Date2SecondConverter> fConverter;
		float fTempo, fStartSecond;
		
		//--------------------------------------------------------------------------
		class GetVideoMapMsgHandler : public GetParamMsgHandler {

			IVideo* fVideo;
			
			protected:
				GetVideoMapMsgHandler(IVideo* video) : fVideo(video) {}
			public: 
				static SMARTP<GetVideoMapMsgHandler> create(IVideo* video) { return new GetVideoMapMsgHandler(video); }
				virtual ~GetVideoMapMsgHandler() {}
				virtual IMessage&  print(IMessage& m) const
				{
					return fVideo->fConverter->print( m );
				}
		};


};

/*! @} */

} // end namespoace

#endif
