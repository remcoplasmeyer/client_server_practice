#ifndef World_h
#define World_h

#include "location.h"
#include "MapLoader.h"
#include "worldSettings.h"
#include "mapTile.h"
#include <vector>
#include <list>
#include <string>


class MapLoader;
class worldSettings;
class Player;
class mapTile;
class specialMapTiles;

class World {

 public:

	World();
    void tick();
    void restartWorld();
    void setMap(std::string mapName);
	void initTestWorld();

 public:
	std::string mapName, mapBackground;
	int mapWidth, mapHeight;

	MapLoader mapLoader;
    worldSettings worldsettings;								//settings of the current world

	std::list<location> spawnPoints;							//contains all spawnpoints
	std::vector<std::vector<mapTile>> mapTiles;					//holds all the immovable maptiles in a 2D vector
	//std::vector< specialMapTiles* > specialMaptiles;			TODO: implement special tiles, someday

    std::vector< Player* > players;								//holds all the current playing characters
};

#endif // World_h
