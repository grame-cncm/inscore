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

#ifndef __VoidViewFactory__
#define __VoidViewFactory__

#include "IModelTypes.h"


namespace inscore
{

/*!
\addtogroup ITLView
@{
*/
class VoidViewFactory
{
	public:

	static VObjectView*		create (const IAppl* object);
	static VObjectView*		create (const IScene* object);

	static VObjectView*		create (const ICurve* object);
	static VObjectView*		create (const IEllipse* object);
	static VObjectView*		create (const IGraphicSignal* object);
	static VObjectView*		create (const IGuidoCode* object);
	static VObjectView*		create (const IGuidoFile* object);
	static VObjectView*		create (const IHtml* object);
	static VObjectView*		create (const IHtmlFile* object);
	static VObjectView*		create (const IImage* object);
	static VObjectView*		create (const ILine* object);
	static VObjectView*		create (const IPolygon* object);
	static VObjectView*		create (const IGrid* object);
	static VObjectView*		create (const IRect* object);
	static VObjectView*		create (const ISVG* object);
	static VObjectView*		create (const ISVGFile* object);
	static VObjectView*		create (const IText* object);
	static VObjectView*		create (const ITextFile* object);
	static VObjectView*		create (const IVideo* object);
};

/*!@} */

} // end namespoace




#endif
