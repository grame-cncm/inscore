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

