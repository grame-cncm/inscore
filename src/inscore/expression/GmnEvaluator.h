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
#ifndef GMNEVALUATOR_H
#define GMNEVALUATOR_H

#include "ExprEvaluator.h"

namespace inscore{

/*!
 * \brief Evaluator used to evaluate score expressions
 */
class GmnEvaluator : public ExprEvaluator
{
public:
	static GmnEvaluator* create(const IObject* contextObject){return new GmnEvaluator(contextObject);}

	const std::string eval(const IObject *arg);
	const std::string eval(const std::string& arg, const IExprArgBase* exprArg=0);

	std::string emptyValue() const {return "[]";}

	virtual ~GmnEvaluator(){}

protected:
        GmnEvaluator(const IObject* contextObject);
		bool isXml(const std::string &score) const;

private:
		static const OperatorList gmnOperators();
		static const OperatorList gOperators;
};

}

#endif // GMNEVALUATOR_H
