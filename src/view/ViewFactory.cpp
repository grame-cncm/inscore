/*

  INScore Project
  Copyright (C) 2010  Grame

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

#include <QGraphicsScene>

#include "IModel.h"
#include "ViewFactory.h"

#include "VGraphicsItemView.h"

#include "VApplView.h"
#include "VCurveView.h"
#include "VEllipseView.h"
#include "VGraphView.h"
#include "VGuidoItemView.h"
#include "VImageView.h"
#include "VLineView.h"
#include "VPolygonView.h"
#include "VRectView.h"
#include "VSceneView.h"
#include "VTextView.h"
#include "VVideoView.h"

namespace inscore
{

//--------------------------------------------------------------------------
VCurveView*		ViewFactory::create (const ICurve* object, QGraphicsScene* scene)			{ return new VCurveView (scene, object); }
VEllipseView*	ViewFactory::create (const IEllipse* object, QGraphicsScene* scene)			{ return new VEllipseView (scene, object); }
VGraphView*		ViewFactory::create (const IGraphicSignal* object, QGraphicsScene* scene)	{ return new VGraphView (scene, object); }
VGuidoItemView* ViewFactory::create (const IGuidoCode* object, QGraphicsScene* scene)		{ return new VGuidoItemView (scene, object); }
VGuidoItemView* ViewFactory::create (const IGuidoFile* object, QGraphicsScene* scene)		{ return new VGuidoItemView (scene, object); }
VTextView*		ViewFactory::create (const IHtml* object, QGraphicsScene* scene)			{ return new VTextView (scene, object); }
VTextView*		ViewFactory::create (const IHtmlFile* object, QGraphicsScene* scene)		{ return new VTextView (scene, object); }
VImageView*		ViewFactory::create (const IImage* object, QGraphicsScene* scene)			{ return new VImageView (scene, object); }
VLineView*		ViewFactory::create (const ILine* object, QGraphicsScene* scene)			{ return new VLineView (scene, object); }
VPolygonView*	ViewFactory::create (const IPolygon* object, QGraphicsScene* scene)			{ return new VPolygonView (scene, object); }
VRectView*		ViewFactory::create (const IRect* object, QGraphicsScene* scene)			{ return new VRectView (scene, object); }
VTextView*		ViewFactory::create (const IText* object, QGraphicsScene* scene)			{ return new VTextView (scene, object); }
VTextView*		ViewFactory::create (const ITextFile* object, QGraphicsScene* scene)		{ return new VTextView (scene, object); }
VVideoView*		ViewFactory::create (const IVideo* object, QGraphicsScene* scene)			{ return new VVideoView (scene, object); }

//--------------------------------------------------------------------------
VSceneView* ViewFactory::create(const IScene* obj)		{ return new VSceneView ( new QGraphicsScene ); }
VApplView*	ViewFactory::create(const IAppl* obj)		{ return new VApplView (); }

}

