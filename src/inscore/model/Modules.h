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


#pragma once

#if defined(MODELONLY) || defined(NOVIEW) || defined(HTMLVIEW)
# define INCLUDEFaust			false
# define INCLUDEFileWatcher		false
# define INCLUDEGestureFollower	false
# define INCLUDESensors			false
# define INCLUDEHttp			false
# define INCLUDEWebSocket		false
# define INCLUDEBundles			false
# define INCLUDEJavascript		false
# define QTView					false
#else
# define INCLUDEFaust			true
# define INCLUDEFileWatcher		true
# define INCLUDEGestureFollower	true
# define INCLUDESensors			true
# define INCLUDEHttp			true
# define INCLUDEWebSocket		true
# define INCLUDEBundles			true
# define INCLUDEJavascript		true
# define QTView					true
#endif

#if defined(NO_OSCSTREAM) || defined(IBUNDLE)
# define HASOSCStream			false
# else
# define HASOSCStream			true
#endif

#if QTView
# define INCLUDEFaustWeb		false
# define HASQGuidoImporter		true
# define HASFileDownloader		true
//#ifndef ANDROID
#if 1
# define HASWSSupport			true
# define HASHTTPSupport			true
# define HASMIDISupport			true
# include <QtNetwork>
# ifndef QT_NO_SSL
# define HASSSLSUPPORT			true
# else
# define HASSSLSUPPORT			false
# endif
#else
# define HASWSSupport			false
# define HASHTTPSupport			false
#endif
class QGraphicsScene;
typedef QGraphicsScene*		ViewContext;
class QGraphicsItem;
typedef QGraphicsItem*		VObjectContext;

#include <QtGlobal>
#if (QT_VERSION >= QT_VERSION_CHECK(6, 0, 0))
# define Qt6 true
# if defined(INSCORE_IOS)
#  define NO_OPENGL
# endif
#else
# define Qt6 false
# if (QT_VERSION >= QT_VERSION_CHECK(5, 15, 0))
#  define QT515 true
# else
#  define QT515 false
# endif
#endif

#elif HTMLVIEW
# define INCLUDEFaustWeb	true
# define HASQGuidoImporter	false
# define HASFileDownloader	false
# define HASWSSupport		false
# define HASHTTPSupport		false
# define HASMIDISupport		true
class SVGObjectView;
typedef SVGObjectView*		ViewContext;
typedef SVGObjectView*		VObjectContext;

#else
# define INCLUDEFaustWeb	false
# define HASQGuidoImporter	false
# define HASFileDownloader	false
# define HASWSSupport		false
typedef void*				ViewContext;
typedef void*				VObjectContext;
#endif
