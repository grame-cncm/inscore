/*
  Interlude Library
  Copyright (C) 2009,2011  Grame

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

#ifndef __mapparser__
#define __mapparser__

#include <iostream>
#include <string>
#include <locale.h>

#include "smartpointer.h"

namespace libmapping 
{

/*!
\addtogroup PARSER Parsing
@{
*/

class mapparser;
class mapreader;

template<typename T1, unsigned int D1, typename T2, unsigned int D2> class TMapping;

/*! \brief a class for reading mapping streams

The mapparser provide an interface to lex and yacc.
*/
class mapparser 
{		
	public:
		mapreader*		fReader;	// the map reader: responsible of the map storage
		void*			fScanner;	// the flex scanner
		std::istream*	fStream;    // input stream
		int				fInt;		// the current int
		float			fFloat;		// the current float
		int				fNested;	// the current nested level

		/*! class constructor
			\param reader a client of the parsing results
			\param stream the stream to be parsed
		*/
				 mapparser(mapreader* reader, std::istream* stream) 
					: fReader(reader), fStream(stream), fInt(0), fFloat(0), fNested(0) {
						setlocale(LC_NUMERIC, "C");
						initScanner();
					}

		virtual ~mapparser() {
						setlocale(LC_NUMERIC, 0);
						destroyScanner();
					}
		
		/*! parse the stream provided to the class constructor
			\return false in case of error (syntax, unexpected map...)
		*/
		bool parse();		

	private:
		void initScanner();	
		void destroyScanner();
};

/*! @} */

} // end namespace

#endif
