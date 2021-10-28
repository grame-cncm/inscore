/*
  Interlude Library
  Copyright (C) 2009,2011  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul, 69002 Lyon - France
  research@grame.fr

*/

#include <iostream>
#include <locale.h>

#include "ITLparser.h"
#include "systemvars.h"

using namespace std;

namespace inscore 
{

//--------------------------------------------------------------------------
ITLparser::ITLparser(std::istream* stream, int line, IAppl* root, bool execute)
	: fReader(root, execute), fStream(stream), fLine(line), fColumn(1)
{
	setlocale(LC_NUMERIC, "C");
	initScanner();
	fLineOffset = fExprStartLine = 0;
	setupEnv();
}

//--------------------------------------------------------------------------
ITLparser::~ITLparser() 
{
	setlocale(LC_NUMERIC, 0);
	destroyScanner();
}

//--------------------------------------------------------------------------
void ITLparser::setupEnv()
{
	IMessage::argslist osname;
	osname.push_back( new IMsgParam<string>(kOSName));
	fReader.variable (kOSNameVar, &osname);
	IMessage::argslist osid;
	osid.push_back( new IMsgParam<int>(kOSID));
	fReader.variable (kOSIDVar, &osid);
}

} // end namespace
