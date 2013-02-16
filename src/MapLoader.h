#ifndef MapLoader_h
#define MapLoader_h
#include <string>

class World;

class MapLoader {

public:
	MapLoader();
	MapLoader(World *_world);
	void loadMap(std::string mapName);

	std::string mapJSON;
private:
	World *world;
	std::string mapBaseDir;
};

#endif // MapLoader_h
