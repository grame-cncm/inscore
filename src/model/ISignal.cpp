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

#include "ISignal.h"
#include "ITLError.h"
#include "Updater.h"
#include "IMessage.h"
#include "IScene.h"
#include "ISignalNode.h"

using namespace std;

namespace inscore
{
//--------------------------------------------------------------------------
const string ISignal::kSignalType("sig");

//--------------------------------------------------------------------------
ISignal::ISignal( const std::string& name, IObject * parent ) : IObject (name, parent) //, fGRefCount(0)
{
	fTypeString = kSignalType;

	fMsgHandlerMap[kdefault_GetSetMethod]= TMethodMsgHandler<ISignal>::create(this, &ISignal::defaultMsg);
	fMsgHandlerMap[ksize_GetSetMethod]	 = TMethodMsgHandler<ISignal>::create(this, &ISignal::sizeMsg);
	fMsgHandlerMap[kreset_SetMethod]	 = TMethodMsgHandler<ISignal>::create(this, &ISignal::resetMsg);
	fMsgHandlerMap[""]		 = TMethodMsgHandler<ISignal>::create(this, &ISignal::dataMsg);
	fMsgHandlerMap[kwatch_GetSetMethod]	 = (void*)0;
	fMsgHandlerMap[kwatchplus_SetMethod] = (void*)0;

	SMsgHandler projhandler = TMethodMsgHandler<ISignal>::create(this, &ISignal::projectionDataMsg);
	fMsgHandlerMap["\\[[0-9]+\\]"]			= projhandler;
	fMsgHandlerMap["\\[[0-9]+~[0-9]*\\]"]	= projhandler;

	fGetMsgHandlerMap[ksize_GetSetMethod]		= TGetParamMethodHandler<ISignal, int (ParallelSignal::*)() const>::create(this, &ParallelSignal::size);
	fGetMsgHandlerMap[kdimension_GetMethod]	= TGetParamMethodHandler<ISignal, int (ParallelSignal::*)() const>::create(this, &ParallelSignal::dimension);
	fGetMsgHandlerMap[kdefault_GetSetMethod]	= GetDefaultParamMsgHandler::create(this);
}

//--------------------------------------------------------------------------
void ISignal::cleanup ()
{
	done();		// notify the parallel signal that it's done with available data
}

//--------------------------------------------------------------------------
void ISignal::accept (Updater* u)
{
	u->updateTo (SISignal(this));
}

#if defined(WIN32) && !defined(__MINGW_GCC)
//#define sscanf sscanf_s  
// commented due to a bug in decodeProjection below
// int values were not set although result was correct
// DF 2014-02-13
#endif
//--------------------------------------------------------------------------
bool ISignal::decodeProjection (const std::string& proj, int& index, int& step) const
{
	int i=0, s=0;
	char c = ' ';
	int result = sscanf(proj.c_str(), "[%d%c%d]", &i, &c, &s);
	if (!result) return false;			// incorrect string format

	index = i;
	step = 0;
	if ((result == 2) && (c == '~')) step = 1;
	else if (result == 3) step = s;
	return true;
}

//--------------------------------------------------------------------------
void ISignal::print (IMessage& out) const
{
	int n = ParallelSignal::dimension();
	if (n == 1) {
		vector<float> values = signal(0)->dump();
		if (values.size())
			out << values;
		else {
			out.setMessage(ksize_GetSetMethod);
			int size = signal(0)->size();
			out << size;
		}

	}
	else {
		out.setMessage(kset_SetMethod);
		for (int i = 0; i < n; i++) {
			const string& signame = signal(i)->name();
			if (signame.size())
				out << signame;
			else
				out << signal(i)->defaultValue();	// constant anonymous signal
		}
	}
}

//--------------------------------------------------------------------------
SIMessageList ISignal::getSetMsg() const
{
	SIMessageList outMsgs = IMessageList::create();
	SIMessage msg = IMessage::create (getOSCAddress());
	print(*msg);
	outMsgs->list().push_back (msg);
	return outMsgs;
}

//--------------------------------------------------------------------------
SISignalNode ISignal::getSignalNode()
{
	SIScene scene = getScene();
	return scene ? scene->signalsNode() : 0;
}

//--------------------------------------------------------------------------
bool ISignal::putAt (const IMessage* msg, int index, int step)
{
	float err = 999.9f;
	int size = msg->size();
	vector<float> values;
	for (int i = 0; i< size; i++) {
		float value;
		if (!msg->param(i, value)) return false;
		if ((value < err) && (value > -err))	// catch nan and inf input
			values.push_back(value);
	}
	if (!values.size()) return false;

	if (!dimension()) *this << TSignal::create(name(), values.size());
	SParallelSignal s = getProjection(index, step);
	if (!s) return false;
	s->put(values);

	if (available() > ParallelSignal::size()) {				// check for over-run
		fix();
		SISignalNode sn = getSignalNode();
		if (sn && sn->debug())
			oscerr << OSCWarn() << "over run for signal" << name() << OSCEnd();
	}
	return true;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignal::set (const IMessage* msg)
{
	int msgsize = msg->size();
	vector<SParallelSignal> signals;
	for (int i = 0; i < msgsize; i++) {

		float value;
		if (msg->param(i, value)) {			// ------------ constant anonymous signal form
			STSignal c = ConstTSignal::create(value);
			SParallelSignal p = ParallelSignal::create();
			if (p && c) *p << c;
			else return MsgHandler::kCreateFailure;		// memory allocation failed
			signals.push_back(p);
		}
		else {								// ------------ a named signal
			string name;
			if ( msg->param(i, name)) {
				SISignalNode sigs = getSignalNode();
				subnodes siglist;
				if (sigs && sigs->find(name, siglist)) {
					signals.push_back(dynamic_cast<ISignal*>((IObject*)siglist[0]));
				}
				else {
					ITLErr << "parallel signal" << this->name() << ": unknown signal" << name << ITLEndl;
					return MsgHandler::kBadParameters;
				}
			}
			else return MsgHandler::kBadParameters;			// syntax error: a string value is expected
		}
	}
	clear();		// clear the previous signals list
	for (unsigned int n=0; n < signals.size(); n++)
		*this << signals[n];
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
// message handlers
//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignal::sizeMsg (const IMessage* msg)
{
	if (msg->size() == 1) {
		int size = msg->param(0)->value<int>(-1);
		if (size > 0) {
			if (!dimension()) {
				*this << TSignal::create(name(), size);
				return dimension() ? MsgHandler::kProcessed : MsgHandler::kCreateFailure;
			}
			return ParallelSignal::size(size) ? MsgHandler::kProcessed : MsgHandler::kCreateFailure;
		}
	}
	return MsgHandler::kBadParameters;
}
//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignal::resetMsg (const IMessage* msg)
{
	if (msg->size()) return MsgHandler::kBadParameters;	// no arg expected
	ParallelSignal::reset();
	return MsgHandler::kProcessed;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignal::defaultMsg (const IMessage* msg)
{
	if (msg->size() ==  ParallelSignal::dimension()) {
		std::vector<float> defaultValue;
		for ( int i = 0 ; i < msg->size() ; i++ )
		{
			float val;
			if (msg->param(i, val)) {
				defaultValue.push_back( val );
			}
			else return MsgHandler::kBadParameters;
		}
		ParallelSignal::setDefaultValue( defaultValue );
		return MsgHandler::kProcessed;
	}
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignal::dataMsg (const IMessage* msg)
{
	if (!msg->size()) return MsgHandler::kBadParameters;
	return putAt(msg, 0, 1) ? MsgHandler::kProcessed : MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
MsgHandler::msgStatus ISignal::projectionDataMsg (const IMessage* msg)
{
	if (!msg->size()) return MsgHandler::kBadParameters;
	const string& msgstr = msg->message();
	int index, step;
	if (decodeProjection(msgstr, index, step))
		return putAt(msg, index, step) ? MsgHandler::kProcessed : MsgHandler::kBadParameters;
	return MsgHandler::kBadParameters;
}

//--------------------------------------------------------------------------
SIMessage&  ISignal::GetDefaultParamMsgHandler::print(SIMessage& out) const
{
	std::vector<float> outVal;
	fSignal->ParallelSignal::defaultValue(outVal);
	for ( unsigned int i = 0 ; i < outVal.size() ; i++ )
		*out << outVal[i];
	return out;
}

}
