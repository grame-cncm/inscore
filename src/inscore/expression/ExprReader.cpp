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
#include "ExprReader.h"

#include "IExpression.h"
#include "IExprParser.h"

#define TAB "   "

namespace inscore{

bool ExprReader::evalExpression(const IExprArgBase *expr, std::string &result, bool printData)
{
	fTab = 0;
    evalSucceed = true;
	fPrintData = printData;

	result = prefix();
	fPrefix = "    ";

	std::string evaluated = expr->accept(this);
	if(evaluated.find('(')!=0)
		evaluated = "( "+evaluated+" )";

	result += "expr"+evaluated;

	if(fTab!=0)
		return false;
    return evalSucceed;
}

bool ExprReader::read(const IExprArgBase *expr, std::string prefix, std::string &result, bool printInternalData)
{
	ExprReader r;
	r.fPrefix = prefix;
	return r.evalExpression(expr, result, printInternalData);
}

//_________________________________
const std::string ExprReader::eval(const std::string& arg, const IExprArgBase *)
{
	return prefix('"'+arg+'"');
}

//_________________________________
const std::string ExprReader::eval(const IExprOperator *arg, const IExprArgBase *)
{
	fTab++;
	std::string arg1 = ((const IExprArgBase*)arg->constArg1())->accept(this);
	std::string arg2 = ((const IExprArgBase*)arg->constArg2())->accept(this);
	fTab--;

	std::string r= "( "+arg->operatorName();

	if(	arg1.length() > 20 || arg1.find('\n') != std::string::npos
	 ||	arg2.length() > 20 || arg2.find('\n') != std::string::npos ){
		//multiline structure
		r	+=							+ "\n"
			+ prefix()	+ TAB	+ arg1	+ "\n"
			+ prefix()	+ TAB	+ arg2	+ "\n"
			+ prefix()	+ ")";
	}else
		r+= " "+ arg1 + " " + arg2 + " " + ")";

	return r;
}

//_________________________________
const std::string ExprReader::eval(const filepath &arg, const IExprArgBase *exprArg)
{
	return argPrefix(exprArg) + prefix('"'+(std::string)arg+'"');
}

//_________________________________
const std::string ExprReader::eval(const itladdress &arg, const IExprArgBase *exprArg)
{
	return argPrefix(exprArg) + prefix(arg);
}

//_________________________________
const std::string ExprReader::eval(const iexpression &arg, const IExprArgBase *exprArg)
{
	return argPrefix(exprArg) + prefix(arg);
}

std::string ExprReader::argPrefix(const IExprArgBase *exprArg)
{
	if(!exprArg)
		return "";

	std::string r = "";


	std::string evaluated = exprArg->getEvaluated();
	if(fPrintData&&!evaluated.empty()){
		if(evaluated.find('\n') == std::string::npos)
			r+="[\""+evaluated+"\"]";	//Single line
		else{
			r+= "[\"";				//Multi line
			fTab++;
			r+= prefix("\n"+evaluated) + "\n";
			fTab--;
			r+= prefix() + "\"]";
		}
	}


	if(exprArg->dynamicEval())
		r+="&";
	if(exprArg->copyEval())
		r+="~";

	return r;
}

std::string ExprReader::prefix(std::string applyPrefixTo)
{
	std::string prefix = fPrefix;
	for (int i = 0; i < fTab; ++i)
		prefix+=TAB;

	if(applyPrefixTo=="")
		return prefix;

	auto it = applyPrefixTo.find('\n');
	while(it != std::string::npos){
		it++;
		applyPrefixTo.insert(it, prefix);
		it = applyPrefixTo.find('\n', it);
	}

	return applyPrefixTo;
}


//_________________________________
ExprReader::ExprReader()
	:constEvaluator()
{
    evalSucceed = true;
}



} //end namespace
