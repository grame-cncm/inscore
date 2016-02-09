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
#include "ExprInfo.h"
#include <sstream>

namespace inscore{


std::set<std::string> ExprInfo::fileDependency(const SIExpression &expr){return ExprFileDependency::fileDependency(expr);}

void ExprInfo::fileReplace(SIExpression &expr, const filepath &search, const filepath &replace){
	ExprSearchReplace<filepath>::searchReplace(expr,search,replace);
}

/****************************************************
 *               ExprFileDependency                 *
 * *************************************************/

std::set<std::string> ExprFileDependency::fileDependency(const IExpression *expr)
{
    ExprFileDependency f;
	((const IExprArgBase*)expr->rootNode())->accept(&f);
    return f.fDependency;
}


const std::string ExprFileDependency::eval(const filepath& arg , const IExprArgBase*){
    fDependency.insert(arg);
    return "";
}
const std::string ExprFileDependency::eval(const IExprOperator *arg, const IExprArgBase *){
	((const IExprArgBase*)arg->constArg1())->accept(this);
	((const IExprArgBase*)arg->constArg2())->accept(this);
    return "";
}



/****************************************************
 *                  SearchReplace                   *
 * *************************************************/
template <typename T>
void ExprSearchReplace<T>::searchReplace(SIExpression &expression, T search, T replace)
{
	ExprSearchReplace e(search, replace);
	expression->rootNode()->accept(&e);

	std::string s = (std::string)search;
	std::string r = (std::string)replace;
	std::string def = expression->definition();

	size_t it= def.find(s);

	while(it<def.size()){
		def.replace(it, s.size(), r);
		it += r.size() - s.size();
		it= def.find(s, it);
	}

	expression->setDefinition(def);
}

template <typename T>
const std::string ExprSearchReplace<T>::eval(const T &value, IExprArgBase *exprArg){
	if(value==fSearch){
		IExprArg<T>* arg = static_cast<IExprArg<T>*>(exprArg);
		arg->setArg(fReplace);
	}
	return "";
}




} // End namespace
