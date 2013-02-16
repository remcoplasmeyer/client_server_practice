#include "../Log.h"
#include "../packetTypes.h"
#include "packetReceiver.h"
#include "netHandler.h"
#include "RakPeerInterface.h"
#include "RakNetTypes.h"

namespace CLIENT {

	packetReceiver::packetReceiver() { }
	
	packetReceiver::packetReceiver(netHandler *_nethandler) { 
		this->nethandler = _nethandler;
	}

	//we receive all the packets here
	void packetReceiver::receive() {
		RakNet::Packet *packet;
		for (packet = this->nethandler->peer->Receive(); packet; this->nethandler->peer->DeallocatePacket(packet), packet = this->nethandler->peer->Receive()) {
			FILE_LOG(logDEBUG) << packet->data[0];
			switch (packet->data[0])		//this is the packet's id (packetTypes.h)
			{
				//we receive the initial packet when connecting to a server
				case INIT_CONNECTOR_PACKET:
					{
						initConnectorPacket *p = (initConnectorPacket*) packet->data;
						FILE_LOG(logDEBUG) << p->mapJSON;
					}
					break;
			}
		} 
	}
} /* End of namespace CLIENT */
