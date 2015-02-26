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
#ifndef QTWEBSOCKETCONTROLLER_H
#define QTWEBSOCKETCONTROLLER_H

#include "IWebSocket.h"
#include "QtWebSocketServer.h"

#include <QThread>
#include <QObject>

namespace inscore
{

class QtWebSocketController : public QObject, public IWebSocket
{
		Q_OBJECT
	public:
		static QtWebSocketController* create(const std::string& name, IObject * parent)	{ return new QtWebSocketController(name, parent); }
		std::string status () const { return fServer->isListening() ? "started": "stopped"; }

	protected:
		explicit QtWebSocketController(const std::string& name, IObject * parent);
		virtual ~QtWebSocketController();

		/*!
		 * \brief init initalize the websocket with the parameters.
		 * \return true if the initialisation is done.
		 */
		bool init();

	private:
		QThread workerThread;
		QtWebSocketServer * fServer;

};

}

#endif // QTWEBSOCKETCONTROLLER_H
