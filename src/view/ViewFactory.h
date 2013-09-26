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

#ifndef __ViewFactory__
#define __ViewFactory__

#include "IModelTypes.h"

class QGraphicsScene;

namespace inscore
{

/*!
\addtogroup ITLView
@{
*/
class ViewFactory
{
	public:

	static VObjectView*		create (const IAppl* object);
	static VObjectView*		create (const IScene* object);

	static VObjectView*		create (const ICurve* object,		QGraphicsScene* scene);
	static VObjectView*		create (const IEllipse* object,		QGraphicsScene* scene);
	static VObjectView*		create (const IGestureFollower* object,QGraphicsScene* scene);
	static VObjectView*		create (const IGraphicSignal* object,  QGraphicsScene* scene);
	static VObjectView*		create (const ISGraphicSignal* object, QGraphicsScene* scene);
	static VObjectView*		create (const IGuidoCode* object,	QGraphicsScene* scene);
	static VObjectView*		create (const IGuidoFile* object,	QGraphicsScene* scene);
	static VObjectView*		create (const IHtml* object,		QGraphicsScene* scene);
	static VObjectView*		create (const IHtmlFile* object,	QGraphicsScene* scene);
	static VObjectView*		create (const IImage* object,		QGraphicsScene* scene);
	static VObjectView*		create (const ILine* object,		QGraphicsScene* scene);
	static VObjectView*		create (const IPolygon* object,		QGraphicsScene* scene);
	static VObjectView*		create (const IGrid* object,		QGraphicsScene* scene);
	static VObjectView*		create (const ILayer* object,       QGraphicsScene* parent);
	static VObjectView*		create (const IRect* object,		QGraphicsScene* scene);
	static VObjectView*		create (const ISVG* object,			QGraphicsScene* scene);
	static VObjectView*		create (const ISVGFile* object,		QGraphicsScene* scene);
	static VObjectView*		create (const IText* object,		QGraphicsScene* scene);
	static VObjectView*		create (const ITextFile* object,	QGraphicsScene* scene);
	static VObjectView*		create (const IVideo* object,		QGraphicsScene* scene);
};

/*!@} */

} // end namespoace




#endif
