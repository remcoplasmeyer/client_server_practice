#include "../Log.h"
#include "viewHandler.h"
#include "Client.h"
#include "resourceLoader.h"
#include "SFML\Window.hpp"

namespace CLIENT {


	CLIENT::viewHandler::viewHandler() { 
		FILE_LOG(logDEBUG) << "view created?!";
	}

	viewHandler::viewHandler(Client *_client) {
		this->client = _client;
		this->resourceLoader = CLIENT::resourceLoader();
	}

} /* End of namespace CLIENT */
