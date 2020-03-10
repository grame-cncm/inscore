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

#pragma once

#include "IModelTypes.h"
#include "Modules.h"


namespace inscore
{

/*!
\addtogroup ITLView
@{
*/
class HTMLObjectView;
class VSceneView;

class ViewFactory
{
	public:

	static VObjectView*		create (const IAppl* object);
	static VSceneView*		create (const IScene* object);

	static VObjectView*		create (const IObject* object,	HTMLObjectView* parent);
//	static VObjectView*		create (const IArc* object,			HTMLObjectView* parent);
//	static VObjectView*		create (const IAudio* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const ICurve* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const IEllipse* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const IGraphicSignal* object,  HTMLObjectView* parent);
//	static VObjectView*		create (const ISGraphicSignal* object, HTMLObjectView* parent);
//	static VObjectView*		create (const IRGraphicSignal* object, HTMLObjectView* parent);
//	static VObjectView*		create (const IGuidoCode* object,	HTMLObjectView* parent);
//	static VObjectView*		create (const IGuidoPianoRoll* object, HTMLObjectView* parent);
//	static VObjectView*		create (const IGuidoPianoRollStream* object, HTMLObjectView* parent);
//	static VObjectView*		create (const IGuidoFile* object,	HTMLObjectView* parent);
//	static VObjectView*		create (const IGuidoPianoRollFile* object,	HTMLObjectView* parent);
//	static VObjectView*		create (const IMusicXMLCode* object,HTMLObjectView* parent);
//	static VObjectView*		create (const IMusicXMLFile* object,HTMLObjectView* parent);
//	static VObjectView*		create (const IHtml* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const IHtmlFile* object,	HTMLObjectView* parent);
//	static VObjectView*		create (const IImage* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const IMemImage* object,	HTMLObjectView* parent);
//	static VObjectView*		create (const ILine* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const IPolygon* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const IGrid* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const ILayer* object,       HTMLObjectView* parent);
//	static VObjectView*		create (const IRect* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const ISVG* object,			HTMLObjectView* parent);
//	static VObjectView*		create (const ISVGFile* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const IText* object,		HTMLObjectView* parent);
//	static VObjectView*		create (const ITextFile* object,	HTMLObjectView* parent);
//	static VObjectView*		create (const IVideo* object,		HTMLObjectView* parent);
};

/*!@} */

} // end namespoace
