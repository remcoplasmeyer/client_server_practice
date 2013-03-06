#ifndef Player_h
#define Player_h
#include <string>
#include "World.h"
#include "worldSettings.h"

enum directionInput { NODIRECTION, INPUT_LEFT, INPUT_RIGHT };
enum playerState { STANDING, RUNNING, INAIR, DUCKING };
class Player {

	//state contains all data that is necessary to do an interpolation
	struct playerState {
		int x;
		int y;
	};

 public:
	World* world;
	worldSettings* set;
	playerState currentState;
	playerState previousState;

	Player();
	Player(unsigned long uniqueid, World *_world);
    void tick();
	void respawn();
    void checkIntersection();
	void resetCollisionVars();
	void checkCollision();

	//char vars
	float width, height;
	float velx, vely;
	float maxY, maxX, minY, minX;					//velocity
	int state;

	//stuff that have to do with the player's state
	bool collisionBottom, collisionTop, collisionLeft, collisionRight;
	bool inAir;			//in air or standing on solid object
	bool goingRight;	//going right (velx>0)

	//controls
	int inputDirection;			//0 = nothing, 1=right, 2=left
	bool inputJump;

 public:
    unsigned long uniqueid;
    std::string name;

};

#endif // Player_h
