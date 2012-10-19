/*
 * Player.h
 *
 *  Created on: Oct 18, 2012
 *      Author: Remco
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <SFML/Network.hpp>

class Player {
public:
	std::string name;
	std::string ipString;				//save ip as a string so we don't have to convert it everytime
	sf::IpAddress ip;

	int x, y, width, height;

	Player();
	Player(std::string name, sf::IpAddress ipString);
	~Player();
};

#endif /* PLAYER_H_ */
