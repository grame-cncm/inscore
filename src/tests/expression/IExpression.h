﻿#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <string>
#include <iostream>

#include "smartpointer.h"

#include "evaluator.h"


namespace inscore{

typedef std::string (*OperatorCb)(std::string,std::string);

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
    OperatorPrototype* fOperatorPrototype;
    SIExprArgbase fArg1, fArg2;

public:
    IExpression(OperatorPrototype* operatorPrototype, SIExprArgbase arg1, SIExprArgbase arg2);



    SIExprArgbase getArg1(){return fArg1;}
    SIExprArgbase getArg2(){return fArg2;}

    OperatorPrototype* getOperatorPrototype(){return fOperatorPrototype;}

    std::string getName();
};


/*!
 * \brief A container class storing all informations needed to construct an Operator
 */
class OperatorPrototype{
    private:
	OperatorCb fCallback;
	std::string fName;

    public:
	/*!
	 * \brief Construct an operator prototype
	 * \param name: the name which will be used to refer to the operator
	 * \param callback: the method called when the operator is used
	 */
	OperatorPrototype(std::string name, OperatorCb callback):fName(name),fCallback(callback){}
	/*!
	 * \brief getName
	 * \return the name of the operator
	 */
	std::string getName() const {return fName;}
	/*!
	 * \brief getCallback
	 * \return the callback method used when the operator is triggered
	 */
	OperatorCb getCallback() const {return fCallback;}
};


//____________________________________________________________________________________________
/*!
 * \brief base classes for all the arguments passed to an operator, it hide the template of IExprArg<T>
 */
class IExprArgbase: public libmapping::smartable, public evaluable{
public:
    virtual std::string accept(evaluator *e)=0;

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
    std::string accept(evaluator *e){
        return e->eval(fArg);
    }

};

}




#endif // EXPRESSIONNODE_H
