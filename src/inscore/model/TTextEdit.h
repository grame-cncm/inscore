/*

  INScore Project

  Copyright (C) 2015  Grame

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


#ifndef __TTextEdit__
#define __TTextEdit__

#include <string>

#include "smartpointer.h"


namespace inscore
{

class IObject;
typedef class libmapping::SMARTP<IObject>	SIObject;
class TTextEdit;
typedef class libmapping::SMARTP<TTextEdit>	STTextEdit;

//--------------------------------------------------------------------------
/*!
	\brief a base class for objects editing
	
*/
class TTextEdit
{
	SIObject	fClient;

	protected:
				 TTextEdit( SIObject obj ) : fClient(obj) {}
		virtual ~TTextEdit() {}

		// editing is asynchronous
		void start() const;

	public:
		static STTextEdit create( SIObject obj ) { return new TTExtEdit( obj ); }
};

} // end namespoace

#endif
