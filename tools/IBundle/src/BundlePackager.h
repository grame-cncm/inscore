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
#ifndef BUNDLEGENERATOR_H
#define BUNDLEGENERATOR_H

#include <string>

#include "ParsedData.h"
#include "QArchive.h"

namespace ibundle{

class BundlePackager
{

	std::map<std::string, std::string> fNamesMap;
	ParsedData& fInputData;

public:
	static qarchive::SQArchive bundle(ParsedData& scripts);
protected:

	BundlePackager(ParsedData& inputData):fInputData(inputData){}

	void mapNames();
	bool setupArchive(qarchive::SQArchive& archive);

};

} // End namespace

#endif // BUNDLEGENERATOR_H
