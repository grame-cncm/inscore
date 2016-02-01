#include "OSCFilter.h"
#include <iostream>

namespace inscorelistener{

OSCFilter::OSCFilter(OSCFilterNode *root)
	:_root(root)
{

}

OSCFilter::~OSCFilter(){delete _root;}

bool OSCFilter::match(const osc::ReceivedMessage &m, bool verbose) const
{
	OSCFilterContext c(m, verbose);
	return _root->match(c);
}

/********************************************************
 *		    OSCFilterContext			*
 * *****************************************************/

OSCFilterContext::OSCFilterContext(const osc::ReceivedMessage &m, bool verbose)
	:_message(m), _verbose(verbose)
{
	osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
	while(arg!=m.ArgumentsEnd())
	_args.push_back(*(arg++));
}

const osc::ReceivedMessageArgument *OSCFilterContext::arg(size_t i) const
{
	if(_args.size()<=i)
		return 0;
	return &_args.at(i);
}

/********************************************************
 *		    OSCFilterExpr			*
 * *****************************************************/


OSCFilterExpr::OSCFilterExpr(OSCFilterExpr::Operator op, const OSCFilterExprArg &argL, const OSCFilterExprArg &argR)
	:_operator(op), _argL(argL), _argR(argR)
{}


bool OSCFilterExpr::eval(OSCFilterContext &filter)
{

	float nbrL=0, nbrR=0;
	bool isNbr = _argL.toNbr(nbrL,filter);
	if(isNbr != _argR.toNbr(nbrR, filter))	//Type mismatch
		return _operator == OSCFilterExpr::kNOTEQUAL;

	std::string sL="", sR="";
	if(!isNbr){
		if( _operator!=OSCFilterExpr::kNOTEQUAL && _operator!=OSCFilterExpr::kEQUAL ){
			if(filter.verbose()){
				std::cerr<<"Inequality only support numbers as arguments, ";
				if(_argL.argIndex()!=-1){
					std::cerr<<"%"<<_argL.argIndex();
					if(_argR.argIndex()!=-1)
						std::cerr<<" and %"<<_argR.argIndex()<<" are strings."<<std::endl;
					else
						std::cerr<<" is a string"<<std::endl;
				}else if(_argR.argIndex()!=-1)
					std::cerr<<"%"<<_argR.argIndex()<<" is a string"<<std::endl;
			}
			return false;
		}
		if( !_argL.toString(sL, filter) || !_argR.toString(sR, filter))
			return false;
	}

	switch(_operator){
	case OSCFilterExpr::kEQUAL:
	if(isNbr)
		return nbrL == nbrR;
	return sL == sR;

	case OSCFilterExpr::kNOTEQUAL:
		if(isNbr)
			return nbrL != nbrR;
		return sL != sR;

	case OSCFilterExpr::kGREATER:
		return nbrL > nbrR;

	case OSCFilterExpr::kGREATEREQUAL:
		return nbrL >= nbrR;

	case OSCFilterExpr::kLOWER:
		return nbrL < nbrR;

	case OSCFilterExpr::kLOWEREQUAL:
		return nbrL <= nbrR;
	}

	return false;
}

/********************************************************
 *		    OSCFilterAddress			*
 * *****************************************************/

bool OSCFilterAddress::eval(OSCFilterContext &filter)
{
	bool r =_addressRegExp.match(filter.address());
	if(!r)	//Si l'addresse du message ne match pas on vérifie que ce n'est pas une regex
		r = inscore::OSCRegexp(filter.address()).match(_address);

	return r;
}

/********************************************************
 *		    OSCFilterLogical			*
 * *****************************************************/
bool OSCFilterLogical::eval(OSCFilterContext &filter)
{
	bool lNodeValue = _lNode->match(filter);
	if(!lNodeValue && _and)
	return false;
	if(lNodeValue && !_and)
	return true;

	return _rNode->match(filter);
}

/********************************************************
 *		    OSCFilterExprArg							*
 * *****************************************************/
OSCFilterExprArg::OSCFilterExprArg()
{
	_argIndex = -1;
	_string = "";
	_float = 0;
	_isNbr = false;
}

OSCFilterExprArg *OSCFilterExprArg::fromArg(unsigned int argIndex)
{
	OSCFilterExprArg* arg = new OSCFilterExprArg();
	arg->_argIndex = argIndex;
	return arg;
}

OSCFilterExprArg *OSCFilterExprArg::fromString(std::string string)
{
	OSCFilterExprArg* arg = new OSCFilterExprArg();
	arg->_string = string;
	return arg;
}

OSCFilterExprArg *OSCFilterExprArg::fromNbr(float nbr)
{
	OSCFilterExprArg* arg = new OSCFilterExprArg();
	arg->_isNbr = true;
	arg->_float = nbr;
	return arg;
}


bool OSCFilterExprArg::toString(std::string &s, const OSCFilterContext &filter) const
{
	if(_argIndex != -1){
		const osc::ReceivedMessageArgument* arg = filter.arg(_argIndex);
		if(!arg)
			return false;

		if(!arg->IsString())
			return false;
		s = std::string(arg->AsStringUnchecked());
	}else{
		if(_isNbr)
			return false;
		s = _string;
	}
	return true;
}

bool OSCFilterExprArg::toNbr(float &nbr, const OSCFilterContext &filter) const
{
	if(_argIndex != -1){
		const osc::ReceivedMessageArgument* arg = filter.arg(_argIndex);
		if(!arg)
			return false;

		if(arg->IsFloat())
			nbr = arg->AsFloatUnchecked();
		else if(arg->IsInt32())
			nbr = (float)arg->AsInt32Unchecked();
		else
			return false;
	}else{
		if(!_isNbr)
			return false;
		nbr = _float;
	}
	return true;
}


}//End namespace
