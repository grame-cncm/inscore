#ifndef BUNDLECREATOR_H
#define BUNDLECREATOR_H

#include "BundleLog.h"

namespace itlbundle {

class ReadingContext;



class BundleCreator
{
	BundleLog fLog;
	bool fShowHierarchy;
	bool fForceOverwrite=false;
	std::string fDefaultRootPath;

public:
	BundleCreator();

	/*!
	 * \brief bundle a INScore script with all its dependency
	 * \param inputFile the path to the input file
	 * \return	0 if succeed
	 *			-1 if inputFile is unreachable
	 */
	int bundle(std::string inputFile, std::string outputFile);


	void setVerbose(bool verbose = true);
	void setDefaultRootPath(std::string rootPath);
	void setShowHierarchy(bool showHierarchy = true);
	void setForceOverwrite(bool forceOverwrite = true);

};

} //end namespace
#endif // BUNDLECREATOR_H
