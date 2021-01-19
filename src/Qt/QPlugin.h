/*
  Copyright (c) Grame 2009-2020

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

  Grame Research Laboratory, 11, cours de Verdun-Gensoul 69002 Lyon - France
  research@grame.fr
  
*/

#pragma once

#include <string>
#include <vector>

#include <QLibrary>

#include "TPlugin.h"

namespace inscore
{

class QPlugin : public TPlugin, public QLibrary {

	public:
				 QPlugin()		{};
		virtual ~QPlugin()		{ if (isLoaded()) unload(); };

		// Gives the possible locations of a plugin in precedence order:
		// in the current folder first, a PlugIns folder in application bundle on macos,
		// a PlugIns folder in application folder
		void	locations (const char* library, std::vector<std::string>& list) override;

		// load the libray
		// when the library name is an absolute path and if loading fails, try to use the file name only
		bool	load (const char* library) override;
		std::string	errorString () const override			{ return QLibrary::errorString().toStdString(); }

		protected:
			virtual void* _resolve (const char* f)	override { return (void*)(QLibrary::resolve(f)); }
};

} // end namespace
