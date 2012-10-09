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
#include "../chatPacket.h"
#include <vector>

class Server {
private:

	std::vector<chatPacket> chatPackets;

	sf::IpAddress serverIP;
	int serverPort;
	sf::UdpSocket serverSocket;

public:
	Server();
	virtual ~Server();
	sf::IpAddress getIP();
};

#endif /* SERVER_H_ */
