#ifndef BUNDLEGENERATOR_H
#define BUNDLEGENERATOR_H

#include <string>

#include "ParsedData.h"
#include "QArchive.h"

namespace ibundle{

class BundlePackager
{

	std::map<std::string, std::string> fNamesMap;
	ParsedData& fInputData;

public:
	static qarchive::SQArchive bundle(ParsedData& scripts);
protected:

	BundlePackager(ParsedData& inputData):fInputData(inputData){}

	void mapNames();
	bool setupArchive(qarchive::SQArchive& archive);

};

} // End namespace

#endif // BUNDLEGENERATOR_H
