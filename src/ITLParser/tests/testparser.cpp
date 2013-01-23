/*
  Interlude Library
  Copyright (C) 2009  Grame

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

#include <iostream>
#include <fstream>
#include "ITLparser.h"
#include "IMessage.h"
#include "IMessageStream.h"
#include "TV8Js.h"

using namespace std;
using namespace inscore;


int main (int argc, char * argv[])
{
	if (argc > 1) {
		ifstream in (argv[1]);
#ifdef V8ENGINE
		TJSEngine js;
		ITLparser p(&in, 0, &js, 0);
#elif defined(LUA)
		TLua lua;
		ITLparser p(&in, 0, 0, &lua);
#else
		ITLparser p(&in, 0, 0, 0);
#endif
		SIMessageList outMsgs;
		outMsgs = p.parse ();
		if (outMsgs) {
			outMsgs->list().set("", "\n");
			cout << outMsgs->list() << endl;
		}
		else
			cout << "error reading " << argv[1] << endl;
	}
 	return 0;
}

