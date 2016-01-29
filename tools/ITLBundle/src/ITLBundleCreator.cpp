#include <iostream>
#include <unistd.h>

using namespace std;
#include "doc.h"
#include "BundleCreator.h"

int main(int argc, char* argv[])
{
	if(argc<2){
		std::cout<<USAGE_CREATOR;
		return 0;
	}

	string inputFile = argv[1];
	string outputFile = "bundle.inscorezip";

	if(inputFile == "-h" || inputFile == "--help"){
		std::cout<<DOC_CREATOR;
		return 0;
	}

	//OPTION
	int argI=2;
	itlbundle::BundleCreator bCreator;
	char* buffer = getcwd(NULL, 0);
	bCreator.setDefaultRootPath(std::string(buffer));

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

		if(arg == "-v" || arg == "--verbose"){
			bCreator.setVerbose();
			if(param=="hierarchy")
				bCreator.setShowHierarchy();

		}else if(arg == "-o" || arg == "--output"){
				outputFile = param;

		}else if(arg == "-h" || arg=="--help"){
				std::cout<<DOC_CREATOR;
			return 0;
		}else if(arg == "-l" || arg == "--rootpath"){
			if(!param.empty())
				bCreator.setDefaultRootPath(param);
		}else if(arg== "-f" || arg == "--force-overwrite"){
			bCreator.setForceOverwrite();
		}else if(arg== "-js" || arg == "--parse-javascript"){
			bCreator.setParseJS();
		}

	}
	inputFile = std::string(buffer)+"/"+inputFile;
	delete[] buffer;
	return bCreator.bundle(inputFile, outputFile);
}


