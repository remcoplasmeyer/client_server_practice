#ifndef CLIENT_inputHandler_h
#define CLIENT_inputHandler_h
#include "netHandler.h"
#include "controlHandler.h"

namespace CLIENT {
class netHandler;
class controlHandler;
} /* End of namespace CLIENT */

namespace CLIENT {

class inputHandler {

public:
	inputHandler();

	void sendTestPacket();

	CLIENT::netHandler nethandler;
	CLIENT::controlHandler controlhandler;
};

} /* End of namespace CLIENT */

#endif // CLIENT_inputHandler_h
