#ifndef MapLoader_h
#define MapLoader_h
#include <string>

class World;

class MapLoader {

public:
	MapLoader();
	void loadMap(std::string mapName);
	void setWorld(World *_world);

	std::string mapJSON;
private:
	World *world;
	std::string mapBaseDir;
};

#endif // MapLoader_h
