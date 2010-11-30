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

#include "VGraphView.h"
#include "VGuidoItemView.h"
#include "VImageView.h"
#include "VTextView.h"
#include "VRectView.h"
#include "VEllipseView.h"
#include "VPolygonView.h"
#include "VCurveView.h"
#include "VLineView.h"
#include "VVideoView.h"

namespace INScore
{

void VQtLocalMappingUpdater::updateTo(IGraphicSignal* o)	{ o->getView()->updateLocalMapping( o );  }
void VQtLocalMappingUpdater::updateTo(IGuidoCode * o)		{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IImage * o)			{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IText* o)				{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IHtml* o)				{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IRect* o)				{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IEllipse* o)			{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(ILine* o)				{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IPolygon* o)			{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(ICurve* o)			{ o->getView()->updateLocalMapping( o ); }
void VQtLocalMappingUpdater::updateTo(IVideo* o)			{ o->getView()->updateLocalMapping( o ); }

} // end namespoace
