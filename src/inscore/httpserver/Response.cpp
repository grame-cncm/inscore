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

#include "Response.h"
#include <cstring>

using namespace std;

namespace inscore {

Response::Response (const char* data, unsigned int size, string format, int http_status, bool allowCache)
{
	if(data != 0 && size != 0) {
		fData = new char[size + 1];
		memcpy (fData, data, size);
		fSize = size;
	} else {
		fData = 0;
		fSize = 0;
	}
	fFormat = format;
	fHttpStatus = http_status;
	fAllowCache = allowCache;
}

Response::Response (string data, string format, int http_status, bool allowCache)
{
	int size = int(data.size());
	const char *cc = data.c_str();
	fData = new char[size + 1];
	memcpy (fData, cc, size + 1);
	fSize = size;
	fFormat = format;
	fHttpStatus = http_status;
	fAllowCache = allowCache;
}

Response::Response ()
{
	fData = 0;
	fSize = 0;
	fFormat = "";
	fHttpStatus = 404;
	fAllowCache = true;
}

Response::Response (const Response &copy)
{
	fSize = copy.fSize;
	fData = new char[fSize + 1];
	memcpy (fData, copy.fData, fSize + 1);
	fFormat = copy.fFormat;
	fHttpStatus = copy.fHttpStatus;
	fAllowCache = copy.fAllowCache;
}

Response::~Response ()
{
  delete[] fData;
}

Response Response::genericSuccess(int http_status, bool allowCache)
{
	return Response (0, 0, "", http_status, allowCache);
}


Response Response::genericFailure(string errorString, int http_status, bool allowCache)
{
	return Response (errorString, "text/plain", http_status, allowCache);
}

}
