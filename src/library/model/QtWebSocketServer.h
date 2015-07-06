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
#include <QReadWriteLock>
#include "WebApi.h"

QT_FORWARD_DECLARE_CLASS(QWebSocket)
QT_FORWARD_DECLARE_CLASS(QGraphicsItem)

namespace json {
class json_object;
}

namespace inscore {

class VObjectView;
class TLua;

/*!
 * \brief The QtWebSocketServer class. A Qt websocket server implementation.
 */
class QtWebSocketServer : public QWebSocketServer
{
		Q_OBJECT

		QList<QWebSocket *> fClients;				///< the clients list
		QTimer				fTimer;					///< time task to check for notifications
		unsigned long		fScreenVersion;			///< version number of the screen
		int					fFrequency;				///< the time task frequency
		WebApi *			fWebApi;				///< the WebApi object to execute reqeuest
		QReadWriteLock		fLock;					///< mutex used to stop server correctly.

	public:
		/*!
		 * \brief QtWebSocketServer Create and start the websocket server.
		 * \param port Port used by the server
		 * \param frequency Max frequency of notifications
		 * \param view The view to be send to clients
		 * \param parent Parent object.
		 */
				 QtWebSocketServer(int frequency, WebApi * api);
		virtual ~QtWebSocketServer();


		bool start(int port);				///< start listening on port 'port'
		void stop();						///< stop the web socket server
		int getClients() const { return fClients.size(); }	///< get the number of clients

	private: Q_SIGNALS:
		void closed();					///< signal emitted when the server closed its connection.

	private Q_SLOTS:
		void onNewConnection();			///< slot fired when a new client is connected.
		void socketDisconnected();		///< slot fired when a client is disconnected.
		void timeTask();				///< the periodic time task, in charge of sending change notifications to clients

		/*!
		 * \brief process all text messages received by the websocket.
		 * \param message the content of the message.
		 */
		void processTextMessage(QString message);

	private:
		/*!
		 * \brief getId Get the request id. Id in json object can be a integer value or a string value.
		 * \param request a request json object
		 * \return a string id
		 */
		const std::string getId(json::json_object * request);

		/*!
		 * \brief getMethod Get the method of the request
		 * \param request a request json object
		 * \return the method.
		 */
		const std::string getMethod(json::json_object * request);

		/*!
		 * \brief getSuccesObject Create a default success object.
		 * \param id the request id to respond to.
		 * \return
		 */
		json::json_object * getSuccesObject(const std::string &id);

		/*!
		 * \brief getErrorObject Get default error object
		 * \param id the request id to respond to.
		 * \param message an error message to add to the response
		 * \return
		 */
		json::json_object * getErrorObject(const std::string& id, const std::string& message);

		/*!
		 * \brief getRequestJsonObject Get a json object from the received string.
		 * \param request
		 * \return
		 */
		json::json_object * getRequestJsonObject(std::string request);

		/*!
		 * \brief getVersion Execute get version request.
		 * \param request the request json object
		 * \return the response json object.
		 */
		json::json_object *getVersion(json::json_object * request);

		/*!
		 * \brief getImage Process the get image request.
		 * \param request the request json object
		 * \return the response json object.
		 */
		json::json_object *getImage(json::json_object * request);

		/*!
		 * \brief postCommand Process the post inscore script request.
		 * \param request the request json object
		 * \return the response json object.
		 */
		json::json_object *postCommand(json::json_object * request);

		/*!
		 * \brief mouseEvent Process the mouse event request.
		 * \param request the request json object
		 * \return the response json object.
		 */
		json::json_object *mouseEvent(json::json_object * request, bool isClick);

		/*!
		 * \brief getFile Process a get file message
		 * \param request the request json object
		 * \return the response json object.
		 */
		json::json_object *getFile(json::json_object * request);
};
}
#endif // QTWEBSOCKETSERVER_H
