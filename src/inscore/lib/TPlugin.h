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

#ifndef __TPlugin__
#define __TPlugin__

#include <string>
#include <vector>

namespace inscore
{

class TPlugin {

	public:
	static std::string	fLocation;

				 TPlugin()		{};
		virtual ~TPlugin()		{};

		// Gives the possible locations of a plugin in precedence order:
		// in the current folder first,
		// a PlugIns folder in application bundle on macos,
		// a PlugIns folder in application folder
		virtual void					locations (const char* library, std::vector<std::string>& list) = 0;

		// load a libray
		// when the library name is an absolute path and if loading fails, try to use the file name only
		virtual bool 			load 	(const char* library)	= 0;
		template <typename T> T	resolve (const char* f)		{ return T(_resolve(f)); }

		virtual std::string	errorString () const	= 0;

		// add a path to the plugins locations and starts looking at this location
		// next the standard strategy is applied
		static void	location (std::string path)		{ fLocation = path; }
		static void	resetlocation ()				{ fLocation.clear(); }

	protected:
		virtual void* _resolve (const char* f)	= 0;
};

} // end namespace

#endif
