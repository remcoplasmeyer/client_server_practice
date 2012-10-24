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
#include "../Player.h"
#include <boost/shared_ptr.hpp>

class Client;					//we don't include Client.h in the header file to prevent infinite recursion

class GUI {
public:
	Client *client;
	sf::RenderWindow *window;					//pointer because i'm too lazy to use initializer lists

	typedef boost::shared_ptr<Drawable> todraw_ptr;
	std::vector<todraw_ptr> toDraw;				//objects that are going to be drawn in current iteration

	//things gotten from the map
	std::vector<Sprite> mapSprites;				//list of single 64*64 sprites, these will be drawn
	std::vector<sf::Texture> mapTextures;		//list of .png textures
	std::vector<int> mapTexturesIndex;

	//textures
	std::map<std::string, GLuint> textures;				//map of all mandatory opengl textures (particles etc)
	std::map<std::string, sf::Texture> spriteTextures;		//map of all mandatory sfml textures (sprites)


	GUI() { };
	GUI(Client*);
	~GUI();

private:
	void drawAllObjects();
	void loadTexturesIntoMap(std::vector<std::string> &textureFiles, std::map<std::string, GLuint> &texturesVector);
	void loadSpritesIntoMap(std::vector<std::string> &textureFiles, std::map<std::string, sf::Texture> &texturesMap);
	void loadAllTextures();
	void resetMapSprites();
};

#endif /* GUI_H_ */
