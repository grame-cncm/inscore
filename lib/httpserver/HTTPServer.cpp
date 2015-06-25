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

#include "HTTPServer.h"
#include "Response.h"
#include <cstring>
#include <iostream>
#include <sstream>
#include <fstream>
#include <iterator>
#include <time.h>
#include <clocale>

#include "WebApi.h"
#include "json_object.h"
#include "json_element.h"
#include "abstractdata.h"

using namespace std;
using namespace json;

#define kInetAddrLen	128

namespace inscorehttpd
{

	const char * kRFC822_1123DateFormat = "%a, %d %b %Y %H:%M:%S %Z";	// RFC1123 date format
	const char * kRFC850DateFormat = "%A, %d-%b-%y %H:%M:%S %Z";		// RFC850 date format
	const char * kAnsiDateFormat = "%a %b %e %H:%M:%S %Y %Z";			// Ansi date format

	const char * kInscoreVersionHttpHeader = "X-Inscore-Version";		// Custom http header to send score version.

//--------------------------------------------------------------------------
// static functions
// provided as callbacks to mhttpd
//--------------------------------------------------------------------------

static int _on_client_connect(void* cls, const sockaddr* addr, socklen_t addrlen)
{
   (void) cls;
   (void) addr;
   (void) addrlen;
   // do nothing.
   // one day, if we want to limit nefarious connections,
   // this is the place
   return MHD_YES;
}

static int _answer_to_connection (void *cls, struct MHD_Connection *connection, const char *url, const char *method, const char *version,
								  const char *upload_data, size_t *upload_data_size, void **con_cls)
{
	HTTPDServer* server = (HTTPDServer*)cls;
	return server->answer(connection, url, method, version, upload_data, upload_data_size, con_cls);
}

//--------------------------------------------------------------------------

void _request_completed (void *cls, struct MHD_Connection *connection,
						 void **con_cls,
						 enum MHD_RequestTerminationCode toe)
{
	(void) cls;
	(void) connection;
	(void) toe;
	struct connection_info_struct *con_info = (connection_info_struct *)(*con_cls);

	if (NULL == con_info) {
		return;
	}

	if (con_info->connectiontype == POST) {
		MHD_destroy_post_processor (con_info->postprocessor);
	}

	delete con_info;
	*con_cls = NULL;
}

/*!
 * \brief _get_params Callback function to give request parameters.
 * \param cls A TArgs pointer.
 * \param key Key of the parameter
 * \param data Data of parameter.
 * \return
 */
static int _get_params (void *cls, enum MHD_ValueKind , const char *key, const char *data)
{
	TArgs* args = (TArgs*)cls;
	TArg arg(key, (data ? data : ""));
	args->insert (arg);
	return MHD_YES;
}

/*!
 * \brief _post_params Callback function to give post request attribute.
 * \param coninfo_cls
 * \param key
 * \param filename
 * \param content_type
 * \param transfer_encoding
 * \param data
 * \param off
 * \param size
 * \return
 */
static int _post_params (void *coninfo_cls, enum MHD_ValueKind , const char *key,
			  const char *filename, const char *content_type,
			  const char *transfer_encoding, const char *data,
			  uint64_t off, size_t size)
{
	(void) filename;
	(void) content_type;
	(void) transfer_encoding;
	(void) off;
	(void) size;
	struct connection_info_struct *con_info = (connection_info_struct *)coninfo_cls;
	string aKey = string(key);
	if (con_info->args.find(aKey) != con_info->args.end()) {
		con_info->args[aKey] += string(data);
	}
	else {
		con_info->args.insert(TArg(aKey, string(data)));
	}
	return MHD_YES;
}

//--------------------------------------------------------------------------
// the http server
//--------------------------------------------------------------------------
HTTPDServer::HTTPDServer(void *api, int verbose, int logmode, bool alloworigin)
	: fApi(static_cast<inscore::WebApi *>(api)), fAccessControlAllowOrigin(alloworigin), fVerbose(verbose), fLogmode(logmode), fServer(0)
{
}

HTTPDServer::~HTTPDServer()
{
	stop();
}

//--------------------------------------------------------------------------
bool HTTPDServer::start(int port)
{
	// MHD_USE_THREAD_PER_CONNECTION created one thread per connection
	fServer = MHD_start_daemon (MHD_USE_THREAD_PER_CONNECTION, port,
								_on_client_connect,
								NULL, _answer_to_connection, this,
								MHD_OPTION_NOTIFY_COMPLETED,
								_request_completed,
								NULL, MHD_OPTION_END);
	return fServer != 0;
}

//--------------------------------------------------------------------------
void HTTPDServer::stop ()
{
	if (fServer) {
		MHD_stop_daemon (fServer);
	}
	fServer=0;
}

//--------------------------------------------------------------------------

int HTTPDServer::status()
{
	const union MHD_DaemonInfo *infos = MHD_get_daemon_info(fServer, MHD_DAEMON_INFO_LISTEN_FD);
	if(infos)
		return infos->listen_fd;
	return 0;
}

//--------------------------------------------------------------------------
int HTTPDServer::send (struct MHD_Connection *connection, Response &response)
{
	struct MHD_Response *mhdResponse = MHD_create_response_from_buffer ( response.fSize, (void *) response.fData, MHD_RESPMEM_MUST_COPY);
	if (!mhdResponse) {
		cerr << "MHD_create_response_from_buffer error: null response\n";
		return MHD_NO;
	}
	if(!response.fFormat.empty())
		MHD_add_response_header (mhdResponse, MHD_HTTP_HEADER_CONTENT_TYPE, response.fFormat.c_str());
	if (fAccessControlAllowOrigin)
		MHD_add_response_header (mhdResponse, MHD_HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN, "*");
	if (!response.fAllowCache) {
		MHD_add_response_header (mhdResponse, MHD_HTTP_HEADER_CACHE_CONTROL, "no-cache");
		// Http 1.0 compliance
		MHD_add_response_header (mhdResponse, MHD_HTTP_HEADER_PRAGMA, "no-cache");
	}
	for(map<string, string>::iterator it = response.fEntitiesHeader.begin(); it != response.fEntitiesHeader.end(); it++) {
		MHD_add_response_header (mhdResponse, it->first.c_str(), it->second.c_str());
	}

	if(!response.fLastModifiedDate.empty()) {
		MHD_add_response_header (mhdResponse, MHD_HTTP_HEADER_LAST_MODIFIED, response.fLastModifiedDate.c_str());
	}
	int ret = MHD_queue_response (connection, response.fHttpStatus, mhdResponse);
	MHD_destroy_response (mhdResponse);
	return ret;
}

//--------------------------------------------------------------------------
int HTTPDServer::sendPostRequest(struct MHD_Connection *connection, const TArgs& args, vector<string> &elems)
{
	string log;
	// execute script
	if(elems.empty() && args.size() == 1 && args.begin()->first == "data") {
		log = fApi->postScript(args.begin()->second);
	} else
	// Mouse click request
	if(elems.size() == 1 && elems[0] == inscore::WebApi::kClickMsg && args.find("x") != args.end() && args.find("y") != args.end()) {
		 string xStr = args.find("x")->second;
		 string yStr = args.find("y")->second;
		 int x, y;
		 istringstream ( xStr ) >> x;
		 istringstream ( yStr ) >> y;

		 log = fApi->postMouseClick(x, y);
	} else
	 // Mouse click request
	 if(elems.size() == 1 && elems[0] == inscore::WebApi::kHoverMsg && args.find("x") != args.end() && args.find("y") != args.end()) {
		  string xStr = args.find("x")->second;
		  string yStr = args.find("y")->second;
		  int x, y;
		  istringstream ( xStr ) >> x;
		  istringstream ( yStr ) >> y;

		  log = fApi->postMouseHover(x, y);
	} else {
		// Error
		Response resp = Response::genericFailure("Unidentified POST request.", 404, false);
		return send(connection, resp);
	}

	// Create a response if request has be processed
	if(log.empty()) {
		Response resp = Response::genericSuccess(200, false);
		return send (connection, resp);
	} else {
		// Error : create json response with log
		json_object *jsonresp = new json_object;
		json_element* elem  = new json_element("error", new json_string_value(log.c_str()));
		jsonresp->add(elem);
		std::ostringstream mystream;
		json_stream jstream(mystream);
		jsonresp->print(jstream);
		Response resp = Response::genericFailure(mystream.str(), 400, false);
		return send (connection, resp);
	}
}

//--------------------------------------------------------------------------
int HTTPDServer::sendDeleteRequest(struct MHD_Connection *connection, const TArgs&)
{
	Response resp = Response::genericFailure("DELETE request not supported by the server");
	return send (connection, resp);
}

//--------------------------------------------------------------------------
int HTTPDServer::sendGetRequest (struct MHD_Connection *connection, const char* url, const TArgs& args, vector<string> &elems)
{
	if(elems.size() == 0) {
		// No element in url, serve score image.
		time_t since = 0;

		// Get If_Modified-Since header
		TArgs headerArgs;
		MHD_get_connection_values (connection, MHD_HEADER_KIND, _get_params, &headerArgs);
		if (headerArgs.size()) {
			TArgs::const_iterator it = headerArgs.find(MHD_HTTP_HEADER_IF_MODIFIED_SINCE);
			if(it != headerArgs.end()) {
				string date = it->second;
				since = parsedate(date);
			}
		}

		if(since >= fVersionTime.second) {
			// fVersionTime is updated each time a version or an image is served. It can be not up to date so we check the version number.
			unsigned int version = fApi->getVersion();
			if(fVersionTime.first == version) {
				Response resp = Response::genericSuccess(304, false);
				string date = formatDate(fVersionTime.second);
				resp.setLastModifiedDate(date);
				return send (connection, resp);
			}
		}
		// Get image data from api
		AbstractData data = fApi->getImage();
		if(data.data) {
			if(data.version != fVersionTime.first)
				updateTime(data.version);

			// Create a response
			string mimetype = "image/png";
			Response resp(data.data, data.size, mimetype, 200, false);
			// Add Last modified date in the response
			string date = formatDate(fVersionTime.second);
			resp.setLastModifiedDate(date);
			// Add custom header for inscore version
			stringstream ss;
			ss << data.version;
			resp.addEntityHeader(kInscoreVersionHttpHeader, ss.str());
			return send (connection, resp);
		}
		// Error
		Response resp = Response::genericFailure("Cannot create image", 400, false);
		return send (connection, resp);
	} else
	// Serve score version.
	if(elems.size() == 1 && elems[0] == inscore::WebApi::kVersionMsg) {
		unsigned int version = fApi->getVersion();

		// Create json response.
		json_object *jsonresp = new json_object;
		json_element* elem  = new json_element("version", new json_int_value(version));
		jsonresp->add(elem);
		std::ostringstream mystream;
		json_stream jstream(mystream);
		jsonresp->print(jstream);
		Response resp (mystream.str(), "application/json", 200, false);
		return send(connection, resp);
	} else {
		// Get absolute file path without leading '/'
		AbstractData data = fApi->readFile(url + 1, false);
		if(data.data) {
			// Create a response
			string mimetype = fApi->getMimetype(url + 1);
			Response resp(data.data, data.size, mimetype, 200, false);
			delete data.data;
			return send (connection, resp);
		}
	}
	Response resp = Response::genericFailure("404 Page Not Found", 404, false);
	return send(connection, resp);
}

//--------------------------------------------------------------------------
int HTTPDServer::sendHeadRequest (struct MHD_Connection *connection, const char* url, const TArgs& args, vector<string> &elems)
{
	Response resp = Response::genericFailure("HEAD request not supported by the server");
	return send (connection, resp);
}

//--------------------------------------------------------------------------
int HTTPDServer::answer (struct MHD_Connection *connection, const char *url, const char *method, const char *version, const char *upload_data, size_t *upload_data_size, void **con_cls)
{
	(void) version;
	if (NULL == *con_cls) {
		struct connection_info_struct *con_info = new connection_info_struct ();
		if (0 == strcmp (method, "POST")) {
			con_info->postprocessor =
				MHD_create_post_processor (connection, 1024, // arbitrary, recommeneded by libmicrohttpd
										   _post_params, (void *) con_info);

			if (NULL == con_info->postprocessor) {
				delete con_info;
				return MHD_NO;
			}
			/*
			  The connectiontype field of con_info currently does nothing:
			 it's a placeholder for using POST/GET distinctions as the server
			 becomes more sophisticated.
			 */
			con_info->connectiontype = POST;
		} else {
			con_info->connectiontype = GET;
		}

		*con_cls = (void *) con_info;

		return MHD_YES;
	}

	TArgs myArgs;
	MHD_get_connection_values (connection, MHD_COOKIE_KIND, _get_params, &myArgs);

	// first, parse the URL
	std::stringstream ss(url);
	std::string item;
	vector<string> elems;
	while (getline(ss, item, '/')) {
		if (item != "") {
			elems.push_back(item);
		}
	}

	if (0 == strcmp (method, "POST")) {
		struct connection_info_struct *con_info = (connection_info_struct *)*con_cls;

		if (*upload_data_size != 0) {
			MHD_post_process (con_info->postprocessor, upload_data,
							  *upload_data_size);
			*upload_data_size = 0;
			return MHD_YES;
		} else {
			struct connection_info_struct *con_info = (connection_info_struct *)*con_cls;
			return sendPostRequest(connection, con_info->args, elems);
		}
	}
	else if (0 == strcmp (method, "DELETE")) {
		TArgs args;
		MHD_get_connection_values (connection, MHD_GET_ARGUMENT_KIND, _get_params, &args);
		return sendDeleteRequest(connection, args);
	}
	else if (0 == strcmp (method, "GET")) {
		TArgs args;
		MHD_get_connection_values (connection, MHD_GET_ARGUMENT_KIND, _get_params, &args);
		return sendGetRequest (connection, url, args, elems);
	}
	else if (0 == strcmp (method, "HEAD")) {
		TArgs args;
		MHD_get_connection_values (connection, MHD_GET_ARGUMENT_KIND, _get_params, &args);
		return sendHeadRequest (connection, url, args, elems);
	}
	else {
	  stringstream ss;
	  ss << "The server does not support the ";
	  ss << method;
	  ss << " command";
	  Response resp = Response::genericFailure(ss.str().c_str ());
	  return send (connection, resp);
	}

	// should never get here
	return MHD_NO;
}

//--------------------------------------------------------------------------
void HTTPDServer::updateTime(unsigned int version)
{
	fVersionTime.first = version;
	fVersionTime.second = time(0);
}

//--------------------------------------------------------------------------
unsigned long HTTPDServer::parsedate(string &date)
{
	setlocale(LC_ALL, "C");
	// A server must accpet all three date format. (RFC2616 3.3.1)
	struct tm tm;
	// Return pointer is the end of parse string
	const char * cdate = date.c_str();
	const char * dateEnd = cdate + date.length();
	char * pointer = strptime(cdate, kRFC822_1123DateFormat, &tm);
	if(pointer != dateEnd) {
		pointer = strptime(cdate, kRFC850DateFormat, &tm);
		if(pointer != dateEnd) {
			pointer = strptime(cdate, kAnsiDateFormat, &tm);
			if(pointer != dateEnd) {
				return 0;
			}
		}
	}
	setlocale(LC_ALL, "");
	return timegm(&tm);
}

//--------------------------------------------------------------------------
string HTTPDServer::formatDate(time_t time)
{
	setlocale(LC_ALL, "C");
	char buffer[100];
	struct tm tm;
	gmtime_r(&time, &tm);
	// Generated dates must be in RFC 1123 format
	strftime(buffer, sizeof(buffer), kRFC822_1123DateFormat, &tm);
	setlocale(LC_ALL, "");
	return string(buffer);
}


} // end namespoace
