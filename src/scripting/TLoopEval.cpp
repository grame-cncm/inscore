/*

  INScore Project

  Copyright (C) 2011  Grame

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
#include <sstream>

#include "TLoopEval.h"

#include "IMessageStream.h"
#include "IMessage.h"
#include "TEnv.h"
#include "TLoop.h"

using namespace std;
namespace inscore 
{

#define kVarChar	'%'
//--------------------------------------------------------------------------------------------
string	TLoopEval::expand (const char* str, const TEnv* env) const
{
	stringstream outstr;

	while (*str) {
		if (*str == kVarChar) {		// start of a loop variable identifier
			str++;					// go to next char
			string ident;			// prepare a string to receive the identifier
			int i;					// and an int to get the iteration number
			Sbaseparam val;			// 
			while (*str) {
				ident += *str;				// adds the next char to the identifier
				val = env->value(ident);	// and try to find a value
				if (val) break;			// exit when the value is found
				else str++;
			}
			if (val) {
				int i = val->value<int>(-1);
				if (i >= 0) outstr << i;
				else cerr << "while expanding variable " << ident << ": unexpected iteration type" << endl;
			}
			else return "";
			ident.clear();
		}
		else outstr << *str;
		str++;
	}

	return outstr.str();
}

//--------------------------------------------------------------------------------------------
TLoopEval::type TLoopEval::getType (const char* str) const
{
	type t = kTypeInt;
	if (*str == '+') str++;
	else if (*str == '-') str++;

	if (!*str)  return kTypeString;	
	while (*str) {
		if (*str == '.') {
			if (t == kTypeInt) return kTypeString;
			t = kTypeFloat;
		}
		else if ((*str == '+') || (*str > '9')) return kTypeString;
		str++;
	}
	return t;
}

//--------------------------------------------------------------------------------------------
bool TLoopEval::eval (TLoop* loop)
{
	return loop->eval (fEnv, fOutMsgs);
}

//--------------------------------------------------------------------------------------------
bool TLoopEval::eval (IMessage* msg)
{
	string	address = expand(msg->address().c_str(), fEnv);
	if (address.empty()) {
		cerr << "unknown variable in address " << msg->address().c_str() << endl;
		return false;
	}
	IMessage * expanded = new IMessage(address, msg->message());
	int n = msg->size();
	for (unsigned int i=0; i< n; i++) {
		string param;
		if (msg->param(i, param)) {
			string tr = expand(param.c_str(), fEnv);
			if (tr.empty()) {
				cerr << "unknown variable in parameter " << param << endl;
				return false;
			}
			else switch (getType(tr.c_str())) {
				case kTypeString:	expanded->add(tr); break;
				case kTypeInt:		expanded->add(atoi(tr.c_str())); break;
				case kTypeFloat:	expanded->add((float)atof(tr.c_str())); break;
			}
		}
		else expanded->add(msg->params()[i]);
	}	
	*fOutMsgs += expanded;
	return true;
}

} // namespace
