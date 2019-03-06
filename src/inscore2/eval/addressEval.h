
#ifndef __addressEval__
#define __addressEval__

#include <exception>

#include "INode.h"

namespace inscore2
{

class addressEvalException: public std::exception
{
	std::string fWhat;
	public:
			 addressEvalException(const char* reason) : fWhat(reason) {}
	virtual ~addressEvalException() noexcept {}
	virtual const char* what() const noexcept { return fWhat.c_str(); }
};

class addressEval
{
	static SINode evalSlash (const SINode& node);
	static SINode evalNode (const SINode& node);

	public:
				 addressEval() {}
		virtual ~addressEval() {}

		static SINode 	eval 	(const SINode& node) throw(addressEvalException);
};

} // end namespace

#endif
