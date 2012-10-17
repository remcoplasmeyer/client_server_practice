/*
 * Settings.cpp
 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */

#include "Settings.h"
#include <SFML/System.hpp>

Settings::Settings() {
	//hardcoded settings, for now
	username = "Anonymous";
	windowWidth = 800;
	windowHeight = 600;
	sf::Uint16 prot(321);
}

Settings::~Settings() {
	// TODO Auto-generated destructor stub
}

