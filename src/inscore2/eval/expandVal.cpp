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

#include "expandVal.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
// evaluation of the expand value form [n...m]
//------------------------------------------------------------
SINode expandVal::eval (const SINode& node, const TEnv& env) throw(expandValException)
{
	if (node->getType() != INode::kExpand) {
		stringstream what;
		what << "line " << node->getLine() << " column " << node->getColumn() << ": unexpected node type " << node->getTypeStr();
		throw (expandValException (what.str().c_str()));
	}

	if (node->size() != 2) {
		stringstream what;
		what << "line " << node->getLine() << " column " << node->getColumn() << ": unexpected childs count = " << node->size();
		throw (expandValException (what.str().c_str()));
	}

	float v1 = node->childs()[0]->getFloat();
	float v2 = node->childs()[1]->getFloat();
	return node->clone();
}

} // end namespace

