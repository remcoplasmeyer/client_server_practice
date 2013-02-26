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
	void viewHandler::tick() {
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

	void viewHandler::drawIngameGUI() {

	}

	viewHandler::~viewHandler() {
	}

	/* end INGAME STUFF */

} /* End of namespace CLIENT */
