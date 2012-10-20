/*
 * Tile.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: Remco
 */

#include "Tile.h"

Tile::Tile() {
	// TODO Auto-generated constructor stub

}

Tile::Tile(int type, int textureType, int textureX, int textureY, int x, int y) {
	this->type = type;
	this->tileImage = tileImage;
	this->textureType = textureType;
	//we'll calculate these later and just preset them for now
	this->offsetX = 0;
	this->offsetY = 0;
	this->angle = 0;
	this->vel = 0;

	this->x = x;
	this->y = y;

	this->height = 1.0f;
	this->width = 1.0f;

	switch(type) {
		case(TILE_NOTHING):
			this->solid = false;
			break;
		case(TILE_BLOCK):
			this->solid = true;
			this->underGoThrough = false;
			break;
	}
}

void Tile::setSprite(int spriteIndex) {
	this->spriteIndex = spriteIndex;
}

Tile::~Tile() {
	// TODO Auto-generated destructor stub
}

