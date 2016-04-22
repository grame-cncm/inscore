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
#ifndef BUNDLECREATOR_H
#define BUNDLECREATOR_H

#include "BundleLog.h"
#include "QArchive.h"

namespace ibundle {

class ReadingContext;
class ParsedData;

/*!
 * \brief The BundleCreator class create an ibundle from a inscore script or a list of ressources.
 */
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
	 * \brief bundle INScore scripts with all theor dependency
	 * \param inputFile the path to the main script
	 * \return	true if succeed, false otherwise
	 */
	bool bundle(std::string inputFile, std::string outputFile);
	/*!
	 * \brief Create a ibundle from a list of files. The main script should be the first file of the list.
	 * \param inputFile the path to the text file containing the list.
	 * \return	true if succeed, false otherwise
	 */
	bool failSafeBundle(std::string inputFile, std::string outputFile);

	/*!
	 * \brief If verbose is set, ingormations will be printed at each step of the bundle creation
	 */
	void setVerbose(bool verbose = true);
	/*!
	 * \brief Specify the default application root path that should be used to parse scripts.
	 */
	void setDefaultRootPath(std::string rootPath);
	/*!
	 * \brief If verbose is true, setting shoowHierarchy to true display the exact dependency needed by each script while parsing.
	 */
	void setShowHierarchy(bool showHierarchy = true);
	/*!
	 * \brief If forceOverwrite is set to true, if an ibundle file already exists overwrite it without asking.
	 */
	void setForceOverwrite(bool forceOverwrite = true);
	/*!
	 * \brief If parseJS is set to true, javascript section in scripts will be read to search for ressources.
	 */
	void setParseJS(bool parseJS = true);

protected:
	/*!
	 * \brief Add to the archive all the scripts and ressources stored in data according to data.filesMap();
	 * \param data The model containing the lists of scripts and ressources to add to the archive
	 * \param archive The archive that should be modify.
	 * \return True on success, false otherwise (file already exist in the archive, path incorect...)
	 */
	bool setupArchive(const ParsedData &data, qarchive::QArchive *archive);
	/*!
	 * \brief Compress an archive to the disk
	 * \param archive The archive that should be compressed to the disk.
	 * \param outputPath The path to the new ibundle.
	 * \param overwrite If set to true, existing ibundle corresponding to outputPath will be overwrite without aksing.
	 * \return True on success, false otherwise (wrong path, permissions...)
	 */
	bool writeArchive(qarchive::QArchive *archive, const std::string& outputPath, bool overwrite);

	/*!
	 * \brief Modify the map of an ParsedData to rename scripts and ressources with numbers and places ressources in a separate folders
	 * \param inputData The data to modify.
	 */
	void mapNames(ParsedData &inputData);
};

} //end namespace
#endif // BUNDLECREATOR_H
