/*
  Copyright (c) Grame 2010

  This library is free software; you can redistribute it and modify it under
  the terms of the GNU Library General Public License as published by the
  Free Software Foundation version 2 of the License, or any later version.

  This library is distributed in the hope that it will be useful, but
  WITHOUT ANY WARRANTY; without even the implied warranty of MERCHANTABILITY
  or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU Library General Public License
  for more details.

  You should have received a copy of the GNU Library General Public License
  along with this library; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#ifndef __ITLError__
#define __ITLError__

#include <iostream>
#include "OSCStream.h"

namespace interlude
{

//--------------------------------------------------------------------------
/*!
\brief	ITL error stream

	Combines the \c cerr and \c oscerr streams
*/
typedef struct ITLError {
	bool oscpending;
	ITLError() { oscpending = false; }
} ITLError;

typedef struct ITLErrorEnd {
} ITLErrEnd;


inline ITLError& operator << (ITLError& err, ITLErrEnd end)
{
	std::cerr << std::endl;
#ifndef NO_OSC
	oscerr <<  OSCEnd();
	err.oscpending = false;
#endif
	return err;
}

template <typename T>	ITLError& operator << (ITLError& err, const T& arg)
{
	std::cerr << arg;
#ifndef NO_OSC
	if (!err.oscpending) {
		oscerr << OSCErr();
		err.oscpending = true;
	}
	oscerr << arg;
#endif
	return err;
}

extern ITLError ITLErr;			// static ITL error output stream
extern ITLErrEnd ITLEndl;		// static ITL error output stream end

} // end namespace

#endif
