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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <set>

#include "IObject.h"
#include "QMouseEventAble.h"
#include "VObjectView.h"
#include "TMessageEvaluator.h"
#include "TRefinedRelation.h"

#include "rational.h"

using namespace libmapping;
using namespace std;

namespace inscore
{

//----------------------------------------------------------------------
TFloatPoint _MouseEventAble::touchPos	( QTouchEvent* event )	{
			QList<QTouchEvent::TouchPoint> touchPoints = event->touchPoints();
			if (touchPoints.count())
//				return touchPoints[0].pos();
				return TFloatPoint (touchPoints[0].pos().x(), touchPoints[0].pos().y());
			return TFloatPoint (0., 0.);
		}

//----------------------------------------------------------------------
void _MouseEventAble::handleEvent (const IObject * obj, float x, float y,  EventsAble::eventype type)
{
	const IMessageList* msgs = obj->getMouseMsgs (type);
	if (!msgs || msgs->list().empty()) return;		// nothing to do, no associated message
	
	VObjectView*	view = obj->getView();
	float w = view->relative2SceneWidth (obj->getWidth());		// next get the object width and height
	float h = view->relative2SceneHeight(obj->getHeight());		// in scene coordinates space

	float xpos = obj->getXPos();								// here is the object position
	float ypos = obj->getYPos();								// in scene coordinates space

	float clippedx = (x < 0) ? 0 : (x > w) ? w : x;				// clip the coordinates to the object width and height
	float clippedy = (y < 0) ? 0 : (y > h) ? h : y;

	float relx = clippedx / w;									// relative position makes use of the clipped values
	float rely = clippedy / h;
	
	float scale = obj->getScale();
	float xo = view->scene2RelativeX (w * obj->getXOrigin());	// get the xorigin displacement in scene coordinates
	float yo = view->scene2RelativeY (h * obj->getYOrigin());	// get the yorigin displacement in scene coordinates

	float sx = xpos - xo + (obj->getWidth()  * scale/2 * (relx * 2 - 1));	// get the position in scene coordinates
	float sy = ypos - yo + (obj->getHeight() * scale/2 * (rely * 2 - 1));	// using the object position and the clipped coordinates

	MouseLocation mouse (relx, rely, x, y, sx, sy);
	obj->originshift(mouse.fx, mouse.fy);

	EventContext env(mouse, rational(0,1), obj);				// create a context
	TMessageEvaluator me;
	SIMessageList outmsgs = me.eval (msgs, relx, rely, env);
	if (outmsgs && outmsgs->list().size()) outmsgs->send();		// when not empty, sends the evaluated messages
}

} // end namespace
