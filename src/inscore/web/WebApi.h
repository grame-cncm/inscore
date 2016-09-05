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
#include "abstractdata.h"

class QGraphicsItem;
class QMutex;
typedef struct abstractdata AbstractData;

namespace inscore
{
    class VObjectView;
    class TParseEnv;
	class TQtJs;
	typedef TQtJs		TJSEngine;
    class TLua;
    class IAppl;

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
		static const char *	kHoverMsg;		///< the mouse hover message
		static const char * kFileMsg;		///< get file message

		WebApi(VObjectView *view, IAppl* root) : fView(view), fRoot(root), fPreviousX(-1), fPreviousY(-1) {}

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

		/*!
		 * \brief postMouseClick post a mouse hover event to inscore.
		 *
		 * A mouse hover leave (GraphicsSceneHoverLeave) is send to the previous item on previous x and y coordinates
		 * and a mouse hover enter (GraphicsSceneHoverEnter) is send to the item on (x, y) coordinates.
		 * \param x the x coordinate
		 * \param y the y coordinate
		 * \return an error string or an empty string if no error
		 */
		std::string postMouseHover(int x, int y);

		/*!
		 * \brief readFile Read a file in application rootPath folder.
		 * \param relativePath a relative path for the file. the "../" expression is not authorized.
		 * \param base64 to true, data is string base64 encoded. To false it binary data of the file.
		 * \return an abstract data structure with a data buffer to delete and a size. Version is not used.
		 */
		AbstractData readFile (const std::string& relativePath, bool base64);

		/*!
		 * \brief getMimetype Get mime type from the filename.
		 * \param filepath a filename
		 * \return a mimetype. If extension is not know, binary mime type is returned.
		 */
		const char * getMimetype(const std::string &filepath);

    private:
		/*!
		 * \brief fView the object view of the scene
		 */
		VObjectView *	fView;
		IAppl*			fRoot;

		int				fPreviousX;		///< Previous x coordinate of a mouse hover item
		int				fPreviousY;		///< Previous y coordinate of a mouse hover item

		/*!
		 * \brief fPostCommandMutex A mutex for script post
		 */
//		static QMutex	fPostCommandMutex;		///< Mutex for all web clients using different websocket servers.

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

		/*!
		 * \brief getAbsoluteFilePath Get an absolute file path from a relative with the application rootPath.
		 * \param relativePath a relative path
		 * \return the absolute path or an empty string if the file is not in the application rootPath or if "../" is used.
		 */
		std::string getAbsoluteFilePath(const std::string &relativePath);

};
}
#endif // WEBAPI_H
