#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "GUI.h"
#include "Client.h"
#include "../Packet.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>

int main() {
	Client client;
	return 0;
}

Client::Client() {
	Settings settings();								//load settings

	//standard values
	serverPort = 1234;
	//end standard values
	sf::UdpSocket clientSocket;
	sf::IpAddress serverIP("94.208.18.229");			//hardcoded for now

	this->connectServer(serverIP);

	//init gui, contains loop
	GUI gui(this);
}

Client::~Client() {
	//nothing yet
}

void Client::connectServer(sf::IpAddress serverIP) {
	//go to loading screen here
	sf::Uint16 ack(1);
	sf::Uint32 ackbitfield(1);
	basePacketStruct basePacket		  = { this->settings.prot, this->sequence, ack, ackbitfield };
	connectPacketStruct connectHolder = { this->settings.username };
	Packet connectPacket(connectHolder, basePacket);
	sf::Packet sendingPacket = connectPacket.getSendingPacket();
	clientSocket.send(sendingPacket, serverIP, serverPort);
}

boost::random::mt19937 gen = boost::random::mt19937();
int generate_random_number(int min, int max) {
	boost::random::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
