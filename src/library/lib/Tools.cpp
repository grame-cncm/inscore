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

#ifdef WIN32
#pragma warning (disable : 4996)
#endif

#include <stdio.h>
#include <iostream>
#include <sstream>

#include "ip/NetworkingUtils.h"
#include "Tools.h"

#ifndef WIN32
#include <unistd.h>
#else
#include <Winsock2.h>
#endif

using namespace std;
using namespace libmapping;

namespace inscore
{

//--------------------------------------------------------------------------
string Tools::getHostName()
{
	char name[1024];
	int ret = gethostname(name, 1024);
	if (ret == -1) return "";
	return name;
}

unsigned long Tools::getIP( const string& hostname)
{
	string name;
	if (!hostname.size())
		name = getHostName();
	else
		name = hostname;
	return GetHostByName(name.c_str());
}

string	Tools::ip2string (unsigned long ip)
{
	stringstream ipStr;
	ipStr	<< ((ip >> 24) & 0xff) << '.'
			<< ((ip >> 16) & 0xff) << '.'
			<< ((ip >> 8) & 0xff) << '.'
			<< (ip & 0xff);
	return ipStr.str();
}

//--------------------------------------------------------------------------
string Tools::getIP()
{
	return ip2string (getIP(""));
}

//--------------------------------------------------------------------------
bool Tools::isurl (const std::string& path)
{
	std::string begin;
	begin.assign(path, 0, 7);
	return (begin == "http://") || (begin == "https:/");
}

//--------------------------------------------------------------------------
bool Tools::regexp (const string& str)
{
	unsigned int n = str.size();
	for (unsigned int i = 0; i < n; i++) {
		if ((str[i] == '*') || (str[i] == '?') || (str[i] == '['))
			return true;
	}
	return false;
}

//--------------------------------------------------------------------------
/**
 *	Convert a string to a rational value.
 */
rational Tools::str2rational (const std::string& rationalstr)
{
	int num, d;
	int n = sscanf (rationalstr.c_str(), "%d/%d", &num, &d);
	return (n == 2) ? rational (num, d) : rational (0,0);
}

//--------------------------------------------------------------------------
/**
 *	Convert a float into a string.
 *	Ensure a float representation for integer values.
 */
string Tools::ensurefloat (float f, int precision)
{
	stringstream stream;
	if (precision) stream.precision(precision);
	stream << f;
	const string& s = stream.str();
	const char* ptr = s.c_str();
	bool hasdot = false;
	while(*ptr) {
		if (*ptr++ == '.') hasdot = true;
	}
	if (!hasdot) stream << ".0";
	return stream.str();
}


} // end namespace
