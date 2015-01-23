/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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

#ifndef __GuidoFontLoader__
#define __GuidoFontLoader__

#include <QFontDatabase>
#include <QFile>

// Path to the Guido font in qrc resources.
#define GUIDO_FONT_FILE ":/guido2.ttf"

/*
 * \brief Install the guido font for the application.
 * The guido font file is included in Qt resources file (see inscore.qrc).
 *
 */
void installGuidoFont()
{
		// Loads dynamically the Guido font
		QFontDatabase::addApplicationFont (GUIDO_FONT_FILE);
}


#endif
