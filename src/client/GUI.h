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
#include <gl/glu.h>

class Client;					//we don't include Client.h in the header file to prevent infinite recursion

class GUI {
public:
	Client *client;
	sf::Window window;

	std::vector<GLuint> textures;		//this vector should relate to the enum type in <Particle.h>

	GUI() { };
	GUI(Client*);
	~GUI();

private:
	void loadTextures();
};

#endif /* GUI_H_ */
