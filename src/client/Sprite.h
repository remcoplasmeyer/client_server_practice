/*
 * Sprite.h
 *
 *  Created on: Oct 19, 2012
 *      Author: Remco
 */

#ifndef SPRITE_H_
#define SPRITE_H_
#include "SFML/Graphics.hpp"

class GUI;
class Sprite {
public:
	//map & location settings
	int x, y, width, height;

	//texture settings
	int textureX, textureY;									//x and y (multiplication of 64) of the texture
	int mapTextureType;							//type sf::Texture, found in [GUI]::mapTextures
	sf::Sprite sprite;										//we'll eventually draw this
	GUI *gui;
	sf::Texture texture;

	Sprite();
	Sprite(GUI *gui, int mapTextureIndex, int x, int y);

	~Sprite();
};

#endif /* SPRITE_H_ */
