/*
  Copyright (c) Grame 2009

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

#include "Tools.h"


namespace interlude
{

//--------------------------------------------------------------------------
bool Tools::regexp (const std::string& str)
{
	unsigned int n = str.size();
	for (unsigned int i = 0; i < n; i++) {
		if ((str[i] == '*') || (str[i] == '?') || (str[i] == '['))
			return true;
	}
	return false;
}


} // end namespace
