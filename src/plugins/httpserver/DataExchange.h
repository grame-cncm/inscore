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

#ifndef __dataexchange__
#define __dataexchange__
#include <string>

// Return value of the callback
struct responsedata {
	char * data;
	unsigned int size;
	const char * type;
};

// Parameters for the callback
struct requestarguments {
	const char * format;
	const char * path;
};

// Prototype of callback function to get data.
typedef struct responsedata * (* callbackGetData)(struct requestarguments*, void *);

#endif
