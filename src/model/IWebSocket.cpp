#include "IWebSocket.h"
#include "IScene.h"
#include "VSceneView.h"

#include <QWebSocketServer>
#include <QWebSocket>

using namespace std;

namespace inscore
{
const string IWebSocket::kIWebSocketType("websocket");

const char * IWebSocket::GET_IMAGE = "getImage";

IWebSocket::IWebSocket(const std::string &name, IObject *parent) : QObject(0), IObject (name, parent),
	fWebSocketServer(new QWebSocketServer(QStringLiteral("Echo Server"),
	QWebSocketServer::NonSecureMode, this)),
	fClients()
{
	fTypeString = kIWebSocketType;
	fGetMsgHandlerMap[kstatus_GetMethod]	= TGetParamMethodHandler<IWebSocket, string (IWebSocket::*)() const>::create(this, &IWebSocket::status);
}

IWebSocket::~IWebSocket()
{
	fWebSocketServer->close();
	qDeleteAll(fClients.begin(), fClients.end());
	delete fTimer;
}

MsgHandler::msgStatus IWebSocket::set (const IMessage* msg)
{
	MsgHandler::msgStatus status = IObject::set(msg);
	if (status & (MsgHandler::kProcessed + MsgHandler::kProcessedNoChange)) return status;

	// Two parameters are mandatory : port and notification time.
	int n = msg->size();
	if (n == 3) {
		if (!msg->param(1, fPort)) {
			return MsgHandler::kBadParameters;
		}
		if (!msg->param(2, fFrequency)) {
			return MsgHandler::kBadParameters;
		}
		// Initialize Http server
		if(init())
			return MsgHandler::kProcessed;
		else {
			ITLErr << "Cannot create http server on port " << fPort << ITLEndl;
			return MsgHandler::kCreateFailure;
		}
	}
	return MsgHandler::kBadParameters;
}


void IWebSocket::onNewConnection()
{
	QWebSocket *pSocket = fWebSocketServer->nextPendingConnection();
	// Connect client to action.
	connect(pSocket, &QWebSocket::disconnected, this, &IWebSocket::socketDisconnected);
	connect(pSocket, &QWebSocket::textMessageReceived, this, &IWebSocket::processTextMessage);
	// Add client in list
	fClients << pSocket;
}

void IWebSocket::socketDisconnected()
{
	// Retrieve the client
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		// Remove the client in the list
		fClients.removeAll(pClient);
		pClient->deleteLater();
	}
}


void IWebSocket::sendNotification() {
	VSceneView *scene = static_cast<VSceneView*>(this->getScene()->getView());
	// The screen have been updated
	if(scene->isNewVersion()) {
		// Send to all clients
		QList<QWebSocket *>::iterator i;
		for (i = fClients.begin(); i != fClients.end(); ++i)  {
			(*i)->sendTextMessage("Screen updated");
		}
		scene->initNewVersion();
	}
}

void IWebSocket::processTextMessage(QString message)
{
	VSceneView *scene = static_cast<VSceneView*>(this->getScene()->getView());
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		if(message == IWebSocket::GET_IMAGE) {
			pClient->sendBinaryMessage(*(scene->getScreenShotByteArray("PNG")));
		} else {
			pClient->sendTextMessage("Error : unknown request.");
		}
	}
}

bool IWebSocket::init() {
	// Start the web socket server.
	if (fWebSocketServer->listen(QHostAddress::Any, fPort)) {
		connect(fWebSocketServer, &QWebSocketServer::newConnection,
				this, &IWebSocket::onNewConnection);
		connect(fWebSocketServer, &QWebSocketServer::closed, this, &IWebSocket::closed);

		// Fired a possible notification in each end of the timer.
		fTimer = new QTimer();
		connect(fTimer, SIGNAL(timeout()),this, SLOT(sendNotification()));
		fTimer->start(fFrequency);
		return true;
	}
	return false;
}

string IWebSocket::status () const
{
	return fWebSocketServer->isListening() ? "started": "stopped";
}

}
