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
#include <boost/shared_ptr.hpp>

class Client;					//we don't include Client.h in the header file to prevent infinite recursion

class GUI {
public:
	Client *client;
	sf::Window window;

	typedef boost::shared_ptr<Drawable> todraw_ptr;
	std::vector<todraw_ptr> toDraw;		//objects that are going to be drawn in current iteration
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
