#include <sstream>
#include <iostream>
#include "BundlePackager.h"


using namespace qarchive;

namespace itlbundle {

bool BundlePackager::bundle(ParsedData &scripts, const std::string &outputPath, bool overwrite)
{
	BundlePackager b(scripts);

	b.mapNames();
	scripts.applyNameMap(b.fNamesMap);

	SQArchive a = qarchive::QArchive::emptyArchive();
	if(!b.setupArchive(a))
		return false;

	return b.writeArchive(a,outputPath, overwrite);
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
	archive->addDir("Export");
	archive->addDir("Ressources");

	std::string fileNames = "";
	//Add ressources and scripts
	for(auto it=fNamesMap.begin(); it!=fNamesMap.end(); it++){
		if(it->second.substr(0,11) != "Ressources/")
			archive->addTextFileStd(it->second, fInputData.generateScript(it->first));
		else if(!archive->addFileStd(it->second, fInputData.mainPath+it->first)){
			std::cerr<<"Ressource: \""<<fInputData.mainPath+it->first<<"\" does not exist!"<<std::endl;
			return false;
		}

		fileNames +=  it->second + "\t" + it->first+"\n";
	}

	//Add fileNames.map
	archive->addTextFileStd("bundleMap.txt", fileNames);
	return true;
}

bool BundlePackager::writeArchive(SQArchive &archive, const std::string &outputPath, bool overwrite)
{
	QArchiveError e = archive->compressStd(outputPath, overwrite);

	std::string r;
	switch(e){
	case NO_ERROR:
		return true;
	case FILE_EXIST:
		std::cout<<"File already exist, do you want to overwrite? [O/n]   ";
		std::cin>>r;
		if(r!="n")
			return writeArchive(archive, outputPath, true);
		else
			return false;
		break;
	case WRONG_PERMISSIONS:
		std::cerr<<"Impossible to write in "<<outputPath<<std::endl;
		break;
	default:
		std::cerr<<"An error occurs during the bundle preparation..."<<std::endl;
		break;
	}
	return false;
}


} // End namespace
