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

using namespace std;

#define kInetAddrLen	128

namespace inscorehttpd
{

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
HTTPDServer::HTTPDServer(int verbose, int logmode, bool alloworigin)
	: fAccessControlAllowOrigin(alloworigin), fVerbose(verbose), fLogmode(logmode), fServer(0)
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
int HTTPDServer::send (struct MHD_Connection *connection, Response &response)
{
	const char *format =  response.fFormat.c_str();
	return send (connection, response.fData, response.fSize, format, response.fHttpStatus);
}

//--------------------------------------------------------------------------
int HTTPDServer::send (struct MHD_Connection *connection, const char *data, int length, const char* type, int status)
{
	/*
	if (fVerbose > 0) {
	  if (fLogmode == 0) {
		const char *sep = " ; ";
		if (fVerbose & CODE_VERBOSE) {
		  log << status << sep;
		}
		if (fVerbose & MIME_VERBOSE) {
		  log << type << sep;
		}
		if (fVerbose & LENGTH_VERBOSE) {
		  log << length << sep;
		}
		log << logend;
	  }
	  else if (fLogmode == 1) {
		const char *tab = "  ";
		if (fVerbose & CODE_VERBOSE) {
		  log << tab << "<code>" << logend;
		  log << tab << tab << status << logend;
		  log << tab << "</code>" << logend;
		}
		if (fVerbose & MIME_VERBOSE) {
		  log << tab << "<mime>" << logend;
		  log << tab << tab << type << logend;
		  log << tab << "</mime>" << logend;
		}
		if (fVerbose & LENGTH_VERBOSE) {
		  log << tab << "<length>" << logend;
		  log << tab << tab << length << logend;
		  log << tab << "</length>" << logend;
		}
		log << "</entry>" << logend;
	  }
	}
	*/
	struct MHD_Response *response = MHD_create_response_from_buffer (length, (void *) data, MHD_RESPMEM_MUST_COPY);
	if (!response) {
		cerr << "MHD_create_response_from_buffer error: null response\n";
		return MHD_NO;
	}
	MHD_add_response_header (response, MHD_HTTP_HEADER_CONTENT_TYPE, type ? type : "text/plain");
	if (fAccessControlAllowOrigin)
		MHD_add_response_header (response, MHD_HTTP_HEADER_ACCESS_CONTROL_ALLOW_ORIGIN, "*");
	int ret = MHD_queue_response (connection, status, response);
	MHD_destroy_response (response);
	return ret;
}

int HTTPDServer::sendPostRequest(struct MHD_Connection *connection, const TArgs& args, vector<string> &elems)
{
	Response resp = Response::genericFailure("POST request not supported by the server");
	return send (connection, resp);
}

int HTTPDServer::sendDeleteRequest(struct MHD_Connection *connection, const TArgs& args)
{
	Response resp = Response::genericFailure("DELETE request not supported by the server");
	return send (connection, resp);
}

void HTTPDServer::logSend(struct MHD_Connection *connection, const char* url, const TArgs& args, const char * type)
{
	/*
	// LOGFILE.
	if (fVerbose > 0) {
	  if (fLogmode == 0) {
		const char *sep = " ; ";
		log << log.date() << sep;
		if (fVerbose & IP_VERBOSE) {
		  struct sockaddr *so;
		  char buf[kInetAddrLen];
		  so = MHD_get_connection_info (connection,
										MHD_CONNECTION_INFO_CLIENT_ADDRESS)->client_addr;
		  log << inet_ntop(so->sa_family,
						   so->sa_data + 2, buf, kInetAddrLen) << sep;
		}
		if (fVerbose & HEADER_VERBOSE) {
		  TArgs headerArgs;
		  MHD_get_connection_values (connection, MHD_HEADER_KIND, _get_params, &headerArgs);
		  if (headerArgs.size()) {
			bool ampersand = false;
			for(TArgs::const_iterator it = headerArgs.begin(); it != headerArgs.end(); it++) {
			  if (!ampersand)
				ampersand = true;
			  else
				log << "&";
			  log << it->first;
			  log << "=";
			  log << it->second;
			}
		  }
		  log << sep;
		}
		if (fVerbose & REQUEST_VERBOSE) {
		  log << type << sep;
		}
		if (fVerbose & URL_VERBOSE) {
		  log << url << sep;
		}
		if (fVerbose & QUERY_VERBOSE) {
		  if (args.size()) {
			bool ampersand = false;
			for(TArgs::const_iterator it = args.begin(); it != args.end(); it++) {
			  if (!ampersand)
				ampersand = true;
			  else
				log << "&";
			  log << it->first;
			  log << "=";
			  log << it->second.c_str();
			}
		  }
		  log << sep;
		}
		// we close the entry when we send
	  }
	  else if (fLogmode == 1) {
		const char *tab = "  ";
		log << "<entry>" << logend;
		log << tab << "<date>" << logend;
		log << tab << tab << log.date() << logend;
		log << tab << "</date>" << logend;
		if (fVerbose & IP_VERBOSE) {
		  struct sockaddr *so;
		  char buf[kInetAddrLen];
		  so = MHD_get_connection_info (connection,
										MHD_CONNECTION_INFO_CLIENT_ADDRESS)->client_addr;
		  log << tab << "<ip>" << logend;
		  log << tab << tab << inet_ntop(so->sa_family,
						   so->sa_data + 2, buf, kInetAddrLen)
			  << logend;
		  log << tab << "</ip>" << logend;
		}
		if (fVerbose & HEADER_VERBOSE) {
		  TArgs headerArgs;
		  MHD_get_connection_values (connection, MHD_HEADER_KIND, _get_params, &headerArgs);
		  if (headerArgs.size()) {
			log << tab << "<header>" << logend;
			for(TArgs::const_iterator it = headerArgs.begin(); it != headerArgs.end(); it++) {
			  log << tab << tab << "<pair>" << logend;
			  log << tab << tab << tab << "<name>" << logend;
			  log << tab << tab << tab << tab << it->first << logend;
			  log << tab << tab << tab << "</name>" << logend;
			  log << tab << tab << tab << "<value>" << logend;
			  log << tab << tab << tab << tab << it->second << logend;
			  log << tab << tab << tab << "</value>" << logend;
			  log << tab << tab << "</pair>" << logend;
			}
			log << tab << "</header>" << logend;
		  }
		}
		if (fVerbose & REQUEST_VERBOSE) {
		  log << tab << "<method>" << logend;
		  log << tab << tab << type << logend;
		  log << tab << "</method>" << logend;
		}
		if (fVerbose & URL_VERBOSE) {
		  log << tab << "<url>" << logend;
		  log << tab << tab << url << logend;
		  log << tab << "</url>" << logend;
		}
		if (fVerbose & QUERY_VERBOSE) {
		  if (args.size()) {
			log << tab << "<query>" << logend;
			for(TArgs::const_iterator it = args.begin(); it != args.end(); it++) {
			  log << tab << tab << "<pair>" << logend;
			  log << tab << tab << tab << "<name>" << logend;
			  log << tab << tab << tab << tab << it->first << logend;
			  log << tab << tab << tab << "</name>" << logend;
			  log << tab << tab << tab << "<value>" << logend;
			  log << tab << tab << tab << tab << curl_escape(it->second.c_str (), 0) << logend;
			  log << tab << tab << tab << "</value>" << logend;
			  log << tab << tab << "</pair>" << logend;
			}
			log << tab << "</query>" << logend;
		  }
		}
		// we close the entry when we send
		//log << "</entry>" << logend;
	  }
	}
	*/
}

//--------------------------------------------------------------------------
int HTTPDServer::sendGetRequest (struct MHD_Connection *connection, const char* url, const TArgs& args, vector<string> &elems)
{
	Response resp("Test server", "text/plain");
	return send (connection, resp);
}

//--------------------------------------------------------------------------
int HTTPDServer::sendHeadRequest (struct MHD_Connection *connection, const char* url, const TArgs& args, vector<string> &elems)
{
	Response resp = Response::genericFailure("HEAD request not supported by the server");
	return send (connection, resp);
}

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

	logSend(connection, url, myArgs, method);

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

} // end namespoace
