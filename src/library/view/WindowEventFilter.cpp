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

#include <QApplication>
#include <QDesktopWidget>

#include "WindowEventFilter.h"
#include "VSceneView.h"
#include "INScore.h"

namespace inscore
{

//--------------------------------------------------------------------------
WindowEventFilter::WindowEventFilter(const std::string& address, ZoomingGraphicsView *parent)
		: QObject(parent), fOSCAddress(address), fGraphicsView(parent)
{
        fTimer = new QTimer(this);
        fTimer->setSingleShot(true);
        connect(fTimer, SIGNAL(timeout()), this, SLOT(updateModel()));
}

//--------------------------------------------------------------------------
void WindowEventFilter::sendMessage( const char * addr , const char * cmd , float f )
{
        INScore::MessagePtr msg = INScore::newMessage( cmd );
        INScore::add(msg, f);
        INScore::postMessage( addr , msg );
}

//--------------------------------------------------------------------------
bool WindowEventFilter::eventFilter(QObject *obj, QEvent *event)
{
		if (isStartTimer(event))
		{
                fTimer->stop();
                fTimer->start(100);
                return false;
        }
        else
                // standard event processing
        return QObject::eventFilter(obj, event);
}

//--------------------------------------------------------------------------
bool ResizeMoveEventFilter::isStartTimer(const QEvent *event)
{
    return !fFrameless && !fFullScreen && ((event->type() == QEvent::Move) || (event->type() == QEvent::Resize));
}

//--------------------------------------------------------------------------
void ResizeMoveEventFilter::updateModel()
{
        if (fFrameless || Qt::NoButton != QApplication::mouseButtons())
                return;

        QWidget * view = dynamic_cast<QWidget *>(parent());
        if ( !view ) {
                qFatal("WindowEventFilter::update(): WindowEventFilter parent must be a QWidget");
                return;
        }

        float x, y;
        QRect r = QApplication::desktop()->screenGeometry();
        float lowestDimension = qMin( r.width(), r.height() );
        if (fAbsoluteXY) {
                x = view->pos().x();
                y = view->pos().y();
        }
        else {
                QPointF screenCenter = r.center();

                x = (view->pos().x() + view->width()/2.0f - screenCenter.x()) / (lowestDimension/2.0f);
                y = (view->pos().y() + view->height()/2.0f - screenCenter.y()) / (lowestDimension/2.0f);
        }
        sendMessage( fOSCAddress.c_str() , kx_GetSetMethod , x );
        sendMessage( fOSCAddress.c_str() , ky_GetSetMethod , y );

        float width = view->width() / (lowestDimension/2.0f);
        float height = view->height() / (lowestDimension/2.0f);
        sendMessage( fOSCAddress.c_str() , kwidth_GetSetMethod , width );
        sendMessage( fOSCAddress.c_str() , kheight_GetSetMethod , height );
}

//--------------------------------------------------------------------------
bool TouchEventFilter::isStartTimer(const QEvent *event)
{
	return event->type() == QEvent::TouchEnd;
}

//--------------------------------------------------------------------------
void TouchEventFilter::updateModel()
{
    // Send Message for scene zoom (scale) and position (xorigin and yorigin)
    sendMessage(fOSCAddress.c_str(), kscale_GetSetMethod, fGraphicsView->getScaleFactor());
	sendMessage(fOSCAddress.c_str(), kxorigin_GetSetMethod, fGraphicsView->getXOrigin());
	sendMessage(fOSCAddress.c_str(), kyorigin_GetSetMethod, fGraphicsView->getYOrigin());
}


} // end namespoace
