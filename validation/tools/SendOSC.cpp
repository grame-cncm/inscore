/* 
    A simple tool to send osc messages from the command line
*/

#include <libgen.h>
#include <stdlib.h>
#include <unistd.h>

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
		p << osc::BeginMessage( argv[2] );
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

