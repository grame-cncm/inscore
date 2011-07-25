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


#ifndef __TEnv__
#define __TEnv__

#include <map>
#include <string>

#include "smartpointer.h"
#include "IMessage.h"

namespace inscore 
{

class TEnv;
typedef SMARTP<TEnv> 	STEnv;

/*!
\brief The inscore scripting environment definition.
*/
class TEnv : public smartable
{
    protected:
		std::map<std::string, Sbaseparam>	fVariables;

				 TEnv() {}
				 TEnv(TEnv* env) { fVariables = env->fVariables; }
		virtual ~TEnv() {}

	public:
        static STEnv create()			{ return new TEnv(); }
        static STEnv create(TEnv* env)	{ return new TEnv(env); }

		STEnv	bind (const char* e, int v)			{ fVariables[e] = new IMsgParam<int>(v); return this; }
		STEnv	bind (const char* e, float v)		{ fVariables[e] = new IMsgParam<float>(v); return this; }
		STEnv	bind (const char* e, const char* v)	{ fVariables[e] = new IMsgParam<std::string>(v); return this; }
		void		clear()							{ fVariables.clear(); }
		int			size() const					{ return fVariables.size(); }
		
		Sbaseparam value(const std::string& e) const { 
			std::map<std::string, Sbaseparam>::const_iterator i = fVariables.find(e);
			if (i != fVariables.end()) return i->second;
			return 0;
		}
		
		void	print(std::ostream& os)	const { 
			os << "env size:" << size() << " : ";
			std::map<std::string, Sbaseparam>::const_iterator i = fVariables.begin();
			while (i != fVariables.end()) {
				os << i->first << ":" << i->second << " , ";
				i++;
			}
		}
};

inline std::ostream& operator << (std::ostream& os, const TEnv* env) { env->print(os); return os; }

} // namespace

#endif
