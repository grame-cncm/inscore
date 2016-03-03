/*

  INScore Project

  Copyright (C) 2016  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#ifndef __TParseEnv__
#define __TParseEnv__

namespace inscore 
{

#ifdef IBUNDLE
typedef ibundle::TDummyJs	TJSEngine;
#else
typedef TQtJs				TJSEngine;
#endif

class TLua;
//--------------------------------------------------------------------------------------------
/*
	\brief an abstract class that provides javascript and lua engines to the parser
	
	The class implements also a method for parsing error notifications.
*/
class TParseEnv
{
	public:
				 TParseEnv() {}
		virtual ~TParseEnv() {}

	virtual TJSEngine*	getJSEngine() = 0;
	virtual TLua*		getLUAEngine()= 0;
	virtual void		error() const	{}
	virtual TParseEnv*	parseEnv()		{ return this; }
};


} // namespace

#endif
