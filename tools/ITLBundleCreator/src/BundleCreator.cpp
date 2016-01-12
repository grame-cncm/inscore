#include "ScriptsParser.h"
#include "ParsedData.h"
#include "BundlePackager.h"

#include "BundleCreator.h"




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

	fLog.section("Parsing \""+inputFile+"\"");

	ParsedData parsedData;
	if(!ScriptsParser::read(inputFile, parsedData, fDefaultRootPath, &fLog, fShowHierarchy))
		return -1;

	fLog.section("Discovered Files");

	fLog<<"Ressources:\n";
	inscore::extvector<std::string> rscNames = parsedData.ressourceNames();
	for(size_t i = 0; i<rscNames.size(); i++)
		fLog<<"  "<<rscNames.at(i)<<"\n";


	fLog<<"Script:\n";
	inscore::extvector<std::string> scriptNames = parsedData.scriptNames();
	for(size_t i = 0; i<scriptNames.size(); i++)
		fLog<<"  "<<scriptNames.at(i)<<"\n";

	fLog<<"Script Regeneration:\n";
	BundlePackager::bundle(parsedData, outputFile);

	return 0;
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
