/*

  Interlude Prototype
  Copyright (C) 2009  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __GuidoFontLoader__
#define __GuidoFontLoader__

#include <QFontDatabase>
#include <QFile>
#define GUIDO_FONT_FILE "guido2.ttf"

#ifdef Q_WS_MAC
#include <CoreFoundation/CoreFoundation.h>

/*
*	\brief MACOSX. Search the Guido font and returns its path, or empty if no font found.
*
*	Looks in:
*		- the application bundle ( standard path for fonts: %bundle/Contents/Resources )
*		- the folder where the bundle is
*/
static QString getGuidoFontPath()
{
	CFURLRef appUrlRef = CFBundleCopyBundleURL(CFBundleGetMainBundle());
	CFStringRef macPath = CFURLCopyFileSystemPath(appUrlRef,
                                               kCFURLPOSIXPathStyle);
	const char *bundlePath = CFStringGetCStringPtr(macPath,
                                               CFStringGetSystemEncoding());
	CFRelease(appUrlRef);
	CFRelease(macPath );
	
	QString guidoFontPath = QString(bundlePath) + "/Contents/Resources/" + QString(GUIDO_FONT_FILE);
	
	if ( QFile::exists(guidoFontPath) )
	{
		return guidoFontPath ;
	}
	else
	{
		if ( QFile::exists(GUIDO_FONT_FILE) )
		{
			return GUIDO_FONT_FILE;
		}
		else
		{
			return  "";
		}
	}
}
#else
/*
*	\brief WIN32 and LINUX. Search the Guido font and returns its path, or empty if no font found.
*
*	Looks in the folder where the bundle is.
*/
static QString getGuidoFontPath()
{
	if ( QFile::exists(GUIDO_FONT_FILE) )
	{
		return GUIDO_FONT_FILE;
	}
	else
	{
		return  "";
	}
}
#endif


void installGuidoFont()
{
	// Try to find the Guido font.
	QString fileName = getGuidoFontPath();
	if ( !fileName.isEmpty() )
		// Loads dynamically the Guido font
		QFontDatabase::addApplicationFont ( fileName );
	// If fileName is empty, the Guido font must be installed in the system to have a correct Guido rendering.
}


#endif
