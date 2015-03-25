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

#include <iostream>

#include "VQtUpdater.h"
#include "IModel.h"

#include "VApplView.h"
#include "VCurveView.h"
#include "VEllipseView.h"
#include "VGraphView.h"
#include "VGestureFollowerView.h"
#include "VGuidoItemView.h"
#include "VImageView.h"
#include "VLineView.h"
#include "VLogWindow.h"
#include "VPolygonView.h"
#include "VRectView.h"
#include "VGridView.h"
#include "VSceneView.h"
#include "VSVGView.h"
#include "VTextView.h"
#include "VVideoView.h"
#include "VLayerView.h"
#include "VUrlIntermediateObjectView.h"
#ifdef ANDROID
#include "VQtInit.h"
#endif

namespace inscore
{

//--------------------------------------------------------------------------
void VQtUpdater::updateTo(IAppl * appl)			{ ((VApplView*)appl->getView())->updateView(appl); }
void VQtUpdater::updateTo(IScene * scene)		{ ((VSceneView*)scene->getView())->updateView(scene); }

void VQtUpdater::updateTo(IImage * img)				{ update<IImage,	VImageView>		(img); }
void VQtUpdater::updateTo(IRect * rect)				{ update<IRect,		VRectView>		(rect); }
void VQtUpdater::updateTo(IGrid * grid)				{ update<IGrid,		VGridView>		(grid); }
void VQtUpdater::updateTo(ILayer * layer)			{ update<ILayer,		VLayerView>		(layer); }
void VQtUpdater::updateTo(IEllipse * e)				{ update<IEllipse,	VEllipseView>	(e); }
void VQtUpdater::updateTo(IPolygon * p)				{ update<IPolygon,	VPolygonView>	(p); }
void VQtUpdater::updateTo(IGestureFollower * gf)	{ update<IGestureFollower,VGestureFollowerView>	(gf); }
void VQtUpdater::updateTo(IGuidoCode * guido)		{ update<IGuidoCode,VGuidoItemView>	(guido); }
void VQtUpdater::updateTo(IText* text)				{ update<IText,		VTextView>		(text); }
void VQtUpdater::updateTo(ISVG* svg)				{ update<ISVG,		VSVGView>		(svg); }
void VQtUpdater::updateTo(ISVGFile* svg)			{ update<ISVGFile,	VSVGView>		(svg); }
void VQtUpdater::updateTo(IGraphicSignal* g)		{ update<IGraphicSignal, VGraphView>(g); }
void VQtUpdater::updateTo(ICurve* curve)			{ update<ICurve,	VCurveView>		(curve); }
void VQtUpdater::updateTo(ILine* line)				{ update<ILine,		VLineView>		(line); }
void VQtUpdater::updateTo (IHtml* html)				{ update<IHtml,		VTextView>		(html); }
void VQtUpdater::updateTo (IVideo* video )			{ update<IVideo,	VVideoView>		(video); }
void VQtUpdater::updateTo (IUrlIntermediateObject* url )			{ update<IUrlIntermediateObject,	VUrlIntermediateObjectView>		(url); }

//--------------------------------------------------------------------------
void VQtUpdater::updateTo(IApplLog * log)
{
	QWidget * w = log->window();
#ifndef ANDROID
	w->setVisible (log->getVisible());
#else
	// Add and remove log window in a tab
	QTabWidget * tw = VQtInit::getTabWidget();
	int index = tw->indexOf(w);
	if(log->getVisible()) {
		if(index == -1) {
			tw->addTab(w, w->windowTitle());
		}
	} else {
		if(index != -1) {
			tw->removeTab(index);
		}
	}
#endif
}

} // end namespoace
