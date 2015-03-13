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

  Grame Research Laboratory, 11, cours Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#ifndef __inscoreserver__
#define __inscoreserver__

#include "HTTPServer.h"
#include "DataExchange.h"

#ifndef VERSION
	#define VERSION "";
#endif

#ifdef __cplusplus
extern "C" {
#endif

	/*!
	 * \brief initialize Create a new HTTPDServer instance
	 * \param callbackFct Call back function to get the data
	 * \param object a pointer on the server object in INScore.
	 * \return the HTTPDServer instance
	 */
	void * initialize(callbackGetData callbackFct, void *object);

	/*!
	 * \brief destroy Destroy a HTTPDServer instance.
	 * \param server the HTTPDServer.
	 */
	void destroy(void * server);

	/*!
	 * \brief start Start a HTTPDServer instance
	 * \param server the server instance
	 * \param port the http port
	 * \return true if server start
	 */
	bool start(void * server, int port);

	/*!
	 * \brief stop Stop a HTTPDServer instance
	 * \param server the server instance
	 * \return true if the server instance is stopped.
	 */
	bool stop(void * server);

	/*!
	 * \brief status Gice the server status
	 * \param server the server isntance
	 * \return the server status.
	 */
	int status(void * server);

	const char * version() { return VERSION; }

#ifdef __cplusplus
}
#endif

#endif
