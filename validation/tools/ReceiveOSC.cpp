#include <iostream>
#include <fstream>
#include <cstring>
#include <cstdlib>
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"

using namespace std;

namespace osc {

class OscReceiveTestPacketListener : public OscPacketListener{
	public:

	private:
			string fGeneratedFile;
			ofstream fOutputFile;
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
		}
	};

void RunReceiveOSC( int port)
{
	osc::OscReceiveTestPacketListener listener;
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
	int port = 7000;
	if(argc <= 3 ) {
		for (int i = 1; i < argc ; i+=2) {
			if(strcmp( argv[i], "-p") == 0) {
				if(argc >= i+1) {
					port = atoi( argv[i+1] );
				}
			} else {
				help = true;
			}
		}
	} else {
		help = true;
	}

	if(help || (argc >= 2 && strcmp( argv[1], "-h" ) == 0 )){
		std::cout << "usage: ReceiveOSC -p [port]" << endl;
		std::cout << "Default port : 7000" << endl;
		return 0;
	}

	osc::RunReceiveOSC(port);

	return 0;
}
