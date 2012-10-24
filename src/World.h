/*
 * World.h
 *
 *  Created on: Oct 9, 2012
 *      Author: Remco
 */

#ifndef WORLD_H_
#define WORLD_H_
#include "Map.h"
#include "Player.h"
#include <map>
#include "worldSettings.h"
#include "Player.h"

class World {
public:
	Map currentMap;
	std::map<int, Player> players;			//players, indexed by their unique id
	worldSettings settings;

	World();
	void Reset();
	void setMap(std::string mapName);

	void addPlayer(Player player);
	void deletePlayer(int playerID);
	void spawnPlayer(int playerID, int x, int y);
	void tick();
	bool boundingBoxIntersect(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);

	virtual ~World();
};

#endif /* WORLD_H_ */
