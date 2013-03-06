#include "Player.h"
#include "World.h"
#include <vector>

Player::Player() {
	//never used.
}

Player::Player(unsigned long _uniqueid, World *_world) {
	this->uniqueid = _uniqueid;
	this->world = _world;
	this->set = &world->worldsettings;

	//standard starting vars
	this->velx = 0.f;
	this->vely = 0.f;
	this->inputDirection = NODIRECTION;

	//TODO: GENERATE THESE VARIABLES
	this->width = 41.f;
	this->height = 64.f;
	this->currentState.x = 0.f;
	this->currentState.y = 0.f;
	this->inAir = true;
}

void Player::tick() {
	this->previousState = this->currentState;

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

	resetCollisionVars();

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
	currentState.x = currentState.x + velx;
	currentState.y = currentState.y + vely;
	//CHECK IF WE'RE OUT OF MAP BOUNDS
	if(currentState.x < -1*set->TILESIZE) {
		currentState.x = this->world->mapWidth*set->TILESIZE + currentState.x;
	}
	else if(currentState.x > this->world->mapWidth*set->TILESIZE) {
		currentState.x = this->world->mapWidth*set->TILESIZE - currentState.x;
	}
	if(currentState.y > (this->world->mapHeight+1)*set->TILESIZE) {
		currentState.y = (this->world->mapHeight+1)*set->TILESIZE - currentState.y;
	}
	else if(currentState.y < -1*set->TILESIZE) {
		currentState.y = (this->world->mapHeight+1)*set->TILESIZE + currentState.y;
	}
	//DONE OUT OF BOUNDS CHECKING
	if(collisionBottom) {
		if(vely >= 0) {
			vely = 0;
			currentState.y = maxY;
			inAir = false;
		}
	}
	if(collisionRight) {
		currentState.x = maxX;
		velx = 0;
	}
	if(collisionLeft) {
		currentState.x = minX;
		velx = 0;
	}
	if(collisionTop) {
		if(vely < 0) {
			currentState.y = minY;
			vely = 0;
		}
	}


}

//called at the beginning of the ticking loop
void Player::resetCollisionVars() {
	collisionBottom = false;
	collisionTop = false;
	collisionLeft = false;
	collisionRight = false;
}

void Player::checkCollision() {
	//map tiles
	std::vector<std::vector<mapTile>> &tiles = this->world->mapTiles;
	std::vector<std::vector<mapTile>>::iterator tileItr;
	std::vector<mapTile>::iterator tileYItr;
	for(tileItr = tiles.begin(); tileItr != tiles.end(); tileItr++) {
		for(tileYItr = tileItr->begin(); tileYItr != tileItr->end(); tileYItr++) {
			mapTile tile = *tileYItr;
			if(tile.solid) {
				bool intersect;
				float checkY, checkX;
				if(vely == 0) { checkY = 1.f; } else { checkY = vely; }
				if(velx == 0) { checkX = 0.f; } else { checkX = velx; }
				intersect = this->world->boundingBoxIntersect(currentState.x+checkX, currentState.y+checkY, width, height, float(tile.location.x*set->TILESIZE), float(tile.location.y*set->TILESIZE), float(tile.width*set->TILESIZE), float(tile.height*set->TILESIZE));
				//if intersect is true, the player will intersect if we keep the current velx and vely
				if(intersect) {
					float tileY = tile.location.y*set->TILESIZE;
					float tileX = tile.location.x*set->TILESIZE;
					float tileYBottom = tileY+tile.height*set->TILESIZE;
					float tileXRight= tileX+tile.width*set->TILESIZE;
					//we should check the position of the player relative to the colliding object
					//but I'm too lazy right now, so we'll just use the direction we're walking right now
					//so, TODO: improve this
					//
					if(currentState.y+height+checkY >= tileY && (currentState.x<tileXRight && currentState.x+width>tileX)) {
						collisionBottom = true;
						maxY = tileY-height;
					}
					if(currentState.x+width <= tileX && currentState.x+width+checkX >= tileX && (currentState.y+height > tileY)) {
						collisionRight = true;
						maxX = tileX-width;
					}
					if(currentState.y >= tileYBottom && currentState.y+checkY <= tileYBottom && (currentState.x<tileXRight && currentState.x+width>tileX)) {
						collisionTop = true;
						minY = tileYBottom;
					}
					if(currentState.x >= tileXRight && currentState.x+checkX <= tileXRight && (currentState.y+height > tileY)) {
						collisionLeft = true;
						minX = tileXRight;
					}

				}
			}
		}
	}
}

void Player::respawn() {
}

void Player::checkIntersection() {
}

