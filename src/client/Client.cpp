#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "GUI.h"
#include "Client.h"

int main()
{
	Client client;
	return 0;
}

Client::Client() {
	Settings settings();								//load settings
	GUI gui(this);

	//standard values
	serverPort = 1234;
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
	sendingPacket << type << this->settings.username;
	clientSocket.send(sendingPacket, serverIP, serverPort);
}
