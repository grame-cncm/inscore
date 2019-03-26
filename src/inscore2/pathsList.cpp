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
static float sumDelays (SINode node, bool parentAddress)
{
	// stop at next root address
	if (!parentAddress && node->address()) return 0;
	
	float delay = node->getDelay();
	node->setDelay(0);
	for (auto n: node->childs()) {
		delay += sumDelays(n, node->address());
	}
	return delay;
}

//------------------------------------------------------------
static SINode clean (SINode node, SINode parent)
{
	if (node->isDelay() && node->empty()) return 0;

	NList l;
	for (auto n: node->childs()) {			// propagate the computation to children since a message can contain messages
		SINode sub = clean (n, node);
		if (sub) l.add (sub);
	}
	return node->clone(l);
}

//------------------------------------------------------------
// computes the total delay along a path and report
// this delay to the root node
// the total delay computation stop at the next message along the path
//------------------------------------------------------------
SINode pathsList::delayed (SINode& node)
{
	if (node->address()) {					// only report the sum to the first address node
		float delay = node->getDelay();
		float sum = 0;
		for (auto n: node->childs())
			sum += sumDelays(n, true);		// computes the delays of the childrens up to the next root address
		node->setDelay (sum + delay);		// and set the node total delay
	}

	for (auto n: node->childs())			// propagate the computation to children since a message can contain messages
		delayed(n);

	NList l;
	for (auto n: node->childs()) {			// propagate the computation to children since a message can contain messages
		SINode sub = clean (n, node);
		if (sub) l.add (sub);
	}
	return node->clone(l);
//	return node;
}

//------------------------------------------------------------
// transform a tree into a list of paths
// and computes the total delay of each path
//------------------------------------------------------------
SINode pathsList::eval (const SINode& node, bool sumdelays)
{
	SINode paths = _eval (node);
	if (!sumdelays) return paths;

	if (paths->isForest()) {
		NList l;
		for (auto n: paths->childs())
			l.add (delayed(n));
		return SINode(new ForestNode (l));
	}
	else return delayed (paths);
}

//------------------------------------------------------------
// transform a tree into a list of paths
//------------------------------------------------------------
SINode pathsList::_eval (const SINode& node)
{
	// node has no subnodes: just clone the node
	if (node->empty()) return node->clone();

	//------------------------------------------------------------
	// node is an address
	if (node->address()) {
		NList l;
		for (auto n: node->childs()) {	// for each subnode
			SINode sub = _eval (n);		// eval the subnode
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
			SINode sub = _eval (n);		// eval the subnode
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
		SINode sub = _eval (n);				// eval the subnode
		// when the evaluated node is a forest, add the subnodes to the list
		if (sub->isForest()) l.add (sub->childs());
		// otherwise add the node to the list
		else l.add (sub);
	}
	return node->isForest() ? SINode(new ForestNode (l)) : node->clone(l);
}

} // end namespace

