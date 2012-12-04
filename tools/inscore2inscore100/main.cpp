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
#include <sstream>
#include <string>
#include "deelx.h"
#include "IMessage.h"
#include "IMessageStream.h"
#include "ITLparser.h"

using namespace std;
using namespace inscore;

//----------------------------------------------
string strip (const string& str)
{
	string out;
	const char* ptr = str.c_str();
	while (*ptr) {
		char c = *ptr;
		if ((c != ' ') && (c!='\t')) break;
		else ptr++;
	}

	string tmp;
	while (*ptr) {
		char c = *ptr++;
		if ((c == ' ') || (c == '\t')) {
			tmp += c;
		}
		else {
			if (tmp.size()) {
				out += tmp;
				tmp.clear();
			}
			out += c;
		}
	}
//cout << "strip '" << str << "' '" << out << "'" << endl;
	return out;
}

//----------------------------------------------------------------------
static string replacevar (const char* str)
{	
	string out;
	bool instring = false;
	bool inmsg = false;
	bool invar = false;
	while (*str) {
		if (*str == '"') {
			if (inmsg) {				// inside a watch message
				out += *str;			// don't change the content
			}
			else {						// ouside a watch message
				if (invar) invar = false;	// closing a variable: skip '"'
				else if (str[1] == '$')		// check for variable start
					invar = true;			// yes: skip '"'
				else {						// not end or beg of a variable
					out += *str;			// don't change
					instring = !instring;	// swap the string status
				}
			}
		}
		else if ((*str == '(') && !instring) {	// check for watch message start
			inmsg = true;				
			out += *str;
		}
		else if ((*str == ')') && inmsg) {		// check for watch message end
			inmsg = false;
			out += *str;
		}
		else out += *str;
		str++;
	}
	return out;
}

//----------------------------------------------
void printMessage (const IMessage* msg)
{
	stringstream s;
	msg->print (s);
	cout << replacevar(s.str().c_str());
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

