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

#include <stdlib.h>

#include "VTextUpdater.h"
#include "IModel.h"
#include "TComposition.h"

using namespace std;

namespace interlude
{

//--------------------------------------------------------------------------
void VTextUpdater::print (IObject* obj, const Master* master)
{
	fOutStream << SIObject(obj) << endl;
	if (master) {
		fOutStream	<< "  => " << obj->name() << " is slave of " << master->getMaster()->name() 
					<< " (mode: " << master->syncmode2string(master->getAlignment()) << ")" << endl;
	}
}

//--------------------------------------------------------------------------
void VTextUpdater::updateTo(IAppl* appl, const Master* master)
{
	print(appl, master);
	if (!appl->running())
		exit(0);
}

//--------------------------------------------------------------------------
void VTextUpdater::updateTo (IObject* obj, const Master* master)			{ print(obj, master); }
void VTextUpdater::updateTo (IScene* scene, const Master* master)			{ print(scene, master); }
void VTextUpdater::updateTo (IText* text, const Master* master)				{ print(text, master); }
void VTextUpdater::updateTo (ITextFile* text, const Master* master)			{ print(text, master); }
void VTextUpdater::updateTo (IGuidoCode* guidoCode, const Master* master)	{ print(guidoCode, master); }
void VTextUpdater::updateTo (IGuidoFile* guidoFile, const Master* master)	{ print(guidoFile, master); }
void VTextUpdater::updateTo (IImage* img, const Master* master)				{ print(img, master); }
void VTextUpdater::updateTo (IGraphicSignal* graph, const Master* master)	{ print(graph, master); }
void VTextUpdater::updateTo (IRect* rect, const Master* master)				{ print(rect, master); }
void VTextUpdater::updateTo (IEllipse* ellipse, const Master* master)		{ print(ellipse, master); }
void VTextUpdater::updateTo (IPolygon* polygon, const Master* master)		{ print(polygon, master); }
void VTextUpdater::updateTo (ICurve* curve, const Master* master)			{ print(curve, master); }
void VTextUpdater::updateTo (ILine* line, const Master* master)				{ print(line, master); }
void VTextUpdater::updateTo (IVideo* v, const Master* master)				{ print(v, master); }

} // end namespoace
