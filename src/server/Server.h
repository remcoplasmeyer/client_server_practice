/*
 * Server.h
 *
 *  Created on: Oct 8, 2012
 *      Author: Remco
 */


#ifndef SERVER_H_
#define SERVER_H_
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Network.hpp>
#include <vector>
#include <map>
#include "packetSender.h"
#include "../Player.h"
#include "../World.h"

class Server {
public:
	typedef std::map<std::string, Player> playerMap;
	playerMap players;								//map of players, key of the map is the ip address of the player

	World currentWorld;
	packetSender packetsender;

	sf::IpAddress serverIP;
	short unsigned int serverPort;
	short unsigned int clientPort;
	sf::UdpSocket serverSocket;

	//basePacket
	sf::Uint16 prot;				//current protocol number
	sf::Uint32 sequence;			//this is the sequence number of our server/packet

	Server();
	virtual ~Server();
	sf::IpAddress getIP();
};

#endif /* SERVER_H_ */
