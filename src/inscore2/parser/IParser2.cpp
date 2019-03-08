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

