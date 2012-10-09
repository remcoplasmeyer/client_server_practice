#include "Server.h"
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>

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
	while(true) {
		//this is the amount of frames elapsed since the last loop
		frametime = clock.getElapsedTime().asSeconds();

		sf::Packet receivingPacket;
		sf::IpAddress receivingAddress;
		unsigned short int receivingPort;
		if(serverSocket.receive(receivingPacket, receivingAddress, receivingPort) == sf::Socket::Done) {
			sf::Int8 type;
			std::string data;
			receivingPacket >> type >> data;
			switch(type) {
			case 1:
				std::cout << "NEW USER: " << data << std::endl;
				//connect packet
				break;
			case 2:
				//chatpacket
				break;
			}
		}

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

