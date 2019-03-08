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


#include <iostream>

#include "pathsList.h"

using namespace std;


namespace inscore2
{

//------------------------------------------------------------
static void addPath (const SINode& path, const SINode& node, NList& list)
{
	INode::TNodeType type 	= path->getType();
	if (type == INode::kForest)
		list.add( node );
	else {
		SINode n = SINode (new INode (path->getValue(), node, type));
		n->setAddress(path->address());
		list.add( n );
	}
}

//------------------------------------------------------------
// transform a tree into a list of paths
//------------------------------------------------------------
SINode pathsList::eval (const SINode& node)
{
	if (node->empty())
		return node->clone();

	if (!node->address() && (node->getType() != INode::kForest)) {
		NList nl;
		for (auto n: node->childs()) {
			SINode e = eval (n);
			if (e->getType() == INode::kForest) nl.add (e->childs());
			else nl.add (e);
		}
		return node->clone(nl);
	}

	NList l;
	for (auto n: node->childs()) {
		SINode sub = eval (n);
		if (sub->getType() == INode::kForest) {
			for (auto s: sub->childs())
				addPath (node, s, l);
		}
		else addPath (node, sub, l);
	}
	return SINode(new ForestNode (l));
}

} // end namespace

