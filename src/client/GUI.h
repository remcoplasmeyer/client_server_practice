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
#include "Sprite.h"
#include <boost/shared_ptr.hpp>

class Client;					//we don't include Client.h in the header file to prevent infinite recursion
enum guiState { NOGUI, GUIMAINSCREEN, GUIINGAME, GUILOADINGWORLD, GUILOADINGMAINSCREEN };

class GUI {
public:
	Client *client;
	sf::RenderWindow window;
	int state;

	typedef boost::shared_ptr<Drawable> todraw_ptr;
	std::vector<todraw_ptr> toDraw;				//objects that are going to be drawn in current iteration
	std::vector<GLuint> textures;				//this vector should relate to the enum type in <Particle.h>

	//things gotten from the map
	std::vector<Sprite> mapSprites;				//list of single 64*64 sprites, these will be drawn
	std::vector<sf::Texture> mapTextures;		//list of .png textures
	std::vector<int> mapTexturesIndex;

	GUI() { };
	GUI(Client*);
	~GUI();

private:
	void drawAllObjects();
	void loadTextures();
	void resetMapSprites();
};

#endif /* GUI_H_ */
