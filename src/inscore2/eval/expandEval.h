
#ifndef __expandEval__
#define __expandEval__

#include <exception>

#include "INode.h"

namespace inscore2
{

typedef struct {
	std::string header;	// the address header
	std::string from;	// the expansion start string
	std::string to;		// the expansion end string
	std::string var1;	// optional variable
	std::string var2;	// optional variable
} TExpandInfos;


class expandEvalException: public std::exception
{
	std::string fWhat;
	public:
			 expandEvalException(const char* reason) : fWhat(reason) {}
	virtual ~expandEvalException() noexcept {}
	virtual const char* what() const noexcept { return fWhat.c_str(); }
};

class expandEval
{
	static TExpandInfos getExpand 	(const std::string& str);
	static SINode 		evalExpand 	(const SINode& node);
	static SINode 		evalNode 	(const SINode& node);

	public:
				 expandEval() {}
		virtual ~expandEval() {}

		static SINode 	eval 	 (const SINode& node) throw(expandEvalException);
};

} // end namespace

#endif
