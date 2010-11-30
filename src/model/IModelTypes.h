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


#ifndef __IModelTypes__
#define __IModelTypes__

#include "smartpointer.h"

namespace inscore
{

class IMessage;

class IAppl;
typedef class SMARTP<IAppl>			SIAppl;

class IColor;
typedef class SMARTP<IColor>		SIColor;

class ICurve;
typedef class SMARTP<ICurve>		SICurve;

class IEllipse;
typedef class SMARTP<IEllipse>		SIEllipse;

class IFileWatcher;
typedef class SMARTP<IFileWatcher>	SIFileWatcher;

class IGraphicSignal;
typedef class SMARTP<IGraphicSignal> SIGraphicSignal;

class IGraphicBasedObject;
typedef class SMARTP<IGraphicBasedObject> SIGraphicBasedObject;

class IGuidoCode;
typedef class SMARTP<IGuidoCode>	SIGuidoCode;

class IGuidoFile;
typedef class SMARTP<IGuidoFile>	SIGuidoFile;

class IHtml;
typedef class SMARTP<IHtml>			SIHtml;

class IHtmlFile;
typedef class SMARTP<IHtmlFile>		SIHtmlFile;

class IImage;
typedef class SMARTP<IImage>		SIImage;

class ILine;
typedef class SMARTP<ILine>		SILine;

class IObject;
typedef class SMARTP<IObject>		SIObject;

class IObjectDebug;
typedef class SMARTP<IObjectDebug>	SIObjectDebug;

class IPDF;
typedef class SMARTP<IPDF>			SIPDF;

class IPolygon;
typedef class SMARTP<IPolygon>		SIPolygon;

class IRect;
typedef class SMARTP<IRect>			SIRect;

class IScene;
typedef class SMARTP<IScene>		SIScene;

class ISceneSync;
typedef class SMARTP<ISceneSync>	SISceneSync;

class IShape;
typedef class SMARTP<IShape>		SIShape;

class IShapeMap;
typedef class SMARTP<IShapeMap>		SIShapeMap;

class IText;
typedef class SMARTP<IText>			SIText;

class ITextFile;
typedef class SMARTP<ITextFile>		SITextFile;

class IVideo;
typedef class SMARTP<IVideo>		SIVideo;

class IWatcher;
typedef class SMARTP<IWatcher>		SIWatcher;

class Master;
class ISync;

} // end namespoace

#endif
