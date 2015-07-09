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

#ifndef IGUIDOPIANOROLLFILE_H
#define IGUIDOPIANOROLLFILE_H


#include <string>
#include "IGuidoPianoRoll.h"
#include "TFile.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IGuidoPianoRollFile;
typedef class libmapping::SMARTP<IGuidoPianoRollFile>	SIGuidoPianoRollFile;
//--------------------------------------------------------------------------
/*!
	\brief a file based piano roll object
 */
class IGuidoPianoRollFile : public IGuidoPianoRoll, public TFile
{
    public:
        static const std::string kGuidoPianoRollFileType;
        static SIGuidoPianoRollFile create(const std::string& name, IObject * parent)	{ return new IGuidoPianoRollFile(name, parent); }

        virtual void	print(std::ostream& out) const;
        virtual void	accept (Updater*u);

    protected:
        IGuidoPianoRollFile( const std::string& name, IObject * parent);
        virtual ~IGuidoPianoRollFile() {}

		/// \brief the \c 'set' message handler. Accept guido (.gmn) and midi file (.mid)
        virtual MsgHandler::msgStatus set (const IMessage* msg);
        void updateUrl();

	private:
		std::string fMidiFile;
};

/*! @} */

} // end namespoace
#endif // IGUIDOPIANOROLLFILE_H
