#ifndef World_h
#define World_h

#include <vector>
#include <string>
#include "MapLoader.h"
#include "worldSettings.h"
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
	//map settings		-		WE BEGIN ALL MAP VALUES WITH THE PREFIX map*
	std::string mapName, mapBackground;
	int mapWidth, mapHeight;
	//end map settings

 public:

    MapLoader mapLoader;
    worldSettings worldsettings;								//settings of the current world

    std::vector< Player* > players;								//holds all the current playing characters
    std::vector< mapTile* > maptiles;							//holds all the immovable maptiles
    //std::vector< specialMapTiles* > specialMaptiles;			TODO: implement special tiles, someday
};

#endif // World_h
