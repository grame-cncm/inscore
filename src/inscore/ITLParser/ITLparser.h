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

#ifndef __ITLparser__
#define __ITLparser__

#include <iostream>
#include <string>
#include <locale.h>

#include "TScripting.h"

namespace inscore 
{

/* \brief a class for reading ITL streams
*/
class ITLparser {	
		
	void initScanner();
	void destroyScanner();

	public:
		class address {
			public:
				std::string				fOsc;		// the osc address
				inscore::IMessage::TUrl	fUrl;		// the address extension (if any)
				 address (const std::string& osc) : fOsc(osc) {}
				 address (const std::string& osc, const inscore::IMessage::TUrl& url) : fOsc(osc), fUrl(url.fHostname.c_str(), url.fPort) {}
				~address () {}
		};

		TScripting		fReader;
		void*			fScanner;	// the flex scanner
		std::istream*	fStream;    // input stream
		std::string		fText;		// the current text
		int				fInt;		// the current int
		float			fFloat;		// the current float
		int				fLine;		// line offset
		int				fExprStartLine;
		bool			fParseSucceed;

				 ITLparser(std::istream* stream, int line, TJSEngine* js, TLua* lua);
		virtual ~ITLparser();
		
		SIMessageList parse();
};

} // end namespace

#endif
