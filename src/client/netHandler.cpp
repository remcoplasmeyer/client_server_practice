#include "../Log.h"
#include "RakPeerInterface.h"

#include "BitStream.h"
#include "RakNetStatistics.h"
#include "MessageIdentifiers.h"

#include "Client.h"
#include "netHandler.h"
#include "packetSender.h"
#include "packetReceiver.h"

/*
	[netHandler] handles all the network input and output
	TODO: set isConnected when connectedd
*/

namespace CLIENT {

	CLIENT::netHandler::netHandler() {
		this->peer = RakNet::RakPeerInterface::GetInstance();
		RakNet::SocketDescriptor socketDescriptor;
		socketDescriptor.port = 0;
		RakNet::StartupResult b = peer->Startup(1,&socketDescriptor,1);
		RakAssert(b == RAKNET_STARTED);
		isConnected	= false;
		
		packetreceiver.setNethandler(this);
		//packetsender = CLIENT::packetSender();
	}

	void netHandler::setClient(Client *_client) {
		this->client = _client;
	}

	void CLIENT::netHandler::connect(char *remoteIPAddress, unsigned short serverPort) {
		FILE_LOG(logINFO) << "Connecting to " << remoteIPAddress << ":" << serverPort;
		bool tryingToConnect;
		tryingToConnect = peer->Connect(remoteIPAddress, serverPort, 0, 0, 0) == RakNet::CONNECTION_ATTEMPT_STARTED;
		if (tryingToConnect == false)
		{
			FILE_LOG(logINFO) << "Client wont start connecting?";
		}
	}

	void CLIENT::netHandler::receivePackets() {
		this->packetreceiver.receive();
	}

	void CLIENT::netHandler::disconnect() {
		if(isConnected) {
			peer->CloseConnection(peer->GetSystemAddressFromIndex(0),true,0);
			isConnected = false;
		}
	}

	void CLIENT::netHandler::sendTestPacket() {
		//packetSender.send(somethinglol);
	}

	void netHandler::tick() {
		receivePackets();
	}

} /* End of namespace CLIENT */
