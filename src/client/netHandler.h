#ifndef CLIENT_netHandler_h
#define CLIENT_netHandler_h
#include "RakPeerInterface.h"
#include "packetSender.h"
#include "packetReceiver.h"

namespace CLIENT {

class netHandler {

public:
	bool isConnected;
	RakNet::RakPeerInterface *peer;

	CLIENT::packetSender packetsender;
    CLIENT::packetReceiver packetreceiver;

	void connect(char *remoteIPAddress, unsigned short serverPort);
	void disconnect();
	netHandler();

	void sendTestPacket();
};

} /* End of namespace CLIENT */

#endif // CLIENT_netHandler_h
