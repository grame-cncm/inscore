#include "ExprInfo.h"

#include "ScriptsParser.h"

#include "ParsedData.h"

namespace itlbundle {

inscore::extvector<std::string> ParsedData::scriptNames() const
{
	inscore::extvector<std::string> vector;
	for(auto it=scripts.begin(); it!=scripts.end(); it++)
		vector.push_back(it->first);
	return vector;
}

inscore::extvector<std::string> ParsedData::ressourceNames() const
{
	inscore::extvector<std::string> vector;
	for(auto it=ressources.begin(); it!=ressources.end(); it++)
		vector.push_back(it->first);
	return vector;
}

//__________________________________________________________
//----------------------------------------------------------
void ParsedData::applyNameMap(std::map<std::string, std::string> nameMap)
{
	for(auto it=nameMap.begin(); it!=nameMap.end(); it++){
		scriptsRessources.renameRsc(it->first, it->second);
		ressources.renameRsc(it->first, it->second);
	}
}

std::string ParsedData::generateScript(std::string name)
{
	std::stringstream script;
	inscore::SIMessageList msgs = scripts.at(name);

	for(size_t i=0; i<msgs->list().size(); i++){
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
		} else if(!ScriptsParser::ignoreCmd(msg->message())){
			msg->print(script);
			script<<std::endl;
		}

	}

	return script.str();
}

void ParsedData::simplifyPaths(int charToDelete)
{
	TScripts simplifiedScripts;
	RessourceMap simplifiedRessources;
	RessourceMap simplifiedRscScripts;

	for(auto it = scripts.begin(); it != scripts.end(); it++)
		simplifiedScripts[it->first.substr(charToDelete)] = it->second;

	for(auto it = ressources.begin(); it != ressources.end(); it++)
		simplifiedRessources[it->first.substr(charToDelete)] = it->second;

	for(auto it = scriptsRessources.begin(); it != scriptsRessources.end(); it++)
		simplifiedRscScripts[it->first.substr(charToDelete)] = it->second;


	scripts = simplifiedScripts;
	ressources = simplifiedRessources;
	scriptsRessources = simplifiedRscScripts;

	mainPath += fMainScript.substr(0,charToDelete);
	fMainScript = fMainScript.substr(charToDelete);
}


//__________________________________________________________
//----------------------------------------------------------
bool RessourceMap::insert(std::string name, SMsgParam param)
{
	auto it = find(name);
	if(it==end()){
		std::list<SMsgParam> l;
		l.push_back(param);
		(*this)[name] = l;
		return true;
	}

	it->second.push_back(param);
	return false;
}

void RessourceMap::insert(std::string name, std::list<SMsgParam> params)
{
	if(!params.size())
		return;

	auto it = find(name);
	if(it==end()){
		(*this)[name] = params;
		return;
	}

	for(auto itParams = params.begin(); itParams!=params.end(); itParams++)
		it->second.push_back(*itParams);

}

void RessourceMap::insert(const RessourceMap &ressources)
{
	for(auto it = ressources.begin(); it!=ressources.end(); it++)
		insert(it->first, it->second);
}

void RessourceMap::renameRsc(std::string search, std::string replace)
{
	auto itSearch = find(search);
	if(itSearch==end())
		return;

	std::list<SMsgParam> list = itSearch->second;

	for(auto it = list.begin(); it!=list.end(); it++)
		(*it)->setValue(replace);
}


//__________________________________________________________
//----------------------------------------------------------
MsgParam::MsgParam(inscore::SIMessage msg, int paramID)
	:fMsg(msg), fParamID(paramID)
{}

void MsgParam::setValue(std::string value)
{
	fMsg->setparam<std::string>(fParamID, value);
}

std::string MsgParam::getValue() const
{
	std::string r;
	if(fMsg->param(fParamID, r))
		return r;
	return "";
}


//__________________________________________________________
//----------------------------------------------------------
ExprParam::ExprParam(inscore::SIMessage msg, int paramID, std::string initialValue)
	: MsgParam(msg,paramID), fInitialValue(initialValue)
{}

void ExprParam::setValue(std::string value){
	inscore::SIExpression expr;
	if(!fMsg->param(fParamID,expr))
		return;
	inscore::ExprInfo::fileReplace(expr, fInitialValue, value);
	fInitialValue = value;
}

std::string ExprParam::getValue() const
{
	return fInitialValue;
}





} // End namespace
