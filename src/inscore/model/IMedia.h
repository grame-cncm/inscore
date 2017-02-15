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


#ifndef __IMedia__
#define __IMedia__

#include <string>

#include "TFile.h"
#include "IRectShape.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief a media object.
*/
class IMedia : public IRectShape, public TFile
{
	int musicalTime2mls (float date) const;

	public:
		/// \brief set the path name \param path the new file path
		void			setFile(const std::string& path);
		
		/// \brief Returns the current media time in seconds, according to the object's date
		float	currentTime() const;
		bool	playing() const			{ return fPlaying; }
		bool	vdateModified() const	{ return fDateModified; }
		bool	rateModified() const	{ return fRateModified; }
		float	volume() const			{ return fVolume; }

		float	rate() const			{ return fRate; }
		int		vDate () const			{ return fCDate; }
		void	setIDate (long date);	// for internal update of the current date

		/// \brief set the object duration according to the media duration (tempo assumed to be 60).
		virtual void	setMediaDuration( long mls);
		virtual void	mediaEnd ();			// called from view when the media reaches the end
		virtual void	mediaReady ();			// called from view when the media data are available

	protected:
		bool  fPlaying;			// the audio playing state
		float fVolume;			// the media sound volume. Range: 0-1
		float fRate;			// the media playing rate. Nominal rate is 1.0
		int	  fVDuration;		// the media duration in mls
		int   fCDate;			// the media current date
		int   fVDate;			// the media requested date
		bool  fDateModified;	// to handle changes of the media date
		bool  fRateModified;	// to handle changes of the media rate
	
				 IMedia( const std::string& name, IObject * parent);
		virtual ~IMedia() {}

		virtual void	cleanup ();

		/// \brief override IObject method
		virtual bool acceptSimpleEvent(EventsAble::eventype t) const;

		/// \brief the \c 'play' message handler
		virtual void setPlay (bool state);

		/// \brief the \c 'vdate' message handler
		virtual void setVDate (long date);

		/// \brief the \c 'volume' message handler
		virtual void setVolume (float volume);

		/// \brief the \c 'volume' message handler
		virtual void setRate (float rate);

		/// \brief the \c 'get vduration' message handler
		virtual libmapping::rational getMediaDuration () const;

		/// \brief the \c 'vdate' message handler
		virtual MsgHandler::msgStatus vdateMsg (const IMessage* msg );

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg );
};

/*! @} */

} // end namespoace

#endif
