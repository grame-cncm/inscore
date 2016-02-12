/*
  INScore Project

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
#include <string>
#include <deelx.h>

#include "ExprFactory.h"

#include "ITLError.h"



using namespace std;

namespace inscore{

SIExprArg ExprFactory::createArg(const std::string &arg)
{
	SIExprArg argResult;


	//  /?(. .? /)*([^/?:*<>|']+/?)+.[^/\?:*<>|']+
	CRegexpT<char> fileRegex("/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+");

	//  (../)*([_a-zA-Z0-9]+/)*[_a-zA-Z0-9]+
	CRegexpT<char> identifierRegex("(\\.\\./)*([_a-zA-Z0-9]+/)*[_a-zA-Z0-9]+");


	if(fileRegex.MatchExact(arg.c_str()).IsMatched() || isurl(arg)){
			//First check if is filepath or an url
		argResult = new IExprArg<filepath>(arg);

	}else if(identifierRegex.MatchExact(arg.c_str()).IsMatched()){
			//Then if is INScore objects
		argResult = new IExprArg<itladdress>(arg);
	}

			//If nothing was found encapsulate the string as it is...
	if(!argResult)
		argResult = new IExprArg<std::string>(arg);

	return argResult;
}

//_______________________________________________________
SIExprArg ExprFactory::createExpr(string operatorName, SIExprArg param1, SIExprArg param2)
{
	SIExprOperator expr;
	if(ExprFactory::createExpr(operatorName, param1, param2, expr))
		return new IExprArg<SIExprOperator>(expr);

	ITLErr<<"ExpressionFactory error: operator \""<< operatorName <<"\" unknown"<<ITLEndl;
	return createEmptyArg();
}


//_______________________________________________________
bool ExprFactory::createExpr(std::string operatorName, SIExprArg param1, SIExprArg param2, SIExprOperator &expr)
{
	if(!param1)
		param1 = createEmptyArg();
	if(!param2)
		param2 = createEmptyArg();

	expr = new IExprOperator(operatorName, param1, param2);

	return true;
}

//_______________________________________________________
bool ExprFactory::isurl (const std::string& path)
{
	std::string begin;
	begin.assign(path, 0, 7);
	return (begin == "http://") || (begin == "https:/");
}
} //end namespace
