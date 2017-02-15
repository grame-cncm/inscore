/*
  INScore Library
  Copyright (C) 2009,2016  Grame

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

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr

*/

#include <iostream>
#include <locale.h>
#include <sstream>

#include "IExprParser.h"

#include "IExpression.h"
#ifndef NO_EXPR_VAR_SUPPORT
#include "TScripting.h"
#include "IMessage.h"
#endif

using namespace std;

namespace inscore 
{

//--------------------------------------------------------------------------
IExprParser::IExprParser(std::istream* stream, const TScripting* reader)
	: fStream(stream)
#ifndef NO_EXPR_VAR_SUPPORT
	, fReader(reader)
#endif
{
	fRootNode = SIExprArg(0);
	fColumnOffset = 0;
	fLineOffset = fLine = 0;
	setlocale(LC_NUMERIC, "C");
	initScanner();
}

//--------------------------------------------------------------------------
IExprParser::~IExprParser()
{
	setlocale(LC_NUMERIC, 0);
	destroyScanner();
}

//--------------------------------------------------------------------------
bool IExprParser::parseExpression(std::string definition, SIExpression &expr, const TScripting* reader, int lineOffset, int columnOffset)
{
	std::istringstream* ss = new std::istringstream(definition);

	IExprParser p( ss, reader);

	p.fColumnOffset = columnOffset;
	p.fLineOffset = lineOffset;
	SIExprArg rootNode = p.parse();

	delete ss;

	if(!rootNode)
		return false;

	expr = IExpression::create(definition, rootNode);
	return true;
}

//--------------------------------------------------------------------------
std::vector<string> *IExprParser::readVar(std::string* varName, int line){
	std::vector<std::string>* l = new std::vector<std::string>();

#ifndef NO_EXPR_VAR_SUPPORT
	if(!fReader){
		ITLErr<<"IExpression parser error: No context to read $"<< *varName << "from."<<ITLEndl;
		return l;
	}


	IMessage::argslist list =  fReader->resolve(varName->c_str(), line);

	for (unsigned int i = 0; i < list.size(); ++i) {
		if(list.at(i)->isType<std::string>())
			l->push_back(list.at(i)->value<std::string>("") );
	}

#else
	std::cerr<<"IExpression parser error: INScore wasn't compiled with variable support for expression."<<std::endl;
#endif

	return l;
}

} // end namespace

