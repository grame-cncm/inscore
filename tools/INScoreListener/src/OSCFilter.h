#ifndef OSCFILTER_H
#define OSCFILTER_H

#include <vector>
#include <string>

#include "osc/OscReceivedElements.h"
#include "OSCRegexp.h"

namespace inscorelistener{

class OSCFilterNode;
class OSCFilterContext;

class OSCFilter
{
	OSCFilterNode* _root;
public:
	OSCFilter(OSCFilterNode* root);
	~OSCFilter();

	bool match(const osc::ReceivedMessage& m) const;

};

class OSCFilterContext{
private:
	std::vector<osc::ReceivedMessageArgument> _args;
	const osc::ReceivedMessage& _message;
public:
	OSCFilterContext(const osc::ReceivedMessage& m);
	const osc::ReceivedMessageArgument* arg(size_t i) const;
	const char* address() const {return _message.AddressPattern();}
};

class OSCFilterNode{
	bool _not;
public:
	void setNot(bool isNot = true){_not = isNot;}
	bool match(OSCFilterContext& filter){return _not != eval(filter);}

	virtual ~OSCFilterNode(){}

protected:
	OSCFilterNode():_not(false){}
	virtual bool eval(OSCFilterContext& filter)=0;
};

class OSCFilterExpr: public OSCFilterNode{
public:
	enum Operator{
	EQUAL,
	NOTEQUAL,
	GREATER,
	GREATEREQUAL,
	LOWER,
	LOWEREQUAL
	};


	static OSCFilterNode* filterArg(Operator op, unsigned int argIndex, float floatValue);
	static OSCFilterNode* filterArg(Operator op, unsigned int argIndex, std::string stringValue);

	virtual ~OSCFilterExpr(){}
protected:
	OSCFilterExpr(Operator op, unsigned int argIndex, float floatValue, std::string stringValue);
	bool eval(OSCFilterContext &filter);
private:
	Operator _operator;
	unsigned int _argIndex;
	float _float;
	std::string _string;


};

class OSCFilterAddress: public OSCFilterNode{
private:
	inscore::OSCRegexp _addressRegExp;
public:
	OSCFilterAddress(std::string addressRegExp):_addressRegExp(addressRegExp.c_str()){}
	virtual ~OSCFilterAddress(){}
protected:
	bool eval(OSCFilterContext &filter);
};

class OSCFilterLogical: public OSCFilterNode{
private:
	bool _and;
	OSCFilterNode *_lNode, *_rNode;

public:
	static OSCFilterNode* andFilter(OSCFilterNode* lNode, OSCFilterNode* rNode){return new OSCFilterLogical(true, lNode, rNode);}
	static OSCFilterNode* orFilter(OSCFilterNode* lNode, OSCFilterNode* rNode){return new OSCFilterLogical(false, lNode, rNode);}

	 bool eval(OSCFilterContext &filter);	 
	 virtual ~OSCFilterLogical(){delete _lNode; delete _rNode;}

protected:
	OSCFilterLogical(bool isAnd, OSCFilterNode* lNode, OSCFilterNode* rNode){_and = isAnd;_lNode=lNode;_rNode=rNode;}
};

}//End namespace

#endif // OSCFILTER_H

