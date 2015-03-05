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

#include <QTimer>
#include <QWebSocketServer>

QT_FORWARD_DECLARE_CLASS(QWebSocket)

namespace inscore {

class VObjectView;
class QtWebSocketServer : public QWebSocketServer
{
		Q_OBJECT

		QList<QWebSocket *> fClients;				///< the clients list
		QTimer				fTimer;					///< time task to check for notifications
		unsigned long		fScreenVersion;			///< version number of the screen
		VObjectView *		fView;					///< the view to be send to clients
		int					fFrequency;				///< the time task frequency

	public:
		/*!
		 * \brief QtWebSocketServer Create and start the websocket server.
		 * \param port Port used by the server
		 * \param frequency Max frequency of notifications
		 * \param view The view to be send to clients
		 * \param parent Parent object.
		 */
				 QtWebSocketServer(int frequency, VObjectView *view);
		virtual ~QtWebSocketServer();


		bool start(int port);				///< start listening on port 'port'
		void stop();						///< stop the web socket server

		void setFrequency(int frequency);	///< change the notifiactions rate
		int  getFrequency() const		{ return fFrequency; }

		int getNbClients() const { return fClients.size(); }

	private: Q_SIGNALS:
		void closed();					///< signal emitted when the server closed its connection.

	private Q_SLOTS:
		void onNewConnection();			///< slot fired when a new client is connected.
		void socketDisconnected();		///< slot fired when a client is disconnected.
		void timeTask();				///< the periodic time task, in charge of sending change notifications to clients

		/*!
		 * \brief process all text messages received by the websocket.
		 *
		 * Only the message "getImage" is allowed. An image in png format is send back to the client on "getImage" request.
		 * An error message is send for any other message.
		 * \param message the content of the message.
		 */
		void processTextMessage(QString message);
};
}
#endif // QTWEBSOCKETSERVER_H
