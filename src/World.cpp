/*
 * World.cpp
 *
 *  Created on: Oct 9, 2012
 *      Author: Remco
 */

#include "World.h"
#include "Player.h"
#include "Log.h"
#include <map>
#include <cmath>

World::World() {
	// TODO Auto-generated constructor stub

}

World::~World() {
	// TODO Auto-generated destructor stub
}

void World::setMap(std::string mapName) {
	this->currentMap.loadMap(mapName);
}

void World::addPlayer(Player player) {
	this->players[player.id] = player;
}

void World::tick() {
	std::map<int, Player> &players = this->players;
	std::map<int, Player>::iterator playerItr;
	for(playerItr = players.begin(); playerItr != players.end(); playerItr++) {
		Player &player = playerItr->second;
		player.Tick();
	}
}

bool World::boundingBoxIntersect(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2) {
	float left1, left2;
	float right1, right2;
	float top1, top2;
	float bottom1, bottom2;

	left1 = x1;
	left2 = x2;
	right1 = x1 + width1;
	right2 = x2 + width2;
	top1 = y1;
	top2 = y2;
	bottom1 = y1 + height1;
	bottom2 = y2 + height2;

	if (bottom1 < top2) { return(false); }
	if (top1 > bottom2) { return(false); }

	if (right1 < left2) { return(false); }
	if (left1 > right2) { return(false); }

	return(true);
}
