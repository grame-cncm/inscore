#ifndef BUNDLEEXTRACTOR_H
#define BUNDLEEXTRACTOR_H

#include <string>
#include "QArchive.h"
#include "ScriptsParser.h"
#include "ParsedData.h"

namespace ibundle {

class BundleExtractor
{

	bool fForceOverwrite = false;
	bool fKeepOriginalPath = false;

public:
	BundleExtractor(){}
	void setForceOverwrite(bool forceOverwrite=true){fForceOverwrite=forceOverwrite;}
	void setKeepOriginalPath(bool keep=true){fKeepOriginalPath=keep;}

	bool extract(std::string bundleFile, std::string outputFolder = "");

	bool writeArchive(qarchive::SQArchive archive, std::string outputFolder, bool overwrite);
	bool writeMappedArchive(qarchive::SQArchive archive, ParsedData& script, const std::map<std::string,std::string>& map, std::string outputFolder);

protected:
	static bool readMapName(qarchive::SQArchive archive, std::map<std::string, std::string>& map);
};

} // End namespace

#endif // BUNDLEEXTRACTOR_H
