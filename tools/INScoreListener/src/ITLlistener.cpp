#include <iostream>
#include <sstream>

#include "ITLlistener.h"
#include "Parser/filterparser.h"

using namespace std;
namespace inscorelistener {


ITLlistener::ITLlistener()
	: _port(7001),
	  _verbose(false),
	  _outputFormat("%addr %args")
{
}

void ITLlistener::setFilter(string filterFormat)
{
	filterparser parser(filterFormat);
	_filter = parser.parse();
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
			if(!_filter->match(m))
				return;

		string out = string(_outputFormat);


		replaceAll(out, "%addr", m.AddressPattern());

		string args = "";
		osc::ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
		int argI=0;
		string argStr="";

		while(readArg(arg,m,argStr)){
			ostringstream argName;
			argName<<"%"<<argI;
			replaceAll(out, argName.str(), argStr);
			args += argStr+" ";
			argI++;
		}

		replaceAll(out, "%args", args);

		cout<<out<<endl;
	}catch( osc::Exception& e ){
		// any parsing errors such as unexpected argument types, or
		// missing arguments get thrown as exceptions.
		if(_verbose)
			std::cout << "error while parsing message: "
				<< m.AddressPattern() << ": " << e.what() << "\n";
	}

}

void ITLlistener::start(){

	if(_verbose)
		cout<<"INScoreListener listening on port: "<<_port<<endl;

	_socket = new UdpListeningReceiveSocket( IpEndpointName( IpEndpointName::ANY_ADDRESS, _port ), this );
	_socket->RunUntilSigInt();
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



}//End namespace
