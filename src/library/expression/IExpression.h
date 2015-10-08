#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <string>
#include <iostream>

#include "smartpointer.h"

#include "Operators.h"
#include "evaluator.h"


namespace inscore{

class IExpression;
typedef libmapping::SMARTP<IExpression> SIExpression;

class OperatorPrototype;

class IExprArgbase;
typedef libmapping::SMARTP<IExprArgbase> SIExprArgbase;


//____________________________________________________________
/*!
 * \brief Evaluable expression made of an operator prototype and two arguments.
 */
class IExpression: public libmapping::smartable{
private:
	const OperatorPrototype* fOperatorPrototype;
    const SIExprArgbase fArg1, fArg2;

public:
	IExpression(OperatorPrototype* operatorPrototype, SIExprArgbase arg1, SIExprArgbase arg2);



    SIExprArgbase getArg1() const {return fArg1;}
    SIExprArgbase getArg2() const {return fArg2;}

	const OperatorPrototype* getOperatorPrototype() const {return fOperatorPrototype;}

    std::string getName() const;
};


//____________________________________________________________________________________________
/*!
 * \brief base classes for all the arguments passed to an operator, it hide the template of IExprArg<T>
 */
class IExprArgbase: public libmapping::smartable, public evaluable{
public:
    virtual std::string accept(evaluator* e) const =0;

protected:
    IExprArgbase():libmapping::smartable(){}
};




//____________________________________________________________________________________________
template <typename argType>
/*!
 * \brief Containers class used to store any arguments of any type passed to an operator.
 */
class IExprArg: public IExprArgbase{
private:
    argType fArg;

public:
    IExprArg(argType arg):IExprArgbase(), fArg(arg){}
    argType getArg(){return fArg;}

    /*!
     * \brief accept the visit from an evaluator
     * \param e the evaluator
     * \return the evaluated string
     */
	std::string accept(evaluator* e) const {
        return e->eval(fArg);
    }

};

std::ostream&	operator << (std::ostream& out, const SIExpression& expr);
std::ostream&	operator << (std::ostream& out, const SIExprArgbase& exprArg);

} //end namespace





#endif // EXPRESSIONNODE_H
