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

#ifndef __IGuidoPianoRoll__
#define __IGuidoPianoRoll__

#include <string>
#include <vector>

#include "IGuidoCode.h"
#include "GUIDOPianoRoll.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IGuidoPianoRoll;
typedef class libmapping::SMARTP<IGuidoPianoRoll>	SIGuidoPianoRoll;
//--------------------------------------------------------------------------
/*!
 * \brief The IGuidoPianoRoll class. A model object to display gmn score in pianoroll format.
 */
class IGuidoPianoRoll : public virtual IGuidoCode
{
	public:		
		static const std::string kGuidoPianoRollType;

		static SIGuidoPianoRoll create(const std::string& name, IObject * parent)	{ return new IGuidoPianoRoll(name, parent); }

		virtual void	accept (Updater*u);
		PianoRoll * getPianoRoll() {return fPianoRoll;}
    
		/*!
		 * \brief getClipTime get the current time limits.
		 * \return
		 */
		std::vector<int> getClipTime() const;

		/*!
		 * \brief setClipTime Set limits in time to pianoroll.
		 * \param msg a message with two date or an empty message to go back to default value.
		 * \return
		 */
		MsgHandler::msgStatus setClipTime(const IMessage *msg);

		/*!
		 * \brief getClipPitch get the current pitch limits.
		 * \return
		 */
		std::vector<int> getClipPitch() const;

		/*!
		 * \brief setClipPitch Set limits to pianoroll pitch
		 * \param msg a message with 2 int parameters, the pitch limits in midi value.
		 * If message has no value, default value are set (-1);
		 * \return
		 */
		MsgHandler::msgStatus setClipPitch(const IMessage *msg);

		/*!
		 * \brief enableKeyboard Enable keyboard display.
		 * \param enable
		 */
		void enableKeyboard(bool enable);

		/*!
		 * \brief enableAutoVoicesColoration. Enable automatic color voice.
		 * \param enable
		 */
		void enableAutoVoicesColoration(bool enable);

		/*!
		 * \brief setRGBColorToVoice Add a color to a voice
		 * \param voice voice number (start to 1)
		 * \param r red
		 * \param g green
		 * \param b blue
		 * \param a transparency.
		 */
		MsgHandler::msgStatus setRGBColorToVoice(const IMessage *msg);

		/*!
		 * \brief getRGBColorToVoice get rgb color of voices.
		 * \return a message corresponding to set messages.
		 */
		SIMessageList getRGBColorToVoice() const;

		/*!
		 * \brief enableMeasureBars Enable measure bars.
		 * \param enable
		 */
		void enableMeasureBars(bool enable);

		/*!
		 * \brief setPitchLinesDisplayMode Set the pitch lines display.
		 * \param msg a message with a list of string parameter of all displayed lines.
		 * \return the message status.
		 */
		MsgHandler::msgStatus setPitchLinesDisplayMode(const IMessage *msg);

		/*!
		 * \brief getPitchLinesDisplayMode get the pitch lines in string format
		 * \return
		 */
		std::vector<std::string> getPitchLinesDisplayMode() const;

	protected:
				 IGuidoPianoRoll( const std::string& name, IObject * parent);
		virtual ~IGuidoPianoRoll() ;

		/// \brief updates the Piano Roll representation according to the AR Representation
		virtual void updatePianoRoll();

		/*!
		 * \brief updatePianoRoll Update or create a piano roll from a midi file
		 * \param midiFile the midi file path.
		 */
		void updatePianoRoll(std::string &midiFile);

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);
	
		ARHandler fArHandler;
		PianoRoll * fPianoRoll;

	private:
		/*!
		 * \brief applyAllSettings update pianoroll with the display settings
		 */
		void applyAllSettings();

		// Pianoroll display settings
		LimitParams fLimits;
		bool		fKeyboard;
		bool		fAutoVoiceColor;
		std::map<int, IColor> fVoicesColor;
		bool		fMeasureBars;
		int			fPitchLines;
};

/*! @} */

} // end namespoace

#endif

