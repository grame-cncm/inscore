/*
  INScore Library
  Copyright (C) 2010  Grame

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
#include "IMessage.h"
#include "IMessageStream.h"
#include "ITLparser.h"

using namespace std;
using namespace inscore;

//----------------------------------------------
string strip (string str)
{
	string out;
	const char * ptr = str.c_str();
	while (*ptr) {
		if ((*ptr != ' ') && (*ptr != '\t'))
			out += *ptr;
		ptr++;
	}
	return out;
}

//----------------------------------------------
SIMessage watchMessage (SIMessage msg)
{
	string method = strip(msg->message());
	if ((method == "watch") || (method == "watch+")) {
		string what;
		if ((msg->size() > 1) && msg->param(0, what)) {
			what = strip(what);
			if ((what == "mouseDown") ||
				(what == "mouseUp") ||
				(what == "mouseEnter") ||
				(what == "mouseLeave") ||
				(what == "mouseMove") ||
				(what == "doubleClick"))
				return msg->buildWatchMsg (1);
			if ((what == "timeEnter") ||
				(what == "timeLeave") ||
				(what == "durLeave") ||
				(what == "durLeave"))
				return msg->buildWatchMsg (5);
			if (what == "newElement")
				return msg->buildWatchMsg (1);
		}
	}
	else if (method == "add") {				// this is for the file watcher
		SIMessage translated = msg->buildWatchMsg (1);
		translated->setMessage("watch");	// the method name has changed
		return translated;
	}
	else if (method == "require")
		return msg->buildWatchMsg (1);
	return msg;
}

//----------------------------------------------
int main (int argc, char * argv[])
{
	if (argc > 1) {
		ifstream in (argv[1]);
		ITLparser p(&in, 0, 0, 0);
		p.parse ();
	}
 	return 0;
}

