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
int BundleCreator::bundle(std::string inputFile, std::string outputFile)
{
	ReadingContext readingResult;
	std::string absoluteFile = absolutePath(inputFile, "/", readingResult);
	if(!absoluteFile.empty())
		inputFile = absoluteFile;

	fLog.section("Parsing \""+inputFile+"\"");
	readingResult.currentScript = inputFile;

	if(!readScript(readingResult))
		return -1;

	simplifyPath(readingResult);

	fLog.section("Discovered Files");

	fLog<<"Ressources:\n";
	for(auto it = readingResult.ressources.begin(); it != readingResult.ressources.end(); it++)
		fLog<<"  "<<*it<<"\n";

	fLog<<"Script:\n";
	for(auto it = readingResult.scripts.begin(); it != readingResult.scripts.end(); it++)
		fLog<<"  "<<(*it).first<<"\n";


	return 0;
}

//__________________________________________________________
//----------------------------------------------------------
bool BundleCreator::readScript( ReadingContext& context)
{
	//Check script validity

	SIMessageList msgs;
	std::string inputFile = context.currentScript;

	if(!parseScript(inputFile, msgs))
		return false;

	context.scripts.insert({inputFile,msgs});

	if(!msgs || !msgs->list().size())
		return true;

	//Analyse messages
	ReadingContext r(inputFile);
	for (int idMsg = 0; idMsg < (int)msgs->list().size(); ++idMsg) {
		SIMessage msg = msgs->list().at(idMsg);
		analyseMsg(msg, r);
	}


	if(fShowHierarchy) fLog<<"Ressources:"<<"\n";
	for(auto it = r.ressources.begin(); it != r.ressources.end(); it++){
		if(fShowHierarchy) fLog<<" - "<<(*it)<<"\n";
		context.ressources.insert(*it);
	}

	if(fShowHierarchy) fLog<<"Imported scripts:"<<"\n";

	for(auto it = r.scripts.begin(); it != r.scripts.end(); it++){
		std::string script = (*it).first;

		if(fShowHierarchy) fLog<<" - "<<script<<"\n";

		if(!context.scripts.count(*it)){
			if(fShowHierarchy) fLog.subSection(script);
			context.currentScript = script;
			bool scriptValid = readScript(context);
			if(fShowHierarchy) fLog.exitSubSection();
			context.currentScript = inputFile;

			if(!scriptValid)
				return false;
		}
	}

	return true;
}

void BundleCreator::analyseMsg(const SIMessage &msg, ReadingContext &context)
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
					script = absolutePath(script, address, context);
					if(!script.empty())
						context.scripts.insert({script,0});
				}
				return;
			}
		}else if(msg->message()=="rootPath"){
			if(msg->size()==1){
				std::string rootPath;

				if(msg->param(0,rootPath)){
					if(!context.acceptRootPathMsg){
						fLog.warn("In \""+context.currentScript+"\"\n         "+msg->address()+" rootpath "+rootPath+";");
						fLog.warn("changing rootPath inside parameters message is not handled!");
						return;
					}

					rootPath = absolutePath(rootPath, address, context);

					if(!rootPath.empty())
						context.rootPaths.insert({address, rootPath});
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
						if(isPath(path)){
							path = absolutePath(path, address, context);
							if(!path.empty())
								context.ressources.insert(path);
						}
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
			bool acceptRootPathMsg = context.acceptRootPathMsg;
			context.acceptRootPathMsg = false;
			for (int i = 0; i < (int)msgList->list().size(); ++i) {
				SIMessage msg = msgList->list().at(i);
				analyseMsg(msg, context);
			}
			context.acceptRootPathMsg = acceptRootPathMsg;
		}else if(msg->param(i, expr)){
			std::set<std::string> exprDependencies = inscore::ExprInfo::fileDependency(expr);
			for(auto it = exprDependencies.begin(); it != exprDependencies.end(); it++){
				std::string path = absolutePath(*it,address,context);
				if(!path.empty())
					context.ressources.insert(path);
			}
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
void BundleCreator::simplifyPath(ReadingContext &context)
{
	if(context.ressources.empty()&&context.scripts.empty())
		return;

	//  -- search for common path trunk --
	std::vector<std::string> trunk = splitPath(context.ressources.empty()? (*context.scripts.begin()).first : *(context.ressources.begin()));
	int commonPath = trunk.size()-1;

	for(auto it = context.ressources.begin(); it != context.ressources.end(); it++){
		std::vector<std::string> path = splitPath(*it);

		int i=0;
		while ( i < commonPath && i < (int)path.size() ) {
			if(path.at(i)!=trunk.at(i)){
				break;
			}
			i++;
		}
		commonPath = i;
	}

	for(auto it = context.scripts.begin(); it != context.scripts.end(); it++){
		std::vector<std::string> path = splitPath((*it).first);

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

	scriptSet simplifiedScripts;
	std::set<std::string> simplifiedRessources;

	for(auto it = context.ressources.begin(); it != context.ressources.end(); it++)
		simplifiedRessources.insert((*it).substr(removable));

	for(auto it = context.scripts.begin(); it != context.scripts.end(); it++){
		std::pair<std::string, inscore::SIMessageList> simplified((*it).first.substr(removable),(*it).second);
		simplifiedScripts.insert(simplified);
	}

	context.ressources = simplifiedRessources;
	context.scripts = simplifiedScripts;
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

bool BundleCreator::isPath(std::string string)
{
	//  /?(. .? /)*([^/?:*<>|']+/?)+.[^/\?:*<>|']+
	CRegexpT<char> fileRegex("/?(\\.\\.?/)*([^/\\?:*<>|']+/?)+\\.[^/\\?:*<>|']+");

	return fileRegex.MatchExact(string.c_str()).IsMatched();
}

std::string BundleCreator::absolutePath(std::string path, std::string address, const ReadingContext& context)
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
		auto rootPathIt= context.rootPaths.find(address);
		if(rootPathIt != context.rootPaths.end()){
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

void BundleCreator::setDefaultRootPath(std::string rootPath)
{
	fDefaultRootPath = rootPath;
}

void BundleCreator::setShowHierarchy(bool showHierarchy)
{
	fShowHierarchy = showHierarchy;
}


} // end namespace
