#ifndef CLIENT_viewHandler_h
#define CLIENT_viewHandler_h
#include "resourceLoader.h"
//#include "Client.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>

namespace CLIENT {
	class Client;
	//class resourceLoader;
}

namespace CLIENT {

class viewHandler {
public:
	CLIENT::Client *client;
	sf::RenderWindow window;

	viewHandler();
	~viewHandler();
	void setClient(Client* _client);
	void interpolate(float alpha);
	void drawPlayers(float alpha);
	void drawWorld();
	void drawIngameGUI();

	//guiHandler guiHandler;			//we'll add this when we add the GUI
	resourceLoader resourceLoader;		/*loads all the resources: sprites etc*/
};

} /* End of namespace CLIENT */

#endif // CLIENT_viewHandler_h
