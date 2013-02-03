#include "Server.h"
#include "serverSettings.h"
#include "../Log.h"

#include <SFML\Network.hpp>
#include "RakPeerInterface.h"
#include "GetTime.h"
#include "BitStream.h"



//Server program start
int main() {
	SERVER::Server server;
	return 0;
}

namespace SERVER {


Server::Server() {
	this->settings = SERVER::serverSettings();			//initializes settings of the server
	
	setupConnection();

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
	
}

Server::~Server() {
	RakNet::RakPeerInterface::DestroyInstance(peer);
}


} /* End of namespace SERVER */
