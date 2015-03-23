/*
  Interlude Library
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
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 9 rue du Garet, 69001 Lyon - France
  research@grame.fr

*/

#ifndef __basicmapreader__
#define __basicmapreader__

#include <iostream>
#include <string>
#include "mapreader.h"

namespace libmapping 
{

/*!
\addtogroup PARSER Parsing
@{
*/

//______________________________________________________________________________
/*!
\brief	A base class for reporting parsing errors.
*/
class TMapError {
	public:
				 TMapError() {}
		virtual ~TMapError() {}
		virtual void error(const char * msg)				{ std::cerr << "error: " << msg << std::endl; }
		virtual void error(const char * msg, int lineno)	{ std::cerr << "error line " << lineno << ": " << msg << std::endl; }
};

//______________________________________________________________________________
/*!
\brief	A base class to support parsing of specicific maps.

basicmapreader doesn't expect any relation type and returns an error when any \c map method is called.
Subclasses should implement the method corresponding to the expected map.

\see float_to_rational_reader long_to_rational_reader float2D_to_rational_reader long2D_to_rational_reader
*/
class basicmapreader : public mapreader
{
	TMapError		fOStreamErrMgr;

	protected:
		std::string fUnexpected;
		std::string fExpected;
		std::string fErrorMsg;
		TMapError*   fErrorManager;
		
	public:
				 basicmapreader(const char* expected, TMapError* errMgr=0) : fExpected(expected), fErrorManager(errMgr) 
								{ if (!fErrorManager) fErrorManager = &fOStreamErrMgr; }
		virtual ~basicmapreader() {}

		virtual bool map(const TSegment<long,2>& , const TSegment<rational,1>& )	{ fUnexpected = "long 2D to rational"; return false; }
		virtual bool map(const TSegment<float,2>& , const TSegment<rational,1>& )	{ fUnexpected = "float 2D to rational"; return false; }
		virtual bool map(const TSegment<long,1>& , const TSegment<rational,1>& )	{ fUnexpected = "long to rational"; return false; }
		virtual bool map(const TSegment<float,1>& , const TSegment<rational,1>& )	{ fUnexpected = "float to rational"; return false; }
		
		virtual void error(const char * msg, int lineno) { 
			if (lineno)	fErrorManager->error (msg, lineno); 
			else		fErrorManager->error (msg); 
		}
		virtual const char* maperror() { fErrorMsg = "unexpected " + fUnexpected + " map: " + fExpected + " map expected";
											return fErrorMsg.c_str(); }			///< unexpected map type handler
};

/*! @} */

} // namespace

#endif
