

#include <sstream>
#include <cctype>
#include <regex>

#include "expandEval.h"
#include "TreeTools.h"

using namespace std;


typedef std::function<void(const string&, int i, int j)> 	TExpEnumFunction;


namespace inscore2
{

//------------------------------------------------------------
static void makelist (int from, int to, TExpEnumFunction f)
{
	int i = 0;
	int step = (from < to) ? 1 : -1;
	f (to_string (from), i++, 0);
	while (from != to) {
		from += step;
		f (to_string (from), i++, 0);
	}
}


//------------------------------------------------------------
static void interpolate (char from, char to, TExpEnumFunction f)
{
	int i = 0;
	char step = (from < to) ? 1 : -1;
	char buff[2] = {from, 0};
	if (isalnum(from)) f (buff, i++, 0);
	while (from != to) {
		from += step;
		buff[0] = from;
		if (isalnum(from)) f (buff, i++, 0);
	}
}

//------------------------------------------------------------
static void interpolate (char from1, char from2, char to1, char to2, int i, TExpEnumFunction f )
{
	int j = 0;
	char buff[3] = {from1, from2, 0};
	char step = (from2 < to2) ? 1 : -1;
	if (isalnum(from1)  && isalnum(from2)) f (buff, i, j++);
	while(from2 != to2) {
		from2 += step;
		buff[1] = from2;
		if (isalnum(from1) && isalnum(from2)) f (buff, i, j++);
	}
}

//------------------------------------------------------------
static void interpolate (const char* from, const char* to, TExpEnumFunction f)
{
	char f1 = from[0]; char t1 = to[0];
	char f2 = from[1]; char t2 = to[1];
	int n = (std::abs(f1 - t1) + 1);
	char step = (f1 < t1) ? 1 : -1;
	for (int i=0; i < n; i++) {
		interpolate (f1, f2, f1, t2, i, f);
		f1 += step;
	}
}

//------------------------------------------------------------
static void interpolate (const string& from, const string& to, TExpEnumFunction f)
{
	size_t fs = from.size(), ts = to.size();
	if ((fs == 1) && (ts == 1)) return interpolate (*from.c_str(), *to.c_str(), f);
	if ((fs == 2) && (ts == 2)) return interpolate (from.c_str(), to.c_str(), f);
}


//------------------------------------------------------------
static void makelist (const string& from, const string& to, TExpEnumFunction f)
{
	if (isNumber (from.c_str()) && isNumber(to.c_str()))
		return makelist (stoi(from), stoi(to), f);
	
	return interpolate (from, to, f);
}

//------------------------------------------------------------
// format string decoding
//------------------------------------------------------------
// in an expression like A[1...3], separate the first part (A) from the expansion string ([1...3]
// on output, 'header' contains the first part and 'expr' contains the expansions string
// without the leading '[' and the trailing ']'
static bool getexpand (const string& input, string& header, string& expr)
{
	string exp = "([_a-zA-Z0-9]*)\\[([a-zA-Z0-9:.]+)\\]$";
	std::regex e (exp);

	smatch m;
	if (regex_match (input, m, e) && (m.size() == 3)) {
		header = m[1].str();
		expr   = m[2].str();
		return true;
	}
	return false;
}

//------------------------------------------------------------
// extract optional variable names from an expansiong string
// on output, 'a' and 'b' contains the variable names if any
// 'out' contains the expansion string without the variable names
// return the decoded variables count
static int getvars (const string& input, string& a, string& b, string& out)
{
	string exp1 = "([a-zA-Z]+):([^:]+)$";
	string exp2 = "([a-zA-Z]+):([a-zA-Z]+):([^:]+)";
	std::regex e1 (exp1);
	std::regex e2 (exp2);

	smatch m;
	if (regex_match (input, m, e1) && (m.size() == 3)) {
		a = m[1].str();
		out = m[2].str();
		return 1;
	}
	if (regex_match (input, m, e2) && (m.size() == 4)) {
		a = m[1].str();
		b = m[2].str();
		out = m[3].str();
		return 2;
	}
	out = input;
	return 0;
}

//------------------------------------------------------------
// in an expansion string like 1...3 or a...l, extract the starting and ending strings
static bool getspan (const string& input, string& from, string& to)
{
	string exp1 = "([[:alnum:]])\\.{3}([[:alnum:]])$";			// for the a...b form
	string exp2 = "([[:alnum:]]{2})\\.{3}([[:alnum:]]{2})$";	// for the aa...bb form
	string exp3 = "([0-9]+)\\.{3}([0-9]+)$";					// for the n...m form, where n and m are numbers

	std::regex e1 (exp1);
	std::regex e2 (exp2);
	std::regex e3 (exp3);

	smatch m;
	if ((regex_match (input, m, e1) ||
		 regex_match (input, m, e2) ||
		 regex_match (input, m, e3)) && (m.size() == 3)) {
		from = m[1].str();
		to   = m[2].str();
		return true;
	}
	return false;
}


//------------------------------------------------------------
TExpandInfos expandEval::getExpand (const string& str)
{
	TExpandInfos infos;
	string part2, span;
	if (getexpand (str, infos.header, part2)) {
		getvars (part2, infos.var1, infos.var2, span);
		if (getspan (span, infos.from, infos.to))
			return infos;
	}
	throw (expandEvalException ("incorrect format string"));
}

//------------------------------------------------------------
// evaluation of the exapnd form [n...m]
//------------------------------------------------------------
SINode expandEval::eval (const SINode& node) throw(expandEvalException)
{
	switch(node->getType()) {
		case INode::kExpand:	return evalExpand(node);
		default:				return evalNode(node);
	}
}

//------------------------------------------------------------
SINode expandEval::evalNode (const SINode& node)
{
	NList l;
	for (auto n: node->childs())
		l.add (eval(n));
	return node->clone(l);
}

//------------------------------------------------------------
SINode expandEval::evalExpand (const SINode& node)
{
	NList l;
	try {
		TExpandInfos info = expandEval::getExpand (node->getName());
		makelist (info.from, info.to, [info, node, &l](const string& s, int i, int j) -> void {
			SINode n = SINode(new INode(info.header + s, node->clone()->childs(), INode::kText));
//			n->setAddress( node->address() );
			n->setAddress( true );
			if (info.var1.size()) n->setEnv (info.var1, i);
			if (info.var2.size()) n->setEnv (info.var2, j);
			n->setLC(node->getLine(), node->getColumn());
			l.push_back(n);
		});
	}
	catch (expandEvalException e) {
		stringstream what;
		what << "line " << node->getLine() << " column " << node->getColumn() << ": " << e.what();
		throw (expandEvalException (what.str().c_str()));
	}
	return SINode(new ForestNode(l));
}


} // end namespace

