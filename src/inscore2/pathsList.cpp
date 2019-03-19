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
#if 0
//------------------------------------------------------------
// add path to a list
// args:
//		path:
//		node:
//		list: the destination list
//------------------------------------------------------------
static void addPath (const SINode& path, const SINode& node, NList& list)
{
	INode::TNodeType type = path->getType();
	if (type == INode::kForest)
		list.add( node );
	else {
		SINode n = SINode (new INode (path->getValue(), node, type));
		n->setInfos (path);
		list.add( n );
	}
}

//------------------------------------------------------------
// transform a tree into a list of paths
//
//------------------------------------------------------------
SINode pathsList::eval (const SINode& node)
{
	// node has no subnodes: just clone the node
	if (node->empty()) return node->clone();

	// node has subnodes
	//------------------------------------------------------------
	// node is not a forest and not an address
	if (!node->address() && !node->isForest()) {
		NList nl;
		for (auto n: node->childs()) {			// for each subnode
			SINode e = eval (n);				// eval the subnode
			// when the evaluated node is a forest, add the subnodes to the list
			if (e->isForest()) nl.add (e->childs());
			// otherwise add the node to the list
			else nl.add (e);
		}
		return node->clone(nl);		// and return a clone of the current node with the evaluated subnodes
	}

	//------------------------------------------------------------
	// node is a forest or an address
	NList l;
	for (auto n: node->childs()) {	// for each subnode
		SINode sub = eval (n);		// eval the subnode
		if (sub->isForest()) {
			// when the evaluated node is a forest, add the subnodes to the paths list
			for (auto s: sub->childs())
				addPath (node, s, l);
		}
		// otherwise add the node to the list
		else addPath (node, sub, l);
	}
	return SINode(new ForestNode (l));
}
#else

//------------------------------------------------------------
// transform a tree into a list of paths
//------------------------------------------------------------
SINode pathsList::eval (const SINode& node)
{
	// node has no subnodes: just clone the node
	if (node->empty()) return node->clone();

	//------------------------------------------------------------
	// node is an address
	if (node->address()) {
		NList l;
		for (auto n: node->childs()) {	// for each subnode
			SINode sub = eval (n);		// eval the subnode
			if (sub->isForest()) {
				// when the evaluated node is a forest, add the subnodes to the paths list
				for (auto s: sub->childs()) l.add (node->clone(s));
			}
			// otherwise add the node to the list
			else l.add (node->clone(sub));
		}
		return SINode(new ForestNode (l));
	}

	//------------------------------------------------------------
	// node is a delay
	if (node->isDelay()) {
		float delay = node->getDelay();
		NList l;
		for (auto n: node->childs()) {	// for each subnode
			SINode sub = eval (n);		// eval the subnode
			sub->setDelay (delay);
			if (sub->isForest()) {
				sub->propagateDelay();
				l.add (sub->childs());
			}
			else l.add (sub);
		}
		return SINode(new ForestNode (l));
	}

	//------------------------------------------------------------
	// node is not an address and not a delay
	NList l;
	for (auto n: node->childs()) {			// for each subnode
		SINode sub = eval (n);				// eval the subnode
		// when the evaluated node is a forest, add the subnodes to the list
		if (sub->isForest()) l.add (sub->childs());
		// otherwise add the node to the list
		else l.add (sub);
	}
	return node->isForest() ? SINode(new ForestNode (l)) : node->clone(l);
}

#endif

} // end namespace

