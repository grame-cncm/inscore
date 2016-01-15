#ifndef BUNDLEGENERATOR_H
#define BUNDLEGENERATOR_H

#include "ParsedData.h"

namespace itlbundle{

class BundlePackager
{

	ParsedData& fInputData;

public:
	static bool bundle(ParsedData& scripts, const std::string& outputPath);
protected:

	BundlePackager(ParsedData& inputData):fInputData(inputData){}

	void mapNames(std::map<std::string, std::string>& namesMap);
	std::string generateScript(std::__cxx11::string scriptName);

private:
	static inline bool ignoreCmd(std::string itlCmd);
};

} // End namespace

#endif // BUNDLEGENERATOR_H
