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


#ifndef __TLoopEval__
#define __TLoopEval__

namespace inscore 
{

class IMessageList;
class IMessage;
class TLoop;
class TEnv;

//--------------------------------------------------------------------------------------------
class TLoopEval 
{
	IMessageList*	fOutMsgs;
	TEnv*			fEnv;
	
	enum type { kTypeString, kTypeInt, kTypeFloat };
	
	std::string	expand (const char* str, const TEnv* env) const;
	type		getType (const char* str) const;
	
	public:	
				 TLoopEval(TEnv* env, IMessageList* outmsgs) : fOutMsgs(outmsgs), fEnv(env) {}
		virtual ~TLoopEval() {}

		virtual bool eval (TLoop* loop);
		virtual bool eval (IMessage* msg);
};

} // namespace

#endif
