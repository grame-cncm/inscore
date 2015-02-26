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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/
#ifndef IWEBSOCKET_H
#define IWEBSOCKET_H

#include <QObject>
#include <QTimer>

#include <string>

#include "IObject.h"


namespace inscore
{	

	class IWebSocket;
	typedef class libmapping::SMARTP<IWebSocket>	SIWebSocket;

/*!
 * \brief The IWebSocket class. A web socket object to be informed when his scene is refresh and to upload a new screenshot of the scene.
 * The websocket object is initialized with a port and a minimum time in millisecond between two notifications.
 */
class IWebSocket : public IObject
{
	public:
		static const std::string kIWebSocketType;

		/*!
		 * \brief GET_IMAGE the message to get the image of the scene.
		 */
		static const char * GET_IMAGE;

		static SIWebSocket create(const std::string& name, IObject * parent)	{ return new IWebSocket(name, parent); }

		/*!
		 * \brief set
		 * \param msg Message must contain the webSocket port and a minimum time in millisecond between two notification.
		 * \return
		 */
		MsgHandler::msgStatus set (const IMessage* msg);

		/*!
		 * \brief status The websocket server status.
		 * \return The string "started" or "stopped"
		 */
		virtual std::string status () const { return "stopped"; }

	protected:
		IWebSocket(const std::string &name, IObject *parent);
		virtual ~IWebSocket();

		/*!
		 * \brief fPort port used by the websocket.
		 */
		int fPort;

		/*!
		 * \brief fFrequency minimum time between two notification.
		 */
		int fFrequency;

		/*!
		 * \brief init initalize the websocket with the parameters.
		 * \return true if the initialisation is done.
		 */
		virtual bool init() { return false; }
};

}

#endif // IWEBSOCKET_H
