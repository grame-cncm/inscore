
#ifndef __parseEval__
#define __parseEval__

#include <exception>

#include "INode.h"

namespace inscore2
{

class parseEvalException: public std::exception
{
	std::string fWhat;
	public:
			 parseEvalException(const char* reason) : fWhat(reason) {}
	virtual ~parseEvalException() noexcept {}
	virtual const char* what() const noexcept { return fWhat.c_str(); }
};

class parseEval
{

	static SINode 	evalSlash 	(const SINode& node);
	static SINode 	evalSeq 	(const SINode& node);
	static SINode 	evalPar 	(const SINode& node);
	static SINode 	evalNode 	(const SINode& node);
	static SINode 	evalExpand	(const SINode& node);
	static SINode 	evalForest	(const SINode& node);

	public:
				 parseEval() {}
		virtual ~parseEval() {}

		static SINode eval 	(const SINode& node) throw(parseEvalException);
		static SINode seq	(const SINode& n1, const SINode& n2);
};

} // end namespace

#endif
