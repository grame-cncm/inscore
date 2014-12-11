/* 
    A simple tool to send osc messages from the command line
*/

#ifdef WIN32
#include <Windows.h>
#define basename(a) a
#define strtof		(float)strtod
#define usleep(a)	Sleep(a/1000)
#else
#include <libgen.h>
#include <unistd.h>
#endif
#include <stdlib.h>

#include <iostream>
#include <stdexcept>

#include "osc/OscOutboundPacketStream.h"
#include "ip/UdpSocket.h"


#define ADDRESS "127.0.0.1"
#define OUTPUT_BUFFER_SIZE 4096

using namespace std;

static void usage (char* name)
{
	cout << "usage: " << basename(name) << " port <args list>>" << endl;
	exit (1);
}

static bool floatarg (const char* name, float& val)
{
	const char* ptr = name;
	bool dot=false;
	while (*ptr && !dot) {
		if (*ptr++ == '.') dot=true;
	}
	if (dot) {
		char* endptr = 0;
 		val = strtof (name, &endptr);
		return (endptr != name) && (*endptr==0);
	}
	return false;
}

static bool intarg (const char* name, int& val)
{
	char* endptr = 0;
	val = strtol (name, &endptr, 10);
	return (endptr != name) && (*endptr==0);
}

int main(int argc, char* argv[])
{
	if (argc < 3) usage (argv[0]);

    char buffer[OUTPUT_BUFFER_SIZE];
	int port = atoi(argv[1]);
    try {
		UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, port ) );
		osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
		string address = argv[2];
		size_t pos = address.find("/ITL");
		const char * addrptr = (pos == std::string::npos) ? address.c_str() : &address.c_str()[pos];
		p << osc::BeginMessage( addrptr );
		for (int i=3; i<argc; i++) {
			const char* arg = argv[i];
			float fval;
			int ival;

			if (floatarg (arg, fval))	 	p << fval;
			else if (intarg (arg, ival)) 	p << ival;
			else							p << arg;
		}
		p << osc::EndMessage;    
		transmitSocket.Send( p.Data(), p.Size() );
		usleep (150000);		// wait 150 mls before exit
	}
	catch (std::runtime_error e) {
		cerr << "error: " << e.what() << endl;
		exit(1);
	}
    
 	return 0;
}

