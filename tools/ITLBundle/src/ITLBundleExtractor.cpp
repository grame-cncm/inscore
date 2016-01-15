#include <iostream>
#include <unistd.h>

using namespace std;
#include "doc.h"
#include "QArchive.h"

int main(int argc, char* argv[])
{
	if(argc<2){
		std::cout<<USAGE;
		return 0;
	}

	string inputFile = argv[1];
	string outputFolder = inputFile.substr(0, inputFile.rfind('.'));


	if(inputFile == "-h" || inputFile == "--help"){
		std::cout<<DOC;
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
				std::cout<<DOC;
			return 0;
		}
	}

	qarchive::SQArchive a = qarchive::QArchive::readArchiveStd(inputFile);


	return a->extractStd(outputFolder);
}


