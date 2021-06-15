/*

  INScore Project

  Copyright (C) 2021  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <algorithm>
#include <cctype>
#include <iostream>
#include <sstream>
#include <regex>

#include "TMidiFilter.h"
#include "IMessageStream.h"

using namespace std;

#define kKeyOff 	8
#define kKeyOn  	9
#define kProgramChge  	0xc
#define kControlChge  	0xb
//#define NoteOff        0x80
//#define NoteOn         0x90
//#define ControlChg     0xb0
//#define ProgramChg     0xc0

namespace inscore
{

//--------------------------------------------------------------------------
TMidiFilter::TMidiValueSelector::operator string () const
{
	stringstream str;
	size_t n = literal.size();
	const char * rstart = n == 1 ? "" : "[";
	const char * rend 	= n == 1 ? "" : "]";
	if (n) {
		str << rstart;
		const char * sep = "";
		for (auto v: literal) { str << sep << v; sep = " "; };
		str << rend;
	}
	else {
		if (range.mode == midivaluerange::kLeave) {
			rstart = ")";
			rend   = "(";
		}
		else if (range.mode == midivaluerange::kEnter) {
			rstart = "(";
			rend   = ")";
		}
		str << rstart << range.low << "-" << range.high << rend;
	}
	return str.str();
}

//--------------------------------------------------------------------------
bool TMidiFilter::TMidiValueSelector::operator < (const TMidiValueSelector& v) const
{
	int sum = 0;
	for (auto n: literal) sum += n;
	int vsum = 0;
	for (auto n: v.literal) vsum += n;
	return (range < v.range) || (sum < vsum);
}

//--------------------------------------------------------------------------
bool TMidiFilter::operator == (const TMidiFilter& f) const {
	if (fChan != f.getChan()) return false;
	int type = getType();
	if (type != f.getType()) return false;
	if (type == kKeyFilter) return *getKey() == *(f.getKey());
	else if (type == kCtrlFilter) return *getCtrl() == *(f.getCtrl());
	else return true;
}

bool TMidiFilter::operator < (const TMidiFilter& f) const
{
	if (fChan < f.getChan()) return true;
	int type = getType();
	if (type < f.getType()) return true;
	else if (type == f.getType()) {
		if (type == kKeyFilter) return *getKey() < *(f.getKey());
		else if (type == kCtrlFilter) return *getCtrl() < *(f.getCtrl());
	}
	return false;
}

//--------------------------------------------------------------------------
bool TMidiFilter::midivaluerange::accept (int val)
{
	if (mode == kIn) return (val >= low) && (val <= high);

	if (last < 0) { last = val; return false; }
	bool result = false;
	switch (mode) {
		case kEnter:
			if ((last < low) || (last > high))
				result = (val >= low) && (val <= high);
			break;
		case kLeave:
			if ((last >= low) && (last <= high))
				result = (val < low) || (val > high);
			break;
	}
	last = val;
	return result;
}

//--------------------------------------------------------------------------
bool TMidiFilter::midivaluesel::accept (int val)
{
	if (literal.size()) {
		const std::set<int>::iterator i = find (literal.begin(), literal.end(), val);
		return i != literal.end();
	}
	else return range.accept(val);
}

//--------------------------------------------------------------------------
void TMidiFilter::midikeysel::print (SIMessage msg) const
{
	const char* type = keyon ? "keyon" : "keyoff";
	*msg << type << string(keyval);
	if (vel)
		*msg << "vel" << string(velval);
}

//--------------------------------------------------------------------------
bool TMidiFilter::midikeysel::accept (char status, char data1, char data2)
{
	TMidiStatus m(status);
	if (keyon) {
		if (m.type != kKeyOn) return false;
	}
	else if (m.type != kKeyOff) return false;
	if (!keyval.accept(data1)) return false;
	if (vel && !velval.accept(data2)) return false;
	return true;
}

//--------------------------------------------------------------------------
void TMidiFilter::midiothersel::print (SIMessage msg) const
{
	const char* typeStr = (type == kProgramChge) ? "prog" : "ctrl";
	*msg << typeStr << num;
	if (type != kProgramChge)
		*msg << string(val);
}

//--------------------------------------------------------------------------
bool TMidiFilter::midiothersel::accept (char status, char data1, char data2)
{
	TMidiStatus m(status);
	if ((type != m.type) || (num != data1))  return false;
	if (type != kProgramChge)
		return val.accept (data2);
	return true;
}

//--------------------------------------------------------------------------
bool TMidiFilter::string2valueRange (const char* str, TMidiValueRange& val) const
{
	size_t i;
	int low = 0;
	int high = 0;
	try {
		low = stoi(&str[1], &i);
		i += 1;
		if (str[i] != '-' ) return false;
		str += i + 1;
		int high = stoi(str, &i);
		char end = str[i];
		if ((end != '(') && (end != ')') && (end != ']')) return false;
		val.low = low;
		val.high = high;
	}
	catch (exception) { return false; }
	return true;
}

//--------------------------------------------------------------------------
bool TMidiFilter::string2valueList (const char* ptr, std::set<int>& list) const
{
	size_t i;
	ptr++;		// skip the leading list marker
	try {
		do {
			int num = 0;
			num = stoi(ptr, &i);
			if (num < 0) return false;
			list.insert (num);
			ptr += i;
			if (*ptr == ']') break;
			else if (*ptr++ != ' ') return false;
		} while (*ptr);
	}
	catch (exception) { return false; }
	return true;
}

//--------------------------------------------------------------------------
bool TMidiFilter::string2valueSelector (const std::string& str, TMidiValueSelector& val) const
{
	bool result = false;
	size_t n = str.size();
	// check first for correctness
	// allowed forms are :
	// - a integer number
	// - a list of space separated int i.e. [a b c]
	// - a range i.e. [a-b] or (a-c) or )a-b(
	if (std::regex_match (str, std::regex("[^0-9[]() -"))) return false;
	const char* ptr = str.c_str();
	if ((ptr[0] == '[') && (ptr[n-1] == ']')) {
		if (string2valueRange (ptr, val.range))
			val.range.mode = midivaluerange::kIn;
		else return string2valueList (ptr, val.literal);
	}
	else if ((ptr[0] == ')') && (ptr[n-1] == '(')) {
		if (!string2valueRange (ptr, val.range)) return false;
		val.range.mode = midivaluerange::kLeave;
	}
	else if ((ptr[0] == '(') && (ptr[n-1] == ')')) {
		if (!string2valueRange (ptr, val.range)) return false;
		val.range.mode = midivaluerange::kEnter;
	}
	else {
		try { val.literal.insert (stoi(ptr)); }
		catch (exception) { return false; }
	}
	return true;
}

//--------------------------------------------------------------------------
bool TMidiFilter::setKey  (bool keyon, const std::string& val)
{
	TMidiValueSelector sel;
	if (string2valueSelector (val, sel)) {
		fKey.keyon = keyon;
		fKey.vel = false;
		fKey.keyval = sel;
		fType = kKeyFilter;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool TMidiFilter::setKey  (bool keyon, const std::string& val, const string& velval)
{
	TMidiValueSelector sel;
	if (string2valueSelector (velval, sel) && setKey(keyon, val)) { // && fKey) {
		fKey.vel = true;
		fKey.velval = sel;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool TMidiFilter::setCtrl (int num, const string& val )
{
	TMidiValueSelector sel;
	if (string2valueSelector (val, sel)) {
		fCtrl.type = kControlChge;
		fCtrl.num = num;
		fCtrl.val = sel;
		fType = kCtrlFilter;
		return true;
	}
	return false;
}

//--------------------------------------------------------------------------
bool TMidiFilter::setProg (int num )
{
	fCtrl.type = kProgramChge;
	fCtrl.num  = num;
	fType = kCtrlFilter;
	return true;
}

//--------------------------------------------------------------------------
bool TMidiFilter::accept (char status, char data1, char data2)
{
	TMidiStatus msg (status);
	if ((fChan >= 0) && (msg.chan != fChan)) return false;
	else if (getCurrent())
		return getCurrent()->accept (status, data1, data2);
	return true;
}

} // end namespace
