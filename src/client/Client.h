/*
 * Client.h
 *
 *  Created on: Oct 8, 2012
 *      Author: Remco
 */
#ifndef CLIENT_H_
#define CLIENT_H_
#include <SFML/Network.hpp>
#include <string>
#include "../World.h"
#include "Settings.h"
#include "GUI.h"
#include "../Packet.h"

class Client {
public:
	int state;	enum clientState { INITLOAD, INGAME };		//client state

	sf::UdpSocket clientSocket;
	short unsigned int serverPort;
	GUI gui;
	World world;
	int clientPlayerID;					//id of the player this client controls
	Settings settings;

	sf::Uint32 sequence;				//current sequence nr

	Client();
	virtual ~Client();

	void getInputAndTick();
	void connectServer(sf::IpAddress);
	Packet receivePacket();
};

//bunch of functions that we use multiple times
int generate_random_number(int min, int max);

#endif /* CLIENT_H_ */
