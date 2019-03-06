

#include <sstream>

#include "parseEval.h"
#include "expandEval.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
// evaluation of the parser output
// handles seq and par operations
//------------------------------------------------------------
SINode parseEval::eval (const SINode& node) throw(parseEvalException)
{
	try {
	switch(node->getType()) {
		case INode::kForest:	return evalForest(node);
		case INode::kSlash:		return evalSlash(node);
		case INode::kSeq:		return evalSeq(node);
		case INode::kPar:		return evalPar(node);
		default:				return evalNode(node);
	}
	}
	catch (parseEvalException e) {
		stringstream what;
		what << "line " << node->getLine() << " column " << node->getColumn() << ": " << e.what();
		throw (parseEvalException (what.str().c_str()));
	}
}

//------------------------------------------------------------
SINode parseEval::evalExpand (const SINode& node)
{
	return expandEval::eval(node);
}

//------------------------------------------------------------
SINode parseEval::evalSlash (const SINode& node)
{
	if (node->size() != 1) {
		stringstream what;
		what << "slash evaluation: 1 node expected, got " << node->size();
		throw (parseEvalException (what.str().c_str()));
	}
	SINode n = eval (node->childs()[0]);
	if (n->isForest())
		return node->clone (n->childs());

	NList l;
	l.add (n);
	return node->clone (l);
}

//------------------------------------------------------------
SINode parseEval::evalNode (const SINode& node)
{
	return node->clone();
}

//------------------------------------------------------------
SINode parseEval::evalForest (const SINode& node)
{
	NList l;
	for (auto n: node->childs())
		l.add (eval(n));
	return node->clone (l);
}

//--------------------------------------------------
SINode parseEval::seq(const SINode& n1, const SINode& n2)
{
	NList l;
	if (n1->size())	{				// node is not a leaf
		for (auto n: n1->childs())	// propagate the seq operation
			l.add (seq (n, n2));	// to descendants
	}
	else {							// node is a leaf
		SINode sub = n2->clone();
		if (n2->isForest())			// in case of forest
			l.add(sub->childs());	// add the forest trees
		else l.add (sub);			// else add the node
	}
	return n1->clone(l);
}

//------------------------------------------------------------
SINode parseEval::evalSeq (const SINode& node)
{
	if (node->size() != 2) {
		stringstream what;
		what << "seq evaluation: 2 nodes expected, got " << node->size();
		throw (parseEvalException (what.str().c_str()));
	}
	const NList& sub = node->childs();
	SINode out = seq (eval(sub[0]), eval(sub[1]));
	out->setEnv (node->getEnv());
	return out;
}

//------------------------------------------------------------
SINode parseEval::evalPar (const SINode& node)
{
	NList l;
	for (auto n: node->childs()) {
		SINode e = eval(n);
		if (e->isForest()) l.add (e->childs());
		else l.add (e);
	}
	SINode out = SINode(new ForestNode(l));
	out->setEnv (node->getEnv());
	return out;
}


} // end namespace

