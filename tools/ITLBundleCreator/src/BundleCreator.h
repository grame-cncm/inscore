#ifndef BUNDLECREATOR_H
#define BUNDLECREATOR_H

#include <string>
#include <istream>

#include "BundleLog.h"

namespace itlbundle {

class BundleCreator
{
	BundleLog fLog;
	std::string fOutputPath;

public:
	BundleCreator();

	/*!
	 * \brief bundle a INScore script with all its dependency
	 * \param inputFile the path to the input file
	 * \return	0 if succeed
	 *			-1 if inputFile is unreachable
	 */
	int bundle(std::string inputFile);


	void setVerbose(bool verbose = true);
	void setOutputPath(std::string outputPath);

private:

	bool parseFile(std::string inputFile);
	bool checkScript(std::string inputScript);
};

} //end namespace
#endif // BUNDLECREATOR_H
