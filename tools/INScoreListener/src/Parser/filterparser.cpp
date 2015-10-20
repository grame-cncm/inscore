/*
  Interlude Library
  Copyright (C) 2009,2011  Grame

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

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include <sstream>
#include <locale.h>

#include "filterparser.h"


namespace inscorelistener{

//--------------------------------------------------------------------------
filterparser::filterparser(std::string string)
	:fStream(new std::istringstream(string))
 {
	setlocale(LC_NUMERIC, "C");
	initScanner();
}

//--------------------------------------------------------------------------
filterparser::~filterparser()
{
	setlocale(LC_NUMERIC, 0);
	destroyScanner();
}

} // end namespace

