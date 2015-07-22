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

#ifndef __httpdserver__
#define __httpdserver__

#include <microhttpd.h>
#include <map>
#include <vector>
#include <string>
 #include <time.h>

#include "Response.h"

#define IP_VERBOSE 1
#define HEADER_VERBOSE 2
#define REQUEST_VERBOSE 4
#define URL_VERBOSE 8
#define QUERY_VERBOSE 16
#define CODE_VERBOSE 32
#define MIME_VERBOSE 64
#define LENGTH_VERBOSE 128

#define HEAD 3
#define DELETE 2
#define POST 1
#define GET 0

namespace inscore {
	class WebApi;

	// Type def for request argument
	typedef std::map<std::string, std::string> TArgs;
	typedef std::pair<std::string, std::string> TArg;

/*!
 \brief a specific thread to listen incoming packets
 */
struct connection_info_struct {
	int connectiontype;
	TArgs args;
	struct MHD_PostProcessor *postprocessor;
};

class HTTPDServer
{
	bool fAccessControlAllowOrigin;
	int fVerbose;
	int fLogmode;

	/*!
	 * \brief fServer libmicrohttpd demon server.
	 */
	struct MHD_Daemon *	fServer;

	/*!
	 * \brief fApi instance of WebApi class to execute request action on inscore.
	 */
	WebApi * fApi;

	std::pair<unsigned int, time_t> fVersionTime;

public:

	/*!
	 * \brief HTTPDServer. The guido engine has to be initailized to create the HTTPDserver.
	 * \param callbackFct a pointer on the callback function to get the result data.
	 * \param object the INScore object for the server.
	 * \param verbose flags for logging
	 * \param logmode mode of log (0 for Apache-like log or 1 for XML log file)
	 * \param g2img
	 * \param allowOrigin if true, Access-Control-Allow-Origin is set to '*' in http response header to allow cross domain request.
	 */
			 HTTPDServer(WebApi * api, int verbose = 0, int logmode = 0, bool allowOrigin = true);
	virtual ~HTTPDServer();

	/// \brief starts the httpd server
	bool start (int port);

	/// \brief stop the httpd server
	void stop ();

	/*!
	 * \brief answer : Main method to respond to a request.
	 * \param connection
	 * \param url
	 * \param method
	 * \param version
	 * \param upload_data
	 * \param upload_data_size
	 * \param con_cls
	 * \return #MHD_NO on error (i.e. reply already sent),
	 *         #MHD_YES on success or if message has been queued
	 */
	int answer (struct MHD_Connection *connection, const char *url, const char *method, const char *version,
				const char *upload_data, size_t *upload_data_size, void **con_cls);

	/*!
	 * \brief status return a non zero value if server is running.
	 * \return file descriptor number (MHD_DAEMON_INFO_LISTEN_FD of libmicorhttpd) or 0 if server not working.
	 */
	int status();

private:
	/*!
	 * \brief sendGetRequest. Perform a request with method get.
	 * \param connection
	 * \param url
	 * \param args
	 * \return #MHD_NO on error (i.e. reply already sent),
	 *         #MHD_YES on success or if message has been queued
	 */
	int sendGetRequest (struct MHD_Connection *connection, const char* url, const TArgs& args, std::vector<std::string> &elems);

	/*!
	 * \brief sendHeadRequest. No head request are handle by server. A 400 error is returned
	 * \param connection
	 * \param url
	 * \param args
	 * \return #MHD_NO on error (i.e. reply already sent),
	 *         #MHD_YES on success or if message has been queued
	 */
	int sendHeadRequest (struct MHD_Connection *connection, const char* url, const TArgs& args, std::vector<std::string> &elems);

	/*!
	 * \brief sendPostRequest. Perform POST request.
	 * \param connection
	 * \param args
	 * \return #MHD_NO on error (i.e. reply already sent),
	 *         #MHD_YES on success or if message has been queued
	 */
	int sendPostRequest (struct MHD_Connection *connection, const TArgs& args, std::vector<std::string> &elems);

	/*!
	 * \brief sendDeleteRequest. No delete request are handle by server. A 400 error is returned
	 * \param connection
	 * \param args
	 * \return
	 */
	int sendDeleteRequest (struct MHD_Connection *connection, const TArgs&);

	/*!
	 * \brief send Send reponse with the connection connection.
	 * Retreive response format and call send (struct MHD_Connection*, const char *, int , const char *, int) to
	 *  make a low level response with a Response
	 * \param connection a MHD_Connection to respond to the request
	 * \param response to send.
	 * \return #MHD_NO on error (i.e. reply already sent),
	 *         #MHD_YES on success or if message has been queued
	 */
	int send (struct MHD_Connection *connection, Response &response);

	/*!
	 * \brief updateTime Update time and version referenced in the server to serve score image or 304 unmodified response.
	 * \param version
	 */
	void updateTime(unsigned int version);

	/*!
	 * \brief parsedate Parse a string date from http request.
	 * \param date the date can have all three standard format (RFC1123, RFC850 and ansi)
	 * \return a time stamp.
	 */
	unsigned long parsedate(std::string &date);

	/*!
	 * \brief formatDate Create a string date from a timestamp
	 * \param time the timestamp.
	 * \return a string date in RFC1123 format.
	 */
	std::string formatDate(time_t time);
};

} // end namespoace

#endif
