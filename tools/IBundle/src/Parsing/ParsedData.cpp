#include "ParsedData.h"

#include <deelx.h>

#include "ExprInfo.h"
#include "ScriptsParser.h"


namespace ibundle {

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

std::vector<std::string> ParsedData::splitPath(std::string path)
{
	std::vector<std::string> result;

	size_t id;
	path = path.substr(1); //removing the first /
	while(!path.empty()){
		id = path.find('/');

		if(id==std::string::npos){
			result.push_back(path);
			return result;
		}

		result.push_back(path.substr(0,id));
		path = path.substr(id+1);
	}

	return result;
}

size_t ParsedData::findFileInJS(const std::string &js, std::string &filePath, size_t startID)
{
	while(startID < js.size()){
		size_t beginDQuoteID = js.find('"', startID);
		size_t beginSQuoteID = js.find('\'', startID);
		size_t beginQuoteID = std::min(beginDQuoteID, beginSQuoteID);
		if(beginQuoteID == std::string::npos)
			return std::string::npos;

		beginQuoteID++;
		bool dQuote = beginDQuoteID < beginSQuoteID;

		size_t endQuoteID = beginQuoteID;
		while(endQuoteID < js.size()){
			endQuoteID = js.find(dQuote?'"':'\'', endQuoteID);
			if(endQuoteID == std::string::npos)
				return std::string::npos;
			if(js.at(endQuoteID-1)!='\\')
				break;
			endQuoteID++;
		}
		endQuoteID--;

		if(dQuote){
			std::string quoted = js.substr(beginQuoteID, endQuoteID-beginDQuoteID);
			if(isFilePath(quoted)){
				filePath = quoted;
				return beginQuoteID;
			}
		}

		startID = endQuoteID+2;
	}
	return std::string::npos;
}

bool ParsedData::isFilePath(std::string string)
{
	//  ^/?(. .? /)*([^/?:*<>|']+/?)+.[^/\?:*<>|']+$
	CRegexpT<char> fileRegex("^/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+$");

	return fileRegex.MatchExact(string.c_str()).IsMatched();
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

	if(fMainScript.empty())
		fMainScript = scripts.begin()->first;

	fMainPath += fMainScript.substr(0,charToDelete);
	fMainScript = fMainScript.substr(charToDelete);
}

void ParsedData::simplifyPaths()
{
	if(ressources.empty()&&scripts.empty())
		return;

	//  -- search for common path trunk --
	std::vector<std::string> trunk = splitPath(ressources.size()? ressources.begin()->first: scripts.begin()->first);
	int commonPath = trunk.size()-1;

	for(auto it = ressources.cbegin(); it != ressources.cend(); it++){
		std::vector<std::string> path = splitPath(it->first);

		int i=0;
		while ( i < commonPath && i < (int)path.size()-1 ) {
			if(path.at(i)!=trunk.at(i)){
				break;
			}
			i++;
		}
		commonPath = i;
	}

	for(auto it = scripts.cbegin(); it != scripts.cend(); it++){
		std::vector<std::string> path = splitPath(it->first);

		int i=0;
		while ( i < commonPath && i < (int)path.size()-1 ) {
			if(path.at(i)!=trunk.at(i))
				break;
			i++;
		}
		commonPath = i;
	}

	if(trunk.empty())
		return;

	std::string trunkPath = "/";

	for (int i = 0; i < commonPath; ++i)
		trunkPath += trunk.at(i)+"/";

	size_t removable = trunkPath.size();
	simplifyPaths(removable);
}



//__________________________________________________________
//----------------------------------------------------------
std::list<SMsgParam>& RessourceMap::insert(std::string name)
{
	auto it = find(name);
	if(it==end()){
		std::list<SMsgParam> l;
		(*this)[name] = l;
		return (*this)[name];
	}

	return it->second;
}

void RessourceMap::insert(std::string name, SMsgParam param)
{
	insert(name).push_back(param);
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

void MsgParam::setValue(const std::string& value)
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

void ExprParam::setValue(const std::string& value){
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

//__________________________________________________________
//----------------------------------------------------------
JsParam::JsParam(inscore::SIMessage msg, std::string path)
	: MsgParam(msg, 0), fPath(path)
{}

void JsParam::setValue(const std::string& value)
{
	std::string js;
	if(!fMsg->param(0, js))
		return;
	std::string path;
	size_t id = ParsedData::findFileInJS(js, path);
	while(id != std::string::npos){
		if(path==fPath){
			js.replace(id,path.size(), value);
			id = ParsedData::findFileInJS(js, path, id + value.size()+ 1);
		}else
			id = ParsedData::findFileInJS(js, path, id + path.size() + 1);
	}

	fMsg->setparam<std::string>(0, js);
	fPath = value;
}

std::string JsParam::getValue() const
{
	return fPath;
}





} // End namespace
