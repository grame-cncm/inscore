/*

  INScore Project

  Copyright (C) 2019  Grame

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

  Grame - Centre national de création musicale, 
  11 cours de Verdun Gensoul, 69002 Lyon - France

*/



#include <algorithm>
#include <sstream>
#include <string>
#include <cmath>
#include <random>

#include "evaluator2.h"
#include "expandEval.h"
#include "expandVal.h"
#include "parseEval.h"
#include "TEnv2.h"
#include "TreeTools.h"

using namespace std;

#include <exception>
using namespace std;


namespace inscore2
{

//------------------------------------------------------------
static SINode getTypedNode (const NList& l, INode::TNodeType t)
{
	for (auto n: l) {
		if (n->getType() == t) return n;
	}
	return 0;
}

//------------------------------------------------------------
evaluator::TType evaluator::getType (const NList& args)
{
	int strcount=0, intcount=0, floatcount=0, delayCount=0;
	for (auto n: args) {
		INode::TNodeType t = n->getType();
		if ((t >= INode::kFirstMath) && (t <=INode::kLastMath))
			return kDefer;		// assumes a subnode has already been deferred

		else switch (n->getType()) {
			case INode::kDelay:		delayCount++; break;
			case INode::kText:		strcount++; break;
			case INode::kInt:		intcount++; break;
			case INode::kFloat:		floatcount++; break;
			
			// a non-evaluated variable prevents the expression evaluation
			// assumes that the variable is intended to be resolved later
			case INode::kVariable:	return kDefer;

			default:
			{
				stringstream what;
				what << "unexpected type of argument (type " << n->getType() << ": " << n->getTypeStr() << ")";
				error (n, what.str());
			}
		}
	}
	if (strcount) 	return kString;
	if (delayCount) return kDelay;
	if (floatcount) return kFloat;
	return kInt;
}

//------------------------------------------------------------
// addition
//------------------------------------------------------------
SINode evaluator::addStrings (const NList& args)
{
	stringstream sum;
	for (auto n: args) sum << n->getValue();
	SINode out = INode::create (sum.str());
	out->setAddress( args.size() ? args[0]->address() : false );
	return out;
}

//------------------------------------------------------------
SINode evaluator::addInt (const NList& args)
{
	int sum = 0;
	for (auto n: args) sum += std::stoi(n->getValue());
	return INode::create (sum);
}

//------------------------------------------------------------
SINode evaluator::addFloat (const NList& args)
{
	float sum = 0;
	for (auto n: args) sum += std::stof(n->getValue());
	return INode::create (sum);
}

//------------------------------------------------------------
SINode evaluator::addDelay (const NList& args)
{
	float sum = 0;
	for (auto n: args) sum += n->getFloat();
	return SINode( new DelayNode( sum) );
}

//------------------------------------------------------------
SINode evaluator::evalAdd 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error( node, "operator '+' requires at least 2 arguments");
	switch (type) {
		case kString:	return addStrings (args);
		case kDelay:	return addDelay (args);
		case kFloat:	return addFloat (args);
		default:		return addInt (args);
	}
}

//------------------------------------------------------------
// substraction
//------------------------------------------------------------
SINode evaluator::subInt (const NList& args)
{
	int result = std::stoi(args[0]->getValue());
	for (size_t i = 1; i < args.size(); i++) result -= std::stoi(args[i]->getValue());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::subFloat (const NList& args)
{
	float result = std::stof(args[0]->getValue());
	for (size_t i = 1; i < args.size(); i++) result -= std::stof(args[i]->getValue());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::subDelay (const NList& args)
{
	float result = args[0]->getFloat();
	for (size_t i = 1; i < args.size(); i++) result -= args[i]->getFloat();
	return SINode( new DelayNode( result) );
}

//------------------------------------------------------------
SINode evaluator::evalSub 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator '-' requires at least 2 arguments");
	switch (type) {
		case kString:	throw (evalException ("invalid string argument passed to operator '-'"));
		case kDelay:	return subDelay (args);
		case kFloat:	return subFloat (args);
		default:		return subInt (args);
	}
}

//------------------------------------------------------------
// divison
//------------------------------------------------------------
SINode evaluator::divInt (const NList& args)
{
	int result = std::stoi(args[0]->getValue());
	for (size_t i = 1; i < args.size(); i++) result /= std::stoi(args[i]->getValue());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::divFloat (const NList& args)
{
	float result = std::stof(args[0]->getValue());
	for (size_t i = 1; i < args.size(); i++) {
		float v = std::stof(args[i]->getValue());
		if (v) result /= v;
		else  error (args[i], "divide by zero");
	}
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::divDelay (const NList& args)
{
	float result = args[0]->getFloat();
	for (size_t i = 1; i < args.size(); i++) {
		float v = args[i]->getFloat();
		if (v) result /= v;
		else  error (args[i], "divide by zero");
	}
	return SINode( new DelayNode( result) );
}

//------------------------------------------------------------
SINode evaluator::evalDiv 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator '/' requires at least 2 arguments");
	switch (type) {
		case kString:	throw (evalException ("invalid string argument passed to operator '/'"));
		case kDelay:	return divDelay (args);
		case kFloat:	return divFloat (args);
		default:		return divInt (args);
	}
}

//------------------------------------------------------------
// multiplication
//------------------------------------------------------------
SINode evaluator::multInt (const NList& args)
{
	int result = std::stoi(args[0]->getValue());
	for (size_t i = 1; i < args.size(); i++) result *= std::stoi(args[i]->getValue());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::multFloat (const NList& args)
{
	float result = std::stof(args[0]->getValue());
	for (size_t i = 1; i < args.size(); i++) result *= std::stof(args[i]->getValue());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::multDelay (const NList& args)
{
	float result = args[0]->getFloat();
	for (size_t i = 1; i < args.size(); i++) result *= args[i]->getFloat();
	return SINode( new DelayNode( result) );
}

//------------------------------------------------------------
SINode evaluator::evalMult 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator '*' requires at least 2 arguments");
	switch (type) {
		case kString:	error (getTypedNode(args, INode::kText), "invalid string argument passed to operator '*'");
		case kDelay:	return multDelay (args);
		case kFloat:	return multFloat (args);
		default:		return multInt (args);
	}
}

//------------------------------------------------------------
// modulo
//------------------------------------------------------------
SINode evaluator::moduloInt (const NList& args)
{
	int result = std::stoi(args[0]->getValue());
	for (size_t i = 1; i < args.size(); i++) result %= std::stoi(args[i]->getValue());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::evalModulo (const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator '%' requires at least 2 arguments");
	switch (type) {
		case kString:	error (getTypedNode(args, INode::kText), "invalid string argument passed to operator '%'");
		case kFloat:	error (getTypedNode(args, INode::kFloat), "unexpected float argument passed to operator '%'");
		default:		return moduloInt (args);
	}
}

//------------------------------------------------------------
bool evaluator::isTrue  (const SINode& n)
{
	string testStr = n->getValue();
	switch (n->getType()) {
		case INode::kText:
			return (testStr == "true") || (testStr=="yes") || (testStr == "on");
		case INode::kFloat:
		case INode::kDelay:
			return  n->getFloat() != 0.f;
		case INode::kInt:
			return  std::stoi(testStr) != 0;
		default:	return false;
	}
}

//------------------------------------------------------------
// the ? (test, a, b) form
//------------------------------------------------------------
SINode evaluator::evalQuest 	(const SINode& node, const NList& args)
{
	if (args.size() != 3) error (node, "operator '?' requires 3 arguments");
	return SINode (isTrue(args[0]) ? args[1]->clone() : args[2]->clone());
}

//------------------------------------------------------------
// boolean operation
//------------------------------------------------------------
SINode evaluator::evalNeg 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() != 1) error (node, "operator '!' requires 1 argument");
	return SINode (new INode (isTrue(args[0]) ? "false" : "true"));
}

SINode evaluator::evalEq 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() != 2) error (node, "operator '==' requires 2 arguments");
	string result = (args[0] == args[1]) ? "true" : "false";
	return SINode (new INode (result));
}

SINode evaluator::compare (const SINode& arg1, const SINode& arg2, TCompStrFunction f)
{
	string result = f(arg1->getValue(), arg2->getValue()) ? "true" : "false";
	return SINode (new INode (result));

}

SINode evaluator::compare (const SINode& arg1, const SINode& arg2, TCompNumFunction f)
{
	float v1 = arg1->getFloat();
	float v2 = arg2->getFloat();
	string result = f(v1, v2) ? "true" : "false";
	return SINode (new INode (result));
}

SINode evaluator::evalGreater (const SINode& node, const NList& args, TType type)
{
	if (args.size() != 2) error (node, "operator '>' requires 2 arguments");
	if (type == kString)
		return compare (args[0], args[1], [](string a, string b) -> bool { return a.compare(b) > 0; });
	return compare (args[0], args[1], [](float a, float b) -> bool { return a > b; });
}

SINode evaluator::evalGreatereq(const SINode& node, const NList& args, TType type)
{
	if (args.size() != 2) error (node, "operator '>=' requires 2 arguments");
	if (type == kString)
		return compare (args[0], args[1], [](string a, string b) -> bool { return a.compare(b) >= 0; });
	return compare (args[0], args[1], [](float a, float b) -> bool { return a >= b; });
}

SINode evaluator::evalLess 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() != 2) error (node, "operator '<' requires 2 arguments");
	if (type == kString)
		return compare (args[0], args[1], [](string a, string b) -> bool { return a.compare(b) < 0; });
	return compare (args[0], args[1], [](float a, float b) -> bool { return a < b; });
}

SINode evaluator::evalLesseq	(const SINode& node, const NList& args, TType type)
{
	if (args.size() != 2) error (node, "operator '>=' requires 2 arguments");
	if (type == kString)
		return compare (args[0], args[1], [](string a, string b) -> bool { return a.compare(b) <= 0; });
	return compare (args[0], args[1], [](float a, float b) -> bool { return a <= b; });
}


//------------------------------------------------------------
// the min function
//------------------------------------------------------------
SINode evaluator::minStrings	(const NList& args)
{
	SINode node = args[0];
	size_t min = node->getValue().size();
	for (size_t i=1; i < args.size(); i++) {
		size_t n = args[i]->getValue().size();
		if (n < min) {
			min = n;
			node = args[i];
		}
	}
	return node->clone();
}

//------------------------------------------------------------
SINode evaluator::minNum	(const NList& args)
{
	SINode node = args[0];
	double min = node->getFloat();
	for (size_t i=1; i < args.size(); i++) {
		float n = args[i]->getFloat();
		if (n < min) {
			min = n;
			node = args[i];
		}
	}
	return node->clone();
}

//------------------------------------------------------------
SINode evaluator::evalMin (const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator 'min' requires at least 2 arguments");
	switch (type) {
		case kString:	return minStrings (args);
		default:		return minNum (args);;
	}
}


//------------------------------------------------------------
// the max function
//------------------------------------------------------------
SINode evaluator::maxStrings	(const NList& args)
{
	SINode node = args[0];
	size_t max = node->getValue().size();
	for (size_t i=1; i < args.size(); i++) {
		size_t n = args[i]->getValue().size();
		if (n > max) {
			max = n;
			node = args[i];
		}
	}
	return node->clone();
}
//------------------------------------------------------------
SINode evaluator::maxNum	(const NList& args)
{
	SINode node = args[0];
	float max = node->getFloat();
	for (size_t i=0; i < args.size(); i++) {
		float n = args[i]->getFloat();
		if (n > max) {
			max = n;
			node = args[i];
		}
	}
	return node->clone();
}

//------------------------------------------------------------
SINode evaluator::evalMax	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator 'max' requires at least 2 arguments");
	switch (type) {
		case kString:	return maxStrings (args);
		default:		return maxNum (args);;
	}
}

//------------------------------------------------------------
SINode evaluator::evalHas	(const SINode& node, const NList& args)
{
	if (args.size() < 2) error (node, "operator 'has' requires at least 2 arguments");
	SINode n = args[0];
	for (size_t i = 1; i < args.size(); i++)
		if (*n.get() == args[i]) return SINode (new INode ("true"));
	return SINode (new INode ("false"));
}

//------------------------------------------------------------
float evaluator::getFArgValue (const SINode& node, const NList& args, TCreateFunction& f)
{
	stringstream what;
	if (args.size() != 1) {
		what << "unexpected arguments: 1 expected, got " << args.size();
		error (node, what.str());
	}
	SINode arg = args[0];
	switch (arg->getType()) {
		case INode::kInt:
		case INode::kFloat:
			f = [] (float v) -> SINode { return INode::create(v); };
			return arg->getFloat();
		case INode::kDelay:
			f = [] (float v) -> SINode { return INode::createDelay(v); };
			return arg->getFloat();
		default:
			what << "unexpected type of argument (type " << arg->getType() << ": " << arg->getTypeStr() << ")";
			error (arg, what.str());
	}
	return 0.f;		// just to avoid the "end of non-void" warning
}

//------------------------------------------------------------
SINode evaluator::evalSin 	(float value, TCreateFunction create) 	{ return create ( sin(value)); }
SINode evaluator::evalCos 	(float value, TCreateFunction create) 	{ return create ( cos(value)); }
SINode evaluator::evalTan 	(float value, TCreateFunction create) 	{ return create ( tan(value)); }
SINode evaluator::evalASin 	(float value, TCreateFunction create) 	{ return create ( asin(value)); }
SINode evaluator::evalACos 	(float value, TCreateFunction create) 	{ return create ( acos(value)); }
SINode evaluator::evalATan 	(float value, TCreateFunction create) 	{ return create ( atan(value)); }
SINode evaluator::evalSinh 	(float value, TCreateFunction create) 	{ return create ( sinh(value)); }
SINode evaluator::evalCosh 	(float value, TCreateFunction create) 	{ return create ( cosh(value)); }
SINode evaluator::evalTanh 	(float value, TCreateFunction create) 	{ return create ( tanh(value)); }
SINode evaluator::evalASinh (float value, TCreateFunction create) 	{ return create ( asinh(value)); }
SINode evaluator::evalACosh (float value, TCreateFunction create) 	{ return create ( acosh(value)); }
SINode evaluator::evalATanh (float value, TCreateFunction create) 	{ return create ( atanh(value)); }

SINode evaluator::evalExp 	(float value, TCreateFunction create) 	{ return create ( exp(value)); }
SINode evaluator::evalLog 	(float value, TCreateFunction create) 	{ return create ( log(value)); }
SINode evaluator::evalLog10 (float value, TCreateFunction create) 	{ return create ( log10(value)); }
SINode evaluator::evalLog2 	(float value, TCreateFunction create) 	{ return create ( log2(value)); }
SINode evaluator::evalSqrt 	(float value, TCreateFunction create) 	{ return create ( sqrt(value)); }
SINode evaluator::evalCbrt 	(float value, TCreateFunction create) 	{ return create ( cbrt(value)); }
SINode evaluator::evalCeil 	(float value, TCreateFunction create) 	{ return create ( ceil(value)); }
SINode evaluator::evalFloor (float value, TCreateFunction create) 	{ return create ( floor(value)); }
SINode evaluator::evalRound (float value, TCreateFunction create) 	{ return create ( round(value)); }

SINode evaluator::evalPow (const SINode& node, const NList& args, TType type)
{
	if ((args.size() != 2) || (type == kString)) error (node, "operator 'pow' requires 2 numeric arguments");
	float val = pow (args[0]->getFloat(), args[1]->getFloat());
	return (type == kDelay) ?  INode::createDelay (val) : INode::create (val);
}

static std::random_device rdev;
SINode evaluator::evalRand () 				{ return INode::create (((float)rdev() / rdev.max()) * 2 - 1); }

//------------------------------------------------------------
SINode evaluator::evalMath (const SINode& node, const TEnv& env)
{
	NList l;
	for (auto n: node->childs()) {
		SINode e = eval(n, env + n->getEnv());
		if (e->getType() == INode::kForest)
			l.add (e->childs());
		else
			l.add (e);
	}

	SINode out;
	INode::TNodeType t = node->getType ();
	if (t == INode::kQuest)
		return evalQuest (node, l);

	TType exprType = getType (l);
	TCreateFunction f;
	if (exprType == kDefer)
		return node->clone(l);
	
	else switch (t) {
		case INode::kAdd:		out = evalAdd		(node, l, exprType); break;
		case INode::kSub:		out = evalSub		(node, l, exprType); break;
		case INode::kDiv:		out = evalDiv		(node, l, exprType); break;
		case INode::kMult:		out = evalMult		(node, l, exprType); break;
		case INode::kModulo:	out = evalModulo	(node, l, exprType); break;
		case INode::kNeg:		out = evalNeg		(node, l, exprType); break;
		case INode::kEq:		out = evalEq		(node, l, exprType); break;
		case INode::kGreater:	out = evalGreater	(node, l, exprType); break;
		case INode::kGreatereq:	out = evalGreatereq (node, l, exprType); break;
		case INode::kLess:		out = evalLess		(node, l, exprType); break;
		case INode::kLesseq:	out = evalLesseq	(node, l, exprType); break;
		case INode::kMin:		out = evalMin		(node, l, exprType); break;
		case INode::kMax:		out = evalMax		(node, l, exprType); break;
		case INode::kHas:		out = evalHas		(node, l); break;

		case INode::kSin:		out = evalSin	(getFArgValue(node, l, f), f); break;
		case INode::kCos:		out = evalCos	(getFArgValue(node, l, f), f); break;
		case INode::kTan:		out = evalTan	(getFArgValue(node, l, f), f); break;
		case INode::kASin:		out = evalASin	(getFArgValue(node, l, f), f); break;
		case INode::kACos:		out = evalACos	(getFArgValue(node, l, f), f); break;
		case INode::kATan:		out = evalATan	(getFArgValue(node, l, f), f); break;
		case INode::kSinh:		out = evalSinh	(getFArgValue(node, l, f), f); break;
		case INode::kCosh:		out = evalCosh	(getFArgValue(node, l, f), f); break;
		case INode::kTanh:		out = evalTanh	(getFArgValue(node, l, f), f); break;
		case INode::kASinh:		out = evalASinh	(getFArgValue(node, l, f), f); break;
		case INode::kACosh:		out = evalACosh	(getFArgValue(node, l, f), f); break;
		case INode::kATanh:		out = evalATanh	(getFArgValue(node, l, f), f); break;

		case INode::kExp: 		out = evalExp	(getFArgValue(node, l, f), f); break;
		case INode::kLog: 		out = evalLog	(getFArgValue(node, l, f), f); break;
		case INode::kLog10: 	out = evalLog10 (getFArgValue(node, l, f), f); break;
		case INode::kLog2: 		out = evalLog2	(getFArgValue(node, l, f), f); break;
		case INode::kSqrt: 		out = evalSqrt	(getFArgValue(node, l, f), f); break;
		case INode::kCbrt: 		out = evalCbrt	(getFArgValue(node, l, f), f); break;
		case INode::kCeil: 		out = evalCeil	(getFArgValue(node, l, f), f); break;
		case INode::kFloor: 	out = evalFloor	(getFArgValue(node, l, f), f); break;
		case INode::kRound: 	out = evalRound	(getFArgValue(node, l, f), f); break;

		case INode::kPow: 		out = evalPow	(node, l, exprType); break;
		case INode::kRand: 		out = evalRand(); break;
		default:
			;
	}

	if (l.size()) {
		SINode m = l[0];		// now merge subnodes
		for (size_t i = 1; i < l.size(); i++) m = m->merge(l[i]);
		return out->clone (m->childs());
	}
	return out;
}

//------------------------------------------------------------
SINode evaluator::evalNode (const SINode& node, const TEnv& env)
{
	NList l;
	bool addr = node->isForest() && node->address();
	for (auto n: node->childs()) {
		SINode e = eval(n, env + n->getEnv());
		if (addr) e->setAddress(true);
		if (e->getType() == INode::kForest)
			l.add (e->childs());
		else
			l.add (e);
	}
	return node->clone(l);
}

//------------------------------------------------------------
SINode evaluator::evalSlash (const SINode& node, const TEnv& env)
{
	if (node->empty()) throw (evalException ("unexpected empty '/' node."));

	NList l;
	for (auto n: node->childs()) {
		SINode e = eval(n, env + n->getEnv());
		e->setAddress (true);
		l.add (e);
	}
	if (l.size() > 1) return SINode( new ForestNode (l));
	return l[0];
}

//------------------------------------------------------------
SINode evaluator::evalExpand (const SINode& node, const TEnv& env)
{
	SINode out = expandEval::eval(node);
	return eval (out, env);
}

//------------------------------------------------------------
SINode evaluator::evalExpandVal (const SINode& node, const TEnv& env)
{
	SINode out = expandVal::eval(node, env);
	return eval (out, env);
}

//------------------------------------------------------------
SINode evaluator::evalVar (const SINode& node, const TEnv& env)
{
    SINode out = env.get (node->getValue());
    if (out) {
        if (node->address()) out->setAddress(true);
        out = eval(out, env + node->getEnv());
        if (node->size()) {
            SINode n = SINode (new ForestNode (node->childs()));
            return eval(parseEval::seq (out, n), env);
        }
        return out->clone();
    }
    return evalNode(node, env);
}

//------------------------------------------------------------
//
//------------------------------------------------------------
SINode evaluator::eval (const SINode& node, const TEnv& env)
{
	INode::TNodeType t = node->getType ();
	if ((t >= INode::kFirstMath) && (t <= INode::kLastMath))
		return evalMath (node, env);
	switch (t) {
		case INode::kSlash: 	return evalSlash (node, env);
		case INode::kVariable: 	return evalVar   (node, env);
		case INode::kExpand: 	return evalExpand(node, env);
		case INode::kExpandVal: return evalExpandVal(node, env);
		default:
			return evalNode (node, env);
	}
}

//------------------------------------------------------------
void evaluator::error  (const SINode& node, const std::string& what)
{
	stringstream msg;
	msg << "line " << node->getLine() << " column " << node->getColumn() << ": " << what;
	throw (evalException (msg.str().c_str()));

}

//------------------------------------------------------------
// bootstrap the evaluation with the current node environment
//------------------------------------------------------------
SINode evaluator::eval (const SINode& node) throw(evalException)
{
	try{
		return eval (node, node->getEnv());
	}
	catch (expandValException e) {
		throw (evalException (e.what()));
	}
}

} // end namespace

