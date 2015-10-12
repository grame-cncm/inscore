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


#ifndef __IController__
#define __IController__

#include <string>

#include "smartpointer.h"
#include "IMessageStack.h"

namespace inscore
{

class IObject;
typedef class libmapping::SMARTP<IObject>	SIObject;

/*!
\addtogroup ITLCtrl
@{
*/

//--------------------------------------------------------------------------
/*! \brief utility abstract class intended for notifications

	A MsgListener is notified of new messages (i.e. its \c msgReceived
	method is called) \e before the message is processed by the model.
*/
class MsgListener
{	
	public:
		virtual ~MsgListener() {}
		/*! \brief the callback to be derived by any implementation
		\param msg a pointer to the message to be processed
		\param status a value indicating the message processing status
		*/
		virtual void	msgReceived(const IMessage* msg, int status) = 0;
};

//--------------------------------------------------------------------------
/*! \brief a controller that processes all pending messages
*/
class IController : public libmapping::smartable
{
	private:
		MsgListener*	fListener;		///< a messages listener
	
	public:
		/// \brief creates a new controller
		static libmapping::SMARTP<IController> create()	{ return new IController(); }

			/*! \brief process all the pending messages on a model
				\param msgs the messages to be applied to the model
				\param obj the target model
			*/
			virtual void	processOn   (SIMessageStack& msgs, SIObject& obj);
			/*! \brief sets a new listener
				\param listener the new listener
			*/
			virtual void	setListener (MsgListener* listener)	{ fListener = listener; }
	
	protected:
				/// \brief IController constructor
				 IController();
		virtual ~IController();

		/*!
			\brief process a message on an object tree.
			
			\param msg the message to be processed
			\param obj the model root object
			\return the message processing status
		*/
		virtual int	processMsg (const IMessage* msg, SIObject& obj);

};
typedef class libmapping::SMARTP<IController>	SIController;

/*!
@}
*/

} // end namespoace

#endif
