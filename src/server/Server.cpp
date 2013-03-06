#include "Server.h"
#include "serverSettings.h"
#include "../World.h"
#include "../Log.h"
#include "../packetTypes.h"

#include <SFML\Network.hpp>
#include "RakPeerInterface.h"
#include "RakNetTypes.h"
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

    float t = 0.0f;
	float dt = 1.f/(1000.f/settings.fps);

	RakNet::Time currentTime = RakNet::GetTimeMS();
	float accumulator = 0.0f;
	
	//client loop
	while (true) 
	{			
		RakNet::Time newTime = RakNet::GetTimeMS();
		float deltaTime = newTime - currentTime;
		currentTime = newTime;
		if (deltaTime > 0.25f)
			deltaTime = 0.25f;
		
		accumulator += deltaTime;
		while (accumulator >= dt)
		{
			accumulator -= dt;
			//previous = current;			TODO: IMPLEMENT STATES
			//integrate(current, t, dt);	TODO: integrate here

			tickWorld();
			sendGameState();
			t += dt;
		}
		tick();
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

void Server::tickWorld() {
	this->currentWorld.tick();
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
					unsigned long uniqueid = RakNet::RakNetGUID::ToUint32(packet->guid);
					//add player to world
					this->currentWorld.addPlayer(uniqueid);
					//send init packet to player
					basePacket base;
					base.useTimeStamp = (unsigned char)ID_TIMESTAMP;
					base.typeId = INIT_CONNECTOR_PACKET;
					base.timeStamp = RakNet::GetTime();
					initConnectorPacket p;
					p.base = base;
					p.mapJSON = RakNet::RakString(this->currentWorld.mapLoader.mapJSON.c_str());
					p.uniqueid = uniqueid;
					RakNet::BitStream stream;

					stream.Write(base.useTimeStamp);
					stream.Write(base.timeStamp);
					stream.Write((RakNet::MessageID)base.typeId);
					stream.Write(p.mapJSON);
					stream.Write(p.uniqueid);
					peer->Send(&stream, LOW_PRIORITY, RELIABLE, 1, packet->systemAddress, false, 0);
					break;
		}
		//remove packet, get next one
		peer->DeallocatePacket(packet);
		packet = peer->Receive();
	}
}

void Server::sendGameState() {
	//send state of all players
	std::map<unsigned long, Player> &players = this->currentWorld.players;
	std::map<unsigned long, Player>::iterator playerItr;
	for(playerItr = players.begin(); playerItr != players.end(); playerItr++) {
		Player &player = playerItr->second;

		//construct move packet
		basePacket base;
		base.useTimeStamp = (unsigned char)ID_TIMESTAMP;
		base.typeId = PLAYERMOVE_PACKET;
		base.timeStamp = RakNet::GetTime();


		//TODO: CLEAN THIS UP!
		playerMovePacket packet;
		packet.base = base;
		packet.uniqueid = player.uniqueid;
		packet.x = player.currentState.x;
		packet.y = player.currentState.y;
		packet.velx = player.velx;
		packet.vely = player.vely;
		packet.inputDirection = player.inputDirection;
		packet.inputJump = player.inputJump;
		
		RakNet::BitStream stream;
		stream.Write(base.useTimeStamp);
		stream.Write(base.timeStamp);
		stream.Write((RakNet::MessageID)base.typeId);
		stream.Write(packet.x);
		stream.Write(packet.y);
		stream.Write(packet.velx);
		stream.Write(packet.vely);
		stream.Write(packet.inputDirection);
		stream.Write(packet.inputJump);

		peer->Send(&stream, MEDIUM_PRIORITY, UNRELIABLE_SEQUENCED, 1, RakNet::UNASSIGNED_SYSTEM_ADDRESS, true, 0);
	}
}

void Server::updateBasePacket() {
	basepacket.timeStamp = RakNet::GetTime();
}

Server::~Server() {
	RakNet::RakPeerInterface::DestroyInstance(peer);
}


} /* End of namespace SERVER */
