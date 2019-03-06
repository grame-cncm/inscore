

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
		SINode n = SINode (new INode (path->getName(), node, type));
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

