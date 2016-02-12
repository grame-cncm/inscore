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
#ifndef BUNDLEEXTRACTOR_H
#define BUNDLEEXTRACTOR_H

#include <string>
#include "QArchive.h"
#include "ScriptsParser.h"
#include "ParsedData.h"

namespace ibundle {

class BundleExtractor
{

	bool fForceOverwrite = false;
	bool fKeepOriginalPath = false;

public:
	BundleExtractor(){}
	void setForceOverwrite(bool forceOverwrite=true){fForceOverwrite=forceOverwrite;}
	void setKeepOriginalPath(bool keep=true){fKeepOriginalPath=keep;}

	bool extract(std::string bundleFile, std::string outputFolder = "");

	bool writeArchive(qarchive::QArchive *archive, std::string outputFolder, bool overwrite);
	bool writeMappedArchive(qarchive::QArchive *archive, ParsedData& script, const std::map<std::string,std::string>& map, std::string outputFolder);

protected:
	static bool readMapName(qarchive::QArchive *archive, std::map<std::string, std::string>& map);
};

} // End namespace

#endif // BUNDLEEXTRACTOR_H
