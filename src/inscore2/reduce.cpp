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

