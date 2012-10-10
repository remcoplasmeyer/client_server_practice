/*
 * GUI.h
 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */
#pragma once
#ifndef GUI_H_
#define GUI_H_
#include <SFML/Window.hpp>

class Client;					//we don't include Client.h in the header file to prevent infinite recursion

class GUI {
public:
	Client *client;
	sf::Window window;

	GUI() { };
	GUI(Client*);
	~GUI();
};

#endif /* GUI_H_ */
