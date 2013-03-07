#include "../Log.h"
#include "viewHandler.h"
#include "resourceLoader.h"
#include "Client.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include "../tileTypes.h"
#include "../mapTile.h"
#include <vector>

namespace CLIENT {


	viewHandler::viewHandler() { 
		FILE_LOG(logDEBUG) << "view created?!";
	}

	//used as constructor
	void viewHandler::setClient(Client* _client) {
		this->client = _client;
		window.create(sf::VideoMode(client->settings.windowWidth, client->settings.windowHeight), "Client", sf::Style::Default, sf::ContextSettings(32));
		sf::Vector2i v((sf::VideoMode::getDesktopMode().width/2)-(client->settings.windowWidth/2),(sf::VideoMode::getDesktopMode().height*0.5)-(client->settings.windowHeight*0.5));
		window.setPosition(v);
	}

	/*tick the viewHandler, called every game loop*/
	/*alpha given is the % to the next game state, in relation to the previous*/
	void viewHandler::interpolate(float alpha = 1.0f) {
		if(window.isOpen()) {
			/*POLL EVENTS - KEEP THIS, OR SFML WILL CRASH*/
			sf::Event event;
			while (window.pollEvent(event))
			{
				if (event.type == sf::Event::Closed) {
					window.close();
				}
			}
			/*DONE POLLING EVENTS*/

			window.clear();		//clear 'previous' window first

			switch(this->client->state) {
				case INGAME:		//client is ingame at the moment
				{
					drawWorld();
					drawPlayers(alpha);
					drawIngameGUI();
				}
				break;
			}

			window.display();			//display window
		}
	}

	/* INGAME STUFF */

	/* this function draws everything in the world */
	/* TODO: PUT THE TILE SIZE SOMEWHERE*/
	void viewHandler::drawWorld() {
		/* DRAW WORLD BACKGROUND */
		int mapWidth = this->client->gameHandler.currentWorld.mapWidth*64;
		int mapHeight = this->client->gameHandler.currentWorld.mapHeight*64;
		sf::Sprite bgSprite;
		bgSprite.setTexture(*this->resourceLoader.getBackground(this->client->gameHandler.currentWorld.mapBackground));
		bgSprite.setPosition(0,0);
		bgSprite.setTextureRect(sf::IntRect(0, 0, mapWidth, mapHeight));
		this->window.draw(bgSprite);

		/*LOOP AAAALLL THE MAP TILES*/
		std::vector<std::vector<mapTile>> &tiles = this->client->gameHandler.currentWorld.mapTiles;
		std::vector<std::vector<mapTile>>::iterator tileItr;
		std::vector<mapTile>::iterator tileYItr;
		for(tileItr = tiles.begin(); tileItr != tiles.end(); tileItr++) {
			for(tileYItr = tileItr->begin(); tileYItr != tileItr->end(); tileYItr++) {
				mapTile tile = *tileYItr;
				if(tile.type != AIR_TILE) {		//we don't draw air tiles... they're air
					float x = float(tile.location.x)*64;			//each tile has a height and width of 64px
					float y = float(tile.location.y)*64;
					sf::Sprite sprite;
					sprite.setTexture(*this->resourceLoader.getMapTexture(tile.image));
					sprite.setPosition(x,y);
					this->window.draw(sprite);
				}
			}
		}
		/*DONE DRAWING MAP TILES*/
	}

	void viewHandler::drawPlayers(float alpha = 1.0f) {
		/*LOOP AAAALLL THE PLAYERS*/
		std::map<unsigned long, Player> &players = this->client->gameHandler.currentWorld.players;
		std::map<unsigned long, Player>::iterator playerItr;
		for(playerItr = players.begin(); playerItr != players.end(); playerItr++) {
			Player &player = playerItr->second;
			//TODO: STORE CHAR SPRITES SOMEWHERE
			sf::Sprite playerSprite;
			int textureX = 0;
			int textureY = 0;
			int charSize = 41;			//TODO: store this somewhere
			switch(player.state) {
			case STANDING:
				textureX = 0;
				break;
			case RUNNING:
				/*if(player.textureStep < 7) {*/
				if(true) {
					textureX = charSize;
				} else {
					textureX = 2*charSize;
				}
				break;
			case INAIR:
				textureX = 3*charSize;
				break;
			}
			//TODO: DO SOMETHING ABOUT SPRITE FLIPPING
			int invert = 1;
			if(!player.goingRight) {
				invert = -1;
				textureX = (textureX+charSize);
			}
			playerSprite.setOrigin(float(invert),1.f);
			playerSprite.setTexture(*this->resourceLoader.getPlayerTexture("mario.png"));
			playerSprite.setTextureRect(sf::IntRect(textureX, textureY, invert*charSize, 64));
			//playerSprite.setScale(invert,1);						//this was used in the SFML2 snapshot version to flip the sprite, not necessary in the lastest version
			playerSprite.setPosition(player.currentState.x,player.currentState.y);
			this->window.draw(playerSprite);
		}

	}

	void viewHandler::drawIngameGUI() {

	}

	viewHandler::~viewHandler() {
	}

	/* end INGAME STUFF */

} /* End of namespace CLIENT */
