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
#include <iostream>
#include <sstream>
#include <stdexcept>

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

int TMaths::toint (const IMessage::argPtr& arg) const {
	if (arg->isType<int>())	return arg->value(0);
	if (arg->isType<float>())	return int(arg->value(0.f));
	
	string empty("");
	if (arg->isType<string>())	return int(arg->value(empty).size());
	return 0;
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
// string & string -> string
// or
// string & num -> string when cast2string is true
//--------------------------------------------------------------------------------------------
TMaths::TType TMaths::type (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2, bool cast2string) const
{
	if (cast2string && (arg1->isType<string>() || arg2->isType<string>()))	return kString;

	if (arg1->isType<string>() && arg2->isType<string>() )	return kString;
	if (arg1->isType<int>()) {
		if (arg2->isType<int>() )			return kInt;
		if (arg2->isType<float>() )			return kFloat;
	}
	else if (arg1->isType<float>()) {
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
		throw std::invalid_argument( "math: unexpected empty args" );
	}
	
	if (n1 == 1) {
		for (size_t i=0; i < n2; i++)
			ret->push_back( (this->*op) (arg1[0], arg2[i]) );
		return ret;
	}
	
	if (n2 == 1) {
		for (size_t i=0; i < n1; i++)
			ret->push_back( (this->*op) (arg1[i], arg2[0]) );
		return ret;
	}

	size_t min=n1, max=n2;
	const IMessage::argslist* larger = &arg2;
	if ( n1 > n2) {						// find the largest list
		min = n2;
		max = n1;
		larger = &arg1;
	}
	for (size_t i=0; i < min; i++) {
		ret->push_back( (this->*op) (arg1[i], arg2[i]) );
	}
	for (size_t i=min; i < max; i++) {
		ret->push_back( (*larger)[i] );
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
	throw std::invalid_argument( "invalid increment on unsupported type of argument" );
}
IMessage::argPtr TMaths::dec (const IMessage::argPtr& arg) const
{
	if (arg->isType<int>()) return new IMsgParam<int>(arg->value(0) - 1);
	if (arg->isType<float>()) return new IMsgParam<float>(-arg->value(0.f) - 1);
	throw std::invalid_argument( "invalid decrement on unsupported type of argument" );
}
IMessage::argslist* TMaths::inc (const IMessage::argslist& arg) const
				{ return apply (&TMaths::inc, arg); }
IMessage::argslist* TMaths::dec (const IMessage::argslist& arg) const
				{ return apply (&TMaths::dec, arg); }

//--------------------------------------------------------------------------------------------
// max and min
//--------------------------------------------------------------------------------------------
IMessage::argslist*	TMaths::max	(const IMessage::argslist& arg) const
{
	IMessage::argslist* ret = new IMessage::argslist();
	size_t n = arg.size();
	if (!n) return ret;

	
	IMessage::argPtr max = arg[0];
	float val = tofloat(max);
	for (size_t i = 1; i < n; i++) {
		float vali = tofloat(arg[i]);
		if (vali > val) {
			max = arg[i];
			val = vali;
		}
	}
	ret->push_back (max);
	return ret;
}

IMessage::argslist*	TMaths::min	(const IMessage::argslist& arg) const
{
	IMessage::argslist* ret = new IMessage::argslist();
	size_t n = arg.size();
	if (!n) return ret;

	
	IMessage::argPtr min = arg[0];
	float val = tofloat(min);
	for (size_t i = 1; i < n; i++) {
		float vali = tofloat(arg[i]);
		if (vali < val) {
			min = arg[i];
			val = vali;
		}
	}
	ret->push_back (min);
	return ret;
}

//--------------------------------------------------------------------------------------------
// addition
//--------------------------------------------------------------------------------------------
IMessage::argPtr TMaths::add (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2, true);
	switch (t) {
		case kInt:		return new IMsgParam<int>(arg1->value(0) + arg2->value(0));
		case kFloat:	return new IMsgParam<float>(tofloat(arg1) + tofloat(arg2));
		case kString:	return new IMsgParam<string>(tostring(arg1) + tostring(arg2));
		default:
			throw std::invalid_argument( "math '+': unsupported type of argument" );
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
		default:
			throw std::invalid_argument( "math '-': unsupported type of argument" );
	}
}
IMessage::argPtr TMaths::minus (const IMessage::argPtr& arg) const
{
	if (arg->isType<int>()) return new IMsgParam<int>(-arg->value(0));
	if (arg->isType<float>()) return new IMsgParam<float>(-arg->value(0.f));
	throw std::invalid_argument( "math '-': unsupported type of argument" );
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
		default:
			throw std::invalid_argument( "math '*': unsupported type of argument" );
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
			throw std::invalid_argument( "math '/': unsupported type of argument" );
	}
	throw std::invalid_argument( "math '/': division by 0" );
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
		case kInt:
		case kFloat: {
			int val2 = toint(arg2);
			if (val2) return new IMsgParam<int>(toint(arg1) % val2);
			throw std::invalid_argument( "math '%': division by 0" );
		}
		break;
		default:
			throw std::invalid_argument( "math '%': unsupported type of argument" );
	}
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
	if (arg->isType<int>())			return arg->value(0) != 0;
	if (arg->isType<float>())		return arg->value(0.f) != 0.f;
	throw std::invalid_argument( "math boolean: unsupported type of argument" );
}

//--------------------------------------------------------------------------------------------
// check the boolean value of an args list
//--------------------------------------------------------------------------------------------
bool TMaths::tobool (const IMessage::argslist& args) const
{
	if (!args.size()) return false;				// an empty array is false
	for (size_t i = 0; i < args.size(); i++) {
		if (!tobool(args[i])) return false;
	}
	return true;
}

bool TMaths::equal (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt:		return arg1->value(0) == arg2->value(0);
		case kFloat:	return tofloat(arg1) == tofloat(arg2);
		case kString: {
			string empty;
			return arg1->value(empty) == arg2->value(empty);
		}
		default:
			throw std::invalid_argument( "math '==': unsupported type of argument" );
	}
}
bool TMaths::greater (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt:		return arg1->value(0) > arg2->value(0);
		case kFloat:	return tofloat(arg1) > tofloat(arg2);
		case kString: {
			string empty;
			return arg1->value(empty).compare (arg2->value(empty)) > 0;
		}
		default:
			throw std::invalid_argument( "math '>': unsupported type of argument" );
	}
}
bool TMaths::greatereq (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt:		return arg1->value(0) >= arg2->value(0);
		case kFloat:	return tofloat(arg1) >= tofloat(arg2);
		case kString: {
			string empty;
			return arg1->value(empty).compare (arg2->value(empty)) >= 0;
		}
		default:
			throw std::invalid_argument( "math '>=': unsupported type of argument" );
	}
}

bool TMaths::less (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt:		return arg1->value(0) < arg2->value(0);
		case kFloat:	return tofloat(arg1) < tofloat(arg2);
		case kString: {
			string empty;
			return arg1->value(empty).compare (arg2->value(empty)) < 0;
		}
		default:
			throw std::invalid_argument( "math '<': unsupported type of argument" );
	}
}
bool TMaths::lesseq (const IMessage::argPtr& arg1, const IMessage::argPtr& arg2) const
{
	TType t = type (arg1, arg2);
	switch (t) {
		case kInt:		return arg1->value(0) <= arg2->value(0);
		case kFloat:	return tofloat(arg1) <= tofloat(arg2);
		case kString: {
			string empty;
			return arg1->value(empty).compare (arg2->value(empty)) <= 0;
		}
		default:
			throw std::invalid_argument( "math '<=': unsupported type of argument" );
	}
}

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


} // namespace

