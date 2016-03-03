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
#include "ParsedData.h"

#include <deelx.h>

#include "ExprInfo.h"



namespace ibundle {

void ParsedData::addScript(std::string name, inscore::SIMessageList msgs)
{
	fScripts[name] = msgs;
	auto it = fFilesMap.find(name);
	if(it==fFilesMap.end())
		fFilesMap[name] = name;
}

void ParsedData::addRessource(std::string name)
{
	if(fRessources.insert(name))
		fFilesMap[name] = name;
}

void ParsedData::addScriptMsg(std::string script, SRessourceRef msg)
{
	fScriptsRessources.insert(script, msg);
}

void ParsedData::addRessourceMsg(std::string ressource, SRessourceRef msg)
{
	if( fRessources.insert(ressource, msg) )
		fFilesMap[ressource] = ressource;
}

bool ParsedData::containsScript(std::string name) const
{
	return fScripts.count(name);
}

inscore::extvector<std::string> ParsedData::scriptNames() const
{
	inscore::extvector<std::string> vector;
	for(auto it=fScripts.begin(); it!=fScripts.end(); it++)
		vector.push_back(it->first);
	return vector;
}

inscore::extvector<std::string> ParsedData::ressourceNames() const
{
	inscore::extvector<std::string> vector;
	for(auto it=fRessources.begin(); it!=fRessources.end(); it++)
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
void ParsedData::applyFileMap(TStringMap fileMap)
{
	if(fileMap.empty() || fFilesMap.empty())
		return;

	auto itLocal = fFilesMap.begin();
	for(auto itNewMap=fileMap.begin(); itNewMap!=fileMap.end(); itNewMap++){
		auto itTemp = itLocal;
		while(itLocal->first!=itNewMap->first && itLocal != fFilesMap.end())
			itLocal++;

		if(itLocal==fFilesMap.end()){
			itLocal = itTemp;
		}else{
			itLocal->second = itNewMap->second;
			fScriptsRessources.renameRsc(itLocal->first, itLocal->second);
			fRessources.renameRsc(itLocal->first, itLocal->second);
		}
	}
}

std::string ParsedData::generateScript(std::string name) const
{
	std::stringstream script;
	auto scriptIt = fScripts.find(name);
	if(scriptIt == fScripts.end())
		return "";
	inscore::SIMessageList msgs = scriptIt->second;

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
		} else {
			msg->print(script);
			script<<std::endl;
		}

	}

	return script.str();
}

void ParsedData::simplifyPaths(int charToDelete)
{
	if(mainScript.empty() && fScripts.empty() && fRessources.empty())
		return;

	TScripts simplifiedScripts;
	RessourceMap simplifiedRessources;
	RessourceMap simplifiedRscScripts;
	std::map<std::string, std::string> simplifiedFilesMap;

	for(auto it = fScripts.begin(); it != fScripts.end(); it++)
		simplifiedScripts[it->first.substr(charToDelete)] = it->second;

	for(auto it = fRessources.begin(); it != fRessources.end(); it++)
		simplifiedRessources[it->first.substr(charToDelete)] = it->second;

	for(auto it = fScriptsRessources.begin(); it != fScriptsRessources.end(); it++)
		simplifiedRscScripts[it->first.substr(charToDelete)] = it->second;

	for(auto it = fFilesMap.begin(); it != fFilesMap.end(); it++){
		std::string  simplifiedFile = it->first.substr(charToDelete);
		if(it->first == it->second)
			simplifiedFilesMap[simplifiedFile] = simplifiedFile;
		else
			simplifiedFilesMap[simplifiedFile] = it->second;
	}


	fScripts.swap(simplifiedScripts);
	fRessources.swap(simplifiedRessources);
	fScriptsRessources.swap(simplifiedRscScripts);
	fFilesMap.swap(simplifiedFilesMap);

	if(mainScript.empty() && !fScripts.empty())
			mainScript = fScripts.begin()->first;

	if(!mainScript.empty()){
		fMainPath += mainScript.substr(0,charToDelete);
		mainScript = mainScript.substr(charToDelete);
	}else
		fMainPath += fRessources.begin()->first.substr(0,charToDelete);
}

void ParsedData::simplifyPaths()
{
	if(fRessources.empty()&&fScripts.empty())
		return;

	//  -- search for common path trunk --
	std::vector<std::string> trunk = splitPath(fRessources.size()? fRessources.begin()->first: fScripts.begin()->first);
	int commonPath = trunk.size()-1;

	for(auto it = fRessources.cbegin(); it != fRessources.cend(); it++){
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

	for(auto it = fScripts.cbegin(); it != fScripts.cend(); it++){
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
std::list<SRessourceRef> &RessourceMap::insert(std::__cxx11::string name, bool &newList)
{
	auto it = find(name);
	if(it==end()){
		std::list<SRessourceRef> l;
		(*this)[name] = l;
		newList = true;
		return (*this)[name];
	}
	newList = false;
	return it->second;
}

bool RessourceMap::insert(std::string name)
{
	bool newList;
	insert(name, newList);
	return newList;
}

bool RessourceMap::insert(std::string name, SRessourceRef param)
{
	bool newList;
	insert(name, newList).push_back(param);
	return newList;
}

bool RessourceMap::insert(std::string name, std::list<SRessourceRef> params)
{
	if(!params.size())
		return false;

	auto it = find(name);
	if(it==end()){
		(*this)[name] = params;
		return true;
	}

	for(auto itParams = params.begin(); itParams!=params.end(); itParams++)
		it->second.push_back(*itParams);

	return false;
}

void RessourceMap::insert(const RessourceMap &ressources)
{
	for(auto it = ressources.begin(); it!=ressources.end(); it++)
		insert(it->first, it->second);
}

bool RessourceMap::renameRsc(std::string search, std::string replace)
{
	auto itSearch = find(search);
	if(itSearch==end())
		return false;

	std::list<SRessourceRef> list = itSearch->second;

	for(auto it = list.begin(); it!=list.end(); it++)
		(*it)->setValue(replace);

	return true;
}

//__________________________________________________________
//----------------------------------------------------------
MsgParam::MsgParam(inscore::SIMessage msg, int paramID)
	:RessourceRef(msg), fParamID(paramID)
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
ExprParam::ExprParam(inscore::SIMessage msg, int paramID, std::string initialPath)
	: MsgParam(msg, paramID), fInitialValue(initialPath)
{}

void ExprParam::setValue(const std::string& value){
	inscore::SIExpression expr;
	if(!fMsg->param(fParamID,expr))
		return;
	inscore::ExprInfo::searchAndReplace<inscore::filepath>(expr, fInitialValue, value);
	fInitialValue = value;
}

std::string ExprParam::getValue() const
{
	return fInitialValue;
}

//__________________________________________________________
//----------------------------------------------------------
JsParam::JsParam(inscore::SIMessage msg, std::string initialPath)
	: RessourceRef(msg), fPath(initialPath)
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
