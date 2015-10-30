#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <string>
#include <iostream>
#include <map>

#include "smartpointer.h"

#include "Operators.h"
#include "evaluator.h"


namespace inscore{

class IExprOperator;
typedef libmapping::SMARTP<IExprOperator> SIExprOperator;

class OperatorPrototype;

class IExpression;
typedef libmapping::SMARTP<IExpression> SIExpression;


//____________________________________________________________
/*!
 * \brief Evaluable expression made of an operator prototype and two arguments.
 */
class IExprOperator: public libmapping::smartable{
private:
	const OperatorPrototype* fOperatorPrototype;
	SIExpression fArg1, fArg2;

public:
	IExprOperator(const OperatorPrototype* operatorPrototype, SIExpression arg1, SIExpression arg2);

	SIExpression& arg1() {return fArg1;}
	SIExpression& arg2() {return fArg2;}

	const SIExpression constArg1() const {return fArg1;}
	const SIExpression constArg2() const {return fArg2;}

	bool dynamicEval() const;

	const OperatorPrototype* operatorPrototype() const {return fOperatorPrototype;}

    std::string getName() const;
};


//____________________________________________________________________________________________
/*!
 * \brief base classes for all the arguments passed to an operator, it hide the template of IExprArg<T>
 */
class IExpression: public libmapping::smartable, public evaluable{
protected:
	bool fCopyEval, fDynamicEval;
	std::string* fEvaluated;

public:
	virtual std::string accept(evaluator* e) =0;
	virtual std::string accept(constEvaluator* e) const = 0;

	void switchToDynamic(){fDynamicEval = true;}
	void switchToCopy(){fCopyEval = true;}
	inline bool copyEval() const {return fCopyEval;}
	inline bool dynamicEval() const {return fDynamicEval;}
	inline bool pureStaticEval() const {return !fCopyEval && !fDynamicEval;}

	virtual SIExpression copy()=0;

	inline std::string getEvaluated() const {return *fEvaluated;}
	inline void setEvaluated(std::string evaluated){*fEvaluated = evaluated;}
	inline std::string* evaluated() const {return fEvaluated;}	//as evaluated is more a buffer than a real attribute
																//the pointer isn't const so evaluated can be change even in a const IExpression
	virtual void recursiveClearEvaluated()=0;

	virtual ~IExpression(){delete fEvaluated;}

protected:
	IExpression(bool dynamicEval = false, bool copyEval = false);
};




//____________________________________________________________________________________________
template <typename argType>
/*!
 * \brief Containers class used to store any arguments of any type passed to an operator.
 */
class IExprArg: public IExpression{
private:
    argType fArg;

public:
	IExprArg(argType arg, bool dynamicEval = false, bool copyEval = false): IExpression(dynamicEval, copyEval), fArg(arg){}
	argType getArg(){return fArg;}

	SIExpression copy(){
		IExpression* r = new IExprArg<argType>(fArg, fDynamicEval, fCopyEval);
		r->setEvaluated(getEvaluated());
		return r;
	}

	void recursiveClearEvaluated(){fEvaluated->clear();}

    /*!
     * \brief accept the visit from an evaluator
     * \param e the evaluator
     * \return the evaluated string
     */
	std::string accept(evaluator* e){
		return e->eval(fArg, this);
    }
	std::string accept(constEvaluator *e) const {
		return e->eval(fArg, this);
	}

};

std::ostream&	operator << (std::ostream& out, const SIExpression& exprArg);
std::ostream&	operator << (std::ostream& out, const IExprOperator& exprArg);

} //end namespace






#endif // EXPRESSIONNODE_H
