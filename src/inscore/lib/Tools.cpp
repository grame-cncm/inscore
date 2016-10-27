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

#include <iostream>
#include <sstream>

#include "ip/NetworkingUtils.h"
#include "Tools.h"
#include "IMessage.h"
#include "rational.h"

#ifndef WIN32
#include <unistd.h>
#else
#include <Winsock2.h>
#endif

using namespace std;
using namespace libmapping;

namespace inscore
{

#ifndef NOHOSTNAME
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
#ifndef PARSERTEST
	return GetHostByName(name.c_str());
#else
	return 0;
#endif
}
#endif

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
bool Tools::isurl (const std::string& path)
{
	std::string begin;
	begin.assign(path, 0, 7);
	if ( (begin == "http://") || (begin == "https:/"))
		return true;
	begin.assign(path, 0,5);
	return begin == "qrc:/";
}

//--------------------------------------------------------------------------
bool Tools::isAbsolutePath (const std::string& path)
{
#ifdef WIN32
		return path[1] == ':';
#else
		return path[0] == '/';
#endif
}

//--------------------------------------------------------------------------
bool Tools::regexp (const string& str)
{
	size_t n = str.size();
	for (size_t i = 0; i < n; i++) {
		if ((str[i] == '*') || (str[i] == '?') || (str[i] == '['))
			return true;
	}
	return false;
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

//--------------------------------------------------------------------------
// converts a string to a decimal number
// check that the string contains only numbers
// return true when the string is a number and has been converted
//--------------------------------------------------------------------------
bool Tools::str2num (const char* ptr, int& num)
{
	num = 0;
	while (*ptr) {
		int c = *ptr++;
		if ((c < '0') || (c > '9')) return false;
		num *= 10;
		num += c - '0';
	}
	return true;
}

//--------------------------------------------------------------------------
libmapping::rational Tools::readRational(const IMessage *msg, bool twoPart, int startIndex)
{
	libmapping::rational out(0, 0);
	if ( !twoPart ) {
		int n; float nf; std::string datestr;
		if (msg->param(startIndex, n)) out = libmapping::rational(n,1);
		else if (msg->param(startIndex, nf)) out = libmapping::rational(int(nf*10000),10000);
		else if (msg->param(startIndex, datestr)) {
			libmapping::rational date(datestr);
			if (date.getDenominator()) out = date;
		}
		else return out;
	} else {
		int n, d;
		if ( !msg->param(startIndex, n) || !msg->param(startIndex + 1, d)) return out;
		out = libmapping::rational(n,d);
	}
	return out;
}

RationalInterval Tools::readRationalInterval(const IMessage *msg, bool twoPart, int startIndex)
{
	libmapping::rational start, end;
	if(twoPart) {
		start = readRational(msg, twoPart, startIndex);
		end = readRational(msg, twoPart, startIndex + 2);
	} else {
		start = readRational(msg, twoPart, startIndex);
		end = readRational(msg, twoPart, startIndex + 1);
	}
	return RationalInterval(start, end);
}

} // end namespace
