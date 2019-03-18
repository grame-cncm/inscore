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

#include <cctype>
#include <cstdlib>
#include <iostream>
#include <sstream>
#include <string>
#include <regex>

#include "INode.h"
#include "TreeTools.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
void NList::add (const SINode& n)
{
	push_back (n);
}
//------------------------------------------------------------
void NList::add (const NList& l)
{
	for (auto n: l) push_back(n);
}

//------------------------------------------------------------
const SINode NList::find (const SINode& node) const
{
	for (auto n: *this) {
		if (*n == node) return n;
	}
	return 0;
}


//------------------------------------------------------------
const NList NList::but (const SINode& node) const
{
	NList out;
	for (auto n: *this)
		if (*n != node) out.push_back (n);
	return out;
}

//------------------------------------------------------------
INode* INode::createSeq (SINode n1, SINode n2)	{ return new SeqNode(n1, n2); }
INode* INode::createPar (SINode n1, SINode n2)	{ return new ParNode(n1, n2); }

//------------------------------------------------------------
INode::INode(const INode* node)
	: fValue(node->getValue()), fType(node->getType()), fAddressPart(node->address()), fDelay(node->getDelay()), fLine(node->getLine()), fColumn(node->getColumn())
{
	setEnv (node->getEnv());
	for (auto n: node->childs()) fSubNodes.push_back(n->clone());
}

//------------------------------------------------------------
SINode INode::clone (const NList& sub) const
{
	SINode out = SINode(new INode(getValue(), sub, getType()));
	out->setInfos( this );
	return out;
}

//------------------------------------------------------------
SINode INode::clone () const
{
	NList l;
	for (auto n: childs()) l.push_back (n->clone());
	SINode out = SINode(new INode (fValue, l, fType));
	out->setInfos( this );
	return out;
}

//------------------------------------------------------------
void INode::setInfos (const INode* n)
{
	setAddress( n->address() );
	setEnv 	  ( n->getEnv());
	setDelay  ( n->getDelay() );
	setLC 	  ( n->getLine(), n->getColumn());
}

//------------------------------------------------------------
SINode  INode::merge (const SINode& node) const
{
	NList l;
	for (auto n: childs()) {
		SINode e = node->find(n);
		if (e) l.push_back ( n->merge (e));
		else l.push_back (n->clone());
	}
	for (auto n: node->childs()) {
		SINode e = find(n);
		if (!e) l.push_back (n->clone());
	}
	return clone (l);
}

//------------------------------------------------------------
void INode::addEnv (const SINode& node)
{
	fEnv += node->getEnv();
}

//------------------------------------------------------------
void INode::setEnv (const TEnv& env) 					{ fEnv = env; }
void INode::setEnv (const std::string& name, int val)	{ fEnv.put (name, create(to_string(val), kInt)); }

//------------------------------------------------------------
bool INode::petiole () const
{
	if (empty()) return false;
	for (auto n: childs())
		if (!n->empty()) return false;
	return true;
}

//------------------------------------------------------------
const char * INode::type2string (TNodeType t)
{
	switch (t) {
		case kACos: 	return "ACos";
		case kACosh: 	return "ACosh";
		case kAdd: 		return "Add";
		case kASin: 	return "ASin";
		case kASinh: 	return "ASinh";
		case kATan: 	return "ATan";
		case kATanh: 	return "ATanh";
		case kCbrt: 	return "Cbrt";
		case kCeil: 	return "Ceil";
		case kCos: 		return "Cos";
		case kCosh: 	return "Cosh";
        case kDelay:    return "Delay";
        case kDiv:      return "Div";
		case kEq: 		return "Eq";
		case kExp: 		return "Exp";
		case kExpand: 	return "Expand";
		case kFloat: 	return "Float";
		case kFloor: 	return "Floor";
		case kForest: 	return "Forest";
		case kGreater: 	return "Greater";
		case kGreatereq: return "Greatereq";
		case kHas: 		return "Has";
		case kInt: 		return "Int";
		case kJScript: 	return "JS";
		case kLess: 	return "Less";
		case kLesseq: 	return "Lesseq";
		case kLog: 		return "Log";
		case kLog2: 	return "Log2";
		case kLog10: 	return "Log10";
		case kMax: 		return "Max";
		case kMin: 		return "Min";
		case kModulo: 	return "Modulo";
		case kMult: 	return "Mult";
		case kNeg: 		return "Neg";
		case kPar: 		return "Par";
		case kPow: 		return "Pow";
		case kQuest: 	return "Quest";
		case kRand: 	return "Rand";
		case kRegexp: 	return "Regexp";
		case kRound: 	return "Round";
		case kSeq: 		return "Seq";
		case kSin: 		return "Sin";
		case kSinh: 	return "Sinh";
		case kSlash: 	return "Slash";
		case kSqrt: 	return "Sqrt";
		case kSub: 		return "Sub";
		case kTan: 		return "Tan";
		case kTanh: 	return "Tanh";
		case kText: 	return "Text";
		case kURLPrefix: return "Prefix";
		case kVariable: return "Variable";
	}
	return "unknown";
}

//------------------------------------------------------------
DelayNode::DelayNode(std::string val) : INode(val, kDelay)
{
	int multiplier = 1000;
	val.pop_back();		// assumes last char is 's'
	if (val.back() == 'm') {
		multiplier = 1;
		val.pop_back();
	}
	float delay = std::stof (val) * multiplier;
	setDelay ( int(delay) );
}

} // end namespace
