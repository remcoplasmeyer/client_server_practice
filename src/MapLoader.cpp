#include "MapLoader.h"
#include "World.h"
#include <string>

/*
	[MapLoader] is used to .map files into a world
*/

MapLoader::MapLoader() {

}

MapLoader::MapLoader(World *_world) {
	this->world = _world;
}


void MapLoader::loadMap(std::string mapName)
{
}
