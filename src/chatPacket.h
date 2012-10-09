/*
 * Packet.h
 *
 *  Created on: Oct 9, 2012
 *      Author: Remco
 */

#ifndef PACKET_H_
#define PACKET_H_
#include <string>
#include <SFML/Network.hpp>
#include "World.h"

class chatPacket {
public:
	World world;
	std::string message;
	sf::IpAddress senderIP;		//always IP of the client, never the server

	chatPacket();
	virtual ~chatPacket();
};

#endif /* PACKET_H_ */
