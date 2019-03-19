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

#ifndef __INode__
#define __INode__

#include <memory>
#include <iostream>
#include <ostream>
#include <string>
#include <vector>

#include "TEnv2.h"


namespace inscore2
{

class INode;
class DelayNode;
typedef std::shared_ptr<INode>	SINode;

//------------------------------------------------------------
class NList : public std::vector<SINode> {
	public:
		virtual ~NList() {}
	
		void 			add (const SINode& n);
		void 			add (const NList& l);
		const SINode 	find (const SINode& n) const;
		const NList 	but  (const SINode& n) const;
};

//------------------------------------------------------------
class INode {

	public:
		enum TNodeType {
			kText, kInt, kFloat, kSeq, kPar, kExpand, kForest, kRegexp, kVariable, kSlash, kJScript, kURLPrefix, kDelay,
			kFirstMath, kAdd=kFirstMath, kSub, kDiv, kMult, kModulo, kQuest, kNeg, kEq, kGreater, kGreatereq, kLess,
            kLesseq, kMin, kMax, kHas, kSin, kCos, kTan, kASin, kACos, kATan, kSinh, kCosh, kTanh, kASinh, kACosh, kATanh,
			kExp, kLog, kLog10, kLog2, kPow, kSqrt, kCbrt, kCeil, kFloor, kRound, kRand, kLastMath=kRand };

		static SINode create (const std::string& val, TNodeType t=kText)  { return SINode(new INode(val, t));}
		static SINode create (float value) 								  { return SINode(new INode(std::to_string(value), kFloat)); }
		static SINode create (int value) 								  { return SINode(new INode(std::to_string(value), kInt)); }
		static SINode createDelay (float value);

				 INode(const std::string& val, TNodeType t=kText)
				 							: fValue(val), fType(t), fAddressPart(false), fLine(0), fColumn(0) 	{}
				 INode(const std::string& val, const NList& sub, TNodeType t)
				 							: fValue(val), fType(t), fAddressPart(false), fLine(0), fColumn(0) { fSubNodes.add(sub); }
				 INode(const std::string& val, const SINode& n, TNodeType t)
				 							: fValue(val), fType(t), fAddressPart(false), fLine(0), fColumn(0) { fSubNodes.add(n); }
				 INode(const SINode n1, const SINode n2, TNodeType t)
				 							: fType(t), fAddressPart(false), fLine(0), fColumn(0)  { fSubNodes.add(n1); fSubNodes.add(n2); }
				 INode(const INode* node);

		virtual ~INode() {}

		virtual const std::string 	getValue () const 	{ return fValue; }
		virtual const std::string 	getFullValue () const { return fValue + ":" + getTypeStr(); }
		virtual TNodeType 			getType () const 	{ return fType; }
        virtual const char*         getTypeStr() const  { return type2string (fType); }
        virtual float               getDelay() const    { return fDelay; }
        virtual float               getFloat() const;
        virtual void                setDelay(float d)   { fDelay = d; }
		virtual void 				setInfos (const SINode& n) { setInfos(n.get()); }
		virtual void 				setInfos (const INode* n);
		virtual void 				propagateDelay ();

		size_t 			size () const 		{ return fSubNodes.size(); }
		bool 			empty () const 		{ return fSubNodes.size() == 0; }
		bool 			isVariable () const { return fType == kVariable; }
		bool 			isForest () const 	{ return fType == kForest; }
		bool 			isDelay () const 	{ return fType == kDelay; }
		bool 			petiole () const;
		bool 			address () const	{ return fAddressPart; }
		const NList& 	childs() const		{ return fSubNodes; }


		virtual SINode  clone (const NList& sub) const;
		virtual SINode  clone (const SINode& n) const;
		virtual SINode  clone () const;
		virtual SINode  merge (const SINode& n) const;
		const SINode 	find  (const SINode& n) const	{ return fSubNodes.find(n); }

		bool operator == (const INode* n) const	 { return (n->getValue() == getValue()) && (n->getType() == getType()); }
		bool operator == (const SINode& n) const { return (n->getValue() == getValue()) && (n->getType() == getType()); }
		bool operator != (const INode* n) const	 { return !(*this == n); }
		bool operator != (const SINode& n) const { return !(*this == n); }

		int 	getLine() const 	{ return fLine; }
		int 	getColumn() const 	{ return fColumn; }
		void 	setLC (int line, int column) 	{ fLine = line; fColumn = column; }

		void 			setEnv (const std::string&, int val);	// sets a single var in environment
		void 			setEnv (const TEnv& env);				// overrides the current environment
		void 			addEnv (const SINode& node);			// add the node environment to the current environment
		const TEnv& 	getEnv () const					{ return fEnv; }
		void 			setAddress (bool state = true)	{ fAddressPart = state; }

		static const char * type2string (TNodeType t);

		//-----------------------------------------------------------------
		// this interface is provided for the parser (only)
		//-----------------------------------------------------------------
		static INode* createSeq (SINode n1, SINode n2);
		static INode* createPar (SINode n1, SINode n2);

	private:
		std::string fValue;
		NList		fSubNodes;
		TNodeType	fType;
		bool		fAddressPart;
        TEnv        fEnv;
        float 		fDelay = 0;

		int fLine;			// line number in file if any (this is for error reporting)
		int	fColumn;		// column number in file if any (this is for error reporting)
};

//------------------------------------------------------------
class SeqNode : public INode {
	public:
			 SeqNode(SINode n1, SINode n2) : INode (n1, n2, kSeq) {}
	virtual ~SeqNode() {}
};


//------------------------------------------------------------
class ParNode : public INode {
	public:
			 ParNode(SINode n1, SINode n2) : INode (n1, n2, kPar) {}
	virtual ~ParNode() {}
};

//------------------------------------------------------------
class ExpandNode : public INode {
	public:
			 ExpandNode(std::string val) : INode(val, kExpand) {}
	virtual ~ExpandNode() {}
};

//------------------------------------------------------------
class DelayNode : public INode {
    public:
             DelayNode(std::string val);
             DelayNode(float val);			// a milliseconds delay
    virtual ~DelayNode() {}
};

//------------------------------------------------------------
class UrlPrefixNode : public INode {
    public:
             UrlPrefixNode(std::string val) : INode(val, kURLPrefix) { setAddress(true); }
    virtual ~UrlPrefixNode() {}
};

//------------------------------------------------------------
class JavascriptNode : public INode {
	public:
			 JavascriptNode(std::string val) : INode(val, kJScript) {}
	virtual ~JavascriptNode() {}
};

//------------------------------------------------------------
class ForestNode : public INode {
	public:
			 ForestNode(SINode node ) 	: INode ("", node, kForest) {}
			 ForestNode(const NList& l) 	: INode ("", l, kForest) {}
	virtual ~ForestNode() {}
};

//------------------------------------------------------------
class RegexpNode : public INode {
	public:
			 RegexpNode(std::string val) : INode(val, kRegexp) {}
			 RegexpNode(std::string val, const NList& l) : INode(val, l, kRegexp) {}
	virtual ~RegexpNode() {}
};

//------------------------------------------------------------
class VariableNode : public INode {
	public:
			 VariableNode(std::string val) : INode (val, kVariable) {}
	virtual ~VariableNode() {}
};


std::ostream& operator<< (std::ostream& os, const SINode n);
std::ostream& operator<< (std::ostream& os, const INode* n);
std::ostream& operator<< (std::ostream& os, const INode& n);

} // end namespace

#endif

