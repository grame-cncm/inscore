#ifndef EXPRESSIONFACTORY_H
#define EXPRESSIONFACTORY_H

#include <string>
#include <unordered_map>

#include "IExpression.h"

namespace inscore{

/*!
 * @brief An EvaluableExpr factory: it can generate ExprArg and EvaluableExpr for the parser
 */
class ExprFactory{
private:
    std::unordered_map<std::string, OperatorPrototype*> fOperatorList;

public:
    /*!
     * \brief create an expression factory and initialise all operator prototype associated with the factory
     */
    static ExprFactory *create();



    /*!
     * \brief create a message param that encapsulate a smart pointer on an argument IExprArg with the corresponding type artT
     * \param argument to encapsulate
     * \return a simple message param
     */

    template<typename argT> SIExprArgbase createArg(argT arg){
        IExprArg<argT>* argB = new IExprArg<argT>(arg);
        SIExprArgbase argBase(argB);
        return SIExprArgbase(argB);
    }

    /*!
     * \brief create a message param that contains an Expression Operator
     * \param operatorName: the name of the operator
     * \param arg1: first argument passed to the operator
     * \param arg2: second argument passed to the operator
     * \param expr: if the operator exists, store the constructed expression
     * \return true if the operator exists, false otherwise
     */
    bool createExpr(std::string operatorName, SIExprArgbase param1, SIExprArgbase param2, SIExpression& expr);

private:
    ExprFactory();

    void registerOperator(OperatorPrototype* op);
    inline void registerOperator(std::string name, OperatorCb callback){registerOperator(new OperatorPrototype(name, callback));}

};



}

#endif // EXPRESSIONFACTORY_H
