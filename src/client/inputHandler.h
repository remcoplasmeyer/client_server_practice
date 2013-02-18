#ifndef CLIENT_inputHandler_h
#define CLIENT_inputHandler_h
#include "netHandler.h"

namespace CLIENT {
class Client;
class netHandler;
class controlHandler;
} /* End of namespace CLIENT */

namespace CLIENT {

class inputHandler {

public:
	inputHandler();
	Client *client;

	void setClient(Client *_client);
	void sendTestPacket();
	void tick();

	netHandler nethandler;
	//controlHandler controlhandler;
};

} /* End of namespace CLIENT */

#endif // CLIENT_inputHandler_h
