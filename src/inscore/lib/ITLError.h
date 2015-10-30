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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA.

  Grame Research Laboratory, 9, rue du Garet 69001 Lyon - France
  research@grame.fr
  
*/

#ifndef __ITLError__
#define __ITLError__

#include <iostream>

#ifdef NO_OSCSTREAM
#define ITLErr	cerr
#define ITLEndl	endl

#else
#include "OSCStream.h"
#include "smartpointer.h"

namespace inscore
{

class IMessage;
class IMessageList;
typedef libmapping::SMARTP<IMessageList>	SIMessageList;

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


ITLError& operator << (ITLError& err, ITLErrEnd end);
ITLError& operator << (ITLError& err, const IMessage* msg );
ITLError& operator << (ITLError& err, const SIMessageList& msg );


template <typename T>	ITLError& operator << (ITLError& err, const T& arg)
{
	std::cerr << arg << " ";
	if (!err.oscpending) {
		oscerr << OSCErr();
		err.oscpending = true;
	}
	oscerr << arg;
	return err;
}

extern ITLError ITLErr;			// static ITL error output stream
extern ITLErrEnd ITLEndl;		// static ITL error output stream end

} // end namespace
#endif

#endif
