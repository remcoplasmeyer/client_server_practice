#ifndef mapTile_h
#define mapTile_h
#include <string>
#include "location.h"

class mapTile {

 public:
    location location;			//struct holding x and y
	int type;
	std::string image;
	bool solid;

	int height, width;

	mapTile();
	mapTile(int _x, int _y, int _type, std::string _image);
};

#endif // mapTile_h
