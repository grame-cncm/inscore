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

#include <iostream>
#include <string>

#include "IObjectFactory.h"
#include "IModel.h"
#include "INScoreScene.h"
#include "ITLError.h"
#include "QtWebSocketController.h"
#ifdef NOVIEW
#include "VoidViewFactory.h"
#elif defined(__MOBILE__)
#include "ViewFactory.h"
#include "VMobileSceneView.h"
#else
#include "ViewFactory.h"
#include "VSceneView.h"
#endif

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
template<typename T> SIObject _create(const std::string& name , IObject* parent)
{
	SMARTP<T> obj = T::create(name, parent);
	if (obj) {
#ifdef NOVIEW
		obj->setView ( VoidViewFactory::create(obj));
#else
        // We created the object, then we create the view
        VObjectView* view = ViewFactory::create(obj, parent->getScene()->getGraphicScene());
        // We set the parent view (only if different from the scene)
        if(parent->getTypeString() != IScene::kSceneType)
            view->setParentItem(parent->getView()?parent->getView():0);
        // and finally we set the view to the object
		obj->setView (view);
        
#endif
	}
	return obj->getView() ? obj : 0;
}

template<> SIObject _create<ISignal>(const std::string& name , IObject* parent)
{
	return ISignal::create(name, parent);
}

template<> SIObject _create<IFaustProcessor>(const std::string& name , IObject* parent)
{
	return IFaustProcessor::create(name, parent);
}

template<> SIObject _create<IFaustDSP>(const std::string& name , IObject* parent)
{
    return IFaustDSP::create(name, parent);
}
    
template<> SIObject _create<IFaustDSPFile>(const std::string& name , IObject* parent)
{
    return IFaustDSPFile::create(name, parent);
}

template<> SIObject _create<IWebSocket>(const std::string& name , IObject* parent)
{
	SIWebSocket obj = IWebSocket::create(name, parent);
	QtWebSocketController * ctrl = new QtWebSocketController (obj);
	if (ctrl) obj->setControler(ctrl);
	else return 0;
	return obj;
}

#ifndef NOVIEW
template<> SIObject _create<IScene>(const std::string& name , IObject* parent)
{
	SIScene obj = IScene::create(name, parent);
	if (obj) {
		string oscaddress = parent->getOSCAddress();
		oscaddress += "/";
		oscaddress += name;
		QGraphicsScene * gscene = 0;
		if (!parent->offscreen()) gscene = new INScoreScene(oscaddress, obj);
#ifdef __MOBILE__
		// Mobile scene view use touch gesture
		VSceneView *sceneView = new VMobileSceneView ();
#else
		VSceneView *sceneView = new VSceneView ();
#endif
        sceneView->initializeView(oscaddress, gscene);
		obj->setView (sceneView);
	}
	return obj->getView() ? obj : 0;
}
#endif

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

	else if ( type == ISGraphicSignal::kSGraphicType )
		obj = _create<ISGraphicSignal> (name, parent);

	else if ( type == IRGraphicSignal::kRGraphicType )
		obj = _create<IRGraphicSignal> (name, parent);

	else if ( type == IGuidoCode::kGuidoCodeType )
		obj = _create<IGuidoCode> (name, parent);

	else if ( type == IGuidoFile::kGuidoFileType )
		obj = _create<IGuidoFile> (name, parent);

	else if ( type == IGuidoPianoRoll::kGuidoPianoRollType )
		obj = _create<IGuidoPianoRoll> (name, parent);

	else if ( type == IGuidoPianoRollStream::kGuidoPianoRollStreamType )
		obj = _create<IGuidoPianoRollStream> (name, parent);

	else if ( type == IGuidoPianoRollFile::kGuidoPianoRollFileType)
		obj = _create<IGuidoPianoRollFile> (name, parent);

	else if ( type == IMusicXMLCode::kMusicXMLCodeType )
		obj = _create<IMusicXMLCode> (name, parent);

	else if ( type == IMusicXMLFile::kMusicXMLFileType )
		obj = _create<IMusicXMLFile> (name, parent);

	else if ( type == IGuidoStream::kGuidoStreamType )
		obj = _create<IGuidoStream> (name, parent);
    
	else if ( type == IHtml::kHtmlType )
		obj = _create<IHtml> (name, parent);

	else if ( type == IHtmlFile::kHtmlFileType )
		obj = _create<IHtmlFile> (name, parent);

	else if ( type == IImage::kImageType )
		obj = _create<IImage> (name, parent);

	else if ( type == IMemImage::kMemImageType )
		obj = _create<IMemImage> (name, parent);

	else if ( type == ILine::kLineType )
		obj = _create<ILine> (name, parent);
	
	else if ( type == IPolygon::kPolygonType )
		obj = _create<IPolygon> (name, parent);

	else if ( type == IRect::kRectType )
		obj = _create<IRect> (name, parent);

	else if ( type == IGrid::kGridType )
		obj = _create<IGrid> (name, parent);
    
    else if (type == ILayer::kLayerType)
		obj = _create<ILayer> (name, parent);
        
	else if ( type == ISignal::kSignalType )
		obj = _create<ISignal> (name, parent);

	else if ( type == IFaustProcessor::kFaustProcessorType )
		obj = _create<IFaustProcessor> (name, parent);
    
    else if ( type == IFaustDSP::kFaustDSPType )
		obj = _create<IFaustDSP> (name, parent);
    
    else if ( type == IFaustDSPFile::kFaustDSPFileType )
		obj = _create<IFaustDSPFile> (name, parent);

	else if ( type == IGestureFollower::kGestureFollowerType )
		obj = _create<IGestureFollower> (name, parent);

	else if ( type == IHttpd::kIHttpdType )		
#if defined(__LINUX__) || defined(MACOS)
		obj = _create<IHttpd> (name, parent);
#else
		ITLErr << "object type: " << type << " is only available on Mac OS and Linux"<< ITLEndl;
#endif
	else if ( type == IText::kTextType )
		obj = _create<IText> (name, parent);

	else if ( type == ITextFile::kTextFileType ) 
		obj = _create<ITextFile> (name, parent);

	else if ( type == IVideo::kVideoType )
		obj = _create<IVideo> (name, parent);

	else if ( type == ISVGFile::kSVGFileType )
		obj = _create<ISVGFile> (name, parent);

	else if ( type == ISVG::kSVGType )
		obj = _create<ISVG> (name, parent);
    
    else if ( type == IUrlIntermediateObject::kUrlIntermediateType )
		obj = _create<IUrlIntermediateObject> (name, parent);

	else if ( type == IScene::kSceneType )
		obj = _create<IScene> (name, parent);

	else if ( type == IWebSocket::kIWebSocketType )
		obj = _create<IWebSocket> (name, parent);

	else
		ITLErr << "unknown object type: " << type << ITLEndl;

	if (obj) {
		obj->setHandlers();
		obj->createVirtualNodes();
		obj->setVisible(IAppl::fDefaultShow);
	}
	return obj;
}

}
