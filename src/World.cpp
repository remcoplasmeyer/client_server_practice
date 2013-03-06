#include "World.h"
#include "Log.h"
#include "MapLoader.h"
#include "Player.h"
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
	//tick each individual player
	playerList &players = this->players;
	playerList::iterator playerItr;
	for(playerItr = players.begin(); playerItr != players.end(); playerItr++) {
		Player &player = playerItr->second;
		player.tick();
	}
}

void World::addPlayer(unsigned long uniqueid) {
	Player player = Player(uniqueid, this);
	this->players[uniqueid] = player;
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
