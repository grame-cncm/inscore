#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"
#include <sys/types.h>
#include <unistd.h>
#include <signal.h>

using namespace std;

namespace osc {

class OscReceiveTestPacketListener : public OscPacketListener{
	public:
		OscReceiveTestPacketListener(bool remoteIp, bool closeAfterFirst) : fRemoteIp(remoteIp), fCloseAfterFirst(closeAfterFirst) {}
	private:
		bool fRemoteIp;
		bool fCloseAfterFirst;

		// Method from inscore::IMessage
		static bool needQuotes (const string& str)
		{
			bool ret = false;
			const char *ptr = str.c_str();
			if (*ptr == '$') return true;
			while (*ptr) {
				int c = *ptr++;
				if (!isdigit(c) && !isalpha(c)					// number and letters
					&& (c != '-') && (c != '_')					// identifiers chars
					&& (c != '+') && (c != '*') && (c != '?'))	// regexp chars (note that class description needs quotes)
					ret = true;
			}
			return ret;
		}
	protected:

		void ProcessMessage( const osc::ReceivedMessage& m, const IpEndpointName& remoteEndpoint )
		{
			// a more complex scheme involving std::map or some other method of
			// processing address patterns could be used here
			// (see MessageMappingOscPacketListener.h for example). however, the main
			// purpose of this example is to illustrate and test different argument
			// parsing methods

			try {
				// argument stream, and argument iterator, used in different
				// examples below.
				ReceivedMessage::const_iterator arg = m.ArgumentsBegin();
				if(fRemoteIp) {
					char address[32];
					remoteEndpoint.AddressAsString(address);
					std::cout << address << " ";
				}
				std::cout << m.AddressPattern();
				for (; arg != m.ArgumentsEnd(); arg++) {
					if (arg->IsBool())
						std::cout << " " << arg->AsBool();
					else
					if (arg->IsInt32())
						std::cout << " " << int(arg->AsInt32Unchecked());
					else
					if (arg->IsFloat())
						std::cout << " " << arg->AsFloatUnchecked();
					else
					if (arg->IsChar())
						std::cout << " " << arg->AsChar();
					else
					if (arg->IsRgbaColor())
						std::cout << " " << arg->AsRgbaColor();
					else
					if (arg->IsMidiMessage())
						std::cout << " " << arg->AsMidiMessage();
					else
					if (arg->IsInt64())
						std::cout << " " << arg->AsInt64();
					else
					if (arg->IsDouble())
						std::cout << " " << arg->AsDouble();
					else
					if (arg->IsString()) {
						string value = arg->AsStringUnchecked();
						if(needQuotes(value)) {
							std::cout << " " << "\"" << value << "\"";
						}
						else std::cout << " " << value;
					}
					else
					if (arg->IsSymbol())
						std::cout << " " << arg->AsSymbol();
				}
				std::cout << ";" << std::endl;
			} catch( Exception& e ){
				std::cout << "error while parsing message: "
							<< m.AddressPattern() << ": " << e.what() << endl;
			}
			if(fCloseAfterFirst) {
				kill(getpid(), SIGINT);
			}
		}
	};

void RunReceiveOSC(int port, bool remoteIp, bool closeAfterFirst)
{
	osc::OscReceiveTestPacketListener listener(remoteIp, closeAfterFirst);
	UdpListeningReceiveSocket s(
			IpEndpointName( IpEndpointName::ANY_ADDRESS, port ),
			&listener );

	std::cerr << "listening for input on port " << port << "..." << endl;
	std::cerr << "press ctrl-c to end" << endl;
	std::cerr << "Command received :" << endl;

	s.RunUntilSigInt();

	std::cerr << "finishing." << endl;
}

} // namespace osc

int main(int argc, char* argv[])
{
	bool help = false;
	bool remoteIp = false;
	bool closeAfterFirst  = false;
	int port = 7000;
	if(argc <= 3 ) {
		for (int i = 1; i < argc ; i+=1) {
			if(strcmp( argv[i], "-p") == 0) {
				if(argc >= ++i) {
					port = atoi( argv[i] );
				}
			} else
			if(strcmp( argv[i], "-ip") == 0)	{
				remoteIp = true;
			} else
			if(strcmp( argv[i], "-c") == 0)	{
				closeAfterFirst = true;
			} else
			{
				help = true;
			}
		}
	} else {
		help = true;
	}

	if(help || (argc >= 2 && strcmp( argv[1], "-h" ) == 0 )){
		std::cout << "usage: ReceiveOSC -p [port] [-ip] [-c]" << endl;
		std::cout << "Default port : 7000" << endl;
		std::cout << "-ip : print remote address of received message" << endl;
		std::cout << "-c : close after first received message" << endl;
		return 0;
	}

	osc::RunReceiveOSC(port, remoteIp, closeAfterFirst);

	return 0;
}
