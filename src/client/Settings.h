/*
 * Settings.h
 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */

#ifndef SETTINGS_H_
#define SETTINGS_H_
#include <string>
#include <SFML/System.hpp>

/*contains all the settings of client, hardcoded for now
 * also contains default settings for when settings can not be loaded or do not exist
 */

class Settings {
public:
	unsigned int clientPort;
	unsigned int windowHeight;
	unsigned int windowWidth;
	unsigned int reconnectTimeOut;
	sf::Uint16 prot;										//protocol id, client version or something like that
	std::string username;

	Settings();
	~Settings();
};

#endif /* SETTINGS_H_ */
