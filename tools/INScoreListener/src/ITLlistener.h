#ifndef INSCORELISTENER_H
#define INSCORELISTENER_H

#include "osc/OscReceivedElements.h"
#include "osc/OscPacketListener.h"
#include "ip/UdpSocket.h"

#include "OSCFilter.h"

namespace inscorelistener{

class ITLlistener: public osc::OscPacketListener{

	int _port;
	UdpListeningReceiveSocket* _socket;

	bool _verbose;
	std::string _outputFormat;

	OSCFilter* _filter;


public:

	ITLlistener();
	~ITLlistener();

	int start();
	void setVerbose(bool verbose= true){_verbose=verbose;}
	void setPort(int port){_port = port;}
	void setOutputFormat(std::string outputFormat){_outputFormat = outputFormat;}
	void setFilter(std::string filterFormat);

	// OscPacketListener interface
protected:
	void ProcessMessage(const osc::ReceivedMessage &m, const IpEndpointName &remoteEndpoint);

	bool readArg(osc::ReceivedMessage::const_iterator &arg, const osc::ReceivedMessage &message, std::string& result);
	static int replaceAll(std::string& replaceIn, std::string search, std::string replaceBy);
};

}

#endif // INSCORELISTENER_H

