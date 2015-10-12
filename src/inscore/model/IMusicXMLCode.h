/*

  INScore Project

  Copyright (C) 2014  Grame

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


#ifndef __IMusicXMLCode__
#define __IMusicXMLCode__

#include <string>
#include <map>
#include <set>

#include "IGuidoCode.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class IMusicXMLCode;
typedef class libmapping::SMARTP<IMusicXMLCode>	SIMusicXMLCode;
//--------------------------------------------------------------------------
/*!
	\brief a textual guido music notation object based on musicxml code.
*/
class IMusicXMLCode : public IGuidoCode
{
	protected:
		std::string	fXML;								/// < MusicXML code.
		
		virtual bool convert (const std::string& xml, std::string& converted) const;


	public:
		static const std::string kMusicXMLCodeType;
		static SIMusicXMLCode create(const std::string& name, IObject * parent)	{ return new IMusicXMLCode(name, parent); }
		virtual void	accept (Updater*u);

//		void	print (std::ostream& out) const;
		const std::string&	getMusicXML() const		{ return fXML; }

	protected:
				 IMusicXMLCode( const std::string& name, IObject * parent );
		virtual ~IMusicXMLCode() {}

		/// \brief the \c 'set' message handler
		virtual MsgHandler::msgStatus set (const IMessage* msg);		
};

/*! @} */

} // end namespoace

#endif
