#ifndef BUNDLECREATOR_H
#define BUNDLECREATOR_H

#include <string>
#include <map>
#include <set>
#include <utility>
#include <istream>

#include "ITLparser.h"

#include "BundleLog.h"

namespace itlbundle {

class ReadingContext;
template <class T> struct stringpairless{
	bool operator() (const std::pair<std::string, T>& x, const std::pair<std::string, T>& y) const
	{return x.first < y.first;}
	typedef std::pair<std::string, T> first_argument_type;
	typedef std::pair<std::string, T> second_argument_type;
	typedef bool result_type;
};
typedef std::set <std::pair<std::string,inscore::SIMessageList> , stringpairless<inscore::SIMessageList>> scriptSet;


class BundleCreator
{
	BundleLog fLog;
	bool fShowHierarchy;
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

private:

	bool readScript(ReadingContext& context);
	bool parseScript(std::string inputScript, inscore::SIMessageList &msgs);
	void analyseMsg(const inscore::SIMessage &msg, ReadingContext &context);
	inline bool isFileObject(std::string ITLCmd);

	void simplifyPath(ReadingContext &context);
	std::vector<std::string> splitPath(std::string path);

	bool isurl(std::string path);
	bool isPath(std::string string);

	/*!
	 * \brief	absolutePath return the absolute path of path according to the rootPath matching an address
	 *			if path or rootPath is an url, return an empty string.
	 * \param path relative or absolute path
	 * \param address address to match rootPath
	 * \param rootPaths list of rootPaths
	 * \return the absolute path of path or empty string if url
	 */
	std::string absolutePath(std::string path, std::string address, const ReadingContext &context);
};


class ReadingContext{
public:
	scriptSet scripts;
	std::set<std::string> ressources;
	std::map<std::string, std::string> rootPaths;
	bool acceptRootPathMsg = true;
	std::string currentScript;

	ReadingContext(std::string script=""):currentScript(script){}
};

} //end namespace
#endif // BUNDLECREATOR_H
