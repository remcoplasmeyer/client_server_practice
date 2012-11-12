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
	clientPort = 1235;
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
	currentWorld.setMap("test");

	int loop = 0;
	int fps = 1000/60;
	while(true) {

		frametime = clock.getElapsedTime().asMilliseconds();					//this is the amount of frames elapsed since the last loop
		if(frametime >= (fps)) {
			this->sequence++;
			loop++;
			if(loop == 5) {
				loop = 0;
			}
			//TODO: WE STILL HAVE TO DO SOMETHING WITH THE ACK HERE
			basePacketStruct serverBasePacket { this->prot, this->sequence, 1, 1};

			sf::Packet receivingPacket;
			sf::IpAddress receivingAddress;
			unsigned short int receivingPort;
			while(serverSocket.receive(receivingPacket, receivingAddress, receivingPort) == sf::Socket::Done) {
				//we get the basePacket(which every packet contains) from the packet
				int type;
				receivingPacket >> type;
				basePacketStruct basePacket;
				receivingPacket >> basePacket;
				//HANDLE AAALLLL THE PACKETS
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
					FILE_LOG(logINFO) << "New player connected at " << connectPacket.clientPort <<": " << connectPacket.name << " at: " << receivingAddress.toString();
					int playerID = this->currentWorld.players.size()+1;
					World* worldptr;
					worldptr = &this->currentWorld;
					Player connectingPlayer(connectPacket.name, receivingAddress, playerID, worldptr);
					connectingPlayer.clientPort = connectPacket.clientPort;
					std::stringstream ss;
					ss << connectingPlayer.clientPort;
					this->players[receivingAddress.toString() + ":" + ss.str()] = connectingPlayer;
					this->currentWorld.players[playerID] = Player(connectPacket.name, receivingAddress, playerID, worldptr);
					serverMessageStruct serverMessage = { "NEW PLAYER CONNECTED at: " + connectPacket.name };
					this->packetsender.addToQueue(Packet(serverMessage, serverBasePacket));

					//TODO: ONLY SEND THIS TO THE CONNECTING PLAYERS
					newPlayerInitStruct newPlayerInit = { this->currentWorld.currentMap.name, playerID };
					this->packetsender.addToQueue(Packet(newPlayerInit, serverBasePacket));
					FILE_LOG(logDEBUG) << "sent player init";

				}
					break;
				case CHATPACKET:
				{
					FILE_LOG(logDEBUG) << "chatPacket";
					chatPacketStruct chatPacket;
					receivingPacket >> chatPacket;
					std::cout << "NEW MSG: " << chatPacket.message << std::endl;
				}
					break;
				case MOVEPACKET:
					//update world with movement
					break;
				case PLAYERINPUTPACKET:
				{
					//we receive input from the player
					inputPacketStruct inputPacket;
					receivingPacket >> inputPacket;
					Player &inputPlayer = this->currentWorld.players[basePacket.id];
					inputPlayer.inputJump = inputPacket.jump;
					inputPlayer.inputDirection = inputPacket.direction;
				}
					break;
				}
			}
			//updateworld here/*
			this->currentWorld.tick();

			if(loop == 4) {
				//sending to players
				std::map<int, Player> &players = this->currentWorld.players;
				std::map<int, Player>::iterator playerItr;
				for(playerItr = players.begin(); playerItr != players.end(); playerItr++) {
					Player &player = playerItr->second;
					playerMoveStruct playerMovePacket = { player.id, player.x, player.y, player.velx, player.vely, player.inputDirection, player.inputJump };
					this->packetsender.addToQueue(Packet(playerMovePacket, serverBasePacket));
				}
				packetsender.sendQueueToAll();
			}

			clock.restart();
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

