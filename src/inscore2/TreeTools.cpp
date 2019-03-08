/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame - Centre national de création musicale, 
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/

#include <algorithm>

#include "TreeTools.h"

using namespace std;


namespace inscore2
{

//------------------------------------------------------------
string lowercase (const string& str)
{
	string out = str;
	std::transform (out.begin(), out.end(), out.begin(), ::tolower);
	return out;
}

//------------------------------------------------------------
bool isNumber (const char* str)
{
	while (*str) {
		if (isdigit(*str++) == 0) return false;
	}
	return true;
}

} // end namespace
