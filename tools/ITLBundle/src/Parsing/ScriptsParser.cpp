#include <istream>
#include <fstream>
#include <deelx.h>


#include "ITLparser.h"
#include "ExprInfo.h"
#include "BundleLog.h"

#include "ScriptsParser.h"

namespace itlbundle{

bool ScriptsParser::read(std::string inputFile, ParsedData &result, const std::string& defaultRootPath, BundleLog* log, const bool& verbose)
{
	ScriptsParser p(result, defaultRootPath);
	p.fLog = log;
	p.fVerbose = verbose;

	std::string absoluteFile = p.absolutePath(inputFile, "/");
	if(!absoluteFile.empty())
		inputFile = absoluteFile;

	result.setMainScript(inputFile);

	if(!p.readScript(inputFile))
		return false;

	p.simplifyPath();

	return true;
}


//__________________________________________________________
//----------------------------------------------------------
using namespace inscore;

bool ScriptsParser::readScript(std::string script)
{
	//Check script validity

	SIMessageList msgs;

	if(!parseScript(script, msgs))
		return false;

	if(fVerbose&&fLog) fLog->subSection(script);
	fData.scripts[script] = msgs;

	if(!msgs || !msgs->list().size()){
		if(fVerbose&&fLog) fLog->exitSubSection();
		return true;
	}

	//Analyse messages
	AnalyseResult r(script);
	for (auto msg = msgs->list().begin(); msg != msgs->list().end(); msg++)
		analyseMsg(*msg, r);


	//Print log

	if(fVerbose&&fLog){
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
		if(!fData.scripts.count(loadedScript)){
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
	std::ifstream ifs(inputFile);
	if(!ifs.is_open()){
		if(fLog)fLog->error("\""+inputFile+"\" is not reachable.");
		return false;
	}

	//parse with INScore parser to check validity

	inscore::TJSEngine javascriptEngine;
#if defined V8ENGINE || defined QTJSENGINE
	javascriptEngine.Initialize();
#endif


	inscore::ITLparser p(&ifs, 0, &javascriptEngine,0);
	msgs = p.parse();

	if(!p.fParseSucceed){
		if(fLog) fLog->error("\""+inputFile+"\" is an incorrect INScore script.");
		return false;
	}

	return true;
}

//______________________________________________
void ScriptsParser::analyseMsg(const SIMessage &msg, AnalyseResult &result, bool acceptRootPathMsg)
{
	if(!msg->size())
		return;

	std::string address = msg->address();

	// --- File and Path specific commands ---
	if(!msg->message().empty()){
		if(msg->message()=="load"){
			if(msg->size()==1){
				std::string script;
				if(msg->param(0,script) ){
					script = absolutePath(script, address);
					if(!script.empty()){
						result.scripts.insert(script);
						fData.scriptsRessources.insert(script, new MsgParam(msg, 0));
					}
				}
				return;
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
						return;
					}

					rootPath = absolutePath(rootPath, address);

					if(!rootPath.empty())
						fRootPaths[address] = rootPath;
				}
				return;
			}
		}else if(msg->message()=="save" || msg->message()=="export"){
			if(fLog){
				fLog->warn("In \""+result.currentScript+"\"\n         "+msg->address()+" "+msg->message()+" ...");
				fLog->warn("Save and export message have undefined behaviour in bundles...");
			}

		}else if("set"){
			if(msg->size()==2){
				std::string cmd;
				if(msg->param(0, cmd) && isFileObject(cmd)){
					std::string path;
					if(msg->param(1, path)){
						if(isPath(path)){
							path = absolutePath(path, address);
							if(!path.empty()){
								fData.ressources.insert(path, new MsgParam(msg, 1));
								result.ressources.insert(path);
							}
						}
					}
				}
			}
		}

	}

	// --- Search for ressources in remaining parameters---
	for (int i = 0; i < msg->size(); ++i) {
		SIMessageList msgList; SIExpression expr;
		if(msg->param(i, msgList)){
			//Search in message list arguments
			for (int i = 0; i < (int)msgList->list().size(); ++i) {
				SIMessage msg = msgList->list().at(i);
				analyseMsg(msg, result, false);
			}
		}else if(msg->param(i, expr)){
			std::set<std::string> exprDependencies = inscore::ExprInfo::fileDependency(expr);
			for(auto it = exprDependencies.begin(); it != exprDependencies.end(); it++){
				std::string path = absolutePath(*it,address);
				if(!path.empty()){
					fData.ressources.insert(path, new ExprParam(msg, i, *it));
					result.ressources.insert(path);
				}
			}
		}
	}

	return;
}

//______________________________________________
void ScriptsParser::simplifyPath()
{
	if(fData.ressources.empty()&&fData.scripts.empty())
		return;


	inscore::extvector<std::string> rscNames = fData.ressourceNames();
	inscore::extvector<std::string> scriptNames = fData.scriptNames();

	//  -- search for common path trunk --
	std::vector<std::string> trunk = splitPath(rscNames.size()? rscNames.at(0): scriptNames.at(0));
	int commonPath = trunk.size()-1;

	for(size_t iRsc = 1; iRsc < rscNames.size(); iRsc++){
		std::vector<std::string> path = splitPath(rscNames.at(iRsc));

		int i=0;
		while ( i < commonPath && i < (int)path.size() ) {
			if(path.at(i)!=trunk.at(i)){
				break;
			}
			i++;
		}
		commonPath = i;
	}

	for(size_t iScript = 1; iScript < scriptNames.size(); iScript++){
		std::vector<std::string> path = splitPath(scriptNames.at(iScript));

		int i=0;
		while ( i < commonPath && i < (int)path.size() ) {
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
	fData.simplifyPaths(removable);
}

//__________________________________________________________
//----------------------------------------------------------
std::string ScriptsParser::absolutePath(std::string path, std::string address)
{
	//_________CHECK IF ABSOLUTE____________
	if(*(path.begin())=='/')
		return path;
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

//______________________________________________
std::vector<std::string> ScriptsParser::splitPath(std::string path)
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



//__________________________________________________________
//----------------------------------------------------------
bool ScriptsParser::isFileObject(std::string ITLCmd)
{
	return ITLCmd == "txtf" || ITLCmd == "htmlf" || ITLCmd=="video"
			|| ITLCmd=="img" || ITLCmd == "gmnf" || ITLCmd == "musicxmlf"
			|| ITLCmd == "svgf" || ITLCmd == "file" || ITLCmd == "faustdspf"
			|| ITLCmd == "gmn" //to support score expression
			;
}

//______________________________________________
bool ScriptsParser::ignoreCmd(std::string ITLCmd)
{
	return ITLCmd=="rootPath";
}

//______________________________________________
bool ScriptsParser::isurl(std::string path)
{
	std::string start = path.substr(0, 7);
	return start=="http://" || start=="https:/";
}
//______________________________________________
bool ScriptsParser::isPath(std::string string)
{
	//  /?(. .? /)*([^/?:*<>|']+/?)+.[^/\?:*<>|']+
	CRegexpT<char> fileRegex("/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+");

	return fileRegex.MatchExact(string.c_str()).IsMatched();
}

} // End namespace
