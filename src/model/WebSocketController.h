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

#ifndef WEBSOCKETCONTROLLER_H
#define WEBSOCKETCONTROLLER_H


namespace inscore
{

class VObjectView;

/*!
 * \brief An abstract implementation of a web socket.
 */
class WebSocketInformer
{
	public:
				 WebSocketInformer() {}
		virtual ~WebSocketInformer() {}

		virtual VObjectView*	getView() const			= 0;
		virtual int				getFrequency() const	= 0;
		virtual int				getPort() const			= 0;
};

/*!
 * \brief An abstract implementation of a web socket.
 */
class WebSocketController
{
	public:
				 WebSocketController() {}
		virtual ~WebSocketController() {}

		/*!
		 * \brief initalize and start the websocket.
		 * \param port the communication port number.
		 * \param frequency the maximum refreshment rate.
		 * \return true if the initialisation is done.
		 */
		virtual bool	start(int port)					= 0;
		virtual void	setFrequency(int frequency)		= 0;
		virtual void	stop()							= 0;
		virtual bool	running () const				= 0;
		virtual int		nbClients () const				= 0;
};

}

#endif // QTWEBSOCKETCONTROLLER_H
