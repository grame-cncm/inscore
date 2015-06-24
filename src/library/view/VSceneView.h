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

#include <string>
#include "VDummyObjectView.h"

class QGraphicsScene;
class QImage;
class QGestureEvent;
class QPinchGesture;
class QSwipeGesture;
class QPanGesture;
class QParallelAnimationGroup;
class QRect;

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/
class IScene;
class Master;
class ResizeMoveEventFilter;
class TouchEventFilter;
class ZoomingGraphicsView;

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of a IScene.
*/
class VSceneView : public VDummyObjectView
{
	QGraphicsScene *	fScene;
	QImage *			fImage;
	ResizeMoveEventFilter * fResizeMoveEventFilter;
	TouchEventFilter *	fTouchEventFilter;
	Qt::WindowFlags		fDefaultFlags;

	// Data of a screenshot
	QByteArray			fDataScreenShot;

	// Size of the data of the screen shot
	int					fDataScreenShotSize;

	// Ask for a screenshot
	bool				fUpdateScreenShot;

	// Version of the screen updated on each redraw of the screen.
	unsigned long		fNewVersion;

	std::string			fScreenshotFormat;

	void				updateOnScreen( IScene * scene );
	void				updateOffScreen( IScene * scene );

	bool				isScreenShotReady() { return fDataScreenShotSize != 0; }

	/*!
	 * \brief setUpdateScreenShot Ask for a update of the screenshot of the scene.
	 * \param format
	 */
	void				setUpdateScreenShot(const char *format);

	QPoint				scenePos(const IScene * scene) const;

	public :
		using VDummyObjectView::updateView;

				 VSceneView();
		virtual ~VSceneView();
		/*!
		 * \brief initialize Initialize scene view  with an address and a scene
		 * \param address the scene OSC address
		 * \param scene the QGraphicsScene or null for offscreen rendering.
		 */
        void				initializeView(const std::string& address, QGraphicsScene * scene);

		bool				copy(unsigned int* dest, int w, int h, bool smooth=false );
		void				setSceneRect(int w, int h)	{ fScene->setSceneRect(0, 0, w, h); }
		void				updateView( IScene * scene );

		/*!
		 * \brief foreground Set the scene in front of other window.
		 */
		virtual void				foreground();
		QGraphicsScene *	scene() const;
		QGraphicsView *		view()			{ return (QGraphicsView*)fGraphicsView; }

		/*!
		 * \brief updateSreenShot. Update athe screenshot if a request as been send with setUpdateScreenShot.
		 * If no request the previous scrrenshot if invalidated.
		 */
		void				updateSreenShot(bool newVersion);

		/*!
		 * \brief getScreenShot get Screenshot data.
		 * \param format Image format of the data. This is the same format as a QT format (see QImage)
		 * \return
		 */
		const AbstractData		getImage(const char *format);

		/*!
		 * \brief getVersion get the score version
		 * \return
		 */
		unsigned long		getVersion() const {
			return fNewVersion;
		}

	protected:
		ZoomingGraphicsView * fGraphicsView;

		/*!
		 * \brief createGraphicsView  create a QGraphicsView object for the GraphicsScene. The method is used in intialize method.
		 * \param scene
		 * \param address
		 * \return
		 */
		virtual ZoomingGraphicsView* createGraphicsView(QGraphicsScene * scene, const char * address);
};

/*!@} */

class ZoomingGraphicsView : public QGraphicsView
{
	std::string		fSceneAddress;
	IScene*	fScene;

	public :
		ZoomingGraphicsView(QGraphicsScene * s);
		virtual ~ZoomingGraphicsView() {}

		void setSceneAddress(const std::string& name)	{ fSceneAddress = name; }
		void setScene		(IScene* scene)		{ fScene = scene; }

		/*!
         * \brief doZoom zoom on the scene and translate the scene in the view. It use scene scale as zoom factor and xorigin / yorigin to translate the scene.
		 */
        void doZoomTranslate();

		/*!
		 * \brief getScaleFactor Get the scale factor of the scene. This value is updated after a zoom with touch gesture.
		 * \return
		 */
		qreal getScaleFactor() { return fScaleFactor; }

		/*!
		 * \brief getXOrigin Get the XOrigin of the scene. This value is updated after a zoom with touch gesture.
		 * \return
		 */
		qreal getXOrigin();

		/*!
		 * \brief getYOrigin Get the YOrigin of the scene. This value is updated after a zoom with touch gesture.
		 * \return
		 */
		qreal getYOrigin();

	protected:
		// Scale factor used during a zoom
		qreal fScaleFactor;
		// Scale factor used as reference during a zoom. It's the model scale factor.
		qreal fTotalScaleFactor;

		// Offset to translate the scene in the view.
		qreal fHorizontalOffset;
		qreal fVerticalOffset;

		QRect fSceneRect;

		virtual void	closeEvent	(QCloseEvent *);
		virtual void	paintEvent  (QPaintEvent * );

		void resizeEvent ( QResizeEvent * );
};

} // end namespoace

#endif
