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


#ifndef __TLua__
#define __TLua__

#include <string>
#include <string>
#ifdef LUA
#include <sstream>
#include <lua.hpp>
#endif
#include "IMessage.h"
#include "smartpointer.h"

namespace inscore 
{

class TEnv;
typedef libmapping::SMARTP<TEnv> STEnv;

//--------------------------------------------------------------------------------------------
class TLua 
{
#ifdef LUA
	lua_State * fLua;
	std::string getTable (lua_State* L, int i) const;
	bool check( int code ) const;
	void bindEnv  (std::stringstream& s, const std::string& name, const IMessage::argslist& values);
	bool bindEnv  (std::stringstream& s, const std::string& name, const IMessage::argPtr& val);
#endif

	public:	
				 TLua();
		virtual ~TLua();

		void	Initialize	();
		bool	eval		(const char* script, std::string& outStr);
		void	bindEnv		(const STEnv& env);
};

} // namespace

#endif
