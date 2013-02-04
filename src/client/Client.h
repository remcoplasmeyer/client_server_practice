#ifndef CLIENT_Client_h
#define CLIENT_Client_h
#include "inputHandler.h"
#include "clientSettings.h"

namespace CLIENT {
class guiHandler;
class inputHandler;
class gameHandler;
class viewHandler;
class clientSettings;
} /* End of namespace CLIENT */

namespace CLIENT {

class Client {

public:
	RakNet::TimeMS currentTime;
	RakNet::TimeMS lastUpdatedTime;

	Client();
    void tick();
	void initHandlers();

	void sendTestPacket();		//for debugging purposes

 public:

    //guiHandler guiHandler;
    CLIENT::inputHandler inputHandler;
    //gameHandler gameHandler;

    //viewHandler view;
    CLIENT::clientSettings settings;
};

} /* End of namespace CLIENT */

#endif // CLIENT_Client_h
