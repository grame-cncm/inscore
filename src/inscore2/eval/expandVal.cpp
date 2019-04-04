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

#include "evaluator2.h"
#include "expandVal.h"

using namespace std;

namespace inscore2
{

const char* expandVal::kDurName   = "dur";
const char* expandVal::kStepName  = "step";
const char* expandVal::kStyleName = "style";

const float expandVal::kDefaultDur		= 1000.f;
const float expandVal::kDefaultStep		= 0.1f;
const char* expandVal::kDefaultStyle	= "linear";

//------------------------------------------------------------
SINode expandVal::duration (const TEnv& env)
{
	SINode dur = env.get(kDurName);
	return dur ? evaluator::eval(dur) : SINode (new DelayNode (kDefaultDur));
}

//------------------------------------------------------------
float expandVal::step (const TEnv& env, float v1, float v2)
{
	SINode node = env.get(kStepName);
	if (node) {
		float val = evaluator::eval(node)->getFloat();
		if (((v1 > v2) && (val > 0)) || ((v1 < v2) && (val < 0)) || (val==0.f)) {
			string what="inconsistent step: ";
			error (node, what + to_string(val));
		}
		return val;
	}
	return (v1 <= v2) ?  kDefaultStep : - kDefaultStep;
}

//------------------------------------------------------------
string expandVal::style (const TEnv& env)
{
	SINode style = env.get(kStyleName);
	return style ? style->getValue() : kDefaultStyle;
}

//------------------------------------------------------------
void expandVal::error  (const SINode& node, const std::string& what)
{
	stringstream msg;
	msg << "line " << node->getLine() << " column " << node->getColumn() << ": " << what;
	throw (expandValException (msg.str().c_str()));
}

//------------------------------------------------------------
SINode expandVal::expand (float from, float to, float step, const SINode& dur, const std::string& style )
{
	float count = (to - from) / step;
	float delay = dur->getDelay();
	float timestep = delay / count;
	float currentDelay = 0;
	float currentVal = from;
	NList l;
	while (currentDelay < delay) {
		SINode v = INode::create (currentVal);
		v->setDelay (currentDelay);
		l.add (v);
		currentVal += step;
		currentDelay += timestep;
	}
	SINode v = INode::create (to);
	v->setDelay (delay);
	l.add (v);
	return SINode(new ForestNode (l));
}

//------------------------------------------------------------
// evaluation of the expand value form [n...m]
//------------------------------------------------------------
SINode expandVal::eval (const SINode& node, const TEnv& env) throw(expandValException)
{
	if (node->getType() != INode::kExpandVal) {
		string what="unexpected node type ";
		error (node, what + node->getTypeStr());
	}

	if (node->size() != 2) {
		string what="unexpected childs count: ";
		error (node, what + to_string(node->size()));
	}

	float v1 = node->childs()[0]->getFloat();
	float v2 = node->childs()[1]->getFloat();
	float vstep = step (env, v1, v2);

	return expand(v1, v2, vstep, duration(env), style(env));
}

} // end namespace

