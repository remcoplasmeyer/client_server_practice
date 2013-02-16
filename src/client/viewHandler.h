#ifndef CLIENT_viewHandler_h
#define CLIENT_viewHandler_h
#include "resourceLoader.h"
//#include "Client.h"

namespace CLIENT {
	class Client;
	class resourceLoader;
}

namespace CLIENT {

class viewHandler {
public:
	CLIENT::Client *client;

	viewHandler();
	viewHandler(Client *_client);
	resourceLoader resourceLoader;
};

} /* End of namespace CLIENT */

#endif // CLIENT_viewHandler_h
