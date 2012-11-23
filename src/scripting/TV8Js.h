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


#ifndef __TV8Js__
#define __TV8Js__

#include <string>
#ifdef V8ENGINE
#include <v8.h>
#endif

#include "smartpointer.h"

namespace inscore 
{
class TEnv;
typedef libmapping::SMARTP<TEnv> STEnv;

//--------------------------------------------------------------------------------------------
class TV8Js 
{
#ifdef V8ENGINE
//	static int	fRefCount;
    v8::Persistent<v8::Context>	fContext;
	int				fLineOffset;

	v8::Persistent<v8::Context> CreateV8Context();
	void ReportException(v8::TryCatch* try_catch) const;
	void getResult (const v8::Handle<v8::Value>& result, std::string& outStr) const;
#endif

	public:	
				 TV8Js();
		virtual ~TV8Js();

		void	Initialize	();
		void	bindEnv		(const STEnv& env);
		bool	eval		(int line, const char* script, std::string& outStr);
};

} // namespace

#endif
