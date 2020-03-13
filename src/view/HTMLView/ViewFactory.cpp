/*

  INScore Project
  Copyright (C) 2010-2020  Grame

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

#include <iostream>

#include "IModel.h"
#include "VApplView.h"
#include "HTMLObjectView.h"
#include "ViewFactory.h"
#include "VSceneView.h"
#ifdef EMCC
#include <emscripten.h>
#include "wasmglue.h"
#endif

//#include "VArcView.h"
//#include "VAudioView.h"
//#include "VCurveView.h"
//#include "VEllipseView.h"
//#include "VGestureFollowerView.h"
//#include "VGraphView.h"
//#include "VGridView.h"
//#include "VGuidoItemView.h"
//#include "VHttpdView.h"
//#include "VImageView.h"
//#include "VLayerView.h"
//#include "VLineView.h"
//#include "VObjectView.h"
//#include "VPianoRollView.h"
//#include "VPolygonView.h"
//#include "VRectView.h"
//#include "VSVGView.h"
//#include "VTextView.h"
//#include "VUrlIntermediateObjectView.h"
//#include "VVideoView.h"

using namespace std;

namespace inscore
{

#ifdef EMCC
int JSSceneCreate (const char* id, const IObject* obj) {
	return EM_ASM_INT( { return JSViewFactory.createScene(Module.UTF8ToString($0), $1);}, id, int(obj));
}
int JSObjectCreate (int parent, const char* type, const IObject* obj) {
	return EM_ASM_INT( { return JSViewFactory.create($0, Module.UTF8ToString($1), $2);}, parent, type, int(obj));
}
#else
int JSSceneCreate  (const char* , const IObject* ) 			{ return 0; }
int JSObjectCreate (int , const char* , const IObject* )	{ return 0; }
#endif

//--------------------------------------------------------------------------
VObjectView*	ViewFactory::create (const IObject* obj, HTMLObjectView* parent)
{
	int id = JSObjectCreate(parent->getID(), obj->getTypeString().c_str(), obj);
	cout << "ViewFactory::create object " << obj->name() << " div id: " << id  << " parent: " << (void*)parent << endl;
	return new HTMLObjectView (id, parent);
}

//--------------------------------------------------------------------------
VSceneView* ViewFactory::create(const IScene* obj)
{
	const char* name = obj->name().c_str();
	int id = JSSceneCreate(name, obj);
//	cout << "ViewFactory::create scene " << name << " div id: " << id << " state: " << obj->getState() << " new: " << obj->newData() << endl;
	return new VSceneView (id);
}

VObjectView* ViewFactory::create(const IAppl* )						{ return new VApplView (); }

}
