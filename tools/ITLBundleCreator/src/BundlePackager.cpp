#include <sstream>

#include "BundlePackager.h"

using namespace inscore;

namespace itlbundle {

bool BundlePackager::bundle(ParsedData &scripts, const std::string &outputPath)
{
	BundlePackager b(scripts);

	std::map<std::string, std::string> namesMap;
	b.mapNames(namesMap);

	for(auto it=scripts.scripts.begin(); it!=scripts.scripts.end(); it++){
		std::cout << " ******* "<<it->first<<" ******* \n";
		std::cout << b.generateScript(it->first);
	}

	return true;
}

//__________________________________________________________
//----------------------------------------------------------
void BundlePackager::mapNames(std::map<std::string, std::string>& namesMap)
{
	int id=1;

	for(auto it=fInputData.scripts.begin(); it!=fInputData.scripts.end(); it++){
		if(fInputData.isMainScript(it->first))
			namesMap["main.inscore"] = it->first;
		else{
			std::stringstream name;
			name << id <<".inscore";
			namesMap[name.str()] = it->first;
			id++;
		}
	}

	for(auto it=namesMap.begin(); it!=namesMap.end(); it++)
		fInputData.scriptsRessources.renameRsc(it->second, it->first);

	id=0;
	for(auto it=fInputData.ressources.begin(); it!=fInputData.ressources.end(); it++){
		//Compute the new name with the extension
		int idExtSuffix = it->first.rfind('.');
		std::stringstream ss;
		ss << id <<"."<<it->first.substr(idExtSuffix+1);
		std::string name = ss.str();
		namesMap[name] = it->first;

		//Rename ressources
		std::list<SMsgParam> list = it->second;
		for(auto itList = list.begin(); itList!=list.end(); itList++)
			(*itList)->setValue(name);
		id++;
	}
}

std::string BundlePackager::generateScript(std::string scriptName)
{

	std::stringstream script;
	inscore::SIMessageList msgs = fInputData.scripts.at(scriptName);

	for(int i=0; i<msgs->list().size(); i++){
		SIMessage msg = msgs->list().at(i);

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

bool BundlePackager::ignoreCmd(std::string itlCmd)
{
	return itlCmd == "rootPath";
}


} // End namespace
