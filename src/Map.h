/*
 * Map.h
 *
 *  Created on: Oct 17, 2012
 *      Author: Remco
 */

#ifndef MAP_H_
#define MAP_H_
#include <string>
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include <vector>
/*
 * We load and store maps in this class
 * does not contain world items and such
 * does contain moving platforms etc, basically everything that's in the .map file
 *
 * .map files are plaintext with their own 'parsing language'
 * EXAMPLE:
 * 2x2-:-Example map-:-background.png			[MAP DATA]
 * 0,0										[TILETYPE,TILEVISUAL]
 * 0,0
 * 1,1
 * 1.1
 * 0,0-1,0									[PLAYER SPAWN PLACES]
 * images/tiles/level0_ground.png		[IMAGE THAT BELONGS TO TILETYPE 0]
 * This is a 2x2 map named 'Example map' with background 'background.png' the lines underneath represent each tile, row by row and left to right
 * if we ever decide to add more variables to the map, they'll be inserted at the end
 */

class Map {
public:
	std::vector<std::vector<Tile> > tiles;
	std::vector<std::string> textures;

	std::string name;
	std::string background;
	int width, height;									//height and width in nr of tiles

	Map();
	Map(std::string mapName);
	void loadMap(std::string mapName);
//	void saveMap();										//added later for the level editor
	~Map();
};

#endif /* MAP_H_ */
