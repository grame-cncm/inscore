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
