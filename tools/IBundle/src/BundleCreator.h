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
