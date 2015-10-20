

#include <iostream>

#include "ITLlistener.h"

using namespace std;

void printHelp();

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
		else if(arg=="-h" || arg=="--help"){
			printHelp();
			return 0;
		}

	}

	listener.start();
	return 0;
}

using namespace std;

void printHelp(){
	cout<< "Use: INScoreListener [OPTIONS]"<<endl;
	cout<< "Print any OSC messages from a given port"<<endl;

	cout<< endl;
	cout<< "OPTIONS"<<endl;

	cout<< "   -p   --port=PORT";
		cout<<"\t\t"<<"Set the listened port (default is 7001)"<<endl;
	cout<< "        --filter=FILTER";
		cout<<"\t\tSet a message filter,"<<endl;
		cout<<"\t\t\t\t   read further for filter specification"<<endl;
	cout<< "        --outFormat=OUT_FORMAT";
		cout<<"\t"<<"Set a the output format where:"<<endl;
			cout<<"\t\t\t\t   %addr will be replaced by the osc address,"<<endl;
			cout<<"\t\t\t\t   %args by all the message arguments separated with space"<<endl;
			cout<<"\t\t\t\t   %ID by the message argument with index=ID"<<endl;
	cout<< "   -v   --verbose";
		cout<<"\t\t"<<"print a welcome message and error logs"<<endl;
	cout<< "   -h   --help";
		cout<<"\t\t\t"<<"print this message and quit"<<endl;

	cout<< endl;
	cout<< "FILTER SPECIFICATION"<<endl;

	cout<<"Filters use the classic conditions syntax with:"<<endl;
			cout<<"\t&&, AND as and operator"<<endl;
			cout<<"\t||, OR  as or  operator"<<endl;
			cout<<"\t! , NOT as not operator"<<endl;
			cout<<"\tpriority for parenthese's condition and then for the left condition"<<endl;

	cout<<"Filters handle conditions on:"<<endl;
		cout<<"\tosc address: %addr == REGEX \t('==' can be replaced by '=')"<<endl;
		cout<<"\tmessage parameters: %ID LOGIC VALUE"<<endl;
		cout<<"\t\tVALUE: the tested value, accept float int and string"<<endl;
		cout<<"\t\tLOGIC: >, >=, <, <= (number only),\t !=, ==, ="<<endl;

	cout<<"The filter will discard the message if:"<<endl;
		cout<<"\t the condition is evaluated false"<<endl;
		cout<<"\t the tested parameters type differs from the VALUE's one (exept if '!=')"<<endl;
}

