#include "Server.h"
#include "serverSettings.h"
#include "../World.h"
#include "../Log.h"
#include "../packetTypes.h"

#include <SFML\Network.hpp>
#include "RakPeerInterface.h"
#include "RakString.h"
#include "GetTime.h"
#include "BitStream.h"
#include "MessageIdentifiers.h"



//Server program start
int main() {
	SERVER::Server server;
	return 0;
}

namespace SERVER {


Server::Server() {
	setupConnection();
	initWorld();

	int wantedFrameTime = 1000/settings.fps;			//time of each tick, in ms
	sequence = 0;
	lastUpdatedTime = RakNet::GetTimeMS();

	//server loop
	while(true) {
		//check our time step!
		currentTime = RakNet::GetTimeMS();
		if((currentTime - lastUpdatedTime) >= wantedFrameTime) {
			//this is all called every 1000/settings.fps milliseconds
			tick();
			sequence++;
			lastUpdatedTime = currentTime;
		}
	}
}

void Server::initWorld() {

}

//setup the connection with RakNet
void Server::setupConnection() {
	FILE_LOG(logINFO) << "Setting up server connection";
	peer = RakNet::RakPeerInterface::GetInstance();
	RakNet::SocketDescriptor socketDescriptor;
	socketDescriptor.port = settings.port;
	bool b = peer->Startup(settings.maxPlayers,&socketDescriptor,1) == RakNet::RAKNET_STARTED;
	RakAssert(b);
	peer->SetMaximumIncomingConnections(settings.maxPlayers);
	serverIP = sf::IpAddress::getPublicAddress();
	FILE_LOG(logINFO) << "Connect setup at: " << serverIP.toString() << ":" << settings.port;
}

//this is all called every 1000/settings.fps milliseconds - server loop
void Server::tick() {
	this->updateBasePacket();
	RakNet::Packet *packet = peer->Receive();
	//receive aaaalll the packets
	while(packet) {
		switch (packet->data[0])
		{
				case ID_CONNECTION_LOST:
					FILE_LOG(logINFO) << "CONNECTION LOST SOMEWHERE?";
					break;
				case ID_DISCONNECTION_NOTIFICATION:
					break;
				case ID_NEW_INCOMING_CONNECTION:
					FILE_LOG(logINFO) << "NEW CONNECTION: " << packet->systemAddress.ToString();
					
					basePacket base;
					base.useTimeStamp = (unsigned char)ID_TIMESTAMP;
					base.typeId = INIT_CONNECTOR_PACKET;
					base.timeStamp = RakNet::GetTime();
					initConnectorPacket p;
					p.base = base;
					//p.mapJSON = this->currentWorld.mapLoader.mapJSON;
					p.mapJSON = RakNet::RakString(this->currentWorld.mapLoader.mapJSON.c_str());
					RakNet::BitStream stream;

					stream.Write(base.useTimeStamp);
					stream.Write(base.timeStamp);
					stream.Write((RakNet::MessageID)base.typeId);
					stream.Write(p.mapJSON);
					peer->Send(&stream, LOW_PRIORITY, RELIABLE, 1, packet->systemAddress, false, 0);
					break;
		}
		//remove packet, get next one
		peer->DeallocatePacket(packet);
		packet = peer->Receive();
	}
}

void Server::updateBasePacket() {
	basepacket.timeStamp = RakNet::GetTime();
}

Server::~Server() {
	RakNet::RakPeerInterface::DestroyInstance(peer);
}


} /* End of namespace SERVER */
