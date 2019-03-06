

#include <sstream>

#include "addressEval.h"
#include "expandEval.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
// remove / nodes and set address flag
//------------------------------------------------------------
SINode addressEval::eval (const SINode& node) throw(addressEvalException)
{
	try {
	if (node->getType() == INode::kSlash) {
		SINode f = evalSlash (node);
		if (f->size() > 1) return f;
		return f->childs()[0];
	}
	return evalNode (node);
	}
	catch (addressEvalException e) {
		stringstream what;
		what << "line " << node->getLine() << " column " << node->getColumn() << ": " << e.what();
		throw (addressEvalException (what.str().c_str()));
	}
}

//------------------------------------------------------------
SINode addressEval::evalSlash (const SINode& node)
{
	NList l;
	for (auto n: node->childs()) {
		SINode e = eval(n);
		e->setAddress (true);
		l.add (e);
	}
	if (l.empty()) throw (addressEvalException ("unexpected empty / node."));
	return SINode( new INode ("", l, INode::kForest ));
}

//------------------------------------------------------------
SINode addressEval::evalNode (const SINode& node)
{
	NList l;
	for (auto n: node->childs()) {
		SINode e = eval(n);
		if (e->getType() == INode::kForest)
			l.add (e->childs());
		else
			l.add (e);
	}
	return node->clone(l);
}

} // end namespace
