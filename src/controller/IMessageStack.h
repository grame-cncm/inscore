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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/


#ifndef __IMessageStack__
#define __IMessageStack__

#include "lffifo.h"
#include "smartpointer.h"

namespace interlude
{

/*!
\addtogroup ITLCtrl
@{
*/

class IMessage;
//--------------------------------------------------------------------------
/*!
	\brief a lock-free message fifo
*/
class IMessageStack : public smartable
{
	private:
		fifo		 fMsgFifo;	
	public:
		static SMARTP<IMessageStack> create()			{ return new IMessageStack; }

		/*!
			\brief returns the messages stack size
			\return the messages stack size
		*/
		int			size();
		/*!
			\brief push a message on the stack
		*/
		void		push(IMessage* msg);
		/*!
			\brief pop a message from the stack
			\return a message pointer, null when the stack is empty
		*/
		IMessage*	pop();
		/*!
			\brief flushes the messages stack
		*/
		void		flush();	
	
	protected:
				 IMessageStack();
		virtual ~IMessageStack();
};
typedef class SMARTP<IMessageStack>	SIMessageStack;

/*!
@}
*/

} // end namespoace

#endif
