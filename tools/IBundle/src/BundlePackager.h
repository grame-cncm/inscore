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
	static bool bundle(ParsedData& scripts, const std::string& outputPath, bool overwrite=false);
protected:

	BundlePackager(ParsedData& inputData):fInputData(inputData){}

	void mapNames();
	bool setupArchive(qarchive::SQArchive& archive);

	bool writeArchive(qarchive::SQArchive& archive, const std::string& outputPath, bool overwrite = false);

};

} // End namespace

#endif // BUNDLEGENERATOR_H
