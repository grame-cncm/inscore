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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>

#include "VQtUpdater.h"
#include "IModel.h"

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

namespace interlude
{

//--------------------------------------------------------------------------
void VQtUpdater::updateTo(IAppl * appl)			{ appl->getView()->updateView(appl); }
void VQtUpdater::updateTo(IScene * scene)		{ scene->getView()->updateView(scene); }

void VQtUpdater::updateTo(IImage * img)				{ update<IImage>(img); }
void VQtUpdater::updateTo(IRect * rect)				{ update<IRect>(rect); }
void VQtUpdater::updateTo(IEllipse * e)				{ update<IEllipse>(e); }
void VQtUpdater::updateTo(IPolygon * p)				{ update<IPolygon>(p); }
void VQtUpdater::updateTo(IGuidoCode * guido)		{ update<IGuidoCode>(guido); }
void VQtUpdater::updateTo(IText* text)				{ update<IText>(text); }
void VQtUpdater::updateTo(IGraphicSignal* g)		{ update<IGraphicSignal>(g); }
void VQtUpdater::updateTo(ICurve* curve)			{ update<ICurve>(curve); }
void VQtUpdater::updateTo(ILine* line)				{ update<ILine>(line); }
void VQtUpdater::updateTo (IHtml* html)				{ update<IHtml>(html); }
void VQtUpdater::updateTo (IVideo* video )			{ update<IVideo>(video); }

} // end namespoace
