#ifndef CLIENT_gameHandler_h
#define CLIENT_gameHandler_h
#include <string>
#include <sstream>
#include "../World.h"

class World;

namespace CLIENT {

class gameHandler {

 public:

    World currentWorld;

	gameHandler();
	void tick();
	void setMapFromStream(std::stringstream &jsonmap);
};

} /* End of namespace CLIENT */

#endif // CLIENT_gameHandler_h
