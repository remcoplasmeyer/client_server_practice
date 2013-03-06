#ifndef World_h
#define World_h

#include "location.h"
#include "MapLoader.h"
#include "worldSettings.h"
#include "mapTile.h"
#include "Player.h"
#include <vector>
#include <list>
#include <string>
#include <map>


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
	void JSONtoMap(std::stringstream &jsonmap);
	void initTestWorld();
	void addPlayer(unsigned long uniqueid);

 public:
	std::string mapName;
	std::string mapBackground;
	int mapWidth, mapHeight;

	MapLoader mapLoader;
    worldSettings worldsettings;								//settings of the current world

	std::list<location> spawnPoints;							//contains all spawnpoints
	std::vector<std::vector<mapTile>> mapTiles;					//holds all the immovable maptiles in a 2D vector
	//std::vector< specialMapTiles* > specialMaptiles;			TODO: implement special tiles, someday

	typedef std::map<unsigned long, Player> playerList;
    playerList players;								//holds all the current playing characters

	//childs use this to check for a bounding box intersection
	bool boundingBoxIntersect(float x1, float y1, float width1, float height1, float x2, float y2, float width2, float height2);
};

#endif // World_h
