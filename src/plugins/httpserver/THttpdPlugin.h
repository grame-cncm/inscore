/*
  Copyright (c) Grame 2015

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr

*/

#ifndef THTTPDPLUGIN_H
#define THTTPDPLUGIN_H

#include "TPlugin.h"
#include "IObject.h"
#include "DataExchange.h"

namespace inscore
{

/*!
 * \brief The THttpdPlugin class.
 * This class aims to create a http server to expose webservice using inscorehttpserver library.
 */
class THttpdPlugin : public TPlugin
{
	private:
		/*!
		 * \brief fParent Server model object
		 */
		IObject * fParent;
		/*!
		 * \brief fHttpdServer HttpServer instance.
		 */
		void * fHttpdServer;

		// Prototype of function to resolve.
		typedef void * (* TInitialize) (callbackGetData, void*);
		typedef void (* TDestroy) (void*);
		typedef bool (* TStart) (void*, int);
		typedef bool (* TStop) (void*);
		typedef int (* TStatus) (void*);

		static TInitialize fInitialize;
		static TDestroy fDestroy;
		static TStart fStart;
		static TStop fStop;
		static TStatus fStatus;

		/*!
		 * \brief isResolved
		 * \return true if the library is already loaded and function all resolved.
		 */
		bool isResolved ();

		/*!
		 * \brief load load the library.
		 * \return true id library is loaded.
		 */
		bool load ();

    public:
		/*!
		 * \brief THttpdPlugin Create a new http server.
		 */
		THttpdPlugin(IObject *parent);

		/*!
		 * \brief ~THttpdPlugin Destroy the http server.
		 */
        virtual ~THttpdPlugin();

		/*!
		 * \brief start start the http server.
		 * \param port http port to use for this server.
		 * \return true if server start.
		 */
        bool start(int port);

		/*!
		 * \brief stop Stop the web server.
		 * \return true if server stop.
		 */
		bool stop();

		/*!
		 * \brief status Give server status.
		 * \return
		 */
		int status();

};

}
#endif // THTTPDPLUGIN_H
