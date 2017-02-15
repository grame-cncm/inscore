/*

  INScore Project

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

#include <stdio.h>
#include <sstream>
#include <string>

#include "IFaustSignal.h"
#include "IScene.h"
#include "ITLError.h"
#include "Tools.h"
#include "Updater.h"

#include "UI.h"

using namespace std;

namespace inscore
{

//--------------------------------------------------------------------------
IFaustSignal::IFaustSignal( const std::string& name, IObject * parent ) : ISignal (name, parent), 
    fNumIntputs(0), fNumOutputs(0), fInBuffers(0), fOutBuffers(0)
{
	fGetMsgHandlerMap[kin_GetMethod]		= TGetParamMsgHandler<int>::create(fNumIntputs);
	fGetMsgHandlerMap[kout_GetMethod]	= TGetParamMsgHandler<int>::create(fNumOutputs);
}

//--------------------------------------------------------------------------
IFaustSignal::~IFaustSignal()
{
	for (int i= 0; i < fNumIntputs; i++)
		delete fInBuffers[i];
	for (int i= 0; i < fNumOutputs; i++)
		delete fOutBuffers[i];
	delete fInBuffers;
	delete fOutBuffers;
}

//--------------------------------------------------------------------------
bool IFaustSignal::putAt (const IMessage* msg, int index, int step)
{
	if (!dimension()) return true;		// nothing to do: there is no space for output signals

	int size = msg->size();
	if (!fNumIntputs) {
		call_compute(size, index, step);
		return true;
	}

	for (int i=0; i < size; i++) {
		int c = i % fNumIntputs;
		int frame = i / fNumIntputs;
		if (!msg->param(i, fInBuffers[c][frame])) return false;
	}
	call_compute (size/fNumIntputs, index, step);
	return true;
}

//--------------------------------------------------------------------------
/*
There are potential conflicts between the Faust UI objects naming scheme and 
the OSC address space. An OSC symbolic names is an ASCII string consisting of
printable characters other than the following:
	space 
#	number sign
*	asterisk
,	comma
/	forward
?	question mark
[	open bracket
]	close bracket
{	open curly brace
}	close curly brace

a simple solution to address the problem consists in replacing 
space or tabulation with '_' (underscore)
all the other osc excluded characters with '-' (hyphen)
*/
const char* IFaustSignal::translate (const char* name) const
{
	static char buffer[1024];
	char * ptr = buffer; int n=1;
	while (*name && (n++ < 1024)) {
		switch (*name) {
			case ' ': case '	':
				*ptr++ = '_';
				break;
			case '#': case '*': case ',': case '/': case '?':
			case '[': case ']': case '{': case '}':
				*ptr++ = '_';
				break;
			default: 
				*ptr++ = *name;
		}
		name++;
	}
	*ptr = 0;
	return buffer;
}

//--------------------------------------------------------------------------
void IFaustSignal::addMsgHandler (const char* name, float* zone)
{
	fMsgHandlerMap[translate(name)]	= SetFaustParamMsgHandler::create(zone);
	fGetMsgHandlerMap[translate(name)]	= GetFaustParamMsgHandler::create(zone);
}

void IFaustSignal::addMsgHandler (const char* name, float* zone, float min, float max)
{
	fMsgHandlerMap[translate(name)]	= SetCheckedFaustParamMsgHandler::create(zone, min, max);
	fGetMsgHandlerMap[translate(name)]	= GetFaustParamMsgHandler::create(zone);
}

//--------------------------------------------------------------------------
// output signals of a faust processor are available as 'name/0-n'
// where 'name' is the faust processor name and '0-n' is an index
// that refers to an output signal
//--------------------------------------------------------------------------
bool IFaustSignal::findSubNode (std::string name, subnodes& outlist)
{
	int index;
	if (!Tools::str2num(name.c_str(), index))	return false;
	if (index >= dimension())					return false;	// index must be less than the signal dimension
	
	string node = this->name() + "/" + name;
	SISignal s = ISignal::create(node, getParent());	// create a signal using the whole name (name/index)
	*s << this->signal(index);							// put it into the parent node
	outlist.push_back(s);								// push the node to the output list
	return true;										// and set the return code to true
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
SIMessage&  IFaustSignal::GetFaustParamMsgHandler::print(SIMessage& out) const
{
	*out << *fValue;
	return out;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus IFaustSignal::SetFaustParamMsgHandler::operator ()(const IMessage* msg)
{
	if ( msg->size() != 1 ) return kBadParameters;
	float val; int ival;
	if ( msg->param(0, ival) ) val = float(ival);
	else if ( !msg->param(0, val) ) return kBadParameters;
	*fValue = check(val);
	return kProcessed;
}

//--------------------------------------------------------------------------
float IFaustSignal::SetCheckedFaustParamMsgHandler::check(float val)
{
	if (val < fMin) return fMin;
	if (val > fMax) return fMax;
	return val;
}

}
