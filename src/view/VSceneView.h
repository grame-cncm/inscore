/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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


#ifndef __VSceneView__
#define __VSceneView__

#include <QGraphicsView>
#include <QObject>
#include <QTimer>

#include <string>
#include "VDummyObjectView.h"

class QGraphicsScene;
class QImage;

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/
class IScene;
class Master;
class WindowEventFilter;
class ZoomingGraphicsView;

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IScene.
*/
class VSceneView : public VDummyObjectView
{
	ZoomingGraphicsView * fGraphicsView;
	QGraphicsScene *	fScene;
	QImage *			fImage;
	WindowEventFilter * fEventFilter;
	Qt::WindowFlags		fDefaultFlags;

	// Data of a screenshot
	QByteArray			fDataScreenShot;

	// Size of the data of the screen shot
	int					fDataScreenShotSize;

	// Ask for a screenshot
	bool				fUpdateScreenShot;

	std::string			fScreenshotFormat;

	void				updateOnScreen( IScene * scene );
	void				updateOffScreen( IScene * scene );

	bool				isScreenShotReady() { return fDataScreenShotSize != 0; }

	/*!
	 * \brief setUpdateScreenShot Ask for a update of the screenshot of the scene.
	 * \param format
	 */
	void				setUpdateScreenShot(const char *format);

	public :
		using VDummyObjectView::updateView;

				 VSceneView(const std::string& address, QGraphicsScene * scene);
		virtual ~VSceneView();

		bool				copy(unsigned int* dest, int w, int h, bool smooth=false );
		void				setSceneRect(int w, int h)	{ fScene->setSceneRect(0, 0, w, h); }
		void				updateView( IScene * scene );
//		void				foreground();
		QGraphicsScene *	scene() const;

		void				updateSreenShot();

		/*!
		 * \brief getScreenShot get Screenshot data.
		 * \param format Image format of the data. This is the same format as a QT format (see QImage)
		 * \return
		 */
		const char *		getScreenShot(const char *format);
		int					getScreenShotSize() { return fDataScreenShotSize; }
};


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
	bool	fAbsoluteXY;
	bool	fFrameless;
	std::string fOSCAddress;
	QTimer * fTimer;

	public:
		WindowEventFilter(const std::string& address, QGraphicsView* parent=0 );
		bool running() const { return fTimer->isActive(); }	/// < Returns the status of timer: the timer is only running
															/// during a move/resize sequence.
		void setAbsoluteXY(bool state)	{ fAbsoluteXY = state; }
		void setFrameless(bool state)	{ fFrameless = state; }
		
	protected:
	
		bool eventFilter(QObject *obj, QEvent *event);
		void sendMessage( const char * addr , const char * cmd , float f );
		
	protected slots:
		void updateModel();
};


/*!@} */

} // end namespoace

#endif
