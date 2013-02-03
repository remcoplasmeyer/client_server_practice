#include "serverSettings.h"

namespace SERVER {

	serverSettings::serverSettings() {
		//Init server settings values hardcoded, for now
		this->name = "Server test name";
		this->password = "password";
		this->port = 1234;
		this->maxPlayers = 8;
		this->fps = 50;
	}

} /* End of namespace SERVER */
