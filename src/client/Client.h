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

class Client {
public:
	sf::UdpSocket clientSocket;
	short unsigned int serverPort;
	GUI gui;
	World world;
	Settings settings;

	Client();
	virtual ~Client();

	void connectServer(sf::IpAddress);
};

//bunch of functions that we use multiple times
int generate_random_number(int min, int max);

#endif /* CLIENT_H_ */
