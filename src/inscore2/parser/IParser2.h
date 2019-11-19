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
#include <locale.h>
#include <string>
#include <map>
#include <stack>


#include "INode.h"
#include "TEnv2.h"

namespace inscore2
{

typedef INode*	TINode;

class IParser {

	void initScanner();			// implemented in .l file
	void destroyScanner();		// implemented in .l file
	NList	fNodes;

	TINode 	set (TINode n) const 	{ n->setLC(fLine, fColumn); n->setEnv(fVars); return n; }

	public:
				 IParser(std::istream* stream) : fStream(stream), fLine(1), fColumn(1) {
					setlocale(LC_NUMERIC, "C");
					initScanner();
				 }
		virtual ~IParser() {
					setlocale(LC_NUMERIC, 0);
					destroyScanner();
				 }

		bool 	parse();			// implemented in .y file
		void 	error (int line, int col, const char* msg) const;	

		SINode 	tree() 							{ return SINode(new ForestNode(fNodes));}
		TINode 	create(std::string name, INode::TNodeType t = INode::kText) const	{ return set (new INode(name, t)); }

		void 	add (TINode n)  						{ fNodes.push_back (SINode(n)); }
		TINode 	seq (TINode n1, TINode n2) const 		{ return set (INode::createSeq (SINode(n1), SINode(n2))); }
	 	TINode 	par (TINode n1, TINode n2) const 		{ return set (INode::createPar (SINode(n1), SINode(n2))); }
	 	TINode 	javascript (const std::string js) const { return set (new JavascriptNode (js)); }
	 	TINode 	prefix (const std::string text) const 	{ return set (new UrlPrefixNode (text)); }
        TINode  delay (const std::string text) const    { return set (new DelayNode (text)); }
		TINode 	expand(const std::string text) const 	{ return set (new ExpandNode (text)); }
		TINode 	expandVal(TINode n1, TINode n2) const 	{ return set (new ExpandValNode (SINode(n1), SINode(n2))); }
		TINode 	operation(INode::TNodeType type) const	{ return set (new INode ("", type)); }
		TINode 	slash(TINode node) const				{ node->setAddress(true); return node; }

		void 	pushEnv()		{ fEnvStack.push(fVars); }
		void 	popEnv()		{ if (fEnvStack.size()) { fVars = fEnvStack.top(); fEnvStack.pop();} }
		TINode 	setEnv(TINode node) const				{ node->setEnv (fVars); return node; }
		TINode 	getEnv(const std::string& var) const	{ SINode n = fVars.get (var); return n ? new INode(n.get()) : 0; }

		void 	declare (const std::string& name, TINode n);
		TINode 	variable(const std::string name) const;

		void*			fScanner;	// the flex scanner
		std::istream*	fStream;    // the input stream
		int				fLine;
		int				fColumn;

		std::string		fText;
		TEnv 			fVars;
		std::stack<TEnv>	fEnvStack;
};

} // end namespace
