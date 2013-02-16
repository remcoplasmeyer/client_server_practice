#include "viewHandler.h"
#include "Client.h"
#include "../Log.h"
#include "inputHandler.h"
#include "clientSettings.h"
#include "GetTime.h"
#include <SFML/Window.hpp>

#include <windows.h>

int main() {
	CLIENT::Client client;
	return 0;
}

namespace CLIENT {

enum CLIENTSTATES {
	INGAME
};

Client::Client() {
	initHandlers();

	FILE_LOG(logINFO) << "Client opened... Opening window";
	sf::RenderWindow window(sf::VideoMode(settings.windowWidth, this->settings.windowHeight), "Client", sf::Style::Default, sf::ContextSettings(32));

	lastUpdatedTime = RakNet::GetTimeMS();

    float t = 0.0f;
	float dt = 1.f/(1000.f/settings.fps);

	RakNet::Time currentTime = RakNet::GetTimeMS();
	float accumulator = 0.0f;
	
	//client loop
	while (true) 
	{			
		RakNet::Time newTime = RakNet::GetTimeMS();
		float deltaTime = newTime - currentTime;
		currentTime = newTime;
		if (deltaTime > 0.25f)
			deltaTime = 0.25f;
		
		accumulator += deltaTime;
		while (accumulator >= dt)
		{
			accumulator -= dt;
			//previous = current;			TODO: IMPLEMENT STATES
			//integrate(current, t, dt);	TODO: integrate here
			t += dt;
		}
		//State state = interpolate(previous, current, accumulator/dt);		TODO: INTERPOLATE HERE, ETC
		this->inputHandler.tick();
		
		window.setActive();
		window.display();		
	}
}


void Client::initHandlers() {
	inputHandler.nethandler.connect("127.0.0.1", 1234);

	//guiHandler *guiHandler;
    //gameHandler *gameHandler;

}

void Client::tick()
{

}

} /* End of namespace CLIENT */
