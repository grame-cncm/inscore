#include "ScriptsParser.h"
#include "ParsedData.h"
#include "BundlePackager.h"

#include "BundleCreator.h"




namespace ibundle{

using namespace inscore;

BundleCreator::BundleCreator()
{
	fShowHierarchy = false;
	fParseJS = false;
	fDefaultRootPath = std::string(getenv("HOME")) + "/";
}
//____________________________________________
bool BundleCreator::bundle(std::string inputFile, std::string outputFile)
{

	fLog.section("Parsing \""+inputFile+"\"");

	ParsedData parsedData;
	if(!ScriptsParser::read(inputFile, parsedData, fDefaultRootPath, fParseJS, &fLog, fShowHierarchy))
		return false;

	fLog.section("Discovered Files");

	fLog<<"Ressources:\n";
	inscore::extvector<std::string> rscNames = parsedData.ressourceNames();
	for(size_t i = 0; i<rscNames.size(); i++)
		fLog<<"  "<<rscNames.at(i)<<"\n";


	fLog<<"Script:\n";
	inscore::extvector<std::string> scriptNames = parsedData.scriptNames();
	for(size_t i = 0; i<scriptNames.size(); i++)
		fLog<<"  "<<scriptNames.at(i)<<"\n";

	fLog.section("Bundle Creation");
	BundlePackager::bundle(parsedData, outputFile, fForceOverwrite);

	return true;
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

void BundleCreator::setForceOverwrite(bool forceOverwrite)
{
	fForceOverwrite= forceOverwrite;
}

void BundleCreator::setParseJS(bool parseJS)
{
	fParseJS = parseJS;
}



} // end namespace
