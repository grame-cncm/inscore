

#include <iostream>
#include <cstdlib>

#include "ITLlistener.h"

using namespace std;
#include "doc.h"

int main(int argc, char* argv[])
{

	inscorelistener::ITLlistener listener;

	int argI=0;

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


		if(arg == "--port" || arg == "-p")
			listener.setPort(std::atoi(param.c_str()));

		else if(arg == "-v" || arg == "--verbose")
			listener.setVerbose();

		else if(arg == "-f" || arg == "--filter")
			listener.setFilter(param);
		else if(arg == "-o" || arg == "--outFormat")
			listener.setOutputFormat(param);
		else if(arg == "-h" || arg=="--help"){
			if(param=="filter ")
				std::cout<<FILTER_DOC;
			else
				std::cout<<DOC;
			return 0;
		}

	}

	return listener.start();
}


