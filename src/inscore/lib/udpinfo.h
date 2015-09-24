/*
  Copyright (c) Grame 2009

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#ifndef __udpinfo__
#define __udpinfo__

#include <iostream>

namespace inscore
{

/*!
\brief	UDP setup information.
*/
typedef struct udpinfo 
{
	int fInPort;
	int fOutPort;
	int fErrPort;
	std::string fOutDstAddress;
	std::string fErrDstAddress;
	
	udpinfo(int port) :
		fInPort(port), fOutPort(port+1), fErrPort(port+2), 
		fOutDstAddress("127.0.0.1"), fErrDstAddress(fOutDstAddress) {}
	udpinfo(int port, int outport, int errport) :
		fInPort(port), fOutPort(outport), fErrPort(errport), 
		fOutDstAddress("127.0.0.1"), fErrDstAddress(fOutDstAddress) {}
} udpinfo;

std::ostream& operator << (std::ostream& out, const udpinfo& infos);

} // end namespace

#endif
