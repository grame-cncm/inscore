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

#pragma once

#include <string>
#include <unordered_map>

#include "smartpointer.h"

#include "evaluator.h"
#include "IExpression.h"

namespace inscore{

class IObject;
class FileDownloader;

/*!
 * \brief Handle the status of the evaluator during the processing of the evaluation (failing...)
 */
class EvaluationStatus{
    bool fEvalSucceed;

	public:
		EvaluationStatus();
		void init();

		inline std::string fail(const IExprArgBase* arg){return fail(arg->getEvaluated());}
		inline std::string fail(const std::string defaultValue){if(defaultValue.empty()){return fail();} return defaultValue;}
		inline std::string fail(){fEvalSucceed = false; return "";}
		bool hasEvalSucceed(){return fEvalSucceed;}
};

typedef const std::string (*OperatorCb)(const std::string&,const std::string&, bool &success);
typedef std::unordered_map<std::string, OperatorCb> OperatorList;

/*!
 * \brief IEvaluableExpr evaluator mother class. Handle context for the evaluation, error...
 */
class ExprEvaluator: public constEvaluator{

	std::string 		fEvalName;
	const IObject* 		fContextObject;
	const OperatorList 	fCallbackList;
	FileDownloader*		fFileDownloader = 0;

	public:
		/*!
		 * \brief create Create an instance of this evaluator.
		 * \param contextObject The object will be used to deduce relative path.
		 * \warning Any evaluator compatible with IExprHandler should implements such method.
		 * \return A valid evaluator.
		 */
		static ExprEvaluator* create(const IObject* contextObject){return new ExprEvaluator("ExprEvaluator", contextObject, OperatorList());}

		/*!
		 * \brief evalExpression Evaluate an IExpression
		 * \param expr The expression to evaluate
		 * \param result Store the result of the evaluation
		 * \return True if the evaluation succeed, false otherwise
		 */
		bool evalExpression(const IExpression *expr, std::string &result);

		/*!
		 * \brief eval Evaluate an IObject as a string. This function is called by the default implementation of eval(const itladdress& arg, const IExprArgBase* exprArg).
		 * \param arg A pointer towards the IObject to evaluate
		 * \return
		 */
		virtual const std::string eval(const IObject *arg);


		/*!
		 * \brief evaluatorName Each evaluator implementation (subclassing) have a different name (default is ExprEvaluator).
		 */
		std::string evaluatorName() const {return fEvalName;}

		/*!
		 * \brief emptyValue This value shall replace any invalid or empty string with a valid empty value that won't cause the operators processing to fail (default is "")
		 */
		virtual std::string emptyValue() const {return "";}

		virtual ~ExprEvaluator();

	protected:
		EvaluationStatus fEvalStatus;

		/*!
		 * \brief ExprEvaluator Constructor for subclassing ExprEvaluator
		 * \param name the evaluator name (set the value return by evaluatorName()).
		 * \param contextObject the context object (transfer the context object from the static create method)
		 * \param operatorList The list of operator (a hash map linking operators name to callback method).
		 * \warning To be compatible with IExprHandler an evaluator shoud implement a static create(const IObject* contextObject()) method.
		 */
		ExprEvaluator(std::string name, const IObject* contextObject, const OperatorList &operatorList);
		
		virtual const std::string eval(const IExprOperator* arg, const IExprArgBase* exprArg=0);
		virtual const std::string eval(const std::string& arg, const IExprArgBase* exprArg=0);
		virtual const std::string eval(const filepath& arg, const IExprArgBase* exprArg=0);
		virtual const std::string eval(const itladdress& arg, const IExprArgBase* exprArg=0);
		virtual const std::string eval(const iexpression& arg, const IExprArgBase* exprArg=0);

		inline const IObject* contextObject(){return fContextObject;}

		/*!
		 * \brief smartEval this method handle the lazy evaluation of expression trees (check if the arguments is dynamically evaluated or if the branch value changed)
		 * \param expr the node to evaluate
		 * \param result The result of the evaluation is stored in this reference.
		 * \return true if a new value was evaluated
		 */
		bool smartEval(const IExprArgBase *expr, std::string &result);
		bool callbackByOperator(const std::string op, OperatorCb &cb) const ;
};

}
