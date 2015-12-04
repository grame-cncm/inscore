#ifndef EXPRESSIONFACTORY_H
#define EXPRESSIONFACTORY_H

#include <string>
#include <unordered_map>

#include "IExpression.h"
#include "Operators.h"

namespace inscore{

/*!
 * @brief An EvaluableExpr factory: it can generate ExprArg and EvaluableExpr for the parser
 */
class ExprFactory{
private:
	static std::unordered_map<std::string, OperatorPrototype*> operatorList;

public:
    /*!
	 * \brief create an expression argument with the corresponding type inferred by analysing arg
     * \param argument to encapsulate
	 * \return the constructed expression argument
     */
	static SIExprArg createArg(const std::__cxx11::string &arg);

	/*!
	 * \brief generate a default, empty expression argument containing an empty string: ""
	 * \return a smart pointer to an empty but still valid expression argument.
	 */
	inline static SIExprArg createEmptyArg(){return new IExprArg<std::string>("");}

	/*!
	 * \brief create an expression arguments that contains an Expression Operator
	 * \param operatorName: the name of the operator
	 * \param arg1: first argument passed to the operator
	 * \param arg2: second argument passed to the operator
	 * \return a smart pointer to the constructed IExprArg if succeed, if not the smart pointer is empty
	 */
	static SIExprArg createExpr(std::string operatorName, SIExprArg param1, SIExprArg param2);

	/*!
     * \brief create a message param that contains an Expression Operator
     * \param operatorName: the name of the operator
     * \param arg1: first argument passed to the operator
     * \param arg2: second argument passed to the operator
     * \param expr: if the operator exists, store the constructed expression
     * \return true if the operator exists, false otherwise
     */
	static bool createExpr(std::string operatorName, SIExprArg param1, SIExprArg param2, SIExprOperator& expr);

	/*!
	 * \brief search for an operator prototype by name
	 * \param name
	 * \param op store the operator at this address
	 * \return true if an operator was found, false otherwise
	 */
	static bool operatorByName(std::string name, OperatorPrototype *&op);


	/*!
	 * \brief register an operator into the operator list
	 * \warning this method shouldn't be called manually (OperatorPrototype constructor automatically calls it)
	 * \param op the operator to register
	 */
	static void registerOperator(OperatorPrototype *op);


};



}

#endif // EXPRESSIONFACTORY_H
