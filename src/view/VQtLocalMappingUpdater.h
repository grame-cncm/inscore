/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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


#ifndef __VQtLocalMappingUpdater__
#define __VQtLocalMappingUpdater__

#include "Updater.h"

namespace interlude
{

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
class export VQtLocalMappingUpdater : public LocalMapUpdater
{
	public :
		static SMARTP<VQtLocalMappingUpdater> create()		{ return new VQtLocalMappingUpdater(); }

		void updateTo (IGraphicSignal* graph);
		void updateTo (IGuidoCode* guidoCode);
		void updateTo (IImage* img);
		void updateTo (IText* text);
		void updateTo (IHtml* text);
		void updateTo (IRect* o);
		void updateTo (IEllipse* o);
		void updateTo (IVideo* o);
		void updateTo (IPolygon* o);
		void updateTo (ICurve* o);
		void updateTo (ILine* o);
				
	protected :
				 VQtLocalMappingUpdater() {}
		virtual ~VQtLocalMappingUpdater() {}
};
typedef class SMARTP<VQtLocalMappingUpdater>	SVQtLocalMappingUpdater;

/*!@} */

} // end namespoace

#endif
