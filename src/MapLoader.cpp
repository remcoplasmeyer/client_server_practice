#include "MapLoader.h"
#include "mapTile.h"
#include "World.h"
#include "location.h"
#include <string>
#include <list>
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
	this->mapBaseDir = "data/maps/";
	this->world = _world;
}

void MapLoader::loadMap(std::string mapName)
{
	try {
		std::stringstream localStream;
		std::string mapLocation = this->mapBaseDir + mapName + ".map";
		std::ifstream t(mapLocation.c_str());
		localStream << t.rdbuf();

		boost::property_tree::ptree pt;
		boost::property_tree::read_json(localStream, pt);

		this->world->mapName = pt.get<std::string>("map.name");
		this->world->mapBackground = pt.get<std::string>("map.background");
		this->world->mapWidth = pt.get<int>("map.width");
		this->world->mapHeight = pt.get<int>("map.height");

		std::vector<std::vector<mapTile>> tiles;

		//create vector for every row for the 2d tile array
		for(int i = 0; i < world->mapWidth;i++) {
			std::vector<mapTile> tileVector;
			tiles.push_back(tileVector);
			for(int j=0; j < world->mapHeight;j++) {
				mapTile tile(0,0,0,"");
				tiles.at(i).push_back(tile);
			}
		}
		//get AAAALLL the tiles - and put them in the 2d tiles array
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("map.tiles")) {
			assert(v.first.empty());
			int y = v.second.get<int>("y");
			int x = v.second.get<int>("x");
			int type = v.second.get<int>("t");
			std::string visual = v.second.get<std::string>("i");
			std::vector<mapTile> *yVec = &tiles[x];
			yVec->insert(yVec->begin() + y, mapTile(x, y, type, visual));
		}
		//get AAAALLL the spawn points 
		std::list<location> spawnpoints;
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("map.playerspawns")) {
			int x = v.second.get<int>("x");
			int y = v.second.get<int>("y");
			location loc = {x,y};
			spawnpoints.push_back(loc);
		}
	} catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}
