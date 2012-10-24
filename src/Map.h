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
#include <string>
#include <fstream>
#include <sstream>
/*
 * We load and store maps in this class
 * does not contain world items and such
 * does contain moving platforms etc, basically everything that's in the .map file
 *
 * .map files are plaintext json
 */

//we make a struct here and init this later in the client, because this is shared code

struct Texture {
	std::string name;							//name of .png file in /images/tiles/[name].png
	int x;										//x-coordinate of texture (x*TILEWIDTH) in the .png
	int y;										//y-coordinate of texture (y*TILEWIDTH) in the .png
};
struct tileCoord {
	int x;
	int y;
};

class Map {
public:
	std::vector<std::vector<Tile> > tiles;
	std::vector<Texture> textures;						//name of the textures, we'll copy the sf::textures to
	std::vector<tileCoord> playerSpawns;

	std::string name;
	std::string background;
	int width, height;									//height and width in nr of tiles

	Map();
	Map(std::string mapName);
	void loadMap(std::string mapName);
//	void saveMap();										//added later for the level editor
	~Map();

private:
	void mapToStringstream(std::string, std::stringstream &stream);
};

#endif /* MAP_H_ */
