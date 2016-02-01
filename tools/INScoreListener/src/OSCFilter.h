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

	bool match(const osc::ReceivedMessage& m, bool verbose = false) const;
};

class OSCFilterContext{
private:
	std::vector<osc::ReceivedMessageArgument> _args;
	const osc::ReceivedMessage& _message;
	const bool _verbose;
public:
	OSCFilterContext(const osc::ReceivedMessage& m, bool verbose=false);
	const osc::ReceivedMessageArgument* arg(size_t i) const;
	const char* address() const {return _message.AddressPattern();}
	bool verbose() const {return _verbose;}
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

class OSCFilterExprArg{
protected:
	unsigned int _argIndex;
	float _float;
	std::string _string;
	bool _isNbr;

	OSCFilterExprArg();

public:

	static OSCFilterExprArg* fromArg(unsigned int argIndex);
	static OSCFilterExprArg* fromString(std::string string);
	static OSCFilterExprArg* fromNbr(float nbr);

	bool toString(std::string &s, const OSCFilterContext& filter) const;
	bool toNbr   (float &nbr, const OSCFilterContext& filter)       const;
	bool isNbr   (const OSCFilterContext& filter) const;

	unsigned int	argIndex()	const {return _argIndex;}
	float			nbr()		const {return _float;}
	std::string		string()	const {return _string;}
};

class OSCFilterExpr: public OSCFilterNode{
public:
	enum Operator{
	kEQUAL,
	kNOTEQUAL,
	kGREATER,
	kGREATEREQUAL,
	kLOWER,
	kLOWEREQUAL
	};

	OSCFilterExpr(Operator op, const OSCFilterExprArg& argL, const OSCFilterExprArg& argR);
	virtual ~OSCFilterExpr(){}
protected:
	bool eval(OSCFilterContext &filter);
private:
	Operator _operator;
	const OSCFilterExprArg _argL, _argR;
};

class OSCFilterAddress: public OSCFilterNode{
private:
	inscore::OSCRegexp _addressRegExp;
	const char* _address;
public:
	OSCFilterAddress(std::string addressRegExp):_addressRegExp(addressRegExp.c_str()), _address(addressRegExp.c_str()){}
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

