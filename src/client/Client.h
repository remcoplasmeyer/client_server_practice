#ifndef CLIENT_Client_h
#define CLIENT_Client_h
#include "viewHandler.h"
#include "inputHandler.h"
#include "gameHandler.h"
#include "clientSettings.h"
#include "RakNetTime.h"

namespace CLIENT {

enum CLIENTSTATES {
	INGAME
};

class Client {

public:
	int state;
	
	sf::RenderWindow window;

	RakNet::TimeMS currentTime;
	RakNet::TimeMS lastUpdatedTime;

	Client();
	void tick();
	void initHandlers();

	void sendTestPacket();		//for debugging purposes

	//HANDLERS

	inputHandler inputHandler;
    gameHandler gameHandler;
	viewHandler view;
    CLIENT::clientSettings settings;
};

} /* End of namespace CLIENT */

#endif // CLIENT_Client_h
