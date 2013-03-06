#include "viewHandler.h"
#include "Client.h"
#include "../Log.h"
#include "inputHandler.h"
#include "gameHandler.h"
#include "clientSettings.h"
#include "GetTime.h"
#include <SFML/Window.hpp>

#include <windows.h>

int main() {
	CLIENT::Client client;
	return 0;
}

namespace CLIENT {

Client::Client() {
	initHandlers();

	FILE_LOG(logINFO) << "Client opened... Opening window";
	
	this->state = INGAME;			//TODO: MAKE THIS GUI DEPENDENT OR SOMETHING
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
			
			this->inputHandler.tick();	
			this->gameHandler.tick();

			t += dt;
		}
		//State state = interpolate(previous, current, accumulator/dt);		TODO: INTERPOLATE HERE, ETC
		//tick renderer
		this->view.interpolate(accumulator/dt);		//we render an alpha of the current to the next state, for interpolation
	}
}


void Client::initHandlers() {
	this->view.setClient(this);
	this->inputHandler.setClient(this);
	inputHandler.nethandler.connect("127.0.0.1", 1234);
}

} /* End of namespace CLIENT */
