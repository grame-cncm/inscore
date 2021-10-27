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

#include "IParser2.h"
#include "parseEval.h"
#include "systemvars.h"

#ifndef TESTV2
#include "ITLError.h"
#endif

using namespace std;

#define SUBSTITUTE_VARS	0

namespace inscore2
{


//------------------------------------------------------------
IParser::IParser(std::istream* stream) : fStream(stream), fLine(1), fColumn(1)
{
	setlocale(LC_NUMERIC, "C");
	initScanner();
	addEnv (inscore::kOSNameVar, inscore::kOSName);
	addEnv (inscore::kOSIDVar, inscore::kOSID);
}
//------------------------------------------------------------
IParser::~IParser() {
	setlocale(LC_NUMERIC, 0);
	destroyScanner();
 }

//------------------------------------------------------------
void IParser::addEnv (const std::string& name, const std::string& val) 	{ fVars.put(name, INode::create (val) ); }
void IParser::addEnv (const std::string& name, int val) 				{ fVars.put(name, INode::create (val) ); }


//------------------------------------------------------------
void IParser::declare(const std::string& name, TINode n)  {
	SINode e = SINode(n);
#if SUBSTITUTE_VARS
	fVars.put(name, e);
#else
	fVars.put(name, parseEval::eval(e));
#endif
}

//------------------------------------------------------------
TINode 	IParser::variable(const std::string name) const		{
#if SUBSTITUTE_VARS
	TINode node = getEnv (name);
	return node ? node : set (new VariableNode (name) );
#else
	return set (new VariableNode (name) );
#endif
}

//------------------------------------------------------------
void 	IParser::error (int line, int col, const char* msg) const {
#if defined(TESTV2) || !HASOSCStream
	cerr << "line " << line << " column " << col << ": " << msg << endl;
#else
	inscore::ITLErr << "line " << line << " column " << col << ": " << msg << inscore::ITLEndl;
#endif
}

} // end namespace

