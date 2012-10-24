/*
 * Player.h
 *
 *  Created on: Oct 18, 2012
 *      Author: Remco
 */

#ifndef PLAYER_H_
#define PLAYER_H_
#include <SFML/Network.hpp>
class World;
#include "worldSettings.h"

enum directionInput { NODIRECTION, INPUT_LEFT, INPUT_RIGHT };
enum playerState { STANDING, RUNNING, INAIR, DUCKING };
class Player {
public:
	World *world;
	worldSettings *set;
	std::string name;
	std::string ipString;				//save ip as a string so we don't have to convert it everytime
	sf::IpAddress ip;

	int id, width, height;
	float oldx, oldy, x, y, velx, vely;
	float maxY, maxX, minY, minX;					//velocity
	int state;

	//stuff that have to do with the player's state
	bool collisionBottom, collisionTop, collisionLeft, collisionRight;
	bool inAir;			//in air or standing on solid object

	//controls
	int inputDirection;
	bool inputJump;
	bool inputDuck;

	//used for drawing
	std::string texturePath;
	int textureStep;

	Player();
	Player(std::string name, sf::IpAddress ipString, int id, World *world);
	void Tick();
	void jump(float modifier);
	void resetCheckingVars();
	void checkCollision();

	~Player();
};

#endif /* PLAYER_H_ */
