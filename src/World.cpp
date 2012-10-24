/*
 * World.cpp
 *
 *  Created on: Oct 9, 2012
 *      Author: Remco
 */

#include "World.h"
#include "Player.h"
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
	float midx1 = (x1+width1*0.5);
	float midx2 = (x2+width2*0.5);
	float midy1 = (y1+height1*0.5);
	float midy2 = (y2+height2*0.5);
	return ((abs(midx1 - midx2) * 2 < (width1 + width2)) && (abs(midy1 - midy2) * 2 < (height1 + height2)));
//	return ((abs(x1 - x2) * 2 < (width1 + width2)) && (abs(y1 - y2) * 2 < (height1 + height2)));
}
