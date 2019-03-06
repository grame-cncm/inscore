


#include <algorithm>
#include <sstream>
#include <string>
#include <cmath>
#include <random>

#include "evaluator2.h"
#include "expandEval.h"
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
	int strcount=0, intcount=0, floatcount=0;
	for (auto n: args) {
		INode::TNodeType t = n->getType();
		if ((t >= INode::kFirstMath) && (t <=INode::kLastMath))
			return kDefer;		// assumes a subnode has already been deferred

		else switch (n->getType()) {
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
	if (floatcount) return kFloat;
	return kInt;
}

//------------------------------------------------------------
// addition
//------------------------------------------------------------
SINode evaluator::addStrings (const NList& args)
{
	stringstream sum;
	for (auto n: args) sum << n->getName();
	SINode out = INode::create (sum.str());
	out->setAddress( args.size() ? args[0]->address() : false );
	return out;
}

//------------------------------------------------------------
SINode evaluator::addInt (const NList& args)
{
	int sum = 0;
	for (auto n: args) sum += std::stoi(n->getName());
	return INode::create (sum);
}

//------------------------------------------------------------
SINode evaluator::addFloat (const NList& args)
{
	float sum = 0;
	for (auto n: args) sum += std::stof(n->getName());
	return INode::create (sum);
}

//------------------------------------------------------------
SINode evaluator::evalAdd 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error( node, "operator '+' requires at least 2 arguments");
	switch (type) {
		case kString:	return addStrings (args);
		case kFloat:	return addFloat (args);
		default:		return addInt (args);
	}
}

//------------------------------------------------------------
// substraction
//------------------------------------------------------------
SINode evaluator::subInt (const NList& args)
{
	int result = std::stoi(args[0]->getName());
	for (size_t i = 1; i < args.size(); i++) result -= std::stoi(args[i]->getName());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::subFloat (const NList& args)
{
	float result = std::stof(args[0]->getName());
	for (size_t i = 1; i < args.size(); i++) result -= std::stof(args[i]->getName());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::evalSub 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator '-' requires at least 2 arguments");
	switch (type) {
		case kString:	throw (evalException ("invalid string argument passed to operator '-'"));
		case kFloat:	return subFloat (args);
		default:		return subInt (args);
	}
}

//------------------------------------------------------------
// divison
//------------------------------------------------------------
SINode evaluator::divInt (const NList& args)
{
	int result = std::stoi(args[0]->getName());
	for (size_t i = 1; i < args.size(); i++) result /= std::stoi(args[i]->getName());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::divFloat (const NList& args)
{
	float result = std::stof(args[0]->getName());
	for (size_t i = 1; i < args.size(); i++) {
		float v = std::stof(args[i]->getName());
		if (v) result /= v;
		else  error (args[i], "divide by zero");
	}
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::evalDiv 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator '/' requires at least 2 arguments");
	switch (type) {
		case kString:	throw (evalException ("invalid string argument passed to operator '/'"));
		case kFloat:	return divFloat (args);
		default:		return divInt (args);
	}
}

//------------------------------------------------------------
// multiplication
//------------------------------------------------------------
SINode evaluator::multInt (const NList& args)
{
	int result = std::stoi(args[0]->getName());
	for (size_t i = 1; i < args.size(); i++) result *= std::stoi(args[i]->getName());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::multFloat (const NList& args)
{
	float result = std::stof(args[0]->getName());
	for (size_t i = 1; i < args.size(); i++) result *= std::stof(args[i]->getName());
	return INode::create (result);
}

//------------------------------------------------------------
SINode evaluator::evalMult 	(const SINode& node, const NList& args, TType type)
{
	if (args.size() < 2) error (node, "operator '*' requires at least 2 arguments");
	switch (type) {
		case kString:	error (getTypedNode(args, INode::kText), "invalid string argument passed to operator '*'");
		case kFloat:	return multFloat (args);
		default:		return multInt (args);
	}
}

//------------------------------------------------------------
// modulo
//------------------------------------------------------------
SINode evaluator::moduloInt (const NList& args)
{
	int result = std::stoi(args[0]->getName());
	for (size_t i = 1; i < args.size(); i++) result %= std::stoi(args[i]->getName());
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
	string testStr = n->getName();
	switch (n->getType()) {
		case INode::kText:
			return (testStr == "true") || (testStr=="yes") || (testStr == "on");
		case INode::kFloat:
			return  std::stof(testStr) != 0.f;
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
	string result = f(arg1->getName(), arg2->getName()) ? "true" : "false";
	return SINode (new INode (result));

}

SINode evaluator::compare (const SINode& arg1, const SINode& arg2, TCompNumFunction f)
{
	float v1 = std::stof(arg1->getName());
	float v2 = std::stof(arg2->getName());
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
	size_t min = node->getName().size();
	for (size_t i=1; i < args.size(); i++) {
		size_t n = args[i]->getName().size();
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
	double min = std::stof(node->getName());;
	for (size_t i=1; i < args.size(); i++) {
		float n = std::stof(args[i]->getName());
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
	size_t max = node->getName().size();
	for (size_t i=1; i < args.size(); i++) {
		size_t n = args[i]->getName().size();
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
	float max = std::stof(node->getName());;
	for (size_t i=0; i < args.size(); i++) {
		float n = std::stof(args[i]->getName());
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
float evaluator::getFArgValue (const SINode& node, const NList& args)
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
			return std::stof(arg->getName());
		default:
			what << "unexpected type of argument (type " << arg->getType() << ": " << arg->getTypeStr() << ")";
			error (arg, what.str());
	}
	return 0.f;		// just to avoid the "end of non-void" warning
}

//------------------------------------------------------------
SINode evaluator::evalSin (float value) 	{ return INode::create ( sin(value)); }
SINode evaluator::evalCos (float value) 	{ return INode::create ( cos(value)); }
SINode evaluator::evalTan (float value) 	{ return INode::create ( tan(value)); }
SINode evaluator::evalASin (float value) 	{ return INode::create ( asin(value)); }
SINode evaluator::evalACos (float value) 	{ return INode::create ( acos(value)); }
SINode evaluator::evalATan (float value) 	{ return INode::create ( atan(value)); }
SINode evaluator::evalSinh (float value) 	{ return INode::create ( sinh(value)); }
SINode evaluator::evalCosh (float value) 	{ return INode::create ( cosh(value)); }
SINode evaluator::evalTanh (float value) 	{ return INode::create ( tanh(value)); }
SINode evaluator::evalASinh (float value) 	{ return INode::create ( asinh(value)); }
SINode evaluator::evalACosh (float value) 	{ return INode::create ( acosh(value)); }
SINode evaluator::evalATanh (float value) 	{ return INode::create ( atanh(value)); }

SINode evaluator::evalExp (float value) 	{ return INode::create ( exp(value)); }
SINode evaluator::evalLog (float value) 	{ return INode::create ( log(value)); }
SINode evaluator::evalLog10 (float value) 	{ return INode::create ( log10(value)); }
SINode evaluator::evalLog2 (float value) 	{ return INode::create ( log2(value)); }
SINode evaluator::evalSqrt (float value) 	{ return INode::create ( sqrt(value)); }
SINode evaluator::evalCbrt (float value) 	{ return INode::create ( cbrt(value)); }
SINode evaluator::evalCeil (float value) 	{ return INode::create ( ceil(value)); }
SINode evaluator::evalFloor (float value) 	{ return INode::create ( floor(value)); }
SINode evaluator::evalRound (float value) 	{ return INode::create ( round(value)); }

SINode evaluator::evalPow (const SINode& node, const NList& args, TType type)
{
	if ((args.size() != 2) || (type == kString)) error (node, "operator 'pow' requires 2 numeric arguments");
	float v1 = 	std::stof(args[0]->getName());
	float v2 = 	std::stof(args[1]->getName());
	return INode::create (pow(v1, v2));
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

		case INode::kSin:		out = evalSin	(getFArgValue(node, l)); break;
		case INode::kCos:		out = evalCos	(getFArgValue(node, l)); break;
		case INode::kTan:		out = evalTan	(getFArgValue(node, l)); break;
		case INode::kASin:		out = evalASin	(getFArgValue(node, l)); break;
		case INode::kACos:		out = evalACos	(getFArgValue(node, l)); break;
		case INode::kATan:		out = evalATan	(getFArgValue(node, l)); break;
		case INode::kSinh:		out = evalSinh	(getFArgValue(node, l)); break;
		case INode::kCosh:		out = evalCosh	(getFArgValue(node, l)); break;
		case INode::kTanh:		out = evalTanh	(getFArgValue(node, l)); break;
		case INode::kASinh:		out = evalASinh	(getFArgValue(node, l)); break;
		case INode::kACosh:		out = evalACosh	(getFArgValue(node, l)); break;
		case INode::kATanh:		out = evalATanh	(getFArgValue(node, l)); break;

		case INode::kExp: 		out = evalExp	(getFArgValue(node, l)); break;
		case INode::kLog: 		out = evalLog	(getFArgValue(node, l)); break;
		case INode::kLog10: 	out = evalLog10 (getFArgValue(node, l)); break;
		case INode::kLog2: 		out = evalLog2	(getFArgValue(node, l)); break;
		case INode::kSqrt: 		out = evalSqrt	(getFArgValue(node, l)); break;
		case INode::kCbrt: 		out = evalCbrt	(getFArgValue(node, l)); break;
		case INode::kCeil: 		out = evalCeil	(getFArgValue(node, l)); break;
		case INode::kFloor: 	out = evalFloor	(getFArgValue(node, l)); break;
		case INode::kRound: 	out = evalRound	(getFArgValue(node, l)); break;

		case INode::kPow: 		out = evalPow(node, l, exprType); break;
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
SINode evaluator::evalJS (const SINode& node, const TEnv& env)
{
cerr << "evaluator::evalJS " << node->getName() << endl;
	return evalNode (node, env);
}

//------------------------------------------------------------
SINode evaluator::evalExpand (const SINode& node, const TEnv& env)
{
	SINode out = expandEval::eval(node);
	return eval (out, env);
}

//------------------------------------------------------------
SINode evaluator::evalVar (const SINode& node, const TEnv& env)
{
	SINode out = env.get (node->getName());
	if (out) {
		if (node->address()) out->setAddress(true);
		out = eval(out, env);
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
		case INode::kJScript: 	return evalJS(node, env);
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
	return eval (node, node->getEnv());
}

} // end namespace

