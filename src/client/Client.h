#ifndef CLIENT_Client_h
#define CLIENT_Client_h
#include "viewHandler.h"
#include "inputHandler.h"
#include "clientSettings.h"

namespace CLIENT {

class Client {

public:
	int state;

	RakNet::TimeMS currentTime;
	RakNet::TimeMS lastUpdatedTime;

	Client();
	void tick();
	void initHandlers();

	void sendTestPacket();		//for debugging purposes

	//HANDLERS

    //guiHandler guiHandler;
	inputHandler inputHandler;
	//viewHandler view;
    //gameHandler gameHandler;

    CLIENT::clientSettings settings;
};

} /* End of namespace CLIENT */

#endif // CLIENT_Client_h
