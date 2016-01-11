#include <deelx.h>
#include <fstream>
#include <cmath>
#include <stdlib.h>

#include "ExprInfo.h"

#include "BundleCreator.h"


//#include "TQtJs.h"

namespace itlbundle{

using namespace inscore;

BundleCreator::BundleCreator()
{
	fShowHierarchy = false;
	fDefaultRootPath = std::string(getenv("HOME")) + "/";
}
//____________________________________________
int BundleCreator::bundle(std::string inputFile)
{
	fLog.section("Parsing \""+inputFile+"\"");
	fImportedScripts.clear();
	fImportedRessources.clear();
	fImportedScripts.insert(inputFile);

	if(!readScript(inputFile))
		return -1;

	simplifyPath();

	fLog.section("Discovered Files");

	fLog<<"Ressources:\n";
	for(auto it = fImportedRessources.begin(); it != fImportedRessources.end(); it++)
		fLog<<"  "<<*it<<"\n";

	fLog<<"Script:\n";
	for(auto it = fImportedScripts.begin(); it != fImportedScripts.end(); it++)
		fLog<<"  "<<*it<<"\n";


	return 0;
}

//__________________________________________________________
//----------------------------------------------------------
bool BundleCreator::readScript(std::string inputFile)
{
	//Check script validity

	SIMessageList msgs;

	if(!parseScript(inputFile, msgs))
		return false;

	if(!msgs || !msgs->list().size())
		return true;

	//Analyse messages
	std::set<std::string> ressourcesList;
	std::set<std::string> importedScripts;
	std::map<std::string,std::string> rootPaths;

	for (int idMsg = 0; idMsg < msgs->list().size(); ++idMsg) {
		SIMessage msg = msgs->list().at(idMsg);
		analyseMsg(msg, ressourcesList, importedScripts, rootPaths);
	}


	if(fShowHierarchy) fLog<<"Ressources:"<<"\n";
	for(auto it = ressourcesList.begin(); it != ressourcesList.end(); it++){
		if(fShowHierarchy) fLog<<" - "<<(*it)<<"\n";
		fImportedRessources.insert(*it);
	}

	if(fShowHierarchy) fLog<<"Imported scripts:"<<"\n";

	for(auto it = importedScripts.begin(); it != importedScripts.end(); it++){
		std::string script = *it;

		if(fShowHierarchy) fLog<<" - "<<script<<"\n";

		if(!fImportedScripts.count(script)){
			fImportedScripts.insert(script);
			if(fShowHierarchy) fLog.subSection(script);
			readScript(script);
			if(fShowHierarchy) fLog.exitSubSection();
		}
	}

	return true;
}

void BundleCreator::analyseMsg(const SIMessage &msg, std::set<std::string> &importedRessources, std::set<std::string> &importedScripts, std::map<std::string, std::string> &rootPaths)
{
	if(!msg->size())
		return;

	std::string address = msg->address();

	// --- File and Path specific commands ---
	if(!msg->message().empty()){
		if(msg->message()=="load"){
			if(msg->size()==1){
				std::string script;
				if(msg->param(0,script) && !isurl(script) ){
					script = absolutePath(script, address, rootPaths);
					if(!script.empty())
						importedScripts.insert(script);
				}
				return;
			}
		}else if(msg->message()=="rootPath"){
			if(msg->size()==1){
				std::string rootPath;
				if(msg->param(0,rootPath)){
					rootPath = absolutePath(rootPath, address, rootPaths);
					if(!rootPath.empty())
						rootPaths.insert({address, rootPath});
				}
				return;
			}
		}else if(msg->message()=="save" || msg->message()=="export"){
			/// TODO: Warn about root path change...
		}else if("set"){
			if(msg->size()==2){
				std::string cmd;
				if(msg->param(0, cmd) && isFileObject(cmd)){
					std::string path;
					if(msg->param(1, path)){
						if(isLocalPath(path))
							importedRessources.insert(absolutePath(path, address, rootPaths));
					}
				}
			}
		}

	}

	// --- Search for ressources ---
	for (int i = 0; i < msg->size(); ++i) {
		SIMessageList msgList; SIExpression expr;
		if(msg->param(i, msgList)){
			//Search in message list arguments
			for (int i = 0; i < msgList->list().size(); ++i) {
				SIMessage msg = msgList->list().at(i);
				analyseMsg(msg, importedRessources, importedScripts, rootPaths);
			}
		}else if(msg->param(i, expr)){
			std::set<std::string> exprDependencies = inscore::ExprInfo::fileDependency(expr);
			for(auto it = exprDependencies.begin(); it != exprDependencies.end(); it++)
				importedRessources.insert(absolutePath(*it,address,rootPaths));
		}
	}
}

inline bool BundleCreator::isFileObject(std::string ITLCmd)
{
	return ITLCmd == "txtf" || ITLCmd == "htmlf" || ITLCmd=="video"
			|| ITLCmd=="img" || ITLCmd == "gmnf" || ITLCmd == "musicxmlf"
			|| ITLCmd == "svgf" || ITLCmd == "file" || ITLCmd == "faustdspf"
			|| ITLCmd == "gmn" //to support score expression
			;
}

//____________________________________________
bool BundleCreator::parseScript(std::string inputScript, SIMessageList &msgs)
{
	//open file
	std::ifstream ifs(inputScript);
	if(!ifs.is_open()){
		fLog.error("\""+inputScript+"\" is not readable.");
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
		fLog.error("\""+inputScript+"\" is an incorrect INScore script.");
		return false;
	}

	return true;
}


//____________________________________________
void BundleCreator::simplifyPath()
{
	if(fImportedRessources.empty()&&fImportedScripts.empty())
		return;

	//  -- search for common path trunk --
	std::vector<std::string> trunk = splitPath(fImportedRessources.empty()? *(fImportedScripts.begin()) : *(fImportedRessources.begin()));
	int commonPath = trunk.size()-1;

	for(auto it = fImportedRessources.begin(); it != fImportedRessources.end(); it++){
		std::vector<std::string> path = splitPath(*it);

		int i=0;
		while ( i < commonPath && i < path.size() ) {
			if(path.at(i)!=trunk.at(i)){
				break;
			}
			i++;
		}
		commonPath = i;
	}

	for(auto it = fImportedScripts.begin(); it != fImportedScripts.end(); it++){
		std::vector<std::string> path = splitPath(*it);

		int i=0;
		while ( i < commonPath && i < path.size() ) {
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

	std::set<std::string> simplifiedImportedScript;
	std::set<std::string> simplifiedImportedRessources;

	for(auto it = fImportedRessources.begin(); it != fImportedRessources.end(); it++)
		simplifiedImportedRessources.insert((*it).substr(removable));

	for(auto it = fImportedScripts.begin(); it != fImportedScripts.end(); it++)
		simplifiedImportedScript.insert((*it).substr(removable));

	fImportedRessources = simplifiedImportedRessources;
	fImportedScripts = simplifiedImportedScript;
}

//____________________________________________
std::vector<std::string> BundleCreator::splitPath(std::string path)
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
bool BundleCreator::isurl(std::string path)
{
	std::string start = path.substr(0, 7);
	return start=="http://" || start=="https:/";
}

bool BundleCreator::isLocalPath(std::string string)
{
	//  /?(. .? /)*([^/?:*<>|']+/?)+.[^/\?:*<>|']+
	CRegexpT<char> fileRegex("/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+");

	return fileRegex.MatchExact(string.c_str()).IsMatched() && !isurl(string);
}

std::string BundleCreator::absolutePath(std::string path, std::string address, const std::map<std::string, std::string> &rootPaths)
{
	//_________CHECK IF ABSOLUTE____________
	if(*(path.begin())=='/')
		return path;

	//_________COMPUTING ROOTPATH____________
	std::string rootPath= fDefaultRootPath;

	//only keep /ITL/scene from the address
	while(!address.empty()){
		//check if the scene has a specific rootPath for the current address
		auto rootPathIt= rootPaths.find(address);
		if(rootPathIt != rootPaths.end()){
			rootPath = rootPathIt->second;
			break;
		}

		//if no rootPath is defined for the object try its parent
		size_t id = address.find_last_of('/');
		address = address.substr(0, id);
	}
	//_________APPLYING ROOTPATH____________
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
				fLog.error(path + " is not a valid path, using the rootPath: "+rootPath);
				return "";
			}
			size_t idPathSepResult = result.find_last_of('/');
			result = result.substr(0, idPathSepResult);
		}else{
			if(result.at(result.size()-1)!='/')
				result+='/';
			result +=currentFile;
		}
	}

	return result;

}


//__________________________________________________________
//----------------------------------------------------------
void BundleCreator::setVerbose(bool verbose)
{
	fLog.setActive(verbose);
}

void BundleCreator::setOutputPath(std::string outputPath)
{
	fOutputPath = outputPath;
}

void BundleCreator::setDefaultRootPath(std::string rootPath)
{
	fDefaultRootPath = rootPath;
}

void BundleCreator::setShowHierarchy(bool showHierarchy)
{
	fShowHierarchy = showHierarchy;
}


} // end namespace
