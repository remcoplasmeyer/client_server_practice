#include "Server.h"
#include "../Log.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "packetSender.h"
#include "../Map.h"
#include "../Packet.h"
#include "../World.h"


Server::Server() {
	this->serverIP = sf::IpAddress::getPublicAddress();
	serverPort = 1234;
	serverSocket.bind(serverPort);

	//setBlocking makes the socket continue regardless of a new connection
	serverSocket.setBlocking(false);
	std::cout << "SERVER STARTED AT " << serverIP.toString() << ":" << serverPort << std::endl;

	//server loop
	float frametime;
	sf::Clock clock;
	this->sequence = 0;

	//MANUALLY MAKE WORLD FOR NOW
	//init a world and packetsender
	packetsender.setServer(this);
	World world;
	world.setMap("test");

	while(true) {
		sequence++;
		frametime = clock.getElapsedTime().asSeconds();					//this is the amount of frames elapsed since the last loop

		//TODO: WE STILL HAVE TO DO SOMETHING WITH THE ACK HERE
		basePacketStruct serverBasePacket { this->prot, this->sequence, 1, 1 };

		sf::Packet receivingPacket;
		sf::IpAddress receivingAddress;
		unsigned short int receivingPort;
		if(serverSocket.receive(receivingPacket, receivingAddress, receivingPort) == sf::Socket::Done) {
			//we get the basePacket(which every packet contains) from the packet
			int type;
			receivingPacket >> type;
			basePacketStruct basePacket;
			receivingPacket >> basePacket;
			switch(type) {
			case CONNECTPACKET:
			{	//added curly brackets for scope problems
				/*	someone connected, so we:
				 * 		send the connector the map data
				 * 		add his player to the world
				 * 		notify all other clients of a new player
				 */
				connectPacketStruct connectPacket;
				receivingPacket >> connectPacket;
				this->players[receivingAddress.toString()] = Player(connectPacket.name);
				serverMessageStruct serverMessage = { "NEW PLAYER CONNECTED: " + connectPacket.name };
				this->packetsender.addToQueue(Packet(serverMessage, serverBasePacket));
				newPlayerInitStruct newPlayerInit { this->currentWorld.currentMap.name };
				this->packetsender.addToQueue(Packet(newPlayerInit, serverBasePacket));
			}
				break;
			case CHATPACKET:
			{
				chatPacketStruct chatPacket;
				receivingPacket >> chatPacket;
				std::cout << "NEW MSG: " << chatPacket.message << std::endl;
			}
				break;
			case MOVEPACKET:
				//update world with movement
				break;
			}
		}
		//updateworld here

		//send packets here
		packetsender.sendQueueToAll();

	}

}

sf::IpAddress Server::getIP() {
	return this->serverIP;
}

Server::~Server() {

}

int main()
{
	//Starting here, opening new server
	Server server;
    return 0;
}

