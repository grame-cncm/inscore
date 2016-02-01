#include <sstream>
#include <iostream>
#include "BundlePackager.h"


using namespace qarchive;

namespace ibundle {

SQArchive BundlePackager::bundle(ParsedData &scripts)
{
	BundlePackager b(scripts);

	b.mapNames();
	scripts.applyNameMap(b.fNamesMap);

	SQArchive a = qarchive::QArchive::emptyArchive();
	if(!b.setupArchive(a))
		return 0;

	return a;
}

//__________________________________________________________
//----------------------------------------------------------
void BundlePackager::mapNames()
{
	int id=1;

	for(auto it=fInputData.scripts.begin(); it!=fInputData.scripts.end(); it++){
		if(fInputData.isMainScript(it->first))
			fNamesMap[it->first] = "main.inscore";
		else{
			std::stringstream name;
			name << id <<".inscore";
			fNamesMap[it->first] = name.str();
			id++;
		}
	}

	id=0;
	for(auto it=fInputData.ressources.begin(); it!=fInputData.ressources.end(); it++){
		//Compute the new name with the extension
		int idExtSuffix = it->first.rfind('.');
		std::stringstream name;
		name << "Ressources/" << id <<"."<<it->first.substr(idExtSuffix+1);
		fNamesMap[it->first] = name.str();
		id++;
	}
}

bool BundlePackager::setupArchive(qarchive::SQArchive &archive)
{
	//Create hierarchy
	archive->changeDir("/");
	archive->addDir("Export");
	archive->addDir("Ressources");

	std::string fileNames = "";
	//Add ressources and scripts
	for(auto it=fNamesMap.begin(); it!=fNamesMap.end(); it++){
		if(it->second.size()<12 || it->second.substr(0,11) != "Ressources/")
			archive->addTextFileStd(it->second, fInputData.generateScript(it->first), true);
		else if(!archive->addFileStd(it->second, fInputData.mainPath()+it->first, true)){
			std::cerr<<"Ressource: \""<<fInputData.mainPath()+it->first<<"\" does not exist!"<<std::endl;
			return false;
		}

		fileNames +=  it->second + "\t" + it->first+"\n";
	}

	//Add fileNames.map
	archive->addTextFileStd("bundleMap.txt", fileNames);
	return true;
}




} // End namespace
