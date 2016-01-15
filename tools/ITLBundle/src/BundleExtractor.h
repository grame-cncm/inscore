#ifndef BUNDLEEXTRACTOR_H
#define BUNDLEEXTRACTOR_H

#include <string>
#include "QArchive.h"

namespace itlbundle {

class BundleExtractor
{

	bool fForceOverwrite = false;

public:
	BundleExtractor(){}
	void setForceOverwrite(bool forceOverwrite=true){fForceOverwrite=forceOverwrite;}

	bool extract(std::string bundleFile, std::string outputFolder = "");

	bool writeFiles(qarchive::SQArchive& archive, std::string outputFolder, bool overwrite);
};

} // End namespace

#endif // BUNDLEEXTRACTOR_H
