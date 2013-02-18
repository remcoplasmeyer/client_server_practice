#include "../Log.h"
#include "gameHandler.h"
#include "../World.h"
#include <string>
#include <sstream>

namespace CLIENT {

	gameHandler::gameHandler() {

	}

	void gameHandler::setMapFromStream(std::stringstream &jsonmap) {
		this->currentWorld.restartWorld();
		this->currentWorld.JSONtoMap(jsonmap);
	}

	void gameHandler::tick() {
		this->currentWorld.tick();
	}

} /* End of namespace CLIENT */
