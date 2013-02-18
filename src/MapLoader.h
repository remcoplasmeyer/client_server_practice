#ifndef MapLoader_h
#define MapLoader_h
#include <string>
#include <sstream>

class World;

class MapLoader {

public:
	MapLoader();
	void test();
	void loadMap(std::string mapName);
	void JSONtoMap(std::stringstream &localStream);
	void setWorld(World *_world);
	std::string mapJSON;
private:
	std::string mapBaseDir;
	World *world;
	
};

#endif // MapLoader_h
