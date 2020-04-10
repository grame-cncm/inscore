/*

  INScore Project

  Copyright (C) 2009,2020  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/


#pragma once

#include "export.h"
#include "IModelTypes.h"
#include "Updater.h"

namespace inscore
{

/*!
\addtogroup ITLCtrl
@{
*/

//--------------------------------------------------------------------------
/*!
	\brief A class intended to update the view
*/
class inscore_export HTMLUpdater : public Updater
{
	protected:
				 HTMLUpdater() {}
		virtual ~HTMLUpdater() {}

	public:		
		virtual void update (IObject*);
		virtual const char* name()	{ return "HTMLUpdater"; }
};
typedef class libmapping::SMARTP<HTMLUpdater>	SHTMLUpdater;


class inscore_export HTMLViewUpdater : public HTMLUpdater {
	public:	
		virtual bool needupdate (IObject*);
		virtual const char* name()	{ return "HTMLViewUpdater"; }
	static libmapping::SMARTP<HTMLViewUpdater> create()	{ return new HTMLViewUpdater(); }
};

class inscore_export HTMLLocalMapUpdater : public LocalMapUpdater {
	public:	
		virtual bool needupdate (IObject*);
		virtual const char* name()	{ return "LocalMapUpdater"; }
	static libmapping::SMARTP<HTMLLocalMapUpdater> create()	{ return new HTMLLocalMapUpdater(); }
	
	void updateTo (IArc* o);
	void updateTo (IAudio* o);
	void updateTo (ICurve* o);
	void updateTo (IEllipse* o);
	void updateTo (IGraphicSignal* graph);
	void updateTo (IGuidoCode* guidoCode);
	void updateTo (IGuidoPianoRoll* guidoCode);
	void updateTo (IGuidoPianoRollStream* guidoCode);
	void updateTo (IHtml* text);
	void updateTo (IImage* img);
	void updateTo (ILine* o);
	void updateTo (IPolygon* o);
	void updateTo (IRect* o);
	void updateTo (ISVG* svg);
	void updateTo (ISVGFile* svg);
	void updateTo (IText* text);
	void updateTo (IVideo* o);
	void updateTo (IGrid* o);
	void updateTo (ILayer* o);
};

//class inscore_export HTMLSlaveMapUpdater : public SlaveMapUpdater {
//	public:	
//		virtual bool needupdate (IObject*);
//		virtual const char* name()	{ return "HTMLSlaveMapUpdater"; }
//	static libmapping::SMARTP<HTMLSlaveMapUpdater> create()	{ return new HTMLSlaveMapUpdater(); }
//};


/*!@} */

} // end namespace
