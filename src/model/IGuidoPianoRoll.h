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
	\brief a file based guido object
*/
class IGuidoPianoRoll : public IGuidoCode
{
	public:		
		static const std::string kGuidoPianoRollType;
		static SIGuidoPianoRoll create(const std::string& name, IObject * parent)	{ return new IGuidoPianoRoll(name, parent); }

		virtual void	accept (Updater*u);
        void setPianoRollType(PianoRollType type) {fType = type;}
        PianoRoll * getPianoRoll() {return fPianoRoll;}
    
	protected:
				 IGuidoPianoRoll( const std::string& name, IObject * parent);
		virtual ~IGuidoPianoRoll() ;

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

        PianoRollType fType;
        PianoRoll * fPianoRoll;
};

/*! @} */

} // end namespoace

#endif

