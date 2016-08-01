/*

  INScore Project

  Copyright (C) 2016  Grame

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


#include <string>
#include <sstream>

#include "TMaths.h"

using namespace std;

namespace inscore 
{

//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------
// simple math operations between messages arguments
//--------------------------------------------------------------------------------------------
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
// type conversion of arguments
//--------------------------------------------------------------------------------------------
float TMaths::tofloat (const IMessage::argPtr& arg) const {
	if (arg->isType<int>())	return float(arg->value(0));
	if (arg->isType<float>())	return arg->value(0.f);
	
	string empty("");
	if (arg->isType<string>())	return float(arg->value(empty).size());
	return 0.f;
}

std::string TMaths::tostring (const IMessage::argPtr& arg) const {
	stringstream sstr;
	if (arg->isType<int>())	{
		sstr << arg->value(0);
		return sstr.str();
	}
	if (arg->isType<float>()) {
		sstr << arg->value(0.f);
		return sstr.str();
	}

	string empty("");
	if (arg->isType<string>())	return arg->value(empty);
	return empty;
}

//--------------------------------------------------------------------------------------------
// check the resulting type of an operation on 2 args
// int & int	-> int
// int & float	-> float
// int & float	-> float
//--------------------------------------------------------------------------------------------
TMaths::TType TMaths::type (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	if (arg1->isType<string>() || arg2->isType<string>() )	return kString;
	if (arg1->isType<int>()) {
		if (arg2->isType<int>() )			return kInt;
		if (arg2->isType<float>() )			return kFloat;
		return kUnknow;
	}
	if (arg1->isType<float>()) {
		if (arg2->isType<int>() )			return kFloat;
		if (arg2->isType<float>() )			return kFloat;
	}
	return kUnknow;
}

//--------------------------------------------------------------------------------------------
// applies an operation to 2 args lists l1 and l2
// if l1 length < l2 length, the last l1 value is applied to the remaining l2 values
//--------------------------------------------------------------------------------------------
IMessage::argslist*	TMaths::apply (operation op, const IMessage::argslist& arg1, const IMessage::argslist& arg2) const
{
	IMessage::argslist* ret = new IMessage::argslist();
	size_t n1 = arg1.size();
	size_t n2 = arg2.size();
	if (!n1 || !n2) {
		ret->push_back (new IMsgParam<string>("TMaths: unexpected empty args"));
		return ret;
	}

	bool loop1 = true, loop2 = true;
	for (size_t i=0, j=0; loop1 || loop2; ) {
		ret->push_back( (this->*op) (arg1[i], arg2[j]) );
		if (i < (n1 - 1)) i++;
		else loop1 = false;
		if (j < (n2 - 1)) j++;
		else loop2 = false;
	}
	return ret;
}
IMessage::argslist*	TMaths::apply (unaryoperation op, const IMessage::argslist& args) const
{
	IMessage::argslist* ret = new IMessage::argslist();
	for (size_t i=0; i < args.size(); i++) {
		ret->push_back( (this->*op) (args[i]) );
	}
	return ret;
}

bool TMaths::apply (booloperation op, const IMessage::argslist& arg1, const IMessage::argslist& arg2) const
{
	size_t n1 = arg1.size();
	size_t n2 = arg2.size();
	if (n1 != n2) return false;
	for (size_t i=0; i < n1; i++) {
		if (! (this->*op) (arg1[i], arg2[i]) ) return false;
	}
	return true;
}

//--------------------------------------------------------------------------------------------
// increment and decrement
//--------------------------------------------------------------------------------------------
IMessage::argPtr TMaths::inc (const IMessage::argPtr& arg) const
{
	if (arg->isType<int>()) return new IMsgParam<int>(arg->value(0) + 1);
	if (arg->isType<float>()) return new IMsgParam<float>(-arg->value(0.f) + 1);
	return new IMsgParam<string>("TMaths: unsupported type for ++");
}
IMessage::argPtr TMaths::dec (const IMessage::argPtr& arg) const
{
	if (arg->isType<int>()) return new IMsgParam<int>(arg->value(0) - 1);
	if (arg->isType<float>()) return new IMsgParam<float>(-arg->value(0.f) - 1);
	return new IMsgParam<string>("TMaths: unsupported type for ++");
}
IMessage::argslist* TMaths::inc (const IMessage::argslist& arg) const
				{ return apply (&TMaths::inc, arg); }
IMessage::argslist* TMaths::dec (const IMessage::argslist& arg) const
				{ return apply (&TMaths::dec, arg); }

//--------------------------------------------------------------------------------------------
// addition
//--------------------------------------------------------------------------------------------
IMessage::argPtr TMaths::add (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt:		return new IMsgParam<int>(arg1->value(0) + arg2->value(0));
		case kFloat:	return new IMsgParam<float>(tofloat(arg1) + tofloat(arg2));
		case kString:	return new IMsgParam<string>(tostring(arg1) + tostring(arg2));
		default:		return new IMsgParam<string>("TMaths: unsupported type for add");
	}
}

IMessage::argslist*	TMaths::add	(IMessage::argslist* arg1, IMessage::argslist* arg2) const
				{ return apply (&TMaths::add, *arg1, *arg2); }

//--------------------------------------------------------------------------------------------
// substraction
//--------------------------------------------------------------------------------------------
IMessage::argPtr TMaths::sub (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt:		return new IMsgParam<int>(arg1->value(0) - arg2->value(0));
		case kFloat:	return new IMsgParam<float>(tofloat(arg1) - tofloat(arg2));
		default:		return new IMsgParam<string>("TMaths: unsupported type for sub");
	}
}
IMessage::argPtr TMaths::minus (const IMessage::argPtr& arg) const
{
	if (arg->isType<int>()) return new IMsgParam<int>(-arg->value(0));
	if (arg->isType<float>()) return new IMsgParam<float>(-arg->value(0.f));
	return new IMsgParam<string>("TMaths: unsupported type for -");
}
IMessage::argslist*	TMaths::sub	(IMessage::argslist* arg1, IMessage::argslist* arg2) const
				{ return apply (&TMaths::sub, *arg1, *arg2); }
IMessage::argslist*	TMaths::minus (IMessage::argslist* arg) const
				{ return apply (&TMaths::minus, *arg); }

//--------------------------------------------------------------------------------------------
// multiplication
//--------------------------------------------------------------------------------------------
IMessage::argPtr TMaths::mult (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt:		return new IMsgParam<int>(arg1->value(0) * arg2->value(0));
		case kFloat:	return new IMsgParam<float>(tofloat(arg1) * tofloat(arg2));
		default:		return new IMsgParam<string>("TMaths: unsupported type for sub");
	}
}

IMessage::argslist*	TMaths::mult (IMessage::argslist* arg1, IMessage::argslist* arg2) const
				{ return apply (&TMaths::mult, *arg1, *arg2); }

//--------------------------------------------------------------------------------------------
// division
//--------------------------------------------------------------------------------------------
IMessage::argPtr TMaths::div (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt: {
			int val = arg2->value(0);
			if (val) return new IMsgParam<int>(arg1->value(0) / val);
		}
		break;
		case kFloat: {
			float val = tofloat(arg2);
			if (val) return new IMsgParam<float>(tofloat(arg1) / val);
		}
		break;
		default:
			return new IMsgParam<string>("TMaths: unsupported type for sub");
	}
	return new IMsgParam<string>("TMaths exception: division by 0");
}

IMessage::argslist*	TMaths::div	(IMessage::argslist* arg1, IMessage::argslist* arg2) const
				{ return apply (&TMaths::div, *arg1, *arg2); }

//--------------------------------------------------------------------------------------------
// modulo
//--------------------------------------------------------------------------------------------
IMessage::argPtr TMaths::mod (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt: {
			int val = arg2->value(0);
			if (val) return new IMsgParam<int>(arg1->value(0) % val);
		}
		break;
		case kFloat: {
			float val = tofloat(arg2);
			if (val) new IMsgParam<string>("TMaths: invalid operand to '%' expression");
		}
		break;
		default:
			return new IMsgParam<string>("TMaths: unsupported type for sub");
	}
	return new IMsgParam<string>("TMaths exception: division by 0");
}

IMessage::argslist*	TMaths::mod	(IMessage::argslist* arg1, IMessage::argslist* arg2) const
				{ return apply (&TMaths::mod, *arg1, *arg2); }

//--------------------------------------------------------------------------------------------
// boolean operations
//--------------------------------------------------------------------------------------------

//--------------------------------------------------------------------------------------------
// check the boolean value of a message argument
// works as expected for numeric values
// for strings, returns false for empty string
//--------------------------------------------------------------------------------------------
bool TMaths::tobool (const IMessage::argPtr& arg) const
{
	string empty("");
	if (arg->isType<std::string>())	return !arg->value(empty).empty();
	if (arg->isType<int>())			return arg->value(0) != 0;
	if (arg->isType<float>())		return arg->value(0.f) != 0.f;
	return false;
}

//--------------------------------------------------------------------------------------------
// check the boolean value of an args list
//--------------------------------------------------------------------------------------------
bool TMaths::tobool (const IMessage::argslist& args) const
{
	for (size_t i = 0; i < args.size(); i++) {
		if (!tobool(args[i])) return false;
	}
	return true;
}

bool TMaths::equal (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	return false;
}
bool TMaths::greater (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
									{ return tofloat(arg1) > tofloat(arg2); }
bool TMaths::greatereq (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
									{ return tofloat(arg1) >= tofloat(arg2); }
bool TMaths::less (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
									{ return tofloat(arg1) < tofloat(arg2); }
bool TMaths::lesseq (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
									{ return tofloat(arg1) <= tofloat(arg2); }

bool TMaths::equal (const IMessage::argslist& arg1, const IMessage::argslist& arg2) const
									{ return apply (&TMaths::equal, arg1, arg2); }
bool TMaths::greater (const IMessage::argslist& arg1, const IMessage::argslist& arg2) const
									{ return apply (&TMaths::greater, arg1, arg2); }
bool TMaths::greatereq (const IMessage::argslist& arg1, const IMessage::argslist& arg2) const
									{ return apply (&TMaths::greatereq, arg1, arg2); }
bool TMaths::less (const IMessage::argslist& arg1, const IMessage::argslist& arg2) const
									{ return apply (&TMaths::less, arg1, arg2); }
bool TMaths::lesseq	(const IMessage::argslist& arg1, const IMessage::argslist& arg2) const
									{ return apply (&TMaths::lesseq, arg1, arg2); }


//IMessage::argslist*	TMaths::cond (IMessage::argslist* arg1, IMessage::argslist* arg2, IMessage::argslist* arg3) const
//{
//	IMessage::argslist* ret = new IMessage::argslist();
//	ret->push_back( tobool(*arg1) ? arg2 : arg3);
//	return ret;
//}


} // namespace

