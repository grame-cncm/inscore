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
     * \brief create a message param that encapsulate a smart pointer on an argument IExprArg with the corresponding type artT
     * \param argument to encapsulate
     * \return a simple message param
     */

	template<typename argT>
	static SIExpression createArg(argT arg, bool dynamicEval=false, bool staticEval=false){
		IExprArg<argT>* argB = new IExprArg<argT>(arg, dynamicEval, staticEval);
        SIExpression argBase(argB);
        return SIExpression(argB);
    }

	static SIExpression createArg(std::string string);
	static SIExpression createArg(SIExprOperator expression);

    /*!
     * \brief create a message param that contains an Expression Operator
     * \param operatorName: the name of the operator
     * \param arg1: first argument passed to the operator
     * \param arg2: second argument passed to the operator
     * \param expr: if the operator exists, store the constructed expression
     * \return true if the operator exists, false otherwise
     */
	static bool createExpr(std::string operatorName, SIExpression param1, SIExpression param2, SIExprOperator& expr);

	/*!
	 * \brief search for an operator prototype by name
	 * \param name
	 * \param op store the operator at this address
	 * \return true if an operator was found, false otherwise
	 */
	static bool operatorByName(std::string name, OperatorPrototype *&op);

	static void registerOperator(OperatorPrototype *op);


};



}

#endif // EXPRESSIONFACTORY_H
