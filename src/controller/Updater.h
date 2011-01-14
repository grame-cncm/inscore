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


#ifndef __Updater__
#define __Updater__

#include "export.h"
#include "IModelTypes.h"
#include "smartpointer.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

class Master;
//--------------------------------------------------------------------------
/*!
	\brief A class intended to update the view
	
	Updater implements the \e visitor design pattern. It is intended to
	resolve the type of the objects of the model.
*/
class export Updater : public smartable
{
	protected:
				 Updater() {}
		virtual ~Updater() {}

	public:		
		virtual void update (IObject*);

		virtual bool needupdate (IObject*) = 0;

		virtual void updateTo (IObject*) {}
		virtual void updateTo (IObjectDebug*) {}
		virtual void updateTo (IAppl*) {}
		virtual void updateTo (IScene*) {}
		virtual void updateTo (IText*) {}
		virtual void updateTo (IHtml*) {}
		virtual void updateTo (ISVG*) {}
		virtual void updateTo (ISVGFile*) {}
		virtual void updateTo (IGuidoCode*) {}
		virtual void updateTo (IImage*) {}
		virtual void updateTo (IGraphicSignal*) {}
		virtual void updateTo (IShape *) {}
		virtual void updateTo (IShapeMap *) {}
		virtual void updateTo (IRect *) {}
		virtual void updateTo (IEllipse *) {}
		virtual void updateTo (IPolygon *) {}
		virtual void updateTo (ICurve*) {}
		virtual void updateTo (ILine*) {}
		virtual void updateTo (IVideo*) {}
};
typedef class SMARTP<Updater>	SUpdater;

class export ViewUpdater : public Updater {
	public:	virtual bool needupdate (IObject*);
};

class export LocalMapUpdater : public Updater {
	public:	virtual bool needupdate (IObject*);
};

class export SlaveMapUpdater : public Updater {
	public:	virtual bool needupdate (IObject*);
};

/*!@} */

} // end namespoace

#endif
