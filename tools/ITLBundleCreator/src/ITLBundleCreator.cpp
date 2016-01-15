#include <iostream>
#include <unistd.h>

using namespace std;
#include "doc.h"
#include "BundleCreator.h"

int main(int argc, char* argv[])
{
	if(argc<2){
		std::cout<<USAGE;
		return 0;
	}

	string inputFile = argv[1];
	string outputFile = "bundle.itlbundle";

	if(inputFile == "-h" || inputFile == "--help"){
		std::cout<<DOC;
		return 0;
	}

	//OPTION
	int argI=2;
	itlbundle::BundleCreator bCreator;

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

		if(arg == "-v" || arg == "--verbose"){
			bCreator.setVerbose();
			if(param=="hierarchy ")
				bCreator.setShowHierarchy();

		}else if(arg == "-o" || arg == "--output"){
			if(param.at(0)!='/'){
				char* buffer = getcwd(NULL, 0);
				outputFile = std::string(buffer) + param;
				delete[] buffer;
			}else
				outputFile = param;

		}else if(arg == "-h" || arg=="--help"){
				std::cout<<DOC;
			return 0;
		}else if(arg == "-l" || arg == "--local"){
			char* buffer = getcwd(NULL, 0);
			bCreator.setDefaultRootPath(std::string(buffer));
			delete[] buffer;
		}

	}
	char* buffer = getcwd(NULL, 0);
	inputFile = std::string(buffer)+"/"+inputFile;
	delete[] buffer;
	return bCreator.bundle(inputFile, outputFile);
}


