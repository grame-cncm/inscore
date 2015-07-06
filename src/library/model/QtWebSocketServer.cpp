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

#include <QWebSocket>
#include <string>
#include <iostream>
#include <sstream>

#include "QtWebSocketServer.h"
#include "IWebSocket.h"
#include "VObjectView.h"
#include "VSceneView.h"
#include "abstractdata.h"
#include "WebApi.h"

#include "json_object.h"
#include "json_element.h"
#include "json_parser.h"

using namespace std;
using namespace json;

namespace inscore {

//-------------------------------------------------------------------------------
QtWebSocketServer::QtWebSocketServer(int frequency, WebApi * api) :
	QWebSocketServer(QStringLiteral("WebSocketServer"), QWebSocketServer::NonSecureMode),
	fScreenVersion(0), fFrequency(frequency), fWebApi(api)
{
	connect(&fTimer, SIGNAL(timeout()),this, SLOT(timeTask()));
}

//-------------------------------------------------------------------------------
QtWebSocketServer::~QtWebSocketServer()
{
	stop();
}

//-------------------------------------------------------------------------------
bool QtWebSocketServer::start(int port)
{
	stop();										// stop the server, in case it's already running

	if (listen(QHostAddress::Any, port)) {		// and start listening in port 'port'
		connect(this, &QWebSocketServer::newConnection, this, &QtWebSocketServer::onNewConnection);
		connect(this, &QWebSocketServer::closed, this, &QtWebSocketServer::closed);
		fTimer.start(fFrequency);
		return true;
	}
	return false;
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::stop()
{
	fTimer.stop ();
	// Wait for the end of all client responses
	fLock.lockForWrite();
	close();										// close the server
	qDeleteAll(fClients.begin(), fClients.end());	// and delete all the clients.
	fClients.clear();
	fLock.unlock();
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::onNewConnection()
{
	QWebSocket *pSocket = nextPendingConnection();
	// Connect client to action.
	connect(pSocket, &QWebSocket::disconnected, this, &QtWebSocketServer::socketDisconnected);
	connect(pSocket, &QWebSocket::textMessageReceived, this, &QtWebSocketServer::processTextMessage);
	fClients << pSocket;		// add the client to the clients list
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::socketDisconnected()
{
	// Retrieve the client
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		// Remove the client in the list
		fClients.removeAll(pClient);
		pClient->deleteLater();
	}
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::timeTask()
{
	// lock for read to not close server before end of this method
	fLock.lockForRead();
	unsigned int version = fWebApi->getVersion();
	if(version != fScreenVersion) {		// check for view updates
		fScreenVersion = version;
		json_object *response = new json_object;
		json_element *elem = new json_element("notification", new json_true_value);
		response->add(elem);
		elem = new json_element(IWebSocket::kVersionKey, new json_int_value(fScreenVersion));
		response->add(elem);
		std::ostringstream mystream;
		json_stream jstream(mystream);
		response->print(jstream);
		const char * message = mystream.str().c_str();
		delete response;
		// The screen have been updated, send notifications to all the clients
		QList<QWebSocket *>::iterator i;
		for (i = fClients.begin(); i != fClients.end(); ++i)  {
			(*i)->sendTextMessage(message);
		}
	}
	fLock.unlock();
}

//-------------------------------------------------------------------------------
void QtWebSocketServer::processTextMessage(QString message)
{
	// lock for read to not close server before end of this method
	fLock.lockForRead();
	QWebSocket *pClient = qobject_cast<QWebSocket *>(sender());
	if (pClient) {
		// Transform request in json object.
		json_object * request = getRequestJsonObject(message.toStdString());

		const string & method = getMethod(request);
		// Verify message and get back image and send it

		json_object * response;
		if(method == WebApi::kVersionMsg) {
			response = getVersion(request);
		} else
		if(method == WebApi::kGetImgMsg) {
			response = getImage(request);
		} else
		if(method == WebApi::kPostCmdMsg) {
			response = postCommand(request);
		} else
		if(method == WebApi::kClickMsg) {
			response = mouseEvent(request, true);
		} else
		if(method == WebApi::kHoverMsg) {
			response = mouseEvent(request, false);
		} else
		if(method == WebApi::kFileMsg) {
			response = getFile(request);
		} else {
			response = getErrorObject(getId(request), "Bad request");
		}
		std::ostringstream mystream;
		json_stream jstream(mystream);
		response->print(jstream);
		qDebug() << "pClient->sendTextMessage(mystream.str().c_str())";
		pClient->sendTextMessage(mystream.str().c_str());
		delete response;
	}
	fLock.unlock();
}

//-------------------------------------------------------------------------------
json_object * QtWebSocketServer::getRequestJsonObject(string request)
{
	// Create a stream
	istringstream stream(request);
	// Initialise parser
	json_parser parser(&stream);
	// Parse the string
	return parser.parse();
}

//-------------------------------------------------------------------------------
json_object * QtWebSocketServer::getSuccesObject(const string &id)
{
	json_object *success = new json_object;
	json_element* elem = new json_element(IWebSocket::kIdKey, new json_string_value(id.c_str()));
	success->add(elem);
	elem = new json_element(IWebSocket::kStatusKey, new json_string_value("OK"));
	success->add(elem);
	return success;
}

//-------------------------------------------------------------------------------
json_object * QtWebSocketServer:: getErrorObject(const string &id, const string &message)
{
	json_object *error = new json_object;
	json_element* elem = new json_element(IWebSocket::kIdKey, new json_string_value(id.c_str()));
	error->add(elem);
	elem = new json_element(IWebSocket::kStatusKey, new json_string_value("ERROR"));
	error->add(elem);
	elem = new json_element("error", new json_string_value(message.c_str()));
	error->add(elem);
	return error;
}

//-------------------------------------------------------------------------------
const string QtWebSocketServer::getId(json_object * request)
{
	if(request) {
		const json_element* idelem = request->getKey(IWebSocket::kIdKey);
		if(idelem) {
			// Try with a string id and an integer id
			const json_string_value * valueString = dynamic_cast<const json_string_value *>(idelem->value());
			if(valueString)
				return valueString->getValue();
			const json_int_value * valueInt = dynamic_cast<const json_int_value *>(idelem->value());
			if(valueInt) {
				ostringstream temp;
				temp << valueInt->getValue();
				return temp.str();
			}
		}
	}
	return "";
}

//-------------------------------------------------------------------------------
const string QtWebSocketServer::getMethod(json_object * request)
{
	if(request) {
		const json_element* element = request->getKey(IWebSocket::kMethodKey);
		if(element) {
			const json_string_value * value = dynamic_cast<const json_string_value *>(element->value());
			if(value)
				return value->getValue();
		}
	}
	return "";
}

//-------------------------------------------------------------------------------
json_object * QtWebSocketServer::getVersion(json_object * request)
{
	string id = getId(request);
	if (!id.empty()) {
		unsigned long version = fWebApi->getVersion();
		json_object *response = getSuccesObject(id);
		json_element* elem  = new json_element(IWebSocket::kVersionKey, new json_int_value(version));
		response->add(elem);
		return response;
	} else {
		return getErrorObject(id, "Bad request");
	}
}

//-------------------------------------------------------------------------------
json_object * QtWebSocketServer::getImage(json_object * request)
{
	string id = getId(request);
	if (!id.empty()) {
		AbstractData data = fWebApi->getImage(true);

		if(data.size == 0) {
			return getErrorObject(id, "Cannot create score image");
		}
		json_object *response = getSuccesObject(id);
		json_element* elem  = new json_element(IWebSocket::kVersionKey, new json_int_value(data.version));
		response->add(elem);
		elem = new json_element("mimeType", new json_string_value("image/png"));
		response->add(elem);
		elem = new json_element("image", new json_string_value(data.data));
		response->add(elem);
		delete[] data.data;
		return response;
	}
	return getErrorObject(id, "Bad request");
}

//-------------------------------------------------------------------------------
json_object * QtWebSocketServer::postCommand(json_object * request)
{
	string id = getId(request);
	if (!id.empty()) {
		const json_element* element = request->getKey("data");
		if(element) {
			const json_string_value * value = dynamic_cast<const json_string_value *>(element->value());
			if(value) {
				string log = fWebApi->postScript(value->getValue());

				if(log.empty()) {
					return getSuccesObject(id);
				} else {
					return getErrorObject(id, log);
				}
			}
		}
	}
	return getErrorObject(id, "Bad request");
}

//-------------------------------------------------------------------------------
json_object * QtWebSocketServer::mouseEvent(json_object * request, bool isClick)
{
	string id = getId(request);
	if (!id.empty()) {
		int x = -1;
		int y = -1;
		const json_element* element = request->getKey("x");
		if(element) {
			const json_int_value * value = dynamic_cast<const json_int_value *>(element->value());
			if(value)
				x = value->getValue();
		}
		element = request->getKey("y");
		if(element) {
			const json_int_value * value = dynamic_cast<const json_int_value *>(element->value());
			if(value)
				y = value->getValue();
		}
		if (x != -1 && y != -1) {
			string log;
			if(isClick)
				log = fWebApi->postMouseClick(x, y);
			else
				log = fWebApi->postMouseHover(x, y);
			if(log.empty()) {
				return getSuccesObject(id);
			} else {
				getErrorObject(id, log);
			}
		}
	}
	return getErrorObject(id, "Bad request");
}

//-------------------------------------------------------------------------------
json_object * QtWebSocketServer::getFile(json_object * request)
{
	string id = getId(request);
	if (!id.empty()) {
		const json_element* element = request->getKey("path");
		if(element) {
			const json_string_value * value = dynamic_cast<const json_string_value *>(element->value());
			string file = value->getValue();
			if(value) {
				AbstractData data = fWebApi->readFile(file, true);

				if(data.size == 0) {
					return getErrorObject(id, "File not found");
				}

				json_object *response = getSuccesObject(id);
				const json_element* elem = new json_element("mimeType", new json_string_value(fWebApi->getMimetype(file)));
				response->add(elem);

				elem = new json_element("file", new json_string_value(data.data));
				response->add(elem);
				delete[] data.data;
				return response;
			}
		}
	}
	return getErrorObject(id, "Bad request");
}

}
