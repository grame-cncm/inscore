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


#ifndef __IProxy__
#define __IProxy__

#include <string>
#include "IObject.h"
#include "smartpointer.h"

namespace interlude
{

/*!
\addtogroup ITLModel
@{
*/

class IMessage;
//--------------------------------------------------------------------------
/*! \brief an object creator proxy

	IProxy is used to create objects when needed. 
	It should be called when the destination address doesn't exist. It handles a unique message:
	the 'set' message, creates the corresponding object and calls the new object \c execute method.
*/
class IProxy
{	
	public:
		/*! \brief execute a signal message for non-existing signals		

		\param msg the message
		\param objName the new object name
		\param parent the new object parent
		\return the message processing status
		*/
		static int signal (const IMessage* msg, const std::string& objName, SIObject parent);

		/*! \brief execute a message for non-existing objects
		
		IProxy handles only the 'set' message. It creates the corresponding object,
		call the \c execute method of the new object with the message as argument and in case of success,
		inserts the object into the \c parent list.
		\param msg the message
		\param objName the new object name
		\param parent the new object parent
		\return the message processing status
		*/
		static int execute (const IMessage* msg, const std::string& objName, SIObject parent);
};

/*!
@}
*/

} // end namespoace

#endif
