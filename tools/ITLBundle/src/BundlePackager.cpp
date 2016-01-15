#include <sstream>
#include <iostream>
#include "BundlePackager.h"


using namespace qarchive;

namespace itlbundle {

bool BundlePackager::bundle(ParsedData &scripts, const std::string &outputPath, bool overwrite)
{
	BundlePackager b(scripts);

	b.mapNames();

	SQArchive a = qarchive::QArchive::emptyArchive();
	b.setupArchive(a);

	return b.writeArchive(a,outputPath, overwrite);
}

//__________________________________________________________
//----------------------------------------------------------
void BundlePackager::mapNames()
{
	int id=1;

	for(auto it=fInputData.scripts.begin(); it!=fInputData.scripts.end(); it++){
		if(fInputData.isMainScript(it->first))
			fNamesMap["main.inscore"] = it->first;
		else{
			std::stringstream name;
			name << id <<".inscore";
			fNamesMap[name.str()] = it->first;
			id++;
		}
	}

	for(auto it=fNamesMap.begin(); it!=fNamesMap.end(); it++)
		fInputData.scriptsRessources.renameRsc(it->second, it->first);

	id=0;
	for(auto it=fInputData.ressources.begin(); it!=fInputData.ressources.end(); it++){
		//Compute the new name with the extension
		int idExtSuffix = it->first.rfind('.');
		std::stringstream ss;
		ss << "Ressources/" << id <<"."<<it->first.substr(idExtSuffix+1);
		std::string name = ss.str();
		fNamesMap[name] = it->first;

		//Rename ressources
		std::list<SMsgParam> list = it->second;
		for(auto itList = list.begin(); itList!=list.end(); itList++)
			(*itList)->setValue(name);
		id++;
	}
}

void BundlePackager::setupArchive(qarchive::SQArchive &archive)
{
	//Create hierarchy
	archive->addDir("Export");
	archive->addDir("Ressources");

	std::string fileNames = "";
	//Add ressources and scripts
	for(auto it=fNamesMap.begin(); it!=fNamesMap.end(); it++){
		if(it->first.substr(0,11) != "Ressources/")
			archive->addTextFileStd(it->first, generateScript(it->second));
		else if(!archive->addFileStd(it->first, fInputData.mainPath+it->second))
			std::cerr<<"Ressource: \""<<fInputData.mainPath+it->second<<"\" does not exist!"<<std::endl;

		fileNames +=  it->first + "\t" + it->second+"\n";
	}

	//Add fileNames.map
	archive->addTextFileStd("fileNames.map", fileNames);
}

std::string BundlePackager::generateScript(std::string scriptName)
{

	std::stringstream script;
	inscore::SIMessageList msgs = fInputData.scripts.at(scriptName);

	for(int i=0; i<msgs->list().size(); i++){
		inscore::SIMessage msg = msgs->list().at(i);

		if(msg->address()=="/ITL/bundle"){
			if(msg->message()=="js"&&msg->size()){
				std::string js;
				if(msg->param(0, js)){
					if(js.find("\n")<js.size()){
						script<<"\n<?javascript\n"<<js<<"\n?>\n";
					}else
						script<<"<?javascript"<<js<<"?>";
				}
			}
		}else if(!ignoreCmd(msg->message())){
			msg->print(script);
			script<<std::endl;
		}

	}

	return script.str();
}

bool BundlePackager::writeArchive(SQArchive &archive, const std::__cxx11::string &outputPath, bool overwrite)
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
			return false;
		else
			return writeArchive(archive, outputPath, true);
		break;
	case WRONG_PERMISSIONS:
		std::cerr<<"Impossible to write in "<<outputPath<<std::endl;
		break;
	default:
		std::cerr<<"An error occurs during the bundle preparation..."<<std::endl;
		break;
	}
	return true;
}

bool BundlePackager::ignoreCmd(std::string itlCmd)
{
	return itlCmd == "rootPath";
}


} // End namespace
