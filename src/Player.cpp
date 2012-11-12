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

Player::Player(std::string name, sf::IpAddress ip, int id, World* world) {
	this->name = name;
	this->ipString = ip.toString();
	this->ip = ip;
	this->id = id;
	this->velx = 0.f;
	this->vely = 0.f;
	this->world = world;
	this->set = &world->settings;
	this->inputDirection = NODIRECTION;

	this->sequence = 0;
	//TODO: GENERATE THESE VARIABLES
	this->width = 41.f;
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
		goingRight = false;
		xDirection = -1.f;
	}
	else if(inputDirection == INPUT_RIGHT) {
		goingRight = true;
		xDirection = 1.f;
	} else {
		xDirection = 0.f;
	}
	resetCheckingVars();
	checkCollision();
	if(!collisionBottom) { inAir = true; } else {
		if(vely == 0) {
			inAir = false;
		}
	}
	//Player is in the air

	if(inAir) {
		state = INAIR;
		//we're in the air
		vely = vely + set->GRAVITATION;
		velx = velx + xDirection * set->AIRFRICTION;
	} else {
		//we're on something solid
		vely = 0.f;
		if(inputJump) {
			inAir = true;
			if(vely == 0) {
				vely = -1*set->VELJUMP;
			}
		} else {
			if(xDirection != 0.f) {
				state = RUNNING;
				velx = velx + xDirection * set->VELMOVING;
				if(textureStep > 13) { textureStep = 0; } else { textureStep++; }		//used for textures frames
			} else {
				state = STANDING;
				if(velx > 0) {
						velx = velx - set->GROUNDFRICTION;
						if(velx < 0) { velx = 0; }
				}
				else if(velx < 0) {
					velx = velx + set->GROUNDFRICTION;
					if(velx > 0) { velx = 0; }
				}
			}
		}
	}
	if(velx > set->MAXWALKSPEED) { velx = set->MAXWALKSPEED; }
	if(velx < set->MAXWALKSPEED*-1.f) { velx = set->MAXWALKSPEED*-1; }
	x = x + velx;
	y = y + vely;
	//CHECK IF WE'RE OUT OF MAP BOUNDS
	if(x < -1*this->world->settings.TILESIZE) {
		x = this->world->currentMap.width*this->world->settings.TILESIZE + x;
	}
	else if(x > this->world->currentMap.width*this->world->settings.TILESIZE) {
		x = this->world->currentMap.width*this->world->settings.TILESIZE - x;
	}
	if(y > (this->world->currentMap.height+1)*this->world->settings.TILESIZE) {
		y = (this->world->currentMap.height+1)*this->world->settings.TILESIZE - y;
	}
	else if(y < -1*this->world->settings.TILESIZE) {
		y = (this->world->currentMap.height+1)*this->world->settings.TILESIZE + y;
	}
	//DONE OUT OF BOUNDS CHECKING
	if(collisionBottom) {
		if(vely >= 0) {
			vely = 0;
			y = maxY;
			inAir = false;
		}
	}
	if(collisionRight) {
		x = maxX;
		velx = 0;
	}
	if(collisionLeft) {
		x = minX;
		velx = 0;
	}
	if(collisionTop) {
		if(vely < 0) {
			y = minY;
			vely = 0;
		}
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
				float checkY, checkX;
				if(vely == 0) { checkY = 1.f; } else { checkY = vely; }
				if(velx == 0) { checkX = 0.f; } else { checkX = velx; }
				intersect = this->world->boundingBoxIntersect(x+checkX, y+checkY, width, height, float(tile.x*set->TILESIZE), float(tile.y*set->TILESIZE), float(tile.width*set->TILESIZE), float(tile.height*set->TILESIZE));
				//if intersect is true, the player will intersect if we keep the current velx and vely
				if(intersect) {
					float tileY = tile.y*set->TILESIZE;
					float tileX = tile.x*set->TILESIZE;
					float tileYBottom = tileY+tile.height*set->TILESIZE;
					float tileXRight= tileX+tile.width*set->TILESIZE;
					//we should check the position of the player relative to the colliding object
					//but I'm too lazy right now, so we'll just use the direction we're walking right now
					//so, TODO: improve this
					//
					if(y+height+checkY >= tileY && (x<tileXRight && x+width>tileX)) {
						collisionBottom = true;
						maxY = tileY-height;
					}
					if(x+width <= tileX && x+width+checkX >= tileX && (y+height > tileY)) {
						collisionRight = true;
						maxX = tileX-width;
					}
					if(y >= tileYBottom && y+checkY <= tileYBottom && (x<tileXRight && x+width>tileX)) {
						collisionTop = true;
						minY = tileYBottom;
					}
					if(x >= tileXRight && x+checkX <= tileXRight && (y+height > tileY)) {
						collisionLeft = true;
						minX = tileXRight;
					}

				}
			}
		}
	}
}

void Player::interpolate() {

	if(this->x > this->interpolateX) {
		this->x = x+velx;
		if(this->x < this->interpolateX) {
			this->x = this->interpolateX;
		}
	} else if ( this->x < this->interpolateX) {
		this->x = x+velx;
		if(this->x > this->interpolateX) {
			this->x = this->interpolateX;
		}
	}

	if(this->y > this->interpolateY) {
		this->y = y+vely;
		if(this->y < this->interpolateY) {
			this->y = this->interpolateY;
		}
	} else if ( this->y < this->interpolateY) {
		this->y = y+vely;
		if(this->y > this->interpolateY) {
			this->y = this->interpolateY;
		}
	}

	if(abs(this->x - this->interpolateX) > 50) {
		FILE_LOG(logDEBUG) << "interp differ too large: " << abs(this->x - this->interpolateX);
		this->x = this->interpolateX;
	}
	if(abs(this->y - this->interpolateY) > 50) {
		FILE_LOG(logDEBUG) << "interp differ too large: " << abs(this->y - this->interpolateY);
		this->y = this->interpolateY;
	}
}
