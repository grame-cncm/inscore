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

#include "oscprinter.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
void oscprinter::print (ostream& os, const SINode& node, std::string prefix)
{
	print (os, node.get(), prefix);
}

//------------------------------------------------------------
void oscprinter::print (ostream& os, const INode* node, std::string prefix)
{
	switch ( node->getType() ) {
	 	case INode::kForest:
			print (os, node->childs(), prefix);
			break;
	 	case INode::kSlash:
			print (os, node->childs(), prefix);
			break;
	 	default:
			string p = prefix + "/" + node->getName();
			for (auto n: node->childs()) print (os, n, p );
			if (node->empty()) os << p << ";" << endl;
	}
}

//------------------------------------------------------------
void oscprinter::print (ostream& os, const NList& nodes, std::string prefix)
{
	for (auto n: nodes) {
		print (os, n, prefix);
	}
}

} // end namespace

