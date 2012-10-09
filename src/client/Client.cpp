#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "Client.h"

int main()
{
	Client client;
	return 0;
}

Client::Client() {
	//standard values
	serverPort = 1234;
	username = "Anonymous";
	//end standard values
	sf::UdpSocket clientSocket;
	sf::IpAddress serverIP("94.208.18.229");			//hardcoded for now

	this->connectServer(serverIP);
}

Client::~Client() {
	//nothing yet
}

void Client::connectServer(sf::IpAddress serverIP) {
	sf::Packet sendingPacket;
	sf::Int8 type = 1;								//send type=1 so the server knows a new user is connecting
	sendingPacket << type << this->username;
	clientSocket.send(sendingPacket, serverIP, serverPort);
}
