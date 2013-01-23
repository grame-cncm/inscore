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
typedef libmapping::SMARTP<TEnv> 	STEnv;

/*!
\brief The inscore scripting environment definition.
*/
class TEnv : public libmapping::smartable
{
	public:
		typedef std::map<std::string, IMessage::argslist>	TEnvList;
    protected:
				 TEnvList	fVariables;

				 TEnv() {}
				 TEnv(TEnv* env) { fVariables = env->fVariables; }
		virtual ~TEnv() {}

	public:
        static STEnv create()			{ return new TEnv(); }
        static STEnv create(TEnv* env)	{ return new TEnv(env); }

		TEnvList::const_iterator begin() const		{ return fVariables.begin(); }
		TEnvList::const_iterator end() const		{ return fVariables.end(); }

		STEnv	bind (const char* e, const IMessage::argPtr v)	{ fVariables[e].push_back(v); return this; }
		void	clear()								{ fVariables.clear(); }
		int		size() const						{ return fVariables.size(); }
		
		IMessage::argslist value(const std::string& e) const { 
			std::map<std::string, IMessage::argslist>::const_iterator i = fVariables.find(e);
			if (i != fVariables.end()) return i->second;
			return IMessage::argslist();
		}
		
//		void	print(std::ostream& os)	const { 
//			os << "env size:" << size() << " : ";
//			std::map<std::string, IMessage::argslist>::const_iterator i = fVariables.begin();
//			while (i != fVariables.end()) {
//				os << i->first << ":";
//				for (IMessage::argslist::const_iterator j = i->second.begin(); j != i->second.end(); j++)
//					os << (*j) << " , ";
//				i++;
//			}
//		}
};

//inline std::ostream& operator << (std::ostream& os, const TEnv* env) { env->print(os); return os; }

} // namespace

#endif
