/*
 * Settings.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */

#include "Settings.h"
#include <Windows.h>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include "Client.h"

Settings::Settings() {
	//hardcoded settings, for now
	username = "Anonymous";
	windowWidth = 1024;
	windowHeight = 768;
	sf::Uint16 prot(321);
	reconnectTimeOut = 600;
	clientPort = 1235;
}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
}

