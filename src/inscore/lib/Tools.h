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

#ifndef __tools__
#define __tools__

#include <string>
#include "maptypes.h"

namespace libmapping {
	class rational;
}

namespace inscore
{
// Forward declaration
class IMessage;

struct Tools
{
	static bool					regexp (const std::string& str);
	static bool					isurl (const std::string& str);
	static std::string			ensurefloat (float f, int precision=0);

	static std::string		getHostName();							///< gives the local host name
	static unsigned long	getIP( const std::string& hostname);	///< resolves hostname to ip number, uses local host name if \c hostname is empty
	static std::string		ip2string (unsigned long ip);

	static libmapping::rational readRational(const IMessage *msg, bool twoPart, int startIndex = 0);
	static RationalInterval readRationalInterval(const IMessage *msg, bool twoPart, int startIndex = 0);
};


} // end namespace

#endif
