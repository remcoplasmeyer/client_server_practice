#include "../Log.h"
#include "../packetTypes.h"
#include "packetReceiver.h"
#include "netHandler.h"
#include "RakPeerInterface.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "RakString.h"

namespace CLIENT {

	packetReceiver::packetReceiver() {
	}

	void packetReceiver::setNethandler(netHandler *_nethandler) {
		this->nethandler = _nethandler;
	}

	//we receive all the packets here
	void packetReceiver::receive() {
		RakNet::Packet *packet;
		for (packet = this->nethandler->peer->Receive(); packet; this->nethandler->peer->DeallocatePacket(packet), packet = this->nethandler->peer->Receive()) {
			RakNet::BitStream bitstream(packet->data, packet->length, false); // The false is for efficiency so we don't make a copy of the passed data
			basePacket base;
			//we can receive bitstreams or something else
			if ((unsigned char)packet->data[0] == ID_TIMESTAMP) {
				bitstream.Read(base.useTimeStamp);
				bitstream.Read(base.timeStamp);
				bitstream.Read(base.typeId);
			} else {
				base.typeId = (unsigned char) packet->data[0];
			}
			
			switch (base.typeId)		//this is the packet's id (packetTypes.h)
			{
				//we receive the initial packet when connecting to a server
				case ID_CONNECTION_REQUEST_ACCEPTED:
					{
						FILE_LOG(logINFO) << "connection accepted";
					}
					break;
				case INIT_CONNECTOR_PACKET:
					{
						FILE_LOG(logINFO) << "received init connector";	
						RakNet::RakString test;
						bitstream.Read(test);
						FILE_LOG(logINFO) << test.C_String();
					}
					break;
			}
		} 
	}
} /* End of namespace CLIENT */
