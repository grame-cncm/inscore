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

#include "IModel.h"
#include "VoidViewFactory.h"
#include "VoidObjectView.h"

namespace inscore
{

//--------------------------------------------------------------------------
VObjectView*	VoidViewFactory::create (const ICurve* )			{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IEllipse* )			{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IGraphicSignal* )	{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IGuidoCode* )		{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IGuidoFile* )		{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IHtml* )				{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IHtmlFile* )			{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IImage* )			{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const ILine* )				{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IPolygon* )			{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IGrid* )				{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IRect* )				{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const ISVG* )				{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const ISVGFile* )			{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IText* )				{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const ITextFile* )			{ return new VoidObjectView (); }
VObjectView*	VoidViewFactory::create (const IVideo* )			{ return new VoidObjectView (); }

//--------------------------------------------------------------------------
VObjectView* VoidViewFactory::create(const IScene* )	{ return new VoidObjectView (); }
VObjectView* VoidViewFactory::create(const IAppl* )		{ return new VoidObjectView (); }

}

