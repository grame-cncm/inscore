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

#ifndef __response__
#define __response__

#include <string>
#include <map>

namespace inscore {

/*!
 * \brief The Response class.
 * Wrap a response.
 */
class Response {
	public:
	/*!
	 * \brief fData data of the response.
	 */
	char* fData;

	/*!
	 * \brief fSize Data size of the response.
	 */
	unsigned int fSize;

	/*!
	 * \brief fFormat MIMEType of the response
	 */
	std::string fFormat;

	/*!
	 * \brief fHttpStatus http status of the response.
	 */
	int fHttpStatus;

	/*!
	 * \brief allowCache
	 */
	bool fAllowCache;

	/*!
	 * \brief fLastModifiedDate a Last modified date to add to the reponse header.
	 */
	std::string fLastModifiedDate;

	/*!
	 * \brief fEntitiesHeader Custom entities header to add to the response.
	 */
	std::map<std::string, std::string> fEntitiesHeader;

	/*!
	 * \brief Response. Create an empty response with http status 404 not found.
	 */
	Response ();

	/*!
	 * \brief Response Create a response with data, mimetype format and status http_status
	 * \param data Data of the response. Data are copied.
	 * \param size Size of data
	 * \param format Mime type of the response.
	 * \param http_status http status
	 * \param allowCache set to false to have a no cache response.
	 */
	Response (const char* data, unsigned int size, std::string format, int http_status = 200, bool allowCache = true);

	/*!
	 * \brief Response Response object
	 * \param data data of the response
	 * \param format mime type of the response.
	 * \param http_status http status, default to 200
	 * \param allowCache set to false to have a no cache response.
	 */
	Response (std::string data, std::string format, int http_status = 200, bool allowCache = true);
	Response (const Response &copy);
	virtual ~Response ();

	/*!
	 * \brief genericSuccess Create a generic succes response without response body.
	 * \param http_status a http status, default to 200 (success)
	 * \param allowCache cache allowed or not
	 * \return
	 */
	static Response genericSuccess(int http_status = 200, bool allowCache = true);

	/*!
	 * \brief genericFailure Create a generic failure response with plain text mime type.
	 * \param errorString The content of the response
	 * \param http_status Http status, default to 400.
	 * \param allowCache set to false to have a no cache response.
	 * \return a Response object
	 */
	static Response genericFailure(std::string errorString, int http_status = 400, bool allowCache = true);

	/*!
	 * \brief setLastModifiedDate Set the Last modified date.
	 * \param date
	 */
	void setLastModifiedDate(std::string &date) { fLastModifiedDate = date;	}

	/*!
	 * \brief addEntityHeader Add new entity header.
	 * \param key the name of the entity header.
	 * \param value the value of the entity header.
	 */
	void addEntityHeader(std::string key, std::string value) { fEntitiesHeader[key] = value; }
};

}
#endif
