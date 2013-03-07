#ifndef CLIENT_netHandler_h
#define CLIENT_netHandler_h
#include "RakPeerInterface.h"
#include "packetSender.h"
#include "packetReceiver.h"
#include <string>

namespace CLIENT {

class Client;

class netHandler {

public:
	Client *client;
	bool isConnected;
	RakNet::RakPeerInterface *peer;
	RakNet::AddressOrGUID server;			//server currently connected to

	//CLIENT::packetSender packetsender;
	CLIENT::packetReceiver packetreceiver;
	CLIENT::packetSender packetsender;
	void setClient(Client *_client);

	void tick();
	void connect(char *remoteIPAddress, unsigned short serverPort);
	void sendClientMovementInput();
	void receivePackets();
	void disconnect();
	netHandler();

	void sendTestPacket();
};

} /* End of namespace CLIENT */

#endif // CLIENT_netHandler_h
