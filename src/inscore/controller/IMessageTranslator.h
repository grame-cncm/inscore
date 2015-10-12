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


#ifndef __IMessageTranslator__
#define __IMessageTranslator__

#include <map>
#include <string>
#include "smartpointer.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

class IMessage;
typedef libmapping::SMARTP<IMessage>	SIMessage;
//--------------------------------------------------------------------------
/*!
	\brief a message translator
	
	A message translator operates messages translations.
	It is used for example to translate the \c type of the \c 'set' message when this type
	is the generic \c 'file' type.
*/
class IMessageTranslator
{	
	protected:
		static std::map<std::string, std::string>	fFileTypeTranslationTable;
	/*!
		\brief translates a \c 'file' type \c 'set' message 
		\param msg the message to be translated
		\return a translated message when a translation exists otherwise null
	*/
			SIMessage	translateFileType(const IMessage* msg);

	public:
				 IMessageTranslator();
		virtual ~IMessageTranslator() {}
	/*!
		\brief translates a message
		\param msg the message to be translated
		\return a translated message when a translation exists otherwise null
		\note it's the caller responsibility to free the translated message
	*/
	virtual SIMessage	translate(const IMessage* msg);
};

/*!
@}
*/

} // end namespoace

#endif
