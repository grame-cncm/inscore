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


namespace inscore
{

/*!
\addtogroup ITLView
@{
*/
class TextObjectView;

class ViewFactory
{
	public:

	public:

	static TextObjectView*		create (const IAppl* object);
	static TextObjectView*		create (const IScene* object);

	static TextObjectView*		create (const IArc* object);
	static TextObjectView*		create (const IAudio* object);
	static TextObjectView*		create (const ICurve* object);
	static TextObjectView*		create (const IEllipse* object);
	static TextObjectView*		create (const IGestureFollower* object);
	static TextObjectView*		create (const IGraphicSignal* object);
	static TextObjectView*		create (const ISGraphicSignal* object);
	static TextObjectView*		create (const IRGraphicSignal* object);
	static TextObjectView*		create (const IGuidoCode* object);
	static TextObjectView*		create (const IGuidoPianoRoll* object);
	static TextObjectView*		create (const IGuidoPianoRollStream* object);
	static TextObjectView*		create (const IGuidoFile* object);
	static TextObjectView*		create (const IGuidoPianoRollFile* object);
	static TextObjectView*		create (const IMusicXMLCode* object);
	static TextObjectView*		create (const IMusicXMLFile* object);
	static TextObjectView*		create (const IHtml* object);
	static TextObjectView*		create (const IHtmlFile* object);
	static TextObjectView*		create (const IHttpd* object);
	static TextObjectView*		create (const IImage* object);
	static TextObjectView*		create (const IMemImage* object);
	static TextObjectView*		create (const ILine* object);
	static TextObjectView*		create (const IPolygon* object);
	static TextObjectView*		create (const IGrid* object);
	static TextObjectView*		create (const ILayer* object);
	static TextObjectView*		create (const IRect* object);
	static TextObjectView*		create (const ISVG* object);
	static TextObjectView*		create (const ISVGFile* object);
	static TextObjectView*		create (const IText* object);
	static TextObjectView*		create (const ITextFile* object);
	static TextObjectView*		create (const IVideo* object);
	static TextObjectView*		create (const IUrlIntermediateObject* object);
};

/*!@} */

} // end namespoace
