#include <iostream>
#include <sstream>
#include <stdexcept>

#include "ITLlistener.h"
#include "Parser/filterparser.h"

#define DEFAULT_PORT 7001

using namespace std;
namespace inscorelistener {


ITLlistener::ITLlistener()
	: _port(DEFAULT_PORT),
	   _socket(0),
	  _verbose(false),
	  _outputFormat("%addr %quotedArgs;"),
	  _filter(0)

{
}

void ITLlistener::setFilter(string filterFormat)
{
	filterparser parser(filterFormat);
	//cout<<"start parsing... ";
	_filter = parser.parse();
	//cout<<"OK"<<endl;
}


ITLlistener::~ITLlistener()
{
	if(_socket)
		delete _socket;

	if(_filter)
		delete _filter;
}

//_______________________________________________________________
void ITLlistener::ProcessMessage(const osc::ReceivedMessage &m, const IpEndpointName & /*remoteEndpoint*/)
{
	try{

		if(_filter)
			if(!_filter->match(m,_verbose))
				return;

		string out = string(_outputFormat);


		replaceAll(out, "%addr", m.AddressPattern());

		string args = "", quotedArgs = "";
		osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
		int argI=0;
		string argStr="";

		while(readArg(arg,m,argStr)){
			ostringstream argName, quotedArgName;
			argName<<"%"<<argI;
			quotedArgName<<"%Q"<<argI;

			replaceAll(out, argName.str(), argStr);
			replaceAll(out, quotedArgName.str(), autoQuotes(argStr));
			args += argStr+" ";
			quotedArgs += autoQuotes(argStr)+" ";
			argI++;
		}

		replaceAll(out, "%args", args);
		replaceAll(out, "%quotedArgs", quotedArgs);

		cout<<out<<endl;
	}catch( osc::Exception& e ){
		// any parsing errors such as unexpected argument types, or
		// missing arguments get thrown as exceptions.
		if(_verbose)
			std::cerr << "error while parsing message: "
				<< m.AddressPattern() << ": " << e.what() << "\n";
	}

}

int ITLlistener::start(){

	try{
		_socket = new UdpListeningReceiveSocket( IpEndpointName( IpEndpointName::ANY_ADDRESS, _port ), this );
	}catch(std::runtime_error &e){
		cerr<<"Unable to connect to port: "<<_port<<"..."<<endl;
		cerr<<"   std::runtime_error: "<<e.what();
		if(_port==DEFAULT_PORT)
			cerr<<"Try another port using INScoreViewer -p PORT"<<endl;
		return -1;
	}

	if(_verbose)
		cout<<"INScoreListener listening on port: "<<_port<<endl;

	_socket->RunUntilSigInt();
	return 0;
}

//_______________________________________________________________

bool ITLlistener::readArg(osc::ReceivedMessage::const_iterator& arg, const osc::ReceivedMessage& message, std::string &result)
{
	if(arg == message.ArgumentsEnd())
		return false;

	if(arg->IsString()){
			result = arg->AsStringUnchecked();
	}else{
		std::ostringstream outS;
		if(arg->IsInt32())
			outS<<arg->AsInt32Unchecked();
		else if(arg->IsFloat())
			outS<<arg->AsFloatUnchecked();
		result = outS.str();
	}

	arg++;
	return true;
}

int ITLlistener::replaceAll(std::string &replaceIn, std::string search, std::string replaceBy)
{
	std::size_t searchSize= search.size();
	int count = 0;
	std::size_t replaceAt = replaceIn.find(search);
	while(replaceAt!=std::string::npos){
		replaceIn.replace(replaceAt, searchSize, replaceBy.c_str());
		replaceAt = replaceIn.find(search);
		count++;
	}

	return count;
}

//_______________________________________________________________
string ITLlistener::autoQuotes (const string& str)
{
	bool ret = false;
	string r = str;
	const char *ptr = str.c_str();
	if (*ptr == '$') ret = true;
	while (*ptr) {
		char c = *ptr++;
		if (!isdigit(c) && !isalpha(c)					// number and letters
			&& (c != '-') && (c != '_')					// identifiers chars
			&& (c != '+') && (c != '*') && (c != '?'))	// regexp chars (note that class description needs quotes)
			ret = true;
	}
	if(ret)
		r = '"'+r+'"';
	return r;
}


}//End namespace
