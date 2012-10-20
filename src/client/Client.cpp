#include "../Log.h"
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "GUI.h"
#include "Client.h"
#include "../Packet.h"
#include "../Map.h"
#include <boost/random/mersenne_twister.hpp>
#include <boost/random/uniform_int.hpp>

int main() {
	Client client;
	return 0;
}

Client::Client() {
	//standard values
	Settings settings();								//load settings
	serverPort = 1234;
	//end standard values

	clientSocket.bind(this->settings.clientPort);

	//HARDCODED STUFF TODO: INIT THESE VIA GUI/SETTINGS/SERVER/WHATEVER
	sf::IpAddress serverIP("94.208.18.229");			//hardcoded for now
	world.setMap("test");
	//END HARDCODED STUFF

//	this->connectServer(serverIP);
	//init gui, contains loop
	GUI gui(this);
}

Client::~Client() {
	//nothing yet
}

Packet Client::receivePacket() {
	Packet returnPacket;
	sf::Packet receivingPacket;
	sf::IpAddress receivingAddress;
	unsigned short int receivingPort = this->settings.clientPort;
	FILE_LOG(logDEBUG) << "trying to receive at " << this->clientSocket.getLocalPort();
	if(clientSocket.receive(receivingPacket, receivingAddress, receivingPort) == sf::Socket::Done) {
		FILE_LOG(logDEBUG) << "received something";
		//we get the basePacket(which every packet contains) from the packet
		int type;
		receivingPacket >> type;
		basePacketStruct basePacket;
		receivingPacket >> basePacket;
		switch(type) {
		case CONNECTPACKET:
		{
			connectPacketStruct connectPacket;
			receivingPacket >> connectPacket;
			returnPacket = Packet(connectPacket, basePacket);
		}
			break;
		case CHATPACKET:
		{
			//
		}
			break;
		case MOVEPACKET:
			//update world with movement
			break;
		}
	}
	return returnPacket;
}

void Client::connectServer(sf::IpAddress serverIP) {
	//go to loading screen or something here
	sf::Uint16 ack(1);
	sf::Uint32 ackbitfield(1);
	basePacketStruct basePacket		  = { this->settings.prot, this->sequence, ack, ackbitfield };
	connectPacketStruct connectHolder = { this->settings.username };
	Packet connectPacket(connectHolder, basePacket);
	bool connected = false;
	clientSocket.send(connectPacket.sendingPacket, serverIP, serverPort);			//send connectpacket
	int i = 0;
	//TODO: MAKE THIS BETTER IN CASE OF PACKET LOSS
	FILE_LOG(logDEBUG) << "packet sent";
	while(!connected || i >= this->settings.reconnectTimeOut) {
		Packet receivedPacket = this->receivePacket();
		if(receivedPacket.packetType == NEWPLAYERINITPACKET) {
			FILE_LOG(logDEBUG) << receivedPacket.newPlayer.mapName;;
			connected = true;
		}
	}
}

boost::random::mt19937 gen = boost::random::mt19937();
int generate_random_number(int min, int max) {
	boost::random::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
