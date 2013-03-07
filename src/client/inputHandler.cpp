#include "../Log.h"
#include "Client.h"
#include "../Player.h"
#include "inputHandler.h"
#include "netHandler.h"
#include "controlHandler.h"
#include "SFML/Window.hpp"

/*
	the [inputHandler] handles all input: user input and input from the network
	Also handles sending out packets, as this is input to the network
*/

namespace CLIENT {

	CLIENT::inputHandler::inputHandler() {
	}

	void inputHandler::setClient(Client *_client) {
		this->client = _client;
		this->nethandler.setClient(_client);
	}

	void CLIENT::inputHandler::sendTestPacket() {
		nethandler.sendTestPacket();
	}

	//ran every client loop
	void CLIENT::inputHandler::tick() {
		//get player input, which is dependent on the current client's state
		switch(this->client->state) {
			case INGAME:
				//TODO: MAKE CONTROLS ADJUSTABLE
				//FILE_LOG(logDEBUG) << this->client->gameHandler.currentWorld.players.size();
				if(!(this->client->gameHandler.currentWorld.players.find(this->client->uniqueid) == this->client->gameHandler.currentWorld.players.end()) ) {
					Player *clientPlayer = &this->client->gameHandler.currentWorld.players[this->client->uniqueid];
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
						clientPlayer->inputJump = true;
					} else {
						clientPlayer->inputJump = false;
					}
					if(sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						clientPlayer->inputDirection = INPUT_LEFT;
					}
					if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						clientPlayer->inputDirection = INPUT_RIGHT;
					}
					if(!sf::Keyboard::isKeyPressed(sf::Keyboard::A) && !sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
						clientPlayer->inputDirection = NODIRECTION;
					}

					this->nethandler.sendClientMovementInput();
				}
			break;
		}
		//get server input
		this->nethandler.receivePackets();
	}

} /* End of namespace CLIENT */
