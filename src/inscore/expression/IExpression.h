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

#ifndef EXPRESSIONNODE_H
#define EXPRESSIONNODE_H

#include <string>
#include <iostream>
#include <map>

#include "smartpointer.h"
#include "evaluator.h"

namespace inscore{

class IExprOperator;
typedef libmapping::SMARTP<IExprOperator> SIExprOperator;

class IExprArgBase;
typedef libmapping::SMARTP<IExprArgBase> SIExprArg;

class IExpression;
typedef libmapping::SMARTP<IExpression> SIExpression;

/*!
 * \brief An IExpression encapsulate an expression tree with its definition string
 */
class IExpression: public libmapping::smartable{
private:
	SIExprArg fRootNode;
	std::string fDefinition;

public:

	/*!
	 * \brief Generate an IExpression using a definition and an expression tree.
	 * \param definition
	 * \param fRootNode the root node of the expression tree
	 * \return A smart pointer on the generated IExpression
	 */
	static SIExpression create(const std::string &definition, const SIExprArg &fRootNode);

	/*!
	 * \brief Generate an empty IExpression defined by 'expr ("")' and with a root node containing an empty string.
	 * \return A smart pointer on the generated IExpression
	 */
	static SIExpression createEmpty();

	inline std::string definition() const				{ return fDefinition;}
	inline void setDefinition(std::string definition)	{ fDefinition = definition;}
	inline const SIExprArg& rootNode() const			{ return fRootNode;}
	void setRootNode(SIExprArg rootNode);

	/*!
	 * \brief isValid Test if the IExpression is valid
	 * \return True if the expression contains a not empty defition and expression tree.
	 */
	inline bool isValid()			{return fRootNode!=0 && !fDefinition.empty();}


protected:
	IExpression(const std::string &definition, const SIExprArg &rootNode);
};

//____________________________________________________________
/*!
 * \brief Expression operator made of an operator name and its two arguments.
 */
class IExprOperator: public libmapping::smartable{
private:
	const std::string fOperatorPrototype;
	SIExprArg fArg1, fArg2;

public:
	IExprOperator(const std::string operatorName, SIExprArg arg1, SIExprArg arg2);

	SIExprArg& arg1() {return fArg1;}
	SIExprArg& arg2() {return fArg2;}

	const SIExprArg constArg1() const {return fArg1;}
	const SIExprArg constArg2() const {return fArg2;}

	/*!
	 * \brief dynamicEval Get the dynamic state of the node
	 * \return False if both arg1 and arg2 are NOT dynamically evaluated, True otherwise.
	 */
	bool dynamicEval() const;

	const std::string operatorName() const {return fOperatorPrototype;}
};


//____________________________________________________________________________________________
/*!
 * \brief base classes for all IExpression nodes , it hide the template of IExprArg<T>
 */
class IExprArgBase: public libmapping::smartable, public evaluable{
protected:
	bool fCopyEval, fDynamicEval;
	std::string* fEvaluated;

public:
	virtual std::string accept(evaluator* e) =0;
	virtual std::string accept(constEvaluator* e) const = 0;

	void switchToDynamic(bool dynamicEval = true){fDynamicEval = dynamicEval;}
	void switchToCopy(bool copyEval = true){fCopyEval = copyEval;}
	inline bool copyEval() const {return fCopyEval;}
	inline bool dynamicEval() const {return fDynamicEval;}
	inline bool pureStaticEval() const {return !fCopyEval && !fDynamicEval;}

	inline virtual SIExprArg copy() const {return SIExprArg(0);}

	inline std::string getEvaluated() const {return *fEvaluated;}
	inline void setEvaluated(std::string evaluated){*fEvaluated = evaluated;}
	inline std::string* evaluated() const {return fEvaluated;}	//as evaluated is more a buffer than a real attribute
																//the pointer isn't const so evaluated can be change even in a const IExpression
	inline virtual void recursiveClearEvaluated() const {fEvaluated->clear();}

	virtual ~IExprArgBase(){delete fEvaluated;}

protected:
	IExprArgBase();
};




//____________________________________________________________________________________________
/*!
 * \brief Containers class used to store any arguments of any type passed to an operator, including operators (through IExprOperator).
 */
template <typename argType>
class IExprArg: public IExprArgBase{
private:
    argType fArg;

public:
	IExprArg(argType arg): IExprArgBase(), fArg(arg){}
	argType getArg(){return fArg;}
	void setArg(argType arg){fArg = arg;}

	inline SIExprArg copy() const{
		IExprArgBase* r = new IExprArg<argType>(fArg);
		if(fDynamicEval)
			r->switchToDynamic();
		if(fCopyEval)
			r->switchToCopy();
		r->setEvaluated(getEvaluated());
		return r;
	}

	inline void recursiveClearEvaluated() const {fEvaluated->clear();}


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



//SIExprArg specification for SIExprOperator
template<>
inline SIExprArg IExprArg<SIExprOperator>::copy() const
{
	IExprOperator* op = new IExprOperator(fArg->operatorName(), fArg->arg1()->copy(), fArg->arg2()->copy());
	IExprArgBase* r = new IExprArg<SIExprOperator>(op);
	if(fDynamicEval)
		r->switchToDynamic();
	r->setEvaluated(getEvaluated());
	return r;
}

//_________________________________________________
template<>
inline void IExprArg<SIExprOperator>::recursiveClearEvaluated()  const
{
	fArg->arg1()->recursiveClearEvaluated();
	fArg->arg2()->recursiveClearEvaluated();
	fEvaluated->clear();
}


std::ostream&	operator << (std::ostream& out, const SIExpression& exprArg);

} //end namespace






#endif // EXPRESSIONNODE_H
