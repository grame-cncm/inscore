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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#pragma once

#include "IMessage.h"
#include "IMessageHandlers.h"

#include <vector>

namespace inscore
{
class IFilterForward;
class IApplLog;

class ForwardEndPoint
{
	IMessage::TUrl 	fDest;

	public:
				 ForwardEndPoint (const IMessage::TUrl& url) : fDest(url) {}
		virtual ~ForwardEndPoint () {}

		virtual void send (const IMessage * imsg) = 0;
		const IMessage::TUrl& dest() const		{ return fDest; }

	protected:
		std::string IMessage2String (const IMessage * imsg, int id);
};

/*!
 * \brief The Forwarder class. Helper class to manage message forwarding.
 * A filter can be added to the Forwarder class.
 */
class Forwarder
{
	void clear();

    public:
		IApplLog * 	fLog = 0;

        /*!
         * \brief Forwarder Construct a forwarder without filter.
         */
        Forwarder(): fFilter(0) {}
        virtual ~Forwarder() {}

        /*!
         * \brief forward Apply filters and forward the message.
         * \param imsg
         */
        void forward(const IMessage * imsg);

        /*!
         * \brief processForwardMsg Process an incomming message of forward.
         * The current list of host is cleared and a new lit is created with the message parameters.
         * \param msg the message
         * \return the status.
         */
        MsgHandler::msgStatus processForwardMsg(const IMessage* msg);

        /*!
         * \brief setFilter Set a filter object to the forwarder. The filter is not deleted by this class.
         * \param filter
         */
        inline void setFilter(IFilterForward * filter) { fFilter = filter; }

        /*!
         * \brief setLog Set the log facility
         * \param log the application log
         */
        inline void setLog(IApplLog * log) { fLog = log; }

        /*!
         * \brief getForwardList Get the list of the forwarded host.
         * \return
         */
        const std::vector<IMessage::TUrl> getForwardList() const; // { return fForwardList; }


    private:
        std::vector<ForwardEndPoint*>	fForwardList;	// list of hosts to forward incoming messages
        IFilterForward * fFilter;
};

} //
