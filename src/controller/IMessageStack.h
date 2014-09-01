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


#ifndef __IMessageStack__
#define __IMessageStack__

#ifdef FIFOLOCK
#include <QMutex>
#endif

#include "MessageBuffer.h"
#include "smartpointer.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

class IMessage;
typedef libmapping::SMARTP<IMessage>		SIMessage;
class IMessageStack;
typedef libmapping::SMARTP<IMessageStack>	SIMessageStack;
extern SIMessageStack gMsgStack;

//--------------------------------------------------------------------------
/*!
	\brief a lock-free message fifo
*/
class IMessageStack : public libmapping::smartable
{
	private:
#ifdef FIFOLOCK
		QMutex		fMutex;					// this is to handle lffifo issue
#endif
		int				fReceivedCount;
		MessageBuffer	fPendingMsgs;
	public:
		static libmapping::SMARTP<IMessageStack> create()			{ return new IMessageStack; }

		/*!
			\brief returns the messages stack size
			\return the messages stack size
		*/
		int			size();
		/*!
			\brief push a message on the stack
		*/
		void		push(SIMessage* msg);
		/*!
			\brief pop a message from the stack
			\return a message pointer, null when the stack is empty
		*/
		SIMessage*	pop();
		/*!
			\brief flushes the messages stack
		*/
		void		flush();	
		/*!
			\brief increments the count of received messages
		*/
		void		inc()			{ fReceivedCount++; }
		/*!
			\brief increments the count of received messages
		*/
		void		reset()			{ fReceivedCount = 0; }
		/*!
			\brief gives the count of received messages
		*/
		int			stat() const	{ return fReceivedCount; }
	
	protected:
				 IMessageStack();
		virtual ~IMessageStack();
};

/*!
@}
*/

} // end namespoace

#endif
