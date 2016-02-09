/*
  INScore Project

  Copyright (C) 2009,2016  Grame

  This library is free software; you can redistribute it and/or
  modify it under the terms of the GNU Lesser General Public
  License as published by the Free Software Foundation; either
  version 2.1 of the License, or (at your option) any later version.

  This library is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
  Lesser General Public License for more details.

  You should have received a copy of the GNU Lesser General Public
  License along with this library; if not, write to the Free Software
  Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA

  Grame Research Laboratory, 11 cours de Verdun Gensoul 69002 Lyon - France
  research@grame.fr
*/
#ifndef SCRIPTSPARSER_H
#define SCRIPTSPARSER_H

#include <set>

#include "ParsedData.h"
#include "QArchive.h"


namespace ibundle {

class AnalyseResult;
class BundleLog;

class ScriptsParser{

	ParsedData &fData;
	std::map<std::string, std::string> fRootPaths;
	std::string fDefaultRootPath;
	bool		fParseJS;
	qarchive::SQArchive fArchive;
	BundleLog *fLog = 0;

	bool fVerbose = false;

public:
	static bool read(std::string inputFile, ParsedData &result, const std::string &defaultRootPath, bool parseJS, BundleLog* log = 0, const bool &verbose=false);
	static bool readArchive(ParsedData &result, qarchive::SQArchive archive);

	static bool ignoreCmd(std::string ITLCmd);

protected:
	ScriptsParser(ParsedData &data, std::string defaultRootPath):fData(data), fDefaultRootPath(defaultRootPath), fArchive(0){}
	ScriptsParser(ParsedData &data, qarchive::SQArchive archive):fData(data), fDefaultRootPath(""), fArchive(archive){}

	bool readScript(std::string script);

	bool parseScript(std::string inputFile, inscore::SIMessageList &msgs);
	bool analyseMsg(const inscore::SIMessage &msg, AnalyseResult& result, bool acceptRootPathMsg=true, std::string contextObject="");
	/*!
	 * \brief	absolutePath return the absolute path of path according to the rootPath matching an address
	 *			if path or rootPath is an url, return an empty string.
	 * \param path relative or absolute path
	 * \param address address to match rootPath
	 * \param rootPaths list of rootPaths
	 * \return the absolute path of path or empty string if url
	 */
	std::string absolutePath(std::string path, std::string address);

	inline bool isFileObject(std::string ITLCmd);
	bool isurl(std::string path);


};

class AnalyseResult{
public:
	std::set<std::string> scripts, ressources;
	std::string currentScript;

	AnalyseResult(std::string script):currentScript(script){}
};



} // End namespace

#endif // SCRIPTSPARSER_H
