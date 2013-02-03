#ifndef World_h
#define World_h

#include <vector>
#include <string>


class MapLoader;
class worldSettings;
class Player;
class mapTile;
class specialMapTiles;

class World {

 public:

    void tick();

    void restartWorld();

    void setMap(std::string mapName);

 public:
    std::string currentMap;
    int width;
    int height;

 public:

    MapLoader *mapLoader;



    worldSettings *worldsettings;

    /**
     * @element-type Player
     */
    std::vector< Player* > players;

    /**
     * @element-type mapTile
     */
    std::vector< mapTile* > maptiles;

    /**
     * @element-type specialMapTiles
     */
    std::vector< specialMapTiles* > specialMaptiles;
};

#endif // World_h
