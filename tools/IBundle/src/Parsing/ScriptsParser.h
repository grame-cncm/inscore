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

/*!
 * \brief The ScriptsParser class recursivly parse inscore scripts to generate the corresponding ParsedData:
 *		- the list of the messages composing the parsed scripts,
 *		- the list of all their dependencies (script or ressources)
 *		- which of them is the main script
 * ScriptsParser can read scripts from the disk or from an ibundle (without uncompresssing it).
 * To ensure a better compatibility with INScore, the creation of the messages list is done by the INScore Parser (ITLParser),
 * However the interpretation of the messages (finding dependencies, rootpath change...) is done through a separated algorythm (the analysMsg method).
 * Any modification related to importing external ressources into INScore should be replacated in the analyseMsg method
 * to ensure the compatibility of dependencies detectin when creating bundles.
 */
class ScriptsParser{

	ParsedData &fData;
	std::map<std::string, std::string> fRootPaths;
	std::string fDefaultRootPath;
	bool		fParseJS;
	qarchive::QArchive* fArchive;
	BundleLog *fLog = 0;

	bool fVerbose = false;

public:
	/*!
	 * \brief Read a script stored on the disk (and any scripts it imports).
	 * \param inputFile The main script.
	 * \param result A reference to the Parsed Data
	 * \param defaultRootPath The default root path that should be used when no root path is specified in the script (Application root path).
	 * \param parseJS Specify if the javascript sections should be parsed to detect ressources.
	 * \param log The log object used to print the result of the parsing.
	 * \param verbose If set, ScriptParser will print a detailled description of the dependencies of each script, if not, it will only print the list of ressources and parsed scripts.
	 * \return True if the parsing completes without error, false otherwise (invalid inscore script, loaded script not found...)
	 */
	static bool read(std::string inputFile, ParsedData &result, const std::string &defaultRootPath, bool parseJS=false, BundleLog* log = 0, const bool &verbose=false);
	/*!
	 * \brief Read the scripts stored in an ibundle (the main script will be /main.inscore).
	 * \param archive The archive that should be parsed.
	 * \param result A reference to the parsed data.
	 * \return True if the parsing completes without error, false otherwise (invalid inscore script)
	 */
	static bool readArchive(qarchive::QArchive *archive, ParsedData &result);

protected:
	//! \brief Construct a ScriptParser that will parse scripts stored on the disk
	ScriptsParser(ParsedData &data, std::string defaultRootPath):fData(data), fDefaultRootPath(defaultRootPath), fArchive(0){}
	//! \brief Construct a ScriptParser that will parse scripts stored in an ibundle
	ScriptsParser(ParsedData &data, qarchive::QArchive* archive):fData(data), fDefaultRootPath(""), fArchive(archive){}

	/*!
	 * \brief Read a specific scripts on the disk or on the archive.
	 * Reading a script consist in:
	 *	- Parsing the script using the ITLParser to retreive the corresponding messages list (using parseScript(script, &msgs) )
	 *  - Analysing every message to detect import of ressources or scripts and to eliminate useless messages and updating the ParsedData
	 *  - Reading every imported scripts found in the previous step that has not been read yet.
	 * \param script The file path to the script.
	 * \return True if the parsing completes without error, false otherwise (invalid inscore script, dependencies not found...)
	 */
	bool readScript(std::string script);

	/*!
	 * \brief Parse a specific script using the INScore parser ITLParser to generate a message list
	 * \param inputFile The path to the input script
	 * \param msgs A reference to the parsed message list
	 * \return True if the parser returned without error.
	 */
	bool parseScript(std::string inputFile, inscore::SIMessageList &msgs);
	/*!
	 * \brief Analyse a specific message, searching for import of external ressources or scripts.
	 * This method try to replicate INScore behaviour when importing files, any modification of this behaviour should be also included in the method.
	 * \param msg The input message.
	 * \param result A reference to the result of the analysis.
	 * \param acceptRootPathMsg If set, the rootPath change will be taken into account (ScriptParser handle application and scenes rootpaths).
	 * \param contextObject The name of the context object: the object that should normally evaluate the message.
	 * \return False if the message should be ignored when regenerating the script (root path changes), false otherwise.
	 */
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
