#ifndef IWEBSOCKET_H
#define IWEBSOCKET_H

#include <QObject>
#include <QTimer>

#include <string>

#include "IObject.h"

QT_FORWARD_DECLARE_CLASS(QWebSocketServer)
QT_FORWARD_DECLARE_CLASS(QWebSocket)

namespace inscore
{	

	class IWebSocket;
	typedef class libmapping::SMARTP<IWebSocket>	SIWebSocket;

/*!
 * \brief The IWebSocket class. A web socket object to be informed when his scene is refresh and to upload a new screenshot of the scene.
 * The websocket object is initialized with a port and a minimum time in millisecond between two notifications.
 */
class IWebSocket : public QObject, public IObject
{
		Q_OBJECT
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
		std::string status () const;

	protected:
			IWebSocket(const std::string &name, IObject *parent);
			virtual ~IWebSocket();

	private:
		/*!
		 * \brief fPort port used by the websocket.
		 */
		int fPort;

		/*!
		 * \brief fFrequency minimum time between two notification.
		 */
		int fFrequency;

		/*!
		 * \brief fWebSocketServer the web socket server.
		 */
		QWebSocketServer *fWebSocketServer;

		/*!
		 * \brief fClients List of clients.
		 */
		QList<QWebSocket *> fClients;
		QTimer * fTimer;

		/*!
		 * \brief init initalize the websocket with the parameters.
		 * \return true if the initialisation is done.
		 */
		bool init();

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

#endif // IWEBSOCKET_H
