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


#ifndef __ISignal__
#define __ISignal__

#include <string>
#include "IObject.h"
#include "TSignal.h"

namespace inscore
{

/*!
\addtogroup ITLModel
@{
*/

class Updater;
class ISignal;
typedef class libmapping::SMARTP<ISignal>	SISignal;
class ISignalNode;
typedef class libmapping::SMARTP<ISignalNode>	SISignalNode;
//--------------------------------------------------------------------------
/*!
	\brief a signal
*/
class ISignal : public IObject, public ParallelSignal
{
	public:		
		static const std::string kSignalType;
		static SISignal create(const std::string& name, IObject * parent)	{ return new ISignal(name, parent); }
		virtual void	accept (Updater* u);

		/*! \brief specific signal cleanup, actually call \c done() of the ParallelSignal
		*/
		virtual void	cleanup ();

	protected:

				 ISignal( const std::string& name, IObject * parent);
		virtual ~ISignal() {}

		// overrides get handlers for color, position and time
		virtual void colorAble ()		{}
		virtual void positionAble ()	{}
		virtual void timeAble ()		{}

		/*! \brief decode a projection string
			\param proj the projection string
			\param index on output the projection start index (default 0)
			\param step on output the projection step (default 0 when no parallel marker or 1)
			\return false in case of incorrect \c proj string format
		*/
		virtual bool	decodeProjection (const std::string& proj, int& index, int& step) const;

		/// \brief signal \c 'get' message handler
		virtual IMessageList getSetMsg () const;

		/// \brief print the signals list
		virtual void	print (IMessage& out) const;

		/// \brief put the message values into a projection of the signal
		virtual bool	put (const IMessage* msg, int index, int step);

		/// \brief set signals to the message signals
		virtual MsgHandler::msgStatus	set (const IMessage* msg);
	
		virtual SISignalNode getSignalNode();

		// ------------------------
		// messages handling
		// ------------------------
		/// \brief osc \c 'size' message handler
		virtual MsgHandler::msgStatus sizeMsg (const IMessage* msg);

		/// \brief osc \c 'size' message handler
		virtual MsgHandler::msgStatus resetMsg (const IMessage* msg);

		/// \brief osc \c 'default' message handler
		virtual MsgHandler::msgStatus defaultMsg (const IMessage* msg);

		/// \brief incoming osc data handler
		virtual MsgHandler::msgStatus dataMsg (const IMessage* msg);

		/// \brief incoming osc projection data handler
		virtual MsgHandler::msgStatus projectionDataMsg (const IMessage* msg);
		
		class GetDefaultParamMsgHandler;
		typedef libmapping::SMARTP<GetDefaultParamMsgHandler> SGetDefaultParamMsgHandler;
		class GetDefaultParamMsgHandler : public GetParamMsgHandler {
				ISignal* fSignal;
				GetDefaultParamMsgHandler(ISignal* signal) : GetParamMsgHandler() , fSignal(signal) {}
			public:
				virtual ~GetDefaultParamMsgHandler() {}
				virtual IMessage&  print(IMessage&) const;
				static SGetDefaultParamMsgHandler create(ISignal* signal) { return new GetDefaultParamMsgHandler(signal); }
		};
};

/*! @} */

} // end namespoace

#endif
