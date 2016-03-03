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
#include <iostream>
#include <istream>
#include <fstream>
#include <deelx.h>


#include "ITLparser.h"
#include "ExprInfo.h"
#include "BundleLog.h"

#include "ScriptsParser.h"
#include "TParseEnv.h"

namespace ibundle{


class BParseEnv : public inscore::TParseEnv {
	inscore::TJSEngine fJavascriptEngine;
	public:
				 BParseEnv () { fJavascriptEngine.Initialize(); }
		virtual ~BParseEnv() {}
		inscore::TJSEngine*	getJSEngine()	{ return &fJavascriptEngine; }
		inscore::TLua*		getLUAEngine()	{ return 0; }

};


bool ScriptsParser::read(std::string inputFile, ParsedData &result, const std::string& defaultRootPath, bool parseJS, BundleLog* log, const bool& verbose)
{
	ScriptsParser p(result, defaultRootPath);
	p.fLog = log;
	p.fVerbose = verbose;
	p.fParseJS = parseJS;

	std::string absoluteFile = p.absolutePath(inputFile, "/");
	if(!absoluteFile.empty())
		inputFile = absoluteFile;

	result.mainScript = inputFile;

	if(!p.readScript(inputFile))
		return false;

	return true;
}

bool ScriptsParser::readArchive( qarchive::QArchive* archive, ParsedData &result)
{
	ScriptsParser p(result, archive);

	result.mainScript = "main.inscore";

	if(!p.readScript("main.inscore"))
		return false;

	return true;
}


//__________________________________________________________
//----------------------------------------------------------
using namespace inscore;
using namespace std;

bool ScriptsParser::readScript(string script)
{
	//Check script validity
	SIMessageList msgs;
	if(!parseScript(script, msgs))
		return false;

	if(fVerbose&&fLog) fLog->subSection(script);
	fData.addScript(script, msgs);

	if(!msgs || !msgs->list().size()){
		if(fVerbose&&fLog) fLog->exitSubSection();
		return true;
	}

	//Analyse messages
	AnalyseResult r(script);
	auto msg = msgs->list().begin();
	while(msg!=msgs->list().end()){
		if(analyseMsg(*msg, r, false))
			msg++;
		else
			msg = msgs->list().erase(msg);
	}

	//Print log
	if(fVerbose && fLog){
		*fLog<<"Ressources:"<<(r.ressources.size()?"\n":" no\n");
		for(auto it = r.ressources.begin(); it != r.ressources.end(); it++)
			*fLog<<" - "<<*it<<"\n";

		*fLog<<"Imported scripts:"<<(r.scripts.size()?"\n":" no\n");
		for(auto it = r.scripts.begin(); it != r.scripts.end(); it++)
			*fLog<<" - "<<*it<<"\n";
	}

	for(auto it = r.scripts.begin(); it != r.scripts.end(); it++){
		std::string loadedScript = *it;

		//Recursively read loaded scripts
		if(!fData.containsScript(loadedScript)){
			bool scriptValid = readScript(loadedScript);

			if(!scriptValid)
				return false;
		}
	}
	if(fVerbose&&fLog) fLog->exitSubSection();
	return true;
}

//______________________________________________
bool ScriptsParser::parseScript(std::string inputFile, SIMessageList &msgs)
{
	//open file
	std::istream* ifs=0;

	if(fArchive){
		QByteArray data;
		if(!fArchive->readFileStd(inputFile,data)){
			if(fLog)fLog->error("cannot open file \""+inputFile+"\"");
			return false;
		}
		std::stringstream* ss = new std::stringstream;
		*ss<<data.toStdString();
		ifs = ss;
	}else{
		std::ifstream* fileStream = new std::ifstream(inputFile.c_str());
		if(!fileStream->is_open()){
			if (fLog)fLog->error("cannot open file \"" + inputFile + "\"");
			delete fileStream;
			return false;
		}
		ifs= fileStream;
	}

	BParseEnv penv;
	inscore::ITLparser p(ifs, 0, &penv);
	msgs = p.parse();

	delete ifs;

	if(!p.fParseSucceed){
		if(fLog) fLog->error("\""+inputFile+"\" is an incorrect INScore script.");
		return false;
	}

	return true;
}

//______________________________________________
bool ScriptsParser::analyseMsg(const SIMessage &msg, AnalyseResult &result, bool acceptRootPathMsg, std::string contextObject)
{
	if(!msg->size())
		return true;

	std::string address = msg->address();
	if(address.at(0)=='.')
		address = contextObject + address.substr(1);

	// --- File and Path specific commands ---
	if(!msg->message().empty()){

		if(msg->message()=="load"){
			if(msg->size()==1){
				std::string script;
				if(msg->param(0,script) ){
					script = absolutePath(script, address);
					if(script.size()>8){
						if(script.substr(script.size()-8)==".inscore"){			// Script
							result.scripts.insert(script);
							fData.addScriptMsg(script, new MsgParam(msg, 0));
						}else if(script.substr(script.size()-8)==".ibundle"){	// IBundle
							result.ressources.insert(script);
							fData.addRessourceMsg(script, new MsgParam(msg, 0));
						}else
							fLog->warn(script+" is not a valid inscore script or bundle.");
					}
				}
				return true;
			}

		}else if(msg->message()=="rootPath"){
			if(msg->size()==1){
				std::string rootPath;
				if(msg->param(0,rootPath)){
					if(!acceptRootPathMsg){
						if(fLog){
							fLog->warn("In \""+result.currentScript+"\"\n         "+msg->address()+" rootPath "+rootPath+";");
							fLog->warn("changing rootPath inside parameters message is not handled!");
						}
						return false;
					}

					rootPath = absolutePath(rootPath, address);

					if(!rootPath.empty())
						fRootPaths[address] = rootPath;
				}
				return false;
			}

		}else if(msg->message()=="save" || msg->message()=="export"){
			if(fLog){
				fLog->warn("In \""+result.currentScript+"\"\n         "+msg->address()+" "+msg->message()+" ...");
				fLog->warn("Save and export message have undefined behaviour in bundles...");
			}

		}else if(msg->message()=="set"){
			if(msg->size()==2){
				std::string cmd;
				if(msg->param(0, cmd) && isFileObject(cmd)){
					std::string path;
					if(msg->param(1, path)){
						if(ParsedData::isFilePath(path)){
							path = absolutePath(path, address);
							if(!path.empty()){
								fData.addRessourceMsg(path, new MsgParam(msg, 1));
								result.ressources.insert(path);
							}
						}
					}
				}
			}

		}else if(msg->message()=="js" && address=="/ITL/bundle"){
			if(fParseJS){
				//Parse javascript
				std::string js;
				if(!msg->param(0,js))
					return false;
				std::string jsPath;
				size_t id = ParsedData::findFileInJS(js, jsPath);
				while(id!=std::string::npos){
					std::string path = absolutePath(jsPath, "/ITL");
					if(!path.empty()){
						fData.addRessourceMsg(path, new JsParam(msg, jsPath));
						result.ressources.insert(path);
					}
					id = ParsedData::findFileInJS(js, jsPath, id+jsPath.size()+1);
				}
				return true;
			}else
				fLog->warn("A javascript section was found but will not be parsed.\n     Use -js to parse javascript sections.");

		}

	}

	// --- Search for ressources in remaining parameters---
	for (int i = 0; i < msg->size(); ++i) {
		SIMessageList msgList; SIExpression expr;
		if(msg->param(i, msgList)){
			//Search in message list arguments
			auto itMsg = msgList->list().begin();
			while(itMsg!=msgList->list().end()){
				if(analyseMsg(*itMsg, result, false, address))
					itMsg++;
				else
					itMsg = msgList->list().erase(itMsg);
			}
		}else if(msg->param(i, expr)){
			std::set<std::string> exprDependencies = inscore::ExprInfo::fileDependency(expr);
			for(auto it = exprDependencies.begin(); it != exprDependencies.end(); it++){
				std::string path = absolutePath(*it,address);
				if(!path.empty()){
					fData.addRessourceMsg(path, new ExprParam(msg, i, *it));
					result.ressources.insert(path);
				}
			}
		}
	}

	return true;
}

//__________________________________________________________
//----------------------------------------------------------
std::string ScriptsParser::absolutePath(std::string path, std::string address)
{
	if(fArchive)
		return path;

	//_________CHECK IF ABSOLUTE____________
	if(*(path.begin())=='/')
		return path;
#ifdef WIN32
	if ((path[1] == ':') && (path[2] == '\\'))
		return path;
#endif

	//_________CHECK IF URL_________________
	if(isurl(path))
		return "";

	//_________COMPUTING ROOTPATH____________
	std::string rootPath= fDefaultRootPath;

	//only keep /ITL/scene from the address
	while(!address.empty()){
		//check if the scene has a specific rootPath for the current address
		auto rootPathIt= fRootPaths.find(address);
		if(rootPathIt != fRootPaths.end()){
			rootPath = rootPathIt->second;
			break;
		}

		//if no rootPath is defined for the object try its parent
		size_t id = address.find_last_of('/');
		address = address.substr(0, id);
	}
	//_________APPLYING ROOTPATH____________

	//if rootPath is url return nothing
	if(isurl(rootPath)){
		return "";
	}

	//else generate absolute path
	std::string currentFile;
	std::string result = rootPath;
	while(!path.empty()){
		size_t idPathSep;
		idPathSep = path.find('/');
		if(idPathSep<path.size()){
			currentFile = path.substr(0,idPathSep);
			path = path.substr(idPathSep+1);
		}else{
			currentFile = path;
			path = "";
		}

		if(currentFile=="." || currentFile=="")
			continue;
		else if(currentFile==".."){
			if(result.size()==1){
				//if the current Path is the root directory, we can't go back -> abort
				if(fLog) fLog->error(path + " is not a valid path, using the rootPath: "+rootPath);
				return "";
			}
			size_t idPathSepResult = result.find_last_of('/');
			result = result.substr(0, idPathSepResult);
		}else{
			if(result.at(result.size( )-1)!='/')
				result+='/';
			result +=currentFile;
		}
	}
	return result;
}


//__________________________________________________________
//----------------------------------------------------------
bool ScriptsParser::isFileObject(std::string ITLCmd)
{
	return ITLCmd == "txtf" || ITLCmd == "htmlf" || ITLCmd=="video"
			|| ITLCmd=="img" || ITLCmd == "gmnf" || ITLCmd == "musicxmlf" || ITLCmd == "pianorollf"
			|| ITLCmd == "svgf" || ITLCmd == "file" || ITLCmd == "faustdspf"
			|| ITLCmd == "gmn" //to support score expression
			;
}

//______________________________________________
bool ScriptsParser::isurl(std::string path)
{
	std::string start = path.substr(0, 7);
	return start=="http://" || start=="https:/";
}


} // End namespace
