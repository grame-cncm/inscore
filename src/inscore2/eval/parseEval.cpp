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
	if (node->address()) out->setAddress (true);
	out->setEnv (node->getEnv());
	return out;
}

//------------------------------------------------------------
SINode parseEval::evalPar (const SINode& node)
{
	NList l;
	for (auto n: node->childs()) {
		SINode en = eval(n);
		if (node->address()) en->setAddress (true);
		l.add (en);
	}
	SINode out = SINode(new ForestNode(l));
	out->setEnv (node->getEnv());
	return out;
}


} // end namespace

