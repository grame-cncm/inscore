/*

  INScore Project

  Copyright (C) 2011  Grame

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


#ifndef __TMozillaJs__
#define __TMozillaJs__

#include <string>
#ifdef JAVASCRIPT
#include <js/jsapi.h>
#endif

#include "smartpointer.h"

namespace inscore 
{
class TEnv;
typedef SMARTP<TEnv> STEnv;

//--------------------------------------------------------------------------------------------
class TMozillaJs 
{
#ifdef JAVASCRIPT
    JSRuntime * fRuntime;
    JSContext *	fContext;
	JSObject  *	fGlobal;
	int			fLineOffset;

	void jsBindEnv (JSContext *cx, const STEnv& env);
	void getResult (const jsval& val, std::string& outStr) const;
#endif

	public:	
				 TMozillaJs();
		virtual ~TMozillaJs();

		void	bindEnv		(const STEnv& env);
		bool	eval		(int line, const char* script, std::string& outStr);
};

} // namespace

#endif
