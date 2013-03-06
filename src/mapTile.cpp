#include "mapTile.h"
#include "tileTypes.h"
#include "location.h"
#include <string>

mapTile::mapTile() { };

mapTile::mapTile(int _x, int _y, int _type, std::string _image) {
	location.x = _x;
	location.y = _y;
	this->type = _type;
	this->solid = false;
	//hardcoded size for now
	this->width = 64;
	this->height = 64;
	if(type != AIR_TILE) {	//air tiles don't have an image
		this->image = _image + ".png";
		this->solid = true;
	}
}