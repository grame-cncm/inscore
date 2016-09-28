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

#include "VQtLocalMappingUpdater.h"

#include "VArcView.h"
#include "VCurveView.h"
#include "VEllipseView.h"
#include "VGraphView.h"
#include "VGridView.h"
#include "VGuidoItemView.h"
#include "VImageView.h"
#include "VLayerView.h"
#include "VLineView.h"
#include "VPianoRollView.h"
#include "VPolygonView.h"
#include "VRectView.h"
#include "VSVGView.h"
#include "VTextView.h"
#include "VUrlIntermediateObjectView.h"
#include "VVideoView.h"

namespace inscore
{

void VQtLocalMappingUpdater::updateTo(IArc* o)				{  view<VArcView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(ICurve* o)			{  view<VCurveView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IEllipse* o)			{  view<VEllipseView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IGraphicSignal* o)	{  view<VGraphView>(o)->updateLocalMapping( o );  }
void VQtLocalMappingUpdater::updateTo(IGrid* o)				{  view<VGridView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IGuidoCode * o)		{  view<VGuidoItemView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IGuidoPianoRoll * o)	{  view<VPianoRollView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IGuidoPianoRollStream * o) {  view<VPianoRollView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IHtml* o)				{  view<VTextView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IImage * o)			{  view<VImageView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(ILayer* o)			{  view<VLayerView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(ILine* o)				{  view<VLineView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IPolygon* o)			{  view<VPolygonView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IRect* o)				{  view<VRectView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(ISVG* o)				{  view<VSVGView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(ISVGFile* o)			{  view<VSVGView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IText* o)				{  view<VTextView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IUrlIntermediateObject* o){  view<VUrlIntermediateObjectView>(o)->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IVideo* o)			{  view<VVideoView>(o)->updateLocalMapping( o ); }


} // end namespoace
