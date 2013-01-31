#include "../Log.h"
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <iostream>
#include "GUI.h"
#include "Client.h"
#include "../Player.h"
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
	state = INITLOAD;
	Settings settings();								//load settings
	connected = false;
	this->serverPort = 1234;
	this->clientPlayerID = 0;
	FILE_LOG(logDEBUG) << this->clientPlayerID;
	//end standard values
	sf::IpAddress publicIP = this->clientIP.getPublicAddress();

	clientSocket.bind(sf::Socket::AnyPort);
	this->settings.clientPort = clientSocket.getLocalPort();
	FILE_LOG(logDEBUG) << "PORT: " << this->settings.clientPort;
	clientSocket.setBlocking(false);
	//HARDCODED STUFF TODO: INIT THESE VIA GUI/SETTINGS/SERVER/WHATEVER
	std::string hardCodedIP = "83.82.82.41";
	//sf::IpAddress serverIPHolder;
	if(hardCodedIP == publicIP.toString()) {
		this->serverIPHolder = sf::IpAddress(hardCodedIP);			//hardcoded for now
	} else {
		this->serverIPHolder = sf::IpAddress("127.0.0.1");
	}
	serverIP = &serverIPHolder;

	state = INGAME;
	//END HARDCODED STUFF

	state = CONNECTING;
	this->connectServer(*serverIP);
	//init gui, contains loop
	GUI guiptr(this);
}

Client::~Client() {
	//nothing yet
}

void Client::setGUI(GUI *gui) {
	this->gui = gui;
}

Packet Client::receivePacket() {
	Packet returnPacket;
	sf::Packet receivingPacket;
	sf::IpAddress receivingAddress;
	unsigned short int receivingPort = this->settings.clientPort;
	if(clientSocket.receive(receivingPacket, receivingAddress, receivingPort) == sf::Socket::Done) {
		//we get the basePacket(which every packet contains) from the packet
		int type;
		receivingPacket >> type;
		basePacketStruct basePacket;
		receivingPacket >> basePacket;
		switch(type) {
		case CONNECTPACKET:
		{
			FILE_LOG(logINFO) << "received connectpacket";
			connectPacketStruct connectPacket;
			receivingPacket >> connectPacket;
			returnPacket = Packet(connectPacket, basePacket);
		}
			break;
		case NEWPLAYERPACKET:
		{
			newPlayerPacketStruct newPlayer;
			receivingPacket >> newPlayer;
			World *worldptr = &world;
			world.addPlayer(Player(newPlayer.name, *this->serverIP, newPlayer.playerID, worldptr));
			break;
		}
		case NEWPLAYERINITPACKET:
		{
			FILE_LOG(logDEBUG) << "new player";
			newPlayerInitStruct newPlayerPacket;
			receivingPacket >> newPlayerPacket;
			if(this->clientPlayerID == 0) {
				this->world.currentMap.loadMap(newPlayerPacket.mapName);
				this->clientPlayerID = newPlayerPacket.playerID;
				FILE_LOG(logDEBUG) << this->clientPlayerID;
				state = INGAME;
				connected = true;
			}
			World *worldptr = &world;
			world.addPlayer(Player("Remco", *this->serverIP, newPlayerPacket.playerID, worldptr));
			break;
		}
		case MOVEPACKET:
			//update world with movement
			break;
		case PLAYERMOVEPACKET:
		{
		//receiving movement of other player
			playerMoveStruct playerMovePacket;
			if(receivingPacket >> playerMovePacket) {		//received successfully
				if(!(this->world.players.find(playerMovePacket.playerid) == this->world.players.end()) ) {
					Player* player;
					player = &this->world.players[playerMovePacket.playerid];
					if(basePacket.sequence > player->sequence) {
						player->sequence = basePacket.sequence;
						if(playerMovePacket.playerid == this->clientPlayerID) {
							//received packet of own player
							//todo: figure out good number here or handle better
							int maxDiffer = 2;
							if(abs(player->x-playerMovePacket.x) > maxDiffer || abs(player->y-playerMovePacket.y) > maxDiffer) {
								player->x = playerMovePacket.x;
								player->y = playerMovePacket.y;
								player->velx = playerMovePacket.velx;
								player->vely = playerMovePacket.vely; 
							}

						} else {
							//received packet of other player
							/* INTERPOLATION INSTEAD OF EXTRAPOLATION
							FILE_LOG(logDEBUG) << "ITNERPOLATING:" << playerMovePacket.x;
							player->interpolateX = playerMovePacket.x;
							player->interpolateY = playerMovePacket.y;
							if(playerMovePacket.velx != 0) {
								player->velx = playerMovePacket.velx;
							}
							if(playerMovePacket.vely != 0) {
								player->vely = playerMovePacket.vely;
							}
							*/
							int maxDiffer = 2;
							FILE_LOG(logDEBUG) << player->x;
							FILE_LOG(logDEBUG) << playerMovePacket.x;
							if(abs(player->x-playerMovePacket.x) > maxDiffer || abs(player->y-playerMovePacket.y) > maxDiffer) {
								player->x = playerMovePacket.x;
								player->y = playerMovePacket.y;
								player->velx = playerMovePacket.velx;
								player->vely = playerMovePacket.vely;
							}

							player->inputDirection = playerMovePacket.direction;
							player->inputJump = playerMovePacket.jump;
						}
					}
				} else {
					//request player info
					FILE_LOG(logDEBUG) << "asking for new player info";
					requestPlayerPacketStruct requestPacket = { playerMovePacket.playerid };
					Packet packet(requestPacket, this->basePacket);
					sendPacket(&packet);
				}
			} else {
				FILE_LOG(logDEBUG) << "something went wrong with the packet translation";
			}
		}
			break;
		}
	}
	return returnPacket;
}

void Client::connectServer(sf::IpAddress serverIP) {
	//go to loading screen or something here
	clientSocket.setBlocking(true);
	sf::Uint16 ack(1);
	sf::Uint32 ackbitfield(1);
	basePacketStruct basePacket		  = { this->settings.prot, this->sequence, ack, ackbitfield };
	connectPacketStruct connectHolder = { this->settings.username, this->settings.clientPort };
	Packet connectPacket(connectHolder, basePacket);
	Packet* packetptr = &connectPacket;
	sendPacket(packetptr);
	int i = 0;
	//TODO: MAKE THIS BETTER IN CASE OF PACKET LOSS
	FILE_LOG(logDEBUG) << "packet sent";
	while(!connected || i >= this->settings.reconnectTimeOut) {
		this->receivePacket();
	}
	clientSocket.setBlocking(false);
}

void Client::getServerPackets() {
	receivePacket();
}

void Client::sendInput() {
	if(connected) {
		inputPacketStruct inputPacket = { world.players[this->clientPlayerID].inputJump, world.players[this->clientPlayerID].inputDirection };
		Packet input(inputPacket, this->basePacket);
		sendPacket(&input);
	}
}

void Client::sendPacket(Packet *packet) {
	clientSocket.send(packet->sendingPacket, *serverIP, serverPort);
}

void Client::setBasePacket() {
	basePacketStruct basePacketPtr = { this->settings.prot, this->sequence, 1, this->clientPlayerID };
	this->basePacket = basePacketPtr;
}

//this function handles all the input, in every state
void Client::getInputAndTick() {
	//HANDLE INPUT FIRST
	switch(state) {
	case INGAME:
		this->setBasePacket();

	//client is in-game, so we get the controls input
		if(this->gui->focus) {
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
				world.players[this->clientPlayerID].inputJump = true;
			} else {
				world.players[this->clientPlayerID].inputJump = false;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
				world.players[this->clientPlayerID].inputDuck = true;
			} else {
				world.players[this->clientPlayerID].inputDuck = false;
			}
			if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				world.players[this->clientPlayerID].inputDirection = INPUT_LEFT;
			}
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				world.players[this->clientPlayerID].inputDirection = INPUT_RIGHT;
			}
			if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
				world.players[this->clientPlayerID].inputDirection = NODIRECTION;
			}

			this->sendInput();
		}
		this->receivePacket();

		//NOW TICK AAAAALL THE ENTITIES
		//LOOP AAAALLL THE PLAYERS
		std::map<int, Player> &players = this->world.players;
		std::map<int, Player>::iterator playerItr;
		for(playerItr = players.begin(); playerItr != players.end(); playerItr++) {
			Player &player = playerItr->second;
			if(player.id != this->clientPlayerID) {
				player.Tick();
			}
		}
//		this->world.tick();		we'll only do this at the server, we only tick our own player here
		this->world.players[this->clientPlayerID].Tick();
			break;
	}
}

boost::random::mt19937 gen = boost::random::mt19937();
int generate_random_number(int min, int max) {
	boost::random::uniform_int_distribution<> dist(min, max);
	return dist(gen);
}
