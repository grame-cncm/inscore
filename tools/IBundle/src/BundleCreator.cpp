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
	qarchive::QArchive* a = BundlePackager::bundle(parsedData);
	if(!a)
		return false;
	bool r = writeArchive(a, outputFile, fForceOverwrite);
	delete a;

	return r;
}

bool BundleCreator::failSafeBundle(std::string inputFile, std::string outputFile)
{
	ParsedData parsedData;
	QFile f(inputFile.c_str());
	if(!f.open(QIODevice::ReadOnly | QIODevice::Text)){
		fLog.error(inputFile+ " is not accessible.");
		return false;
	}

	QStringList files = QString::fromUtf8(f.readAll()).split("\n", QString::SkipEmptyParts);
	if(files.empty()){
		fLog.error(inputFile+ " is empty, check if the text codec is utf8.");
		return false;
	}

	QFileInfo fInfo(f);
	fInfo.setFile(files.first());
	parsedData.setMainScript(fInfo.canonicalFilePath().toStdString());
	foreach (QString file, files){
		fInfo = QFileInfo(f);
		fInfo.setFile(file);
		parsedData.ressources.insert(fInfo.canonicalFilePath().toStdString());
	}

	parsedData.simplifyPaths();

	inscore::extvector<std::string> names = parsedData.ressourceNames();
	qarchive::QArchive* a = qarchive::QArchive::emptyArchive();

	for(size_t i=0; i<names.size(); i++)
		if( !a->addFileStd(names.at(i), parsedData.mainPath()+names.at(i)) ){
			fLog.error(parsedData.mainPath()+names.at(i)+" not found.");
			return false;
		}

	std::string mainScriptPath = parsedData.mainScript();
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

	bool r = writeArchive(a, outputFile, fForceOverwrite);
	delete a;

	return r;
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

bool BundleCreator::writeArchive(qarchive::QArchive* archive, const std::string &outputPath, bool overwrite)
{
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

} // end namespace
