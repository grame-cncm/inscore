

#include <iostream>

#include "ITLlistener.h"

using namespace std;

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
			listener.setPort(std::stoi(param));

		else if(arg == "-v" || arg == "--verbose")
			listener.setVerbose();

		else if(arg == "--filter")
			listener.setFilter(param);
		else if(arg == "--outFormat")
			listener.setOutputFormat(param);


	}




	listener.start();
	return 0;
}

