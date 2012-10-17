/*
 * Map.cpp
 *
 *  Created on: Oct 17, 2012
 *      Author: Remco
 */

#include "Map.h"
#include "Tile.h"
#include <string>
#include <fstream>
#include <boost/algorithm/string/split.hpp>
#include <SFML/Graphics.hpp>
#include <boost/lexical_cast.hpp>
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
	for (	string_split_iterator It = make_split_iterator(str,first_finder(splitter, is_iequal()));
			It != string_split_iterator();
			++It ) {

		splits.push_back(copy_range<std::string>(*It));
	}
	return splits;
}

void Map::loadMap(std::string mapName) {
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
}

Map::~Map() {
	//
}

