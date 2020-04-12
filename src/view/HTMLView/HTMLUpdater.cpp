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


#include "HTMLUpdater.h"
#include "IArc.h"
#include "IAudio.h"
#include "ICurve.h"
#include "IEllipse.h"
#include "IGraphicSignal.h"
#include "IGrid.h"
#include "IGuidoCode.h"
#include "IGuidoPianoRoll.h"
#include "IGuidoPianoRollStream.h"
#include "IHtml.h"
#include "IImage.h"
#include "ILayer.h"
#include "ILine.h"
#include "IObject.h"
#include "IPolygon.h"
#include "IRect.h"
#include "ISVG.h"
#include "ISVGFile.h"
#include "ISync.h"
#include "IText.h"
#include "IVideo.h"
#include "VObjectView.h"

#include <iostream>
using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
void HTMLUpdater::update (IObject* object)
{
	if (needupdate (object)) {
		VObjectView* view = object->getView();
		if (view) {
			view->updateView(object);
		}
	}
	if (object->getState() & IObject::kSubModified) {
		for (auto elt: object->elements())
			update (elt);
	}
}

//--------------------------------------------------------------------------
bool HTMLViewUpdater::needupdate (IObject* o)
{
	int state = o->getState();
	bool ret = state & (IObject::kModified + IObject::kNewObject + IObject::kMasterModified);
	return ret;
}

//--------------------------------------------------------------------------
bool HTMLLocalMapUpdater::needupdate (IObject* o)
{
	bool ret = (o->fAutoMap && o->durationModified()) || o->localMapModified() || o->newData();
	return ret;
}

//--------------------------------------------------------------------------
void HTMLLocalMapUpdater::updateTo (IArc* o)			{ o->updateGraphic2GraphicMapping(); }
void HTMLLocalMapUpdater::updateTo (IAudio* o)			{ o->updateGraphic2GraphicMapping(); }
void HTMLLocalMapUpdater::updateTo (ICurve* o)			{ o->updateGraphic2GraphicMapping(); }
void HTMLLocalMapUpdater::updateTo (IEllipse* o)		{ o->updateGraphic2GraphicMapping(); }
void HTMLLocalMapUpdater::updateTo (IGraphicSignal* graph)		{}
void HTMLLocalMapUpdater::updateTo (IGuidoCode* guidoCode)		{}
void HTMLLocalMapUpdater::updateTo (IGuidoPianoRoll* guidoCode)	{}
void HTMLLocalMapUpdater::updateTo (IGuidoPianoRollStream* guidoCode) {}
void HTMLLocalMapUpdater::updateTo (IHtml* text)		{ }
void HTMLLocalMapUpdater::updateTo (IImage* o) 			{ o->updateLocalMapping(); }
void HTMLLocalMapUpdater::updateTo (ILine* o)			{ o->updateGraphic2GraphicMapping(); }
void HTMLLocalMapUpdater::updateTo (IPolygon* o)		{ o->updateGraphic2GraphicMapping(); }
void HTMLLocalMapUpdater::updateTo (IRect* o)			{ o->updateGraphic2GraphicMapping(); }
void HTMLLocalMapUpdater::updateTo (ISVG* o) 			{ o->updateLocalMapping(); }
void HTMLLocalMapUpdater::updateTo (ISVGFile* svg) {}
void HTMLLocalMapUpdater::updateTo (IText* text) {}
void HTMLLocalMapUpdater::updateTo (IVideo* o) {}
void HTMLLocalMapUpdater::updateTo (IGrid* o) {}
void HTMLLocalMapUpdater::updateTo (ILayer* o)			{  o->updateGraphic2GraphicMapping(); }


//--------------------------------------------------------------------------
//bool HTMLSlaveMapUpdater::needupdate (IObject* o)
//{
//	return true;
//
////	return o->localMapModified() || o->dateModified(); // || master->getMaster()->localMapModified() || master->modified();
//
////	int state = o->getState();
////	return (state & (IObject::kModified + IObject::kNewObject + IObject::kMasterModified));
//}

} // end namespoace
