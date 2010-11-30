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

namespace INScore
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
class VSceneView
{
	ZoomingGraphicsView * fGraphicsView;
	QGraphicsRectItem * fBackground;
	WindowEventFilter * fEventFilter;

	public :
				 VSceneView(QGraphicsScene * scene);
		virtual ~VSceneView();

		void				updateView( IScene * scene );
		QGraphicsScene *	scene() const;
};


/**
*	\brief The WindowEventFilter will detect any move or resize event
*	on its parent QGraphicsView and will send an OSC message
*	to update the model /ITL/scene.
*	
*	The OSC message won't be sent at each move or resize event, but
*	only 100ms after the end of a resize or move sequence.
*/
class WindowEventFilter : public QObject
{
	Q_OBJECT

	QTimer * fTimer;

	public:
		WindowEventFilter( QGraphicsView* parent=0 );
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
