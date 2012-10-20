/*
 * Sprite.cpp
 *
 *  Created on: Oct 19, 2012
 *      Author: Remco
 */

#include "Sprite.h"
#include "SFML/Graphics.hpp"
#include "GUI.h"
#include "../Log.h"

Sprite::Sprite() {
	// TODO Auto-generated constructor stub

}

Sprite::Sprite(GUI *gui, int mapTextureIndex, int x, int y) {
	this->textureX = x;
	this->textureY = y;
	this->mapTextureType = mapTextureIndex;
	this->gui = gui;
	sprite.setTexture(gui->mapTextures.at(mapTextureType));
	sprite.setTextureRect(sf::IntRect(textureX, textureY, 64, 64));
}

Sprite::~Sprite() {
	// TODO Auto-generated destructor stub
}

