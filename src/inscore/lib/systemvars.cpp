/*
	Interlude Library
	Copyright (C) 2021  Grame

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

 */

#include "systemvars.h"

namespace inscore
{

const char * kOSNameVar	= "OSName";
const char * kOSIDVar	= "OSId";

#ifdef EMCC
const char *	kOSName	= "Web";
const int		kOSID	= kWeb;
#elif MACOS
const char *	kOSName	= "MacOS";
const int		kOSID	= kMacOS;
#elif defined WINDOWS
const char *	kOSName	= "Windows";
const int		kOSID	= kWindows;
#elif defined INSCORE_IOS
const char *	kOSName	= "iOS";
const int		kOSID	= kiOS;
#elif defined ANDROID
const char *	kOSName	= "Android";
const int		kOSID	= kAndroid;
#elif defined __LINUX__
const char *	kOSName	= "Linux";
const int		kOSID	= kLinux;
#else
#error "undefined operating system"
#endif

}

