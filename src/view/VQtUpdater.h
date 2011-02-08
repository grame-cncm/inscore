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


#ifndef __VQtUpdater__
#define __VQtUpdater__

#include "IController.h"
#include "IModelTypes.h"
#include "Updater.h"
#include "ISync.h"

namespace inscore
{

class IRectShape;

/*!
\addtogroup ITLCtrl
@{
*/

//--------------------------------------------------------------------------
/**
*	\brief a graphic view of the model state. 
*
*	Uses Qt's QGraphicsScene/QGraphicsView framework.
*/
class export VQtUpdater : public ViewUpdater
{
	public :
		static SMARTP<VQtUpdater> create()	{ return new VQtUpdater(); }

		void updateTo (IAppl* appl);
		void updateTo (IScene*);

		virtual void updateTo (ICurve * curve);
		virtual void updateTo (IEllipse * ellipse);
		virtual void updateTo (IGraphicSignal* graph);
		virtual void updateTo (IGuidoCode* guidoCode);
		virtual void updateTo (IHtml* html);
		virtual void updateTo (IImage* img);
		virtual void updateTo (ILine * line);
		virtual void updateTo (IPolygon * polygon );
		virtual void updateTo (IRect * rect );
		virtual void updateTo (IText* text );
		virtual void updateTo (ISVG* svg );
		virtual void updateTo (ISVGFile* svg );
		virtual void updateTo (IVideo* video );

	protected :
				 VQtUpdater() {}
		virtual ~VQtUpdater() {}

		template <typename T> void update (T* obj) {
			if (obj->getDeleted()) {
				delete obj->getView();
				obj->setView (0);
			}
			else {
//				obj->getView()->setParentView (obj);
				obj->getView()->updateView (obj);				
				obj->getView()->updateObjectSize (obj);
			}
		}
};
typedef class SMARTP<VQtUpdater> SVQtUpdater;

/*!@} */

} // end namespoace

#endif
