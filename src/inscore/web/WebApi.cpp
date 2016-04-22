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

  Grame Research Laboratory, 11 cours Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <sstream>
#include <fstream>
#include <cstring>

#include <QByteArray>
#include <QWaitCondition>
#include <QMutex>
#include <QEvent>
#include <QGraphicsSceneMouseEvent>

#include "WebApi.h"
#include "VSceneView.h"
#include "ITLparser.h"
#include "IAppl.h"

using namespace std;

namespace inscore
{
    const char * WebApi::kVersionMsg = "version";
    const char * WebApi::kGetImgMsg = "image";
    const char * WebApi::kPostCmdMsg = "post";
    const char * WebApi::kClickMsg = "click";
	const char * WebApi::kHoverMsg = "hover";
	const char * WebApi::kFileMsg = "file";

	extern QWaitCondition gModelUpdateWaitCondition;	///< a wait condition to wait for model update.
    QMutex WebApi::fPostCommandMutex;

//------------------------------------kHoverMsg-------------------------------------------.
unsigned long WebApi::getVersion()
{
    return fView->getVersion();
}

//-------------------------------------------------------------------------------.
AbstractData WebApi::getImage(bool base64)
{
    AbstractData data = fView->getImage("PNG");
    if(base64) {
        QByteArray bArray = QByteArray::fromRawData(data.data, data.size);
        bArray = bArray.toBase64();
		data.size = bArray.size() + 1;
        data.data = new char[data.size];
        strcpy(data.data, bArray.data());
    }
    return data;
}

//-------------------------------------------------------------------------------.
std::string WebApi::postScript(const std::string &inscoreScript)
{
    stringstream stream;
    stream.str(inscoreScript);
    ITLparser p (&stream, 0, fParseEnv);

    // wait for other network users
	fPostCommandMutex.lock();

	oscerr.activeConcatError(true);
	SIMessageList msgs = p.parse();
	oscerr.activeConcatError(false);

	string logParse = oscerr.streamConcat().str();

	if(msgs->list().size()) {
		// Add messages to network stack
		msgs->sendWebMsg();
		// Wait for a model update from time task
		gModelUpdateWaitCondition.wait(&fPostCommandMutex);
	}
    // Get back log and unlock
	string logExec = oscerr.streamConcat().str();
	fPostCommandMutex.unlock();
	return logParse + logExec;
}

//-------------------------------------------------------------------------------.
std::string WebApi::postMouseClick(int x, int y)
{
    // Get item from coordinate in pixel.
    QGraphicsItem * item = getItem(x, y);

    if(item) {
        // Create and send a mouse event to the item
        sendEvent(item, QEvent::GraphicsSceneMousePress);
        return "";
    }
    return "Unknown object";
}

//-------------------------------------------------------------------------------.
std::string WebApi::postMouseHover(int x, int y)
{
	// Leave previous item
	if(fPreviousX != -1 && fPreviousY != -1) {
		QGraphicsItem * item = getItem(fPreviousX, fPreviousY);
		if(item) {
			// Create and send a mouse event to the item
			sendEvent(item, QEvent::GraphicsSceneHoverLeave);
		}
	}
	// Get current item from coordinate in pixel.
	QGraphicsItem * item = getItem(x, y);

	if(item) {
		// Create and send a mouse event to the item
		sendEvent(item, QEvent::GraphicsSceneHoverEnter);
		fPreviousX = x;
		fPreviousY = y;
		return "";
	}
	return "Unknown object";
}

//-------------------------------------------------------------------------------.
QGraphicsItem * WebApi::getItem(int x, int y)
{
        VSceneView * sceneView = dynamic_cast<VSceneView *>(fView);
        if(sceneView) {
                QGraphicsView* view = sceneView->view();

                // get item at position (x and y in pixel coordinate)
                return view->itemAt(x, y);
        }
        return 0;
}

//-------------------------------------------------------------------------------.
void WebApi::sendEvent(QGraphicsItem * item, int eventType)
{
        VSceneView * sceneView = dynamic_cast<VSceneView *>(fView);
        // Create an event
        QGraphicsSceneMouseEvent event((QEvent::Type) eventType);
        // Coordinate of the click in item coordinate
        QPointF point(0, 0);
        event.setPos(point);
        event.setButton(Qt::LeftButton);
        event.setButtons(Qt::LeftButton);

        if(!item->isEnabled())
            item->setEnabled(true);

        QGraphicsScene * scene = sceneView->scene();
        scene->sendEvent(item, &event);
}

//--------------------------------------------------------------------------
AbstractData WebApi::readFile(const std::string& relativePath, bool base64)
{
	string path = getAbsoluteFilePath(relativePath);
	AbstractData data;
	data.data = 0;
	data.size = 0;

	if(!path.empty()) {
		ifstream file;
		file.open (path.c_str(), ifstream::binary);
		if (file.is_open()) {
			// get length of file:
			file.seekg (0, file.end);
			data.size = file.tellg();
			file.seekg (0, file.beg);

			if (data.size) {
				// allocate memory:
				data.data = new char [data.size];
				// read data as a block:
				file.read (data.data, data.size);

				if(base64) {
					QByteArray bArray = QByteArray::fromRawData(data.data, data.size);
					bArray = bArray.toBase64();
					delete data.data;
					data.size = bArray.size() + 1;
					data.data = new char[data.size];
					strcpy(data.data, bArray.data());
				}
			}
			file.close();
		}
	}
	return data;
}

//-------------------------------------------------------------------------------.
string WebApi::getAbsoluteFilePath(const std::string &relativePath)
{
	if(relativePath.find("../") != string::npos)
		return "";
	return IAppl::absolutePath(relativePath);
}

//-------------------------------------------------------------------------------.
const char * WebApi::getMimetype(const string &filepath)
{
	string::size_type pos = filepath.rfind(".");
	string extension;
	if(pos != string::npos) {
		extension = filepath.substr(pos + 1);
	}
	if(extension == "inscore" || extension == "txt")
		return "text/plain";
	else if(extension == "pdf")
		return "application/pdf";
	else if(extension == "png")
		return "image/png";
	else if(extension == "jpeg" || extension == "jpg")
		return "image/jpeg";
	return "application/octet-stream";
}

}
