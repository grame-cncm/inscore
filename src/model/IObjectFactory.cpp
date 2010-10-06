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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <iostream>
#include "IObjectFactory.h"
#include "IModel.h"
#include "ViewFactory.h"
#include "VSceneView.h"


namespace interlude
{


//--------------------------------------------------------------------------
template<typename T> SIObject _create(const std::string& name , IObject* parent) 
{
	SMARTP<T> obj = T::create(name, parent);
	if (obj) {
		obj->setView ( ViewFactory::create(obj, parent->getScene()->getView()->scene()));
	}
	return obj->getView() ? obj : 0;
}

template<> SIObject _create<IWatcher>(const std::string& name , IObject* parent) 
{
	return IWatcher::create(name, parent);
}

template<> SIObject _create<ISignal>(const std::string& name , IObject* parent) 
{
	return ISignal::create(name, parent);
}


//--------------------------------------------------------------------------
SIObject IObjectFactory::create(const std::string& name , const std::string& type, IObject* parent)
{
	SIObject obj;
	
	if ( type == ICurve::kCurveType )
		obj = _create<ICurve> (name, parent);
	
	else if ( type == IEllipse::kEllipseType )
		obj = _create<IEllipse> (name, parent);

	else if ( type == IGraphicSignal::kGraphicType )
		obj = _create<IGraphicSignal> (name, parent);

	else if ( type == IGuidoCode::kGuidoCodeType )
		obj = _create<IGuidoCode> (name, parent);

	else if ( type == IGuidoFile::kGuidoFileType )
		obj = _create<IGuidoFile> (name, parent);

	else if ( type == IHtml::kHtmlType )
		obj = _create<IHtml> (name, parent);

	else if ( type == IHtmlFile::kHtmlFileType )
		obj = _create<IHtmlFile> (name, parent);

	else if ( type == IImage::kImageType )
		obj = _create<IImage> (name, parent);

	else if ( type == ILine::kLineType )
		obj = _create<ILine> (name, parent);
	
	else if ( type == IPolygon::kPolygonType )
		obj = _create<IPolygon> (name, parent);

	else if ( type == IRect::kRectType )
		obj = _create<IRect> (name, parent);

	else if ( type == ISignal::kSignalType )
		obj = _create<ISignal> (name, parent);

	else if ( type == IText::kTextType )
		obj = _create<IText> (name, parent);

	else if ( type == ITextFile::kTextFileType ) 
		obj = _create<ITextFile> (name, parent);

	else if ( type == IVideo::kVideoType )
		obj = _create<IVideo> (name, parent);
		
	else if ( type == IWatcher::kWatcherType )
		obj = _create<IWatcher> (name, parent);
		
	if (obj) {
		obj->createVirtualNodes();
		obj->setVisible(IAppl::fDefaultShow);
	}
	return obj;
}

}
