#include "MapLoader.h"
#include "World.h"
#include <string>
#include <sstream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>

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
	try {
		std::stringstream localStream;
		std::string mapLocation = "data/maps/" + mapName + ".map";
		std::ifstream t(mapLocation.c_str());
		localStream << t.rdbuf();

		boost::property_tree::ptree pt;
		boost::property_tree::read_json(localStream, pt);

		this->world->mapName = pt.get<std::string>("map.name");
		this->world->mapBackground = pt.get<std::string>("map.background");
		this->world->mapWidth = pt.get<int>("map.width");
		this->world->mapHeight = pt.get<int>("map.height");


		for(int i = 0; i < world->mapWidth;i++) {
			//create vector for every row for the 2d tile array
			//std::vector<Tile> tileVector;
			//this->tiles.push_back(tileVector);
			//for(int j=0; j < mapHeight;j++) {
			//	Tile tile(0,0,0,0,i,j);
			//	this->tiles.at(i).push_back(tile);
			//}
		}
		//get AAAALLL the tiles
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("map.tiles")) {
			/*
			assert(v.first.empty());
			int y = v.second.get<int>("y");
			int x = v.second.get<int>("x");
			int type = v.second.get<int>("t");
			int visual = v.second.get<int>("v");
			int textureX = v.second.get<int>("vx");
			int textureY = v.second.get<int>("vy");
			std::vector<Tile> *yVec = &tiles[x];
			yVec->insert(yVec->begin() + y, Tile(type,visual,textureX, textureY, x, y));
			*/
		}
		//get AAAALLL the spawn points
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("map.playerspawns")) {
			/*
			tileCoord playerSpawnPoint = { v.second.get<int>("x"), v.second.get<int>("y") };
			this->playerSpawns.push_back(playerSpawnPoint);
			*/
		}
	} catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}
