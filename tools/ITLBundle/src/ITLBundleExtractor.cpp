#include <iostream>
#include <unistd.h>

using namespace std;
#include "doc.h"
#include "BundleExtractor.h"

int main(int argc, char* argv[])
{
	if(argc<2){
		std::cout<<USAGE_EXTRACTOR;
		return 0;
	}

	string inputFile = argv[1];
	string outputFolder = inputFile.substr(0, inputFile.rfind('.'));

	itlbundle::BundleExtractor b;

	if(inputFile == "-h" || inputFile == "--help"){
		std::cout<<DOC_EXTRACTOR;
		return 0;
	}

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

		if(arg == "-o" || arg == "--output"){
			if(param.at(0)!='/'){
				char* buffer = getcwd(NULL, 0);
				outputFolder = std::string(buffer) + param;
				delete[] buffer;
			}else
				outputFolder = param;

		}else if(arg == "-h" || arg=="--help"){
				std::cout<<DOC_EXTRACTOR;
			return 0;
		}else if(arg == "-f" || arg=="--force-overwrite"){
			b.setForceOverwrite();
		}
	}


}


