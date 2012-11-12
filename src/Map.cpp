/*
 * Map.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: Remco
 */

#include "Log.h"
#include "Map.h"
#include "Tile.h"
#include <boost/algorithm/string/split.hpp>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/foreach.hpp>
#include <cassert>
#include <exception>
#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <vector>
using namespace boost;
using namespace std;

Map::Map() {

}

Map::Map(std::string mapName) {
	loadMap(mapName);

}

//splits str by splitter, returns vector
vector<string> splitString(string str, string splitter) {
	vector<string> splits;
	typedef split_iterator<string::iterator> string_split_iterator;
	for (string_split_iterator It = make_split_iterator(str,
			first_finder(splitter, is_iequal())); It != string_split_iterator();
			++It) {

		splits.push_back(copy_range<std::string>(*It));
	}
	return splits;
}

void Map::loadMap(std::string mapName) {
	/*
	 std::string mapFile = "data/maps/" + mapName + ".map";
	 ifstream ifs;
	 ifs.open(mapFile.c_str());
	 string line;
	 unsigned int i = 0;
	 int x = 0;
	 int y = 0;
	 if(ifs) {
	 while (getline(ifs, line)) {
	 if(i == 0) {
	 //first line, get map data
	 //widthxheight-:-mapname-:-mapbg
	 //2x2-:-Example map-:-background.png			[MAP DATA]
	 vector<string> mapdata = splitString(line, "-:-");
	 if((int)mapdata.size() == 3) {
	 //set bg
	 std::string background;
	 background = "images/" + mapdata[2];

	 this->name = mapdata[1];
	 std::string size = mapdata[0];
	 vector<string> sizes = splitString(size,"x");
	 this->width =  boost::lexical_cast<int>(sizes[0]);
	 this->height =  boost::lexical_cast<int>(sizes[1]);
	 std::cout << width << "x" << height << " " << name << " " << background << std::endl;
	 }
	 x=0;
	 y=0;
	 vector<Tile> vector;
	 tiles.push_back(vector);
	 }
	 else if(i < width*height+1) {
	 vector<string> tileData = splitString(line,",");
	 int type = boost::lexical_cast<int>(tileData[0]);
	 int visual = boost::lexical_cast<int>(tileData[1]);
	 Tile tile(type, visual);
	 tiles.at(y).push_back(tile);
	 std::cout << x << " " << y << " " << tileData[0] << " " << tileData[1] << std::endl;
	 x++;
	 if(x>width-1) {
	 x=0;
	 y++;
	 vector<Tile> vector;
	 tiles.push_back(vector);
	 }
	 }
	 else if(i == width*height+1) {
	 //get all player spawn spots here
	 }
	 else if(i > width*height+1) {
	 //get visuals here
	 std::cout << line << std::endl;
	 textures.push_back(line);
	 }
	 i++;
	 }
	 } else {
	 std::cout << "could not open file";
	 }
	 ifs.close();
	 */

	//MEH, let's use json instead
	try {
		std::stringstream localStream;
		std::string mapLocation = "data/maps/" + mapName + ".map";
		std::ifstream t(mapLocation.c_str());
		localStream << t.rdbuf();

		boost::property_tree::ptree pt;
		boost::property_tree::read_json(localStream, pt);

		this->name = pt.get<std::string>("map.name");
		this->background = pt.get<std::string>("map.background");
		this->width = pt.get<int>("map.width");
		this->height = pt.get<int>("map.height");
		for(int i = 0; i < width;i++) {
			//create vector for every row for the 2d tile array
			std::vector<Tile> tileVector;
			this->tiles.push_back(tileVector);
			for(int j=0; j < height;j++) {
				Tile tile(0,0,0,0,i,j);
				this->tiles.at(i).push_back(tile);
			}
		}
		//get AAAALLL the textures
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("map.visuals")) {
			assert(v.first.empty());
			int x = 1;		//TEMP, TODO: DELETE THIS
			int y = 1;
			std::string name = v.second.get<std::string>("name");			//name of .png file in /images/tiles/[name].png
			Texture texture = {name, x, y};
			this->textures.push_back(texture);
		}
		//get AAAALLL the tiles
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("map.tiles")) {
			assert(v.first.empty());
			int y = v.second.get<int>("y");
			int x = v.second.get<int>("x");
			int type = v.second.get<int>("t");
			int visual = v.second.get<int>("v");
			int textureX = v.second.get<int>("vx");
			int textureY = v.second.get<int>("vy");
			std::vector<Tile> *yVec = &tiles[x];
			yVec->insert(yVec->begin() + y, Tile(type,visual,textureX, textureY, x, y));
		}
		//get AAAALLL the spawn points
		BOOST_FOREACH(boost::property_tree::ptree::value_type &v, pt.get_child("map.playerspawns")) {
			tileCoord playerSpawnPoint = { v.second.get<int>("x"), v.second.get<int>("y") };
			this->playerSpawns.push_back(playerSpawnPoint);
		}
	} catch (std::exception const& e) {
		std::cerr << e.what() << std::endl;
	}
}

void Map::mapToStringstream(std::string mapName, std::stringstream &localStream) {

}

Map::~Map() {
//
}

