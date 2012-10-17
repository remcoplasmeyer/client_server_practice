/*
 * World.h
 *
 *  Created on: Oct 9, 2012
 *      Author: Remco
 */

#ifndef WORLD_H_
#define WORLD_H_
#include "Map.h"

class World {
public:
	Map *currentMap;

	World();
	void Reset();
	void setMap(Map *map);
	virtual ~World();
};

#endif /* WORLD_H_ */
