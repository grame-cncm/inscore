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

#include "dotprinter.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
void dotprinter::print (ostream& os, const INode* node)
{
	fStream = &os;
	start (os);
	printNames (node);
	os << endl;
	printLinks (node);
	end(os);
}

//------------------------------------------------------------
void dotprinter::print (ostream& os, const NList& nodes)
{
	fStream = &os;
	start (os);
	for (auto n: nodes) printNames (n.get());
	os << endl;
	for (auto n: nodes) printLinks (n.get());
	end(os);
}

//------------------------------------------------------------
void dotprinter::printNames (const INode* node)
{
	if (!fPrintEnv)
		*fStream << id (node) << "\t[label=\"" << label (node) << "\"];" << endl;
	else {
		if (node->getEnv().empty())
			*fStream << id (node) << "\t[label=\"" << label (node) << "\"];" << endl;
		else {
			stringstream s;
			s << "|" << node->getEnv();
			*fStream << id (node) << "\t[shape=record fontsize=12 label=\"" << label (node) << s.str() << "\"];" << endl;
		}
	}
	for (auto n: node->childs()) printNames(n.get());
}

//------------------------------------------------------------
void dotprinter::printLinks (const INode* node)
{
	if (node->size()) {
		string s = id (node);
		const NList sub = node->childs();
		for (auto n: sub) { *fStream << s << " -> " << id(n.get()) << endl; }
		for (auto n: sub) { printLinks(n.get()); }
	}
}

//------------------------------------------------------------
string dotprinter::id (const INode * node) const
{
	stringstream s;
	s << "n" << (void*)node;
	return s.str();
}

//------------------------------------------------------------
string dotprinter::label (const INode * node) const
{
	string str;
	if (node->address()) str = "/";
	str += node->getName();
	switch(node->getType()) {
		case INode::kText:
		case INode::kInt:
		case INode::kFloat:
			break;
		case INode::kSlash:		str += ":/"; break;

		case INode::kSeq:		str += ":seq"; break;
		case INode::kPar:		str += ":par"; break;
		case INode::kExpand:	str += ":expand"; break;
		case INode::kForest:	str += ":forest"; break;
		case INode::kRegexp:	str += ":RE"; break;
//		case INode::kValue:		str += ":value"; break;
		case INode::kVariable:	str += ":var"; break;
		case INode::kJScript:	str += ":js"; break;

		case INode::kAdd:		str += ":+"; break;
		case INode::kSub:		str += ":-"; break;
		case INode::kDiv:		str += ":/"; break;
		case INode::kMult:		str += ":*"; break;
		case INode::kModulo:	str += ":%"; break;
		case INode::kQuest:		str += ":?"; break;
		case INode::kNeg:		str += ":!"; break;
		case INode::kEq:		str += ":=="; break;
		case INode::kGreater:	str += ":>"; break;
		case INode::kGreatereq:	str += ":>="; break;
		case INode::kLess:		str += ":<"; break;
		case INode::kLesseq:	str += ":<="; break;
		case INode::kMin:		str += ":min"; break;
		case INode::kMax:		str += ":max"; break;
		case INode::kHas:		str += ":has"; break;

		case INode::kSin:		str += ":sin"; break;
		case INode::kCos:		str += ":cos"; break;
		case INode::kTan:		str += ":tan"; break;
		case INode::kASin:		str += ":asin"; break;
		case INode::kACos:		str += ":acos"; break;
		case INode::kATan:		str += ":atan"; break;
		case INode::kSinh:		str += ":sinh"; break;
		case INode::kCosh:		str += ":cosh"; break;
		case INode::kTanh:		str += ":tanh"; break;
		case INode::kASinh:		str += ":asinh"; break;
		case INode::kACosh:		str += ":acosh"; break;
		case INode::kATanh:		str += ":atanh"; break;

		case INode::kExp: 		str += ":exp"; break;
		case INode::kLog: 		str += ":log"; break;
		case INode::kLog10: 	str += ":log10"; break;
		case INode::kLog2: 		str += ":log2"; break;
		case INode::kSqrt: 		str += ":sqrt"; break;
		case INode::kCbrt: 		str += ":cbrt"; break;
		case INode::kCeil: 		str += ":ceil"; break;
		case INode::kFloor: 	str += ":floor"; break;
		case INode::kRound: 	str += ":round"; break;

		case INode::kPow: 		str += ":pow"; break;
		case INode::kRand: 		str += ":rand"; break;
	}

	return str;
}

} // end namespace
