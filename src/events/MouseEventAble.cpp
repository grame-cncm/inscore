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

#include <QDebug>
#include <set>

#include "MouseEventAble.h"
#include "VGraphicsItemView.h"
#include "TMessageEvaluator.h"
#include "TRefinedRelation.h"

#include "rational.h"

using namespace libmapping;
using namespace std;

namespace inscore
{

//----------------------------------------------------------------------
/** \brief converts a point to a date in the context of an object and a given map
*
*	\param obj		the object context
*	\param x		the point x coordinate
*	\param y		the point y coordinate
*	\param mapname	the map to be used for conversion
*	\param n		the repeat number to be retrieved (indexed from 0)
*/
rational _MouseEventAble::point2date (const IObject * obj, float x, float y, const std::string& mapname, int n)
{
	rational nodate(0,0);
	const SRelativeTime2GraphicMapping&	mapping = obj->getMapping (mapname);	// get the mapping first
	if (!mapping) return nodate;												// failed to get the mapping
	
	GraphicSegment gseg (x, y, x+1, y+1);
	SGraphicSegmentation gset = GraphicSegmentation::create(gseg);				// create a graphic segmentation
	gset->add (gseg);															// and adds a segment starting at x, y

	TRefinedRelation<float,2,rational,1> g2rt (mapping->reverse(), gset);		// defines a refined relation using this segmentation
	set<RelativeTimeSegment> dates = g2rt.get (gseg);							// and query the relation to get the dates associated to x, y
	
	for (set<RelativeTimeSegment>::const_iterator i = dates.begin(); i != dates.end(); i++, n--) {
		// n is used in case of repeated sections to select a given repetition
		if (n == 0) {
			rational outdate = i->start();		// returns the time segment start, that corresponds to x, y
			outdate.rationalize();
			while (outdate.getNumerator() > 0xfffffff)  // check for int overflow
				// this is necessary because the value is sent over OSC and thus cast to osc-int
				outdate.set(outdate.getNumerator()/2, outdate.getDenominator()/2);
			return outdate;
		}
	}
	return nodate;							// no such segment or repeat
}

//----------------------------------------------------------------------
static void originshift (const IObject * obj, float& relx, float& rely)
{
	float xoriginscaled = (obj->getXOrigin() + 1) / 2.;
	float yoriginscaled = (obj->getYOrigin() + 1) / 2.;
	relx = xoriginscaled - relx;
	rely = yoriginscaled - rely;
	if (relx < 0) relx = -relx;
	if (rely < 0) rely = -rely;
}

//----------------------------------------------------------------------
SIMessageList _MouseEventAble::eval (const IMessageList* msgs, float x, float y, EventContext& env)
{
	TMessageEvaluator me;
	SIMessageList outmsgs = IMessageList::create();
	for (unsigned int i=0; i < msgs->list().size(); i++) {
		const IMessage* msg = msgs->list()[i];

		std::string mapname;
		if (me.hasDateVar (msg, mapname))
			env.date = point2date (env.object, x, y, mapname, 0);

		SIMessage evaluated = me.eval (msg, env);
		if (evaluated) outmsgs->list().push_back(evaluated);
	}
	return outmsgs;
}

//----------------------------------------------------------------------
void _MouseEventAble::handleEvent (const IObject * obj, QPointF pos,  EventsAble::eventype type)
{
	const IMessageList* msgs = obj->getMouseMsgs (type);
	if (!msgs || msgs->list().empty()) return;		// nothing to do, no associated message
	
	VObjectView*	view = obj->getView();
	float x = pos.x();
	float y = pos.y();
	float w = view->relative2SceneWidth (obj->getWidth());
	float h = view->relative2SceneHeight(obj->getHeight());

	float xpos = obj->getXPos();
	float ypos = obj->getYPos();

	float clippedx = (x < 0) ? 0 : (x > w) ? w : x;
	float clippedy = (y < 0) ? 0 : (y > h) ? h : y;

	float relx = clippedx / w;
	float rely = clippedy / h;

	float sx = xpos + (obj->getWidth()  * obj->getScale()/2 * (relx * 2 - 1));
	float sy = ypos + (obj->getHeight() * obj->getScale()/2 * (rely * 2 - 1));

	MouseLocation mouse (relx, rely, x, y, sx, sy);
	originshift (obj, mouse.fx, mouse.fy);

//if (type == EventsAble::kMouseDown)
//qDebug() << "handle event pos " << " w/h " << w << h << "xy" << relx << rely << pos ;
	
	EventContext env(mouse, rational(0,1), obj);
	SIMessageList outmsgs = eval (msgs, relx, rely, env);
	if (outmsgs && outmsgs->list().size()) outmsgs->send();
	
//	for (unsigned int i=0; i<msgs->list().size(); i++) {
//		std::string mapname;
//		int num=0, denum=0;
//		bool floatval;
//		rational date (0,0);
//		bool relative;
//		EventContext env(mouse, date, obj);
//		if (msgs->list()[i]->hasDateVar (mapname, num, denum, relative, floatval)) {
//			date = point2date (obj, relx, rely, mapname, 0, relative);
//			if (num && date.getDenominator()) {
//				float fd = float(date);
//				date.set (int(fd * denum / num) * num, denum);
//			}
//		}
//		EventContext env(mouse, date, floatval, obj);
//		msgs[i]->send(env);
//	}
}

} // end namespoace
