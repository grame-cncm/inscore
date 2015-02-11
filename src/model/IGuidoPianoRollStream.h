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


#ifndef __IGuidoPianoRollStream__
#define __IGuidoPianoRollStream__

#include <string>
#include "IGuidoPianoRoll.h"
#include "IGuidoStream.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class IGuidoPianoRollStream;
typedef class libmapping::SMARTP<IGuidoPianoRollStream>	SIGuidoPianoRollStream;
//--------------------------------------------------------------------------
/*!
	\brief a stream piano roll guido object
*/
class IGuidoPianoRollStream : public IGuidoStream, public IGuidoPianoRoll
{
	public:		
		static const std::string kGuidoPianoRollStreamType;
		static SIGuidoPianoRollStream create(const std::string& name, IObject * parent)	{ return new IGuidoPianoRollStream(name, parent); }

		virtual void	accept (Updater*u);
    
	protected:
				 IGuidoPianoRollStream( const std::string& name, IObject * parent);
		virtual ~IGuidoPianoRollStream() ;

        void clear();

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);

		/// \brief the \c 'write' message handler
		virtual MsgHandler::msgStatus write (const IMessage* msg);

};

/*! @} */

} // end namespoace

#endif