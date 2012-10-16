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
#include "Drawable.h"

class Client;					//we don't include Client.h in the header file to prevent infinite recursion

class GUI {
public:
	Client *client;
	sf::Window window;

	std::vector<Drawable*> toDraw;		//objects that are going to be drawn in current iteration
	std::vector<Drawable*> toDrawNext;	//objects copied from previous iteration
	std::vector<GLuint> textures;		//this vector should relate to the enum type in <Particle.h>

	GUI() { };
	GUI(Client*);
	~GUI();

private:
	void drawAllObjects();

private:
	void loadTextures();
};

#endif /* GUI_H_ */
