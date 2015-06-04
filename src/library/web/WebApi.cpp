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
#include "WebApi.h"
#include "VObjectView.h"
#include "VSceneView.h"
#include "ITLparser.h"
#include "abstractdata.h"

#include <QByteArray>
#include <QWaitCondition>
#include <QMutex>
#include <QEvent>

#include <sstream>
#include <cstring>

using namespace std;

namespace inscore
{
    const char * WebApi::kVersionMsg = "version";
    const char * WebApi::kGetImgMsg = "image";
    const char * WebApi::kPostCmdMsg = "post";
    const char * WebApi::kClickMsg = "click";

	extern QWaitCondition gModelUpdateWaitCondition;	///< a wait condition to wait for model update.
    QMutex WebApi::fPostCommandMutex;

//-------------------------------------------------------------------------------.
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
    ITLparser p (&stream, 0, fJsEngine, fLua);
    SIMessageList msgs = p.parse();

    // wait for other network users
    fPostCommandMutex.lock();
    // Add messages to network stack
    msgs->sendWebMsg();
    // Wait for a model update from time task
    gModelUpdateWaitCondition.wait(&fPostCommandMutex);
    // Get back log and unlock
    string log = oscerr.streamConcat().str();
    fPostCommandMutex.unlock();
	return log;
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

}
