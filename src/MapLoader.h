#ifndef MapLoader_h
#define MapLoader_h
#include <string>

class World;

class MapLoader {

public:
	MapLoader();
	MapLoader(World *_world);
	void loadMap(std::string mapName);

private:
	std::string mapBaseDir;
	World *world;
};

#endif // MapLoader_h
