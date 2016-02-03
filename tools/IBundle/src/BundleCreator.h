#ifndef BUNDLECREATOR_H
#define BUNDLECREATOR_H

#include "BundleLog.h"
#include "QArchive.h"

namespace ibundle {

class ReadingContext;



class BundleCreator
{
	BundleLog fLog;
	bool fShowHierarchy;
	bool fParseJS;
	bool fForceOverwrite=false;
	std::string fDefaultRootPath;

public:
	BundleCreator();

	/*!
	 * \brief bundle a INScore script with all its dependency
	 * \param inputFile the path to the input file
	 * \return	true if succeed, false otherwise
	 */
	bool bundle(std::string inputFile, std::string outputFile);
	bool failSafeBundle(std::string inputFile, std::string outputFile);

	void setVerbose(bool verbose = true);
	void setDefaultRootPath(std::string rootPath);
	void setShowHierarchy(bool showHierarchy = true);
	void setForceOverwrite(bool forceOverwrite = true);
	void setParseJS(bool parseJS = true);

protected:
	bool writeArchive(qarchive::SQArchive& archive, const std::string& outputPath, bool overwrite);
};

} //end namespace
#endif // BUNDLECREATOR_H
