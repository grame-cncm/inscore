/*

  INScore Project

  Copyright (C) 2015  Grame

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

  Grame Research Laboratory, 11 cours Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/
#ifndef WEBAPI_H
#define WEBAPI_H

#include <string>

class QGraphicsItem;
class QMutex;
typedef struct abstractdata AbstractData;

namespace inscore
{
    class VObjectView;

#ifdef V8ENGINE
class TV8Js;
typedef TV8Js		TJSEngine;
#elif defined QTJSENGINE
class TQtJs;
typedef TQtJs		TJSEngine;
#else
typedef void*		TJSEngine;
#endif
    class TLua;

/*!
 * \brief The WebApi class
 */
class WebApi
{
	public:
		static const char *	kVersionMsg;	///< the get version message
		static const char *	kGetImgMsg;		///< the get image message
		static const char *	kPostCmdMsg;	///< the post inscore script message
		static const char *	kClickMsg;		///< the mouse click message

        WebApi(VObjectView *view, TJSEngine* engine, TLua* lua) : fView(view), fJsEngine(engine), fLua(lua) {}

        virtual ~WebApi() {}

		/*!
		 * \brief getVersion Get score version
		 * \return
		 */
        unsigned long getVersion();

		/*!
		 * \brief getImage get score image
		 * \param base64 if base64 is true, image is encoded in a string base64, and the array data buffer must be deleted.
		 * \return
		 */
        AbstractData getImage(bool base64 = false);

		/*!
		 * \brief postScript send message in inscoreScript variable to inscore.
		 * \param inscoreScript the script
		 * \return an error string or an empty string if no error
		 */
        std::string postScript(const std::string &inscoreScript);

		/*!
		 * \brief postMouseClick post a mouse click event to inscore.
		 * \param x the x coordinate
		 * \param y the y coordinate
		 * \return an error string or an empty string if no error
		 */
        std::string postMouseClick(int x, int y);

    private:
		/*!
		 * \brief fView the object view of the scene
		 */
		VObjectView *	fView;

        TJSEngine*		fJsEngine;
        TLua*			fLua;
		/*!
		 * \brief fPostCommandMutex A mutex for script post
		 */
		static QMutex	fPostCommandMutex;		///< Mutex for all web clients using different websocket servers.

        /*!
         * \brief getItem Get a item from the coordinate in pixel.
         * \param x
         * \param y
         * \return the QGraphicsItem or null if no item.
         */
        QGraphicsItem * getItem(int x, int y);

        /*!
         * \brief sendEvent Send an event to the item
         * \param item the QGraphicsItem
         * \param eventType the Type of the event.
         */
        void sendEvent(QGraphicsItem * item, int eventType);
};
}
#endif // WEBAPI_H
