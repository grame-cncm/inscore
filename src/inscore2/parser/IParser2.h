
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
		TINode 	create(std::string name, INode::TNodeType t = INode::kText) 	{ TINode n = new INode(name, t); n->setLC(fLine, fColumn); return n; }

		void 	add (TINode n)  						{ fNodes.push_back (SINode(n)); }
		TINode 	seq (TINode n1, TINode n2) const 		{ return set (INode::createSeq (SINode(n1), SINode(n2))); }
	 	TINode 	par (TINode n1, TINode n2) const 		{ return set (INode::createPar (SINode(n1), SINode(n2))); }
	 	TINode 	javascript (const std::string text) const 	{ return set (new JavascriptNode (text)); }
	 	TINode 	regexp (const std::string text) const 	{ return set (new RegexpNode (text)); }
		TINode 	expand(const std::string text) const 	{ return set (new ExpandNode (text)); }
		TINode 	operation(INode::TNodeType type) const	{ return set (new INode ("", type)); }
		TINode 	slash(TINode node) const				{ return set (new INode ("", SINode(node), INode::kSlash)); }

		void 	pushEnv()		{ fEnvStack.push(fVars); }
		void 	popEnv()		{ if (fEnvStack.size()) { fVars = fEnvStack.top(); fEnvStack.pop();} }
	
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
