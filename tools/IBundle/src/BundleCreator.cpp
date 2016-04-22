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
#include "ScriptsParser.h"
#include "ParsedData.h"
#include "INScore.h"

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

	parsedData.simplifyPaths();

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

	mapNames(parsedData);

	// Setup Archive
	qarchive::QArchive* archive = qarchive::QArchive::emptyArchive();
	std::string fileNames = "";

	//Create hierarchy
	archive->changeDir("/");
	archive->addDir("Export");
	archive->addDir("Ressources");

	setupArchive(parsedData, archive);

	bool r = writeArchive(archive, outputFile, fForceOverwrite);
	delete archive;

	return r;
}

bool BundleCreator::failSafeBundle(std::string inputFile, std::string outputFile)
{
	// Open files list
	ParsedData parsedData;
	QFile f(inputFile.c_str());
	if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
		fLog.error(inputFile+ " is not accessible.");
		return false;
	}

	// Parse files list
	QStringList files = QString::fromUtf8(f.readAll()).split("\n", QString::SkipEmptyParts);
	if(files.empty()){
		fLog.error(inputFile+ " is empty, check if the text codec is utf8.");
		return false;
	}

	// Add files list to parsedData
	QFileInfo fInfo(f);
	fInfo.setFile(files.first());
	parsedData.mainScript = fInfo.canonicalFilePath().toStdString();
	foreach (QString file, files){
		fInfo = QFileInfo(f);
		fInfo.setFile(file);
		parsedData.addRessource(fInfo.canonicalFilePath().toStdString());
	}

	// Simplify files path
	parsedData.simplifyPaths();

	qarchive::QArchive* a = qarchive::QArchive::emptyArchive();

	setupArchive(parsedData, a);

	// Create main.inscore
	std::string mainScriptPath = parsedData.mainScript;
	std::string rootPath = "";
	size_t idPath = mainScriptPath.rfind('/');
	if(idPath != std::string::npos){
		rootPath = mainScriptPath.substr(0, idPath);
		mainScriptPath.substr(idPath);
	}
	std::string main;
	if(!rootPath.empty())
		main += "/ITL rootPath "+rootPath+";\n";
	main+="/ITL load "+mainScriptPath+";";
	if(!a->addTextFileStd("/main.inscore", main)){
		fLog.error(parsedData.mainPath()+"main.inscore must be rename or not included in the bundle.");
		return false;
	}

	// Write archive
	bool r = writeArchive(a, outputFile, fForceOverwrite);
	delete a;

	return r;
}



//__________________________________________________________
//----------------------------------------------------------
bool BundleCreator::setupArchive(const ParsedData& data, qarchive::QArchive* archive){
	std::string mapTrace = "";

	for(auto it=data.filesMap().begin(); it!=data.filesMap().end(); it++){
		std::string archiveName = it->second, fileName = it->first;
		if(archiveName != fileName)
			mapTrace +=  archiveName + "\t" + fileName +"\n";

		// -- SCRIPTS --
		if(fileName.size()>8 && fileName.substr(fileName.size()-8)==".inscore"){
			//Generate Script
			std::string script = data.generateScript(fileName);
			if(!script.empty()){
				//add script to archive
				archive->addTextFileStd(archiveName, script);
				continue;
			}
		}

		// -- RESSOURCES --
		if(!archive->addFileStd(archiveName, data.mainPath()+fileName)){
			std::cerr<<"Ressource: \""<<data.mainPath()+it->first<<"\" does not exist!"<<std::endl;
			return false;
		}

	}

	if(!mapTrace.empty())
		archive->addTextFileStd("bundleMap.txt", mapTrace);

	return true;
}

bool BundleCreator::writeArchive(qarchive::QArchive* archive, const std::string &outputPath, bool overwrite)
{
	archive->header().addNbrProperty(0,INScore::version());
	qarchive::QArchiveError e = archive->compressStd(outputPath, overwrite);

	std::string r;
	switch(e){
	case qarchive::ARCH_OK:
		return true;
	case qarchive::FILE_EXIST:
		std::cout<<"File already exist, do you want to overwrite? [O/n]   ";
		std::cin>>r;
		if(r!="n")
			return writeArchive(archive, outputPath, true);
		else
			return false;
		break;
	case qarchive::WRONG_PERMISSIONS:
		std::cerr<<"Impossible to write in "<<outputPath<<std::endl;
		break;
	default:
		std::cerr<<"An error occurs during the bundle preparation..."<<std::endl;
		break;
	}
	return false;
}

void BundleCreator::mapNames(ParsedData& inputData)
{
	int idRsc=0, idScript=1;
	TStringMap map = inputData.filesMap();

	for(auto it = map.begin(); it!=map.end(); it++){
		std::string fileName = it->first;
		std::string& mapped = it->second;

		if(fileName.substr(fileName.size()-8)==".inscore"){
			if(inputData.isMainScript(fileName))
				mapped = "main.inscore";
			else{
				std::stringstream name;
				name << idScript <<".inscore";
				mapped = name.str();
				idScript++;
			}
		}else{
			size_t idExtSuffix = fileName.rfind('.');
			std::stringstream name;
			name << "Ressources/" << idRsc <<"."<<fileName.substr(idExtSuffix+1);
			mapped = name.str();
			idRsc++;
		}
	}

	inputData.applyFileMap(map);
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
