#ifndef BUNDLECREATOR_H
#define BUNDLECREATOR_H

#include <string>
#include <map>
#include <set>
#include <istream>

#include "ITLparser.h"

#include "BundleLog.h"

namespace itlbundle {

class BundleCreator
{
	BundleLog fLog;
	bool fShowHierarchy;
	std::string fOutputPath;
	std::string fDefaultRootPath;

	std::set<std::string> fImportedScripts;
	std::set<std::string> fImportedRessources;
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
	void setDefaultRootPath(std::string rootPath);
	void setShowHierarchy(bool showHierarchy = true);

private:

	bool readScript(std::string inputFile);
	bool parseScript(std::string inputScript, inscore::SIMessageList &msgs);
	void analyseMsg(const inscore::SIMessage &msg, std::set<std::string> &importedRessources, std::set<std::string> &importedScripts, std::map<std::string, std::string> &rootPaths);
	inline bool isFileObject(std::string ITLCmd);

	void simplifyPath();
	std::vector<std::string> splitPath(std::string path);

	bool isurl(std::string path);
	bool isLocalPath(std::string string);
	std::string absolutePath(std::string path, std::string address, const std::map<std::string, std::string> &rootPaths);
};

} //end namespace
#endif // BUNDLECREATOR_H
