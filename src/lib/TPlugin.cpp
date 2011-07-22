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

#include <QFileInfo>
#include "TPlugin.h"

namespace inscore
{

// ------------------------------------------------------------------------------
bool TPlugin::load (const char* library)
{
	setFileName (library);
	if (QLibrary::load()) return true;

	// loading failed: try to get the file name only and restart
	QFileInfo file (library);
	setFileName (file.baseName());
	if (QLibrary::load()) return true;

	return false;
}


} // end namespace
