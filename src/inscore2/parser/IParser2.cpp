
#include <iostream>

#include "IParser2.h"
#include "parseEval.h"
#include "addressEval.h"

#include "ITLError.h"

using namespace std;

namespace inscore2
{

//------------------------------------------------------------
void IParser::declare(const std::string& name, TINode n)  {
	SINode e = SINode(n);
	fVars.put(name, addressEval::eval(parseEval::eval(e)));
}

//------------------------------------------------------------
TINode 	IParser::variable(const std::string name) const		{
	return set (new VariableNode (name) );
}

//------------------------------------------------------------
void 	IParser::error (int line, int col, const char* msg) const {
	inscore::ITLErr << "line " << line << " column " << col << ": " << msg << inscore::ITLEndl;
}

} // end namespace

