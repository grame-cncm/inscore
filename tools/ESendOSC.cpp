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
	cout << "usage: " << basename(name) << " count mls port <args list>" << endl;
	cout << "       where 'count' is the count of messages to send (-1 for endless loop)" << endl;
	cout << "             'msl' is the time interval between messages (expressed in msl)" << endl;
	cout << "             'port' is the udp destination port (on localhost)" << endl;
	cout << "             '<args list>' is an OSC message" << endl;
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

static bool send(int argc, char* argv[], int startpos)
{
     char buffer[OUTPUT_BUFFER_SIZE];
   try {
	        int port = atoi(argv[startpos]);
		UdpTransmitSocket transmitSocket( IpEndpointName( ADDRESS, port ) );
		osc::OutboundPacketStream p( buffer, OUTPUT_BUFFER_SIZE );
		p << osc::BeginMessage( argv[startpos+1] );
		for (int i=startpos+2; i<argc; i++) {
			const char* arg = argv[i];
			float fval;
			int ival;

			if (floatarg (arg, fval))	 	p << fval;
			else if (intarg (arg, ival)) 	p << ival;
			else							p << arg;
		}
		p << osc::EndMessage;    
		transmitSocket.Send( p.Data(), p.Size() );
		return true;
	}
	catch (std::runtime_error e) {
		cerr << "error: " << e.what() << endl;
		return false;
	}
}


int main(int argc, char* argv[])
{
    if (argc < 5) usage (argv[0]);
 	int count = atoi(argv[1]);
	int mls = atoi(argv[2]);
	cout << "Sending " << count << " messages. Wait " << mls << " mls" << endl;
       while (count--) {
		send (argc, argv, 3);
    	 	usleep (mls * 1000);
	}   
	return 0;
}

