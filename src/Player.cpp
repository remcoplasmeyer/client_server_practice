/*
 * Player.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: Remco
 */

#include "Player.h"
#include <string>
#include <SFML/Network.hpp>
Player::Player() {
	// TODO Auto-generated constructor stub

}

Player::Player(std::string name, sf::IpAddress ip) {
	this->name = name;
	this->ipString = ip.toString();
	this->ip = ip;
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

