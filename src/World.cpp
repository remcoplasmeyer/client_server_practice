#include "World.h"
#include "Log.h"
#include "MapLoader.h"
#include <string>
#include <vector>


World::World() {
	mapLoader.setWorld(this);
	initTestWorld();
	this->mapName = "testasdfasdf";
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
	this->mapTiles.clear();
	this->players.clear();
	this->spawnPoints.clear();
}

void World::JSONtoMap(std::stringstream &jsonmap) {
	FILE_LOG(logDEBUG) << "json to map...";
	mapLoader.JSONtoMap(jsonmap);
}

//sets map to mapName, through [mapLoader]
void World::setMap(std::string mapName)
{
	FILE_LOG(logDEBUG) << "Trying to load map: " << mapName;
	mapLoader.loadMap(mapName);
	FILE_LOG(logDEBUG) << "Should be done loading map...";
}

