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

#ifndef QTWEBSOCKETSERVER_H
#define QTWEBSOCKETSERVER_H

#include <QObject>
#include <QTimer>
#include <QWebSocketServer>

QT_FORWARD_DECLARE_CLASS(QWebSocket)

namespace inscore {

	class VObjectView;

class QtWebSocketServer : public QObject
{
		Q_OBJECT
	public:
		/*!
		 * \brief QtWebSocketServer Create and start the websocket server.
		 * \param port Port used by the server
		 * \param frequency Max frequency of notification
		 * \param exportedView The view to export as an image
		 * \param parent Parent object.
		 */
		QtWebSocketServer(int port, int frequency, inscore::VObjectView *exportedView, QObject *parent = 0);

		virtual ~QtWebSocketServer();

		/*!
		 * \brief isListening Status of the server.
		 * \return
		 */
		inline bool isListening() const { return fWebSocketServer->isListening(); }

	private:
		/*!
		 * \brief fWebSocketServer the web socket server.
		 */
		QWebSocketServer *fWebSocketServer;

		/*!
		 * \brief fClients List of clients.
		 */
		QList<QWebSocket *> fClients;

		/*!
		 * \brief fTimer Timer to send notification if screen has changed.
		 */
		QTimer * fTimer;

		/*!
		 * \brief fScreenVersion Screenversion to compare to the screen version manage by inscore
		 */
		unsigned long fScreenVersion;

		/*!
		 * \brief fExportedView
		 */
		VObjectView * fExportedView;

		/*!
		 * \brief fPort
		 */
		int fPort;

		/*!
		 * \brief fFrequency
		 */
		int fFrequency;

	Q_SIGNALS:
		/*!
		 * \brief closed Close the server.
		 */
		void closed();

	private Q_SLOTS:
		/*!
		 * \brief onNewConnection fired when a new client is connected.
		 */
		void onNewConnection();

		/*!
		 * \brief socketDisconnected fired when a new client is disconnected.
		 */
		void socketDisconnected();

		/*!
		 * \brief processTextMessage. Process all text message received by the websocket.
		 * Only the message "getImage" is allowed and send to the client an image in png format. Otherwise a text message with an error message is send.
		 * \param message the content of the message.
		 */
		void processTextMessage(QString message);

		/*!
		 * \brief sendNotification. Send a notification (a text message "Screen updated") to all clients when the screen have been updated.
		 */
		void sendNotification();
};
}
#endif // QTWEBSOCKETSERVER_H
