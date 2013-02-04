#include "World.h"
#include "MapLoader.h"


World::World() {
	mapLoader = MapLoader(this);
	initTestWorld();
}

void World::initTestWorld() {
	setMap("test");
}

//update the whole world, called every server loop
void World::tick()
{
}

//restarts world 
void World::restartWorld()
{
}

//sets map to mapName, through [mapLoader]
void World::setMap(std::string mapName)
{
}

