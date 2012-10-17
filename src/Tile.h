/*
 * Tile.h
 *
 *  Created on: Oct 17, 2012
 *      Author: Remco
 */

#ifndef TILE_H_
#define TILE_H_
#include <string>

/* Contains all tiles and their types
 * NOTE: these are not items/players
 */

enum tileTypes { TILE_NOTHING, TILE_BLOCK };

class Tile {
public:
	int type;
	float width, height;				//size relative to 1 tile
	float offsetX, offsetY;				//offset from upperleft corner of tile in [0,1>, always 0 on non-moving tiles

	int vel, angle;						//always 0 for non-moving tiles
	bool solid;
	bool underGoThrough;				//if set, you can jump through bottom

	int tileImage;						//tile image, string of file can be found in [Map].textures

	Tile();
	Tile(int type, int tileImage);
	~Tile();
};

#endif /* TILE_H_ */
