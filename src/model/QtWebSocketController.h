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

/*!
 * \brief The Thread class. Specific thread to run the websocket server.
 */
class Thread : public QThread
{
		Q_OBJECT
	public:
		/*!
		 * \brief Thread
		 * \param port
		 * \param frequency
		 * \param exportedView
		 * \param parent
		 */
		Thread(int port, int frequency, VObjectView *exportedView, QObject *parent = 0);
		virtual ~Thread();

		/*!
		 * \brief isListening Verify status of server
		 * \return a boolean
		 */
		inline bool isListening() const { return fServer->isListening(); }

		/*!
		 * \brief changeFrequency
		 * \param frequency
		 */
		void changeFrequency(int frequency);

		/*!
		 * \brief changePort change communication port
		 * \param port
		 * \return
		 */
		bool changePort(int port);
	Q_SIGNALS:
		/*!
		 * \brief signalPort a signal to change communication port.
		 * \param port
		 */
		void signalPort(int port);
	protected:
		/*!
		 * \brief run Main function.
		 */
		void run();

	private:
		/*!
		 * \brief fExportedView the view exported in image
		 */
		VObjectView * fExportedView;

		/*!
		 * \brief fPort Port used by the socket server
		 */
		int fPort;

		/*!
		 * \brief fFrequency
		 */
		int fFrequency;

		/*!
		 * \brief fServer the server
		 */
		QtWebSocketServer * fServer;
};

/*!
 * \brief The QtWebSocketController class. A Qt implementation of IWebSocket. It create and start the websocket server in a new thread.
 */
class QtWebSocketController : public QObject, public IWebSocket
{
		Q_OBJECT
	public:
		static QtWebSocketController* create(const std::string& name, IObject * parent)	{ return new QtWebSocketController(name, parent); }

		/*!
		 * \brief status
		 * \return a string "started" or "stopped"
		 */
		inline std::string status () const { return fThreadServer->isListening() ? "started": "stopped"; }

	protected:
		explicit QtWebSocketController(const std::string& name, IObject * parent);
		virtual ~QtWebSocketController();

		/*!
		 * \brief init initalize the websocket with the parameters.
		 * \return true if the initialisation is done.
		 */
		bool init(int port, int frequency);

	private:
		/*!
		 * \brief fThreadServer The thread for the server.
		 */
		Thread *fThreadServer;
};

}

#endif // QTWEBSOCKETCONTROLLER_H
