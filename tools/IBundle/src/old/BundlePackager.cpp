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
#include <sstream>
#include <iostream>
#include "BundlePackager.h"


using namespace qarchive;

namespace ibundle {

QArchive* BundlePackager::bundle(ParsedData &scripts)
{
//	BundlePackager b(scripts);
	BundlePackager b;

	b.mapNames();
	scripts.applyFileMap(b.fNamesMap);

	QArchive* a = qarchive::QArchive::emptyArchive();
	if(!b.setupArchive(a))
		return 0;

	return a;
}

//__________________________________________________________
//----------------------------------------------------------
void BundlePackager::mapNames()
{
//	int id=1;

//	for(auto it=fInputData.fScripts.begin(); it!=fInputData.fScripts.end(); it++){
//		if(fInputData.isMainScript(it->first))
//			fNamesMap[it->first] = "main.inscore";
//		else{
//			std::stringstream name;
//			name << id <<".inscore";
//			fNamesMap[it->first] = name.str();
//			id++;
//		}
//	}

//	id=0;
//	for(auto it=fInputData.fRessources.begin(); it!=fInputData.fRessources.end(); it++){
//		//Compute the new name with the extension
//		size_t idExtSuffix = it->first.rfind('.');
//		std::stringstream name;
//		name << "Ressources/" << id <<"."<<it->first.substr(idExtSuffix+1);
//		fNamesMap[it->first] = name.str();
//		id++;
//	}
}

bool BundlePackager::setupArchive(qarchive::QArchive* /*archive*/)
{
	//Create hierarchy
//	archive->changeDir("/");
//	archive->addDir("Export");
//	archive->addDir("Ressources");

//	std::string fileNames = "";
//	//Add ressources and scripts
//	for(auto it=fNamesMap.begin(); it!=fNamesMap.end(); it++){
//		if(it->second.size()<12 || it->second.substr(0,11) != "Ressources/")
//			archive->addTextFileStd(it->second, fInputData.generateScript(it->first), true);
//		else if(!archive->addFileStd(it->second, fInputData.mainPath()+it->first, true)){
//			std::cerr<<"Ressource: \""<<fInputData.mainPath()+it->first<<"\" does not exist!"<<std::endl;
//			return false;
//		}

//		fileNames +=  it->second + "\t" + it->first+"\n";
//	}

//	//Add fileNames.map
//	archive->addTextFileStd("bundleMap.txt", fileNames);
	return true;
}




} // End namespace
