#include "World.h"
#include "Log.h"
#include "MapLoader.h"


World::World() {
	mapLoader.setWorld(this);
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
	FILE_LOG(logDEBUG) << "Trying to load map: " << mapName;
	mapLoader.loadMap(mapName);
	FILE_LOG(logDEBUG) << "Should be done loading map...";
}

