#ifndef SCRIPTSPARSER_H
#define SCRIPTSPARSER_H

#include <set>

#include "ParsedData.h"


namespace itlbundle {

class AnalyseResult;
class BundleLog;

class ScriptsParser{

	ParsedData &fData;
	std::map<std::string, std::string> fRootPaths;
	std::string fDefaultRootPath;
	BundleLog *fLog = 0;

	bool fVerbose = false;

public:
	static bool read(std::string inputFile, ParsedData &result, const std::string &defaultRootPath, BundleLog* log = 0, const bool &verbose=false);


protected:
	ScriptsParser(ParsedData &data, std::string defaultRootPath):fData(data), fDefaultRootPath(defaultRootPath){}

	bool readScript(std::string script);

	bool parseScript(std::string inputFile, inscore::SIMessageList &msgs);
	void analyseMsg(const inscore::SIMessage &msg, AnalyseResult& result, bool acceptRootPathMsg=true);
	void simplifyPath();
	/*!
	 * \brief	absolutePath return the absolute path of path according to the rootPath matching an address
	 *			if path or rootPath is an url, return an empty string.
	 * \param path relative or absolute path
	 * \param address address to match rootPath
	 * \param rootPaths list of rootPaths
	 * \return the absolute path of path or empty string if url
	 */
	std::string absolutePath(std::string path, std::string address);

	std::vector<std::string> splitPath(std::string path);

	inline bool isFileObject(std::string ITLCmd);
	bool isurl(std::string path);
	bool isPath(std::string string);


};

class AnalyseResult{
public:
	std::set<std::string> scripts, ressources;
	std::string currentScript;

	AnalyseResult(std::string script):currentScript(script){}
};



} // End namespace

#endif // SCRIPTSPARSER_H
