#include "Server.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
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
	Map map("test");
	World world;
	world.setMap(&map);

	while(true) {
		//this is the amount of frames elapsed since the last loop
		frametime = clock.getElapsedTime().asSeconds();

		sf::Packet receivingPacket;
		sf::IpAddress receivingAddress;
		unsigned short int receivingPort;
		if(serverSocket.receive(receivingPacket, receivingAddress, receivingPort) == sf::Socket::Done) {
			int type;
			receivingPacket >> type;
			basePacketStruct basePacket;
			receivingPacket >> basePacket;
			switch(type) {
			case CONNECTPACKET:
			{															//added curly brackets for scope problems
				connectPacketStruct connectPacket;
				receivingPacket >> connectPacket;
				std::cout << "NEW USER: " << connectPacket.name << std::endl;
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

