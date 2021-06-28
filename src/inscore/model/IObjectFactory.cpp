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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <iostream>
#include <string>

#include "Modules.h"

#include "IObjectFactory.h"
#include "IModel.h"
#include "ITLError.h"
#include "ViewFactory.h"

#if INCLUDESensors
#include "SensorsModel.h"
#endif

#if INCLUDEWebSocket
#include "QtWebSocketController.h"
#endif

#if defined(__MOBILE__)
#include "INScoreScene.h"
#include "VMobileSceneView.h"
#elif QTView
#include "INScoreScene.h"
#include "VSceneView.h"
#endif

#if INCLUDEFaustWeb
#include "IFaustProcessor.h"
#include "IFaustfProcessor.h"
#include "IFaustwProcessor.h"
#include "AudioIO.h"
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
#if QTView
        // We created the object, then we create the view
        VObjectView* view = ViewFactory::create(obj, parent->getScene()->getGraphicScene());
        // We set the parent view (only if different from the scene)
        if(parent->getTypeString() != IScene::kSceneType)
            view->setParentItem(parent->getView()?parent->getView():0);
        // and finally we set the view to the object
		obj->setView (view);
#elif defined (HTMLVIEW)
		obj->setView ( ViewFactory::create(obj, (HTMLObjectView*)parent->getView()));
#elif defined (NOVIEW)
		obj->setView ( ViewFactory::create(obj));
#endif
	}
	return obj->getView() ? obj : 0;
}

template<typename T> SIObject _createNoView(const std::string& name , IObject* parent)
{
	return T::create(name, parent);
}

#if INCLUDEWebSocket
template<> SIObject _create<IWebSocket>(const std::string& name , IObject* parent)
{
	SIWebSocket obj = IWebSocket::create(name, parent);
	QtWebSocketController * ctrl = new QtWebSocketController (obj);
	if (ctrl) obj->setControler(ctrl);
	else return 0;
	return obj;
}
#endif

#if QTView
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
#elif HTMLVIEW
template<> SIObject _create<IScene>(const std::string& name , IObject* parent)
{
	SIScene obj = IScene::create(name, parent);
	if (obj) {
		VSceneView *sceneView = ViewFactory::create(obj);
		obj->setView ((VObjectView*)sceneView);
		obj->cleanup();			// no update at object creation
		obj->setState(IObject::kClean);
	}
	return obj->getView() ? obj : 0;
}
#endif

//--------------------------------------------------------------------------
SIObject IObjectFactory::create(const std::string& name , const std::string& type, IObject* parent)
{
	SIObject obj;
	
	if (fCreateMap.empty()) init();

	TCreateMethod m = fCreateMap[type];
	if (m) {
		obj = m(name, parent);
		if (obj) {
			obj->setHandlers();
			obj->createVirtualNodes();
			obj->setVisible(IAppl::fDefaultShow);
		}
	}
	else ITLErr << "unknown object type: " << type << ITLEndl;
	return obj;
}

//---------------------------------------------------------------------------------
// methods to create a new object are associated to the object type in a statis map
//---------------------------------------------------------------------------------
map<string, IObjectFactory::TCreateMethod> IObjectFactory::fCreateMap;
void IObjectFactory::init()
{
	fCreateMap[IArc::kArcType]								= _create<IArc>;
	fCreateMap[IAudio::kAudioType]							= _create<IAudio>;
	fCreateMap[ICurve::kCurveType]							= _create<ICurve>;
	fCreateMap[IEllipse::kEllipseType]						= _create<IEllipse>;
#if INCLUDEFaust
	fCreateMap[IFaustDSP::kFaustDSPType]					= _createNoView<IFaustDSP>;
	fCreateMap[IFaustDSPFile::kFaustDSPFileType]			= _createNoView<IFaustDSPFile>;
	fCreateMap[IFaustProcessor::kFaustProcessorType]		= _createNoView<IFaustProcessor>;
#endif
#if INCLUDEFaustWeb
	fCreateMap[IFaustProcessor::kFaustProcessorType]		= _create<IFaustProcessor>;
	fCreateMap[IFaustfProcessor::kFaustfProcessorfType]		= _create<IFaustfProcessor>;
	fCreateMap[IFaustwProcessor::kFaustwProcessorfType]		= _create<IFaustwProcessor>;
	fCreateMap[AudioIO::kAudioIOType]						= _create<AudioIO>;
#endif
#if INCLUDEGestureFollower
	fCreateMap[IGestureFollower::kGestureFollowerType]		= _create<IGestureFollower>;
#endif
	fCreateMap[IGraphicSignal::kGraphicType]				= _create<IGraphicSignal>;
	fCreateMap[IGrid::kGridType]							= _create<IGrid>;
	fCreateMap[IGuidoCode::kGuidoCodeType]					= _create<IGuidoCode>;
	fCreateMap[IGuidoFile::kGuidoFileType]					= _create<IGuidoFile>;
	fCreateMap[IGuidoPianoRoll::kGuidoPianoRollType]		= _create<IGuidoPianoRoll>;
	fCreateMap[IGuidoPianoRollFile::kGuidoPianoRollFileType]= _create<IGuidoPianoRollFile>;
	fCreateMap[IGuidoPianoRollStream::kGuidoPianoRollStreamType] = _create<IGuidoPianoRollStream>;
	fCreateMap[IGuidoStream::kGuidoStreamType]				= _create<IGuidoStream>;
	fCreateMap[IHtml::kHtmlType]							= _create<IHtml>;
	fCreateMap[IHtmlFile::kHtmlFileType]					= _create<IHtmlFile>;
	fCreateMap[IImage::kImageType]							= _create<IImage>;
	fCreateMap[ILayer::kLayerType]							= _create<ILayer>;
	fCreateMap[ILine::kLineType]							= _create<ILine>;
	fCreateMap[IMemImage::kMemImageType]					= _create<IMemImage>;
	fCreateMap[IMusicXMLCode::kMusicXMLCodeType]			= _create<IMusicXMLCode>;
	fCreateMap[IMusicXMLFile::kMusicXMLFileType]			= _create<IMusicXMLFile>;
	fCreateMap[IPolygon::kPolygonType]						= _create<IPolygon>;
	fCreateMap[IRect::kRectType]							= _create<IRect>;
	fCreateMap[IRGraphicSignal::kRGraphicType]				= _create<IRGraphicSignal>;
	fCreateMap[IScene::kSceneType]							= _create<IScene>;
	fCreateMap[ISGraphicSignal::kSGraphicType]				= _create<ISGraphicSignal>;
	fCreateMap[ISignal::kSignalType]						= _createNoView<ISignal>;
	fCreateMap[ISVG::kSVGType]								= _create<ISVG>;
	fCreateMap[ISVGFile::kSVGFileType]						= _create<ISVGFile>;
	fCreateMap[IText::kTextType]							= _create<IText>;
	fCreateMap[ITextFile::kTextFileType]					= _create<ITextFile>;
	fCreateMap[IUrlIntermediateObject::kUrlIntermediateType] = _create<IUrlIntermediateObject>;
	fCreateMap[IVideo::kVideoType]							= _create<IVideo>;
#if INCLUDEWebSocket
	fCreateMap[IWebSocket::kIWebSocketType]					= _create<IWebSocket>;
#endif
#if INCLUDESensors
	fCreateMap[IAccelerometer::kAccelerometerType]			= _createNoView<IAccelerometer>;
	fCreateMap[IAmbientLight::kAmbientLightType]			= _createNoView<IAmbientLight>;
	fCreateMap[ICompass::kCompassType]						= _createNoView<ICompass>;
	fCreateMap[IGyroscope::kGyroscopeType]					= _createNoView<IGyroscope>;
	fCreateMap[ILight::kLightType]							= _createNoView<ILight>;
	fCreateMap[IMagnetometer::kMagnetometerType]			= _createNoView<IMagnetometer>;
	fCreateMap[IOrientation::kOrientationType]				= _createNoView<IOrientation>;
	fCreateMap[IProximity::kProximityType]					= _createNoView<IProximity>;
	fCreateMap[IRotation::kRotationType]					= _createNoView<IRotation>;
	fCreateMap[ITilt::kTiltType]							= _createNoView<ITilt>;
#endif

#if INCLUDEHttp && (defined(__LINUX__) || defined(MACOS))
	// httpd server is not yet supported on windows
	fCreateMap[IHttpd::kIHttpdType]							= _create<IHttpd>;
#endif
}

} // end namespace
