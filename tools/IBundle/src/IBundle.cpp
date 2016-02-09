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
#include <unistd.h>

#include "doc.h"

#include "BundleExtractor.h"
#include "BundleCreator.h"

using namespace std;

int main(int argc, char* argv[])
{
	if(argc<2){
		std::cout<<USAGE;
		return 0;
	}
	string inputFile = argv[1];
	if(inputFile == "-h" || inputFile == "--help"){
		std::cout<<DOC;
		return 0;
	}

	//Setup input file
	char* currentDir = getcwd(NULL, 0);
	if(inputFile.at(0) != '/')
		inputFile = std::string(currentDir)+"/"+inputFile;
	delete[] currentDir;

	ibundle::BundleExtractor bExt;
	ibundle::BundleCreator bCreator;
	bCreator.setDefaultRootPath(inputFile.substr(0, inputFile.rfind('/')));
	bool createBundle = true;
	bool failSafe = false;


	string output = "";

	//OPTION
	int argI=2;

	while(argI<argc){
		string arg = argv[argI];
		string param = "";

		argI++;
		while(argI<argc){
			string t = argv[argI];
			if(t.find_first_of('-'))
				param+=t+" ";
			else
				break;
			argI++;
		}
		param = param.substr(0,param.size()-1);

		if(arg == "-o" || arg == "--output"){
			output = param;
		}else if(arg == "-h" || arg=="--help"){
				std::cout<<DOC;
			return 0;
		}else if(arg == "-f" || arg=="--force-overwrite"){
			bExt.setForceOverwrite();
			bCreator.setForceOverwrite();
		}else
		    // Options Specific Creator
		    if(arg == "-v" || arg == "--verbose"){
		    bCreator.setVerbose();
		    if(param=="hierarchy")
			    bCreator.setShowHierarchy();
		}else if(arg == "-l" || arg == "--rootpath"){
			if(!param.empty())
				bCreator.setDefaultRootPath(param);
		}else if(arg== "-js" || arg == "--parse-javascript"){
			bCreator.setParseJS();
		}else if(arg== "--fail-safe"){
				failSafe = true;
		}else
		    // Options Specific Extractor
		    if(arg == "-k" || arg=="--keepOriginalPath"){
			bExt.setKeepOriginalPath();
		}else if(arg == "-e" || arg=="--extract-bundle"){
		    createBundle = false;
		}
	}


	//Setup default output
	if(output.empty()){
		std::string fileName = inputFile.substr(0, inputFile.rfind('.'));
		size_t idPath = fileName.rfind('/');
		if(idPath!=std::string::npos)
			fileName = fileName.substr(idPath+1);

		if(!createBundle)
			output = fileName;
	    else
			output =  fileName+".ibundle";
	}

	//Start bundle creation or extraction
	if(createBundle){
		if(failSafe)
			return bCreator.failSafeBundle(inputFile, output)?0:1;
		return bCreator.bundle(inputFile, output)?0:1;
	}

	return bExt.extract(inputFile, output)?0:1;
}


