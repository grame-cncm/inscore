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
#ifndef WINDOWEVENTFILTER_H
#define WINDOWEVENTFILTER_H

#include <QObject>
#include <QTimer>

#include <string>

namespace inscore
{
class ZoomingGraphicsView;
/*!
\addtogroup ITLView
@{
*/

/**
*	The WindowEventFilter will detect any move or resize event
*	on its parent QGraphicsView and will send an OSC message
*	to update the model.
*
*	The OSC message won't be sent at each move or resize event, but
*	only 100ms after the end of a resize or move sequence.
*/
class WindowEventFilter : public QObject
{
    Q_OBJECT
	protected:
		std::string fOSCAddress;
		QTimer * fTimer;
		ZoomingGraphicsView * fGraphicsView ;

    public:
        WindowEventFilter(const std::string& address, ZoomingGraphicsView* parent=0 );
        virtual bool running() const { return fTimer->isActive(); }	/// < Returns the status of timer
    protected:

        bool eventFilter(QObject *obj, QEvent *event);
        void sendMessage( const char * addr , const char * cmd , float f );

	protected slots:
		virtual void updateModel() = 0;

    private:
		virtual bool isStartTimer(const QEvent *event) = 0;
};

/*!
 * \brief The ResizeMoveEventFilter class. A filter to send OSC message after a resize event.
 */
class ResizeMoveEventFilter : public WindowEventFilter
{
		Q_OBJECT
	bool	fAbsoluteXY;

    public:
		ResizeMoveEventFilter(const std::string& address, ZoomingGraphicsView* parent=0 ) : WindowEventFilter(address, parent),
		  fAbsoluteXY(false) {}
		void setAbsoluteXY(bool state)	{ fAbsoluteXY = state; }

    protected slots:
        virtual void updateModel();

    private:
		virtual bool isStartTimer(const QEvent *event);
};

/*!
 * \brief The TouchEventFilter class. A filter to send OSC message at end of touch event.
 */
class TouchEventFilter : public WindowEventFilter
{
		Q_OBJECT
	public:
        TouchEventFilter(const std::string& address, ZoomingGraphicsView* parent=0 );
        bool running() const 	{ return fIsRunning; }

	public slots:
		void noDoubleTap() 	{ fDoubleTap = false; }

   protected:
        bool eventFilter(QObject *obj, QEvent *event);
	protected slots:
		virtual void updateModel();

	private:
		virtual bool isStartTimer(const QEvent *event);

        bool fIsRunning;
	bool fDoubleTap = false;
};
/*!@} */

} // end namespoace

#endif // WINDOWEVENTFILTER_H
