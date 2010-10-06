/*

  INScore Project

  Copyright (C) 2009,2010  Grame

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
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#include "ISignalProfiler.h"

#include "interlude.h"
#include <iostream>

namespace interlude
{

//--------------------------------------------------------------------------
void ISignalProfiler::send()
{
//	std::cout	<< "ISignalProfiler::send(): time = " << float(fElapsed) / float(fTimeUnit)
//				<< std::endl;

	Interlude::MessagePtr m =  Interlude::newMessage();
	Interlude::add( m , float(fElapsed) / float(fTimeUnit) );
	Interlude::postMessage( std::string( "/ITL/scene/signal/debug-" + fObjectName + "-" + fSignalName).c_str() , m );
}

}