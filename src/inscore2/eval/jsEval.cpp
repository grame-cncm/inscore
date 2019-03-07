

#include <sstream>

#include "jsEval.h"
#include "IParser2.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
// evaluation of the javascript sections
//------------------------------------------------------------
SINode jsEval::eval (const SINode& node) throw(jsEvalException)
{
	try {
	switch(node->getType()) {
		case INode::kForest:	return evalForest(node);
		case INode::kJScript:	return evalJavascript(node);
		default:				return evalNode(node);
	}
	}
	catch (jsEvalException e) {
		stringstream what;
		what << "line " << node->getLine() << " column " << node->getColumn() << ": " << e.what();
		throw (jsEvalException (what.str().c_str()));
	}
}

//------------------------------------------------------------
SINode jsEval::evalJavascript (const SINode& node)
{
	string jsOut;
	bool done = fJavascript->eval(node->getLine(), node->getName().c_str(), jsOut);
	if (done) {
		if (jsOut.size()) {
			stringstream stream (jsOut);
			IParser p (&stream);
			if (p.parse()) return p.tree();
		}
	}
	return 0;
}


//------------------------------------------------------------
SINode jsEval::evalNode (const SINode& node)
{
	return node->clone();
}

//------------------------------------------------------------
SINode jsEval::evalForest (const SINode& node)
{
	NList l;
	for (auto n: node->childs()) {
		SINode e = eval(n);
		if (e) l.add (e);
	}
	return node->clone (l);
}

} // end namespace

