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

#ifndef __TPlugin__
#define __TPlugin__

#include <string>
#include <QLibrary>

namespace inscore
{

class TPlugin : public QLibrary {

	public:
				 TPlugin()		{};
		virtual ~TPlugin()		{ if (isLoaded()) unload(); };

		// load the libray
		// when the library name is an absolute path and if loading fails, try to use the file name only
		bool	load (const char* library);
		template <typename T> T	resolve (const char* f)	{ return T(QLibrary::resolve(f)); }

		std::string	errorString () const	{ return QLibrary::errorString().toStdString(); }
};


} // end namespace

#endif
