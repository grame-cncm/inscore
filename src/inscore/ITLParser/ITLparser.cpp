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

#include <iostream>
#include <locale.h>

#include "ITLparser.h"

using namespace std;

namespace inscore 
{

static const char * kOSNameVar	= "OSName";
static const char * kOSIDVar	= "OSId";

static const char * kMacOSName		= "MacOS";
static const char * kWindowsName	= "Windows";
static const char * kLinuxName		= "Linux";
static const char * kAndroidName	= "Android";
static const char * kiOSName		= "iOS";

enum { kAndroid=1, kiOS, kLinux, kMacOS, kWindows };

#ifdef MACOS
const char *	kOSName	= kMacOSName;
const int		kOSID	= kMacOS;
#elif defined WINDOWS
const char *	kOSName	= kWindowsName;
const int		kOSID	= kWindows;
#elif defined INSCORE_IOS
const char *	kOSName	= kiOSName;
const int		kOSID	= kiOS;
#elif defined ANDROID
const char *	kOSName	= kAndroidName;
const int		kOSID	= kAndroid;
#elif defined __LINUX__
const char *	kOSName	= kLinuxName;
const int		kOSID	= kLinux;
#else
#error "undefined operating system"
#endif


//--------------------------------------------------------------------------
ITLparser::ITLparser(std::istream* stream, int line, IAppl* root, bool execute)
	: fReader(root, execute), fStream(stream), fLine(line), fColumn(1)
{
	setlocale(LC_NUMERIC, "C");
	initScanner();
	fLineOffset = fColumn = fLine = fExprStartLine = 0;
	setupEnv();
}

//--------------------------------------------------------------------------
ITLparser::~ITLparser() 
{
	setlocale(LC_NUMERIC, 0);
	destroyScanner();
}

//--------------------------------------------------------------------------
void ITLparser::setupEnv()
{
	IMessage::argslist osname;
	osname.push_back( new IMsgParam<string>(kOSName));
	fReader.variable (kOSNameVar, &osname);
	IMessage::argslist osid;
	osid.push_back( new IMsgParam<int>(kOSID));
	fReader.variable (kOSIDVar, &osid);
}

} // end namespace
