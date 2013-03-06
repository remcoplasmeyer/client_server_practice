#include "../Log.h"
#include "../packetTypes.h"
#include "gameHandler.h"
#include "packetReceiver.h"
#include "netHandler.h"
#include "RakPeerInterface.h"
#include "BitStream.h"
#include "RakNetTypes.h"
#include "RakString.h"
#include "Client.h"
#include "../World.h"
#include <sstream>

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
						RakNet::RakString receivedMap;
						bitstream.Read(receivedMap);
						const char* mapCStr = receivedMap.C_String();
						std::stringstream s;
						s << mapCStr;
						unsigned long receivedUniqueid;
						bitstream.Read(receivedUniqueid);
						this->nethandler->client->gameHandler.setMapFromStream(s);
					}
					break;
				case PLAYERMOVE_PACKET:
					{
							//FILE_LOG(logDEBUG) << "RECEIVED PLAYER MOVE PACKET";
					}
					break;
			}
		} 
	}
} /* End of namespace CLIENT */
