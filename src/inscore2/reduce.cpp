

#include "reduce.h"
#include "pathsList.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
SINode reduce::applySubs (const SINode& n1, const SINode& n2)
{
	NList l;
	const SINode f = n1->find (n2);
	if (f) {
		l = n1->childs().but(f);
		if (f->empty())
			l.add (n2->clone());
		else if (n2->empty())
			l.add (f->clone());
		else
			l.add (applySubs (f, n2->childs()[0]));
	}
	else {
		if (!n1->petiole())
			l = n1->childs();
		l.add (n2->clone());
	}
	return n1->clone( l );
}

//------------------------------------------------------------
SINode reduce::apply (const SINode& n1, const SINode& n2)
{
	if (!n1) return n2->clone();
	if (*n1 == n2) return applySubs (n1, n2->childs()[0]);
	else return SINode (new INode (n1, n2, INode::kForest));
}


//------------------------------------------------------------
SINode reduce::apply (const SINode& node)
{
	SINode out = 0;
	SINode plist = pathsList::eval(node);
	for (auto n:plist->childs())
		out = apply (out, n);
	return out;
}

} // end namespace

