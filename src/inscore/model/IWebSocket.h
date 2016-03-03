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

#include <string>

#include "IObject.h"
#include "WebSocketController.h"

namespace inscore
{	

class TParseEnv;
class IWebSocket;
typedef class libmapping::SMARTP<IWebSocket>	SIWebSocket;

/*!
 * \brief The IWebSocket class. A web socket object to be informed when his scene is refresh and to upload a new screenshot of the scene.
 * The websocket object is initialized with a port and a minimum time in millisecond between two notifications.
 */
class IWebSocket : public IObject, public WebSocketInformer
{
	WebSocketController * fWebServer;

	public:
		static const std::string	kIWebSocketType;

		static const char *			kMethodKey;		///< the method key in json object request
		static const char *			kIdKey;			///< the id key in json object request
		static const char *			kStatusKey;		///< the status key in json object response
		static const char *			kVersionKey;	///< the status key in json object request

		static SIWebSocket create(const std::string& name, IObject * parent)	{ return new IWebSocket(name, parent); }

		void	setControler (WebSocketController* ctrl)	{ fWebServer = ctrl; }

		bool			running () const;
		SIMessageList	getSetMsg () const;
		SIMessageList	getMsgs(const IMessage* msg) const;

		//------------------------------------------------------------
		// the WebSocketInformer interface
		//------------------------------------------------------------
		VObjectView*	getView() const;
		int				getPort () const			{ return fPort; }
		int				getFrequency () const		{ return fFrequency; }
		TParseEnv*		getParseEnv();

	protected:
		int fPort;			///< the web socket communnication port
		int fFrequency;		///< the notification maximum frequency

				 IWebSocket(const std::string &name, IObject *parent);
		virtual ~IWebSocket();

		bool start (int port);									///< start the web socket on port 'port'
		void del();

		// the message handlers
		MsgHandler::msgStatus set (const IMessage* msg);		///< the 'set' message handler
		std::string		status () const;						///< gives the server status
};

}

#endif // IWEBSOCKET_H
