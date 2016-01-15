#ifndef TDUMMYJS_H
#define TDUMMYJS_H

#include <string>
#include <sstream>
#include "IMessage.h"
#include "smartpointer.h"

namespace inscore{
class TEnv;
typedef libmapping::SMARTP<TEnv> STEnv;
}

namespace itlbundle {

class TDummyJs
{
	std::string fRootPath;
	std::string fVars;
public:
	TDummyJs();
	virtual ~TDummyJs();

	void	Initialize	();
	void	bindEnv		(const inscore::STEnv& env);

	bool	bindEnv  (std::stringstream& s, const std::string& name, const inscore::IMessage::argPtr& val);
	void	bindEnv  (std::stringstream& s, const std::string& name, const inscore::IMessage::argslist& values);

	bool	eval		(int line, const char* script, std::string& outStr);
	void	setRootPath	(const char* path);
};



} // End namespace
#endif // TDUMMYJS_H
