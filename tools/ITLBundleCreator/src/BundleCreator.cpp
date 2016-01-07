
#include <fstream>

#include "BundleCreator.h"

//#include "Parser/itlbundleparser.h"

#include "ITLparser.h"
//#include "TQtJs.h"

namespace itlbundle{

BundleCreator::BundleCreator()
{

}
//____________________________________________
int BundleCreator::bundle(std::string inputFile)
{
	fLog.section("Parsing \""+inputFile+"\"");

	if(!parseFile(inputFile))
		return -1;

	return 0;
}

//__________________________________________________________
//----------------------------------------------------------
bool BundleCreator::parseFile(std::string inputFile)
{
	//Check script validity
	if(!checkScript(inputFile))
		return false;

	//Analyse script
//	std::ifstream ifs(inputFile);
//	itlbundleparser p(&ifs);
//	if(!p.parse()){
//		fLog.error("Analysis of the script: \""+inputFile+"\" failed.");
//		return false;
//	}

//	///TODO: store analysis result

//	//Print analyse result in logs
//	fLog<<"Ressources:"<<std::endl;
//	for(auto it = p.fRessourcesList.begin(); it != p.fRessourcesList.end(); it++)
//		fLog<<" - "<<(*it)<<std::endl;

//	fLog<<"Imported scripts:"<<std::endl;
//	for(auto it = p.fImportedScript.begin(); it != p.fImportedScript.end(); it++){
//		fLog.subSection(*it);
//		parseFile(*it);
//	}

}

//____________________________________________
bool BundleCreator::checkScript(std::string inputScript)
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
	p.parse();

	if(!p.fParseSucceed){
		fLog.error("\""+inputScript+"\" is an incorrect INScore script.");
		return false;
	}

	return true;
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


} // end namespace
