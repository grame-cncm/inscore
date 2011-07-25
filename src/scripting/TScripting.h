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


#ifndef __TScripting__
#define __TScripting__

#include <stack>
#include "smartpointer.h"

namespace inscore 
{

class IMessageList;
class IMessage;
class TLoop;
typedef SMARTP<TLoop> STLoop;
class TEnv;
typedef SMARTP<TEnv> STEnv;

//--------------------------------------------------------------------------------------------
class TScripting 
{
	IMessageList*		fMessages;
	STEnv				fEnv;
	std::stack<STLoop>	fLoops;

	public:	
				 TScripting();
		virtual ~TScripting();

		void	add			(IMessage* msg);
		void	variable	(const std::string& ident, int val);
		void	variable	(const std::string& ident, float val);
		void	variable	(const std::string& ident, const std::string& val);
		void	startLoop	(const std::string ident, unsigned int count);
		bool	endLoop		();
		
		IMessageList* messages() const { return fMessages; }
};

} // namespace

#endif
