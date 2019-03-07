
#ifndef __jsEval__
#define __jsEval__

#include <exception>

#include "TQtJs.h"
#include "INode.h"

namespace inscore2
{

class jsEvalException: public std::exception
{
	std::string fWhat;
	public:
			 jsEvalException(const char* reason) : fWhat(reason) {}
	virtual ~jsEvalException() noexcept {}
	virtual const char* what() const noexcept { return fWhat.c_str(); }
};

class jsEval
{
	inscore::TQtJs* fJavascript;
	
	SINode 	evalNode 		(const SINode& node);
	SINode 	evalJavascript	(const SINode& node);
	SINode 	evalForest		(const SINode& node);

	public:
				 jsEval(inscore::TQtJs* jsengine) : fJavascript(jsengine) {}
		virtual ~jsEval() {}

		SINode eval 	(const SINode& node) throw(jsEvalException);
};

} // end namespace

#endif
