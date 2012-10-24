/*
 * Player.cpp
 *
 *  Created on: Oct 18, 2012
 *      Author: Remco
 */

#include "Player.h"
#include <string>
#include <SFML/Network.hpp>
#include "World.h"
#include "worldSettings.h"
#include "Log.h"

Player::Player() {
	// TODO Auto-generated constructor stub

}

Player::Player(std::string name, sf::IpAddress ip, int id, World *world) {
	this->name = name;
	this->ipString = ip.toString();
	this->ip = ip;
	this->id = id;
	this->velx = 0.f;
	this->vely = 0.f;
	this->world = world;
	this->set = &world->settings;

	//TODO: GENERATE THESE VARIABLES
	this->width = 32.f;
	this->height = 64.f;
	this->x = 0.f;
	this->y = 0.f;
	this->inAir = true;

	this->texturePath = "images/chars/mario/template.png";
	this->textureStep = 0;
}

Player::~Player() {
	// TODO Auto-generated destructor stub
}

void Player::Tick() {
	oldx = x;
	oldy = y;
	int xDirection;
	if(inputDirection == INPUT_LEFT) {
		xDirection = -1.f;
	}
	else if(inputDirection == INPUT_RIGHT) {
		xDirection = 1.f;
	} else {
		xDirection = 0.f;
	}
	resetCheckingVars();
	checkCollision();
	if(!collisionBottom) { inAir = true; } else { inAir = false; }
	//Player is in the air

	if(inAir) {
		state = INAIR;
		//we're in the air
		vely = vely + set->GRAVITATION;
	} else {
		//we're on something solid
		vely = 0.f;
		if(inputJump) {
			inAir = true;
			vely = -1*set->VELJUMP;
		} else {
			if(xDirection != 0.f) {
				state = RUNNING;
				velx = velx + xDirection * set->VELMOVING;
				if(textureStep > 9) { textureStep = 0; } else { textureStep++; }
			} else {
				if(velx > 0) { velx = velx - set->VELMOVING; }
				if(velx < 0) { velx = velx + set->VELMOVING; }
				state = STANDING;
			}
		}
	}
	if(velx > set->MAXWALKSPEED) { velx = set->MAXWALKSPEED; }
	if(velx < set->MAXWALKSPEED*-1.f) { velx = set->MAXWALKSPEED*-1; }
	x = x + velx;
	y = y + vely;
	if(collisionBottom) {
		y = maxY-height;
		inAir = false;
	}
}

//we divide all player states etc in separate functions, for readable code
void Player::jump(float modifier) {

}

void Player::resetCheckingVars() {
	collisionBottom = false;
	collisionTop = false;
	collisionLeft = false;
	collisionRight = false;
}

//we check for collision with all objects in the game here
void Player::checkCollision() {
	//map tiles
	std::vector<std::vector<Tile> > &tiles = this->world->currentMap.tiles;
	std::vector<std::vector<Tile> >::iterator tileItr;
	std::vector<Tile>::iterator tileYItr;
	for(tileItr = tiles.begin(); tileItr != tiles.end(); tileItr++) {
		for(tileYItr = tileItr->begin(); tileYItr != tileItr->end(); tileYItr++) {
			Tile tile = *tileYItr;
			if(tile.solid) {
				bool intersect;
				float checkY;
				if(vely == 0) { checkY = 1.f; } else { checkY = vely; }
				intersect = this->world->boundingBoxIntersect(x+velx, y+checkY, width, height, float(tile.x*set->TILESIZE), float(tile.y*set->TILESIZE), float(tile.width*set->TILESIZE), float(tile.height*set->TILESIZE));
				if(intersect) {
					//check which way we're moving, to find the relative position to the tile
					//also decide the max x and y, to prevent getting in the tiles
					if(y+checkY+height > tile.y*set->TILESIZE && y+checkY+height < tile.y*set->TILESIZE+tile.height*set->TILESIZE) {
						collisionBottom = true;
						maxY = tile.y*set->TILESIZE;
					}
					else if(y+checkY < tile.y*set->TILESIZE && y+checkY > tile.y) {
						collisionTop = true;
						maxY = tile.y*set->TILESIZE;
					}
				}
			}
		}
	}
}

