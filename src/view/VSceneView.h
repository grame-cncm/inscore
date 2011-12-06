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
	QGraphicsRectItem * fBackground;
	QGraphicsScene *	fScene;
	QImage *			fImage;
	WindowEventFilter * fEventFilter;

	void				updateOnScreen( IScene * scene );
	void				updateOffScreen( IScene * scene );

	public :
				 VSceneView(const std::string& address, QGraphicsScene * scene);
		virtual ~VSceneView();

		bool				copy(unsigned int* dest, int w, int h, bool smooth=false );
		void				setSceneRect(int w, int h)	{ fScene->setSceneRect(0, 0, w, h); }
		void				updateView( IScene * scene );
//		void				foreground();
		QGraphicsScene *	scene() const;
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

	std::string fOSCAddress;	
	QTimer * fTimer;

	public:
		WindowEventFilter(const std::string& address, QGraphicsView* parent=0 );
		bool running() const { return fTimer->isActive(); }	/// < Returns the status of timer: the timer is only running
															/// during a move/resize sequence.
		
	protected:
	
		bool eventFilter(QObject *obj, QEvent *event);
		void sendMessage( const char * addr , const char * cmd , float f );
		
	protected slots:
		void updateModel();
};


/*!@} */

} // end namespoace

#endif
