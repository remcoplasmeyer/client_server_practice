/*
 * GUI.cpp

 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */

#include "../Log.h"
#include "GUI.h"
#include "Client.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <GL/glu.h>
#include "Effect.h"
#include "Drawable.h"
#include <algorithm>
#include <cmath>

#include <boost/foreach.hpp>

//preload all textures to video card, so we can use them with glBindTextures
//this is only for opengl textures, particles etc
void GUI::loadTexturesIntoMap(std::vector<std::string> &textureFiles, std::map<std::string, GLuint> &texturesVector) {
	for(unsigned int i = 0; i < textureFiles.size(); ++i) {
		sf::Image texture;
		if(texture.loadFromFile(textureFiles.at(i))) {
			GLuint texture_handler;
			glGenTextures(1, &texture_handler);
			glBindTexture(GL_TEXTURE_2D, texture_handler);
			glTexImage2D(
				GL_TEXTURE_2D, 0, GL_RGBA,
				texture.getSize().x, texture.getSize().y, 0,
				GL_RGBA, GL_UNSIGNED_BYTE, texture.getPixelsPtr()
			);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
			glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
			texturesVector[textureFiles.at(i)] = texture_handler;
		}
	}
}
//we use this function for sfml textures, which will be used with sfml sprites
void GUI::loadSpritesIntoMap(std::vector<std::string> &textureFiles, std::map<std::string, sf::Texture> &texturesMap) {
	for(unsigned int i = 0; i < textureFiles.size(); ++i) {
		sf::Texture texture;
		texture.setRepeated(true);
		texture.loadFromFile(textureFiles[i]);
		texturesMap[textureFiles.at(i)] = texture;
	}
}

void GUI::loadAllTextures() {
	std::map<std::string, GLuint> &textureLink = textures;
	std::map<std::string, sf::Texture> &spriteTextureLink = spriteTextures;

	std::vector<std::string> effectTextures;
	effectTextures.push_back("images/effects/particle_splatter.png");
	std::vector<std::string> &effectTexturesLink = effectTextures;
	loadTexturesIntoMap(effectTexturesLink, textureLink);

	std::vector<std::string> charTextures;
	charTextures.push_back("images/chars/mario/template.png");
	std::vector<std::string> &charTexturesLink = charTextures;
	loadSpritesIntoMap(charTexturesLink, spriteTextureLink);

	std::vector<std::string> bgTextures;
	bgTextures.push_back("images/backgrounds/testbg.png");
	std::vector<std::string> &bgTexturesLink = bgTextures;
	loadSpritesIntoMap(bgTexturesLink, spriteTextureLink);
}

GUI::GUI(Client * client) {
	this->client = client;
	this->client->setGUI(this);

	sf::RenderWindow window(sf::VideoMode(this->client->settings.windowWidth, this->client->settings.windowHeight), "Client", sf::Style::Default, sf::ContextSettings(32));
	this->window = &window;
    this->window->setVerticalSyncEnabled(true);
    window.setView(view);
//    view.setCenter(500,0);
	this->window->setView(sf::View(sf::FloatRect(0, 0, this->window->getSize().x, this->window->getSize().y)));

    this->loadAllTextures();
	this->resetMapSprites();

	//get window settings
	window.setFramerateLimit(60);
	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Setup a perspective projection
	glViewport(0, 0, this->window->getSize().x, this->window->getSize().y);
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	glShadeModel(GL_SMOOTH);
	glOrtho(0.f, (float)this->window->getSize().x, (float)this->window->getSize().y, 0.f, -1.f, 1.f);

	// The main loop - ends as soon as the window is closed
	while (this->window->isOpen()) {
		//GET WINDOW EVENTS
		sf::Event event;
		while (window.pollEvent(event)) {
			//we fetch all window events in this loop
			if (event.type == sf::Event::Closed) {
				this->window->close();
			}
			if(event.type == sf::Event::LostFocus) {
				this->focus = false;
			}
			if(event.type == sf::Event::GainedFocus) {
				this->focus = true;
			}
		}
		//DONE GETTING WINDOW EVENTS

		//GET INPUT AND TICK CLIENT/WORLD
		//we fetch all other inputs here
		//we handle mouse inputs here, because they are gui dependant
		if(focus) {
			sf::Vector2i mouseVector = sf::Mouse::getPosition(window);
			float mouseX = float(mouseVector.x);
			float mouseY = float(mouseVector.y);
			//left click
			if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
				// Clear color and depth buffer
				Effect effect(mouseX, mouseY, SPLATTER, this);
			}
		}
		this->client->getInputAndTick();
		//DONE TICKING

		//DRAW EVERYTHING
		this->window->clear();
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		drawAllObjects();
		//DONE DRAWING
		handleCamera();

		//activate window, for rendering
		this->window->setActive();
		this->window->display();
	}
}

//draw all objects in toDraw and copies toDrawNext to toDraw
void GUI::drawAllObjects() {
	this->window->pushGLStates();
	//DRAW MAP BG
	int mapWidth = this->client->world.currentMap.width*this->client->world.settings.TILESIZE;
	int mapHeight = this->client->world.currentMap.height*this->client->world.settings.TILESIZE;
	sf::Texture &bgTexture = this->spriteTextures[this->client->world.currentMap.background];
	bgTexture.setRepeated(true);
	sf::Sprite bgSprite;
	bgTexture.setRepeated(true);
	bgSprite.setTexture(bgTexture);
	bgSprite.setPosition(0,0);
	bgSprite.setTextureRect(sf::IntRect(0, 0, mapWidth, mapHeight));
	this->window->draw(bgSprite);

	//LOOP AAAALLL THE TILES!
	std::vector<std::vector<Tile> > &tiles = this->client->world.currentMap.tiles;
	std::vector<std::vector<Tile> >::iterator tileItr;
	std::vector<Tile>::iterator tileYItr;
	for(tileItr = tiles.begin(); tileItr != tiles.end(); tileItr++) {
		for(tileYItr = tileItr->begin(); tileYItr != tileItr->end(); tileYItr++) {
			Tile tile = *tileYItr;
			if(tile.type != 0) {
				float x = float(tile.x)*64;
				float y = float(tile.y)*64;
				this->mapSprites.at(tile.spriteIndex).sprite.setPosition(x,y);
				this->window->draw(this->mapSprites.at(tile.spriteIndex).sprite);
			}
		}
	}

	//LOOP AAAALLL THE PLAYERS
	std::map<int, Player> &players = this->client->world.players;
	std::map<int, Player>::iterator playerItr;
	for(playerItr = players.begin(); playerItr != players.end(); playerItr++) {
		Player &player = playerItr->second;
		//TODO: STORE CHAR SPRITES SOMEWHERE
		sf::Sprite playerSprite;
		int textureX;
		int textureY = 0;
		int charSize = 41;			//TODO: store this somewhere
		switch(player.state) {
		case STANDING:
			textureX = 0;
			break;
		case RUNNING:
			if(player.textureStep < 7) {
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
		playerSprite.setTexture(this->spriteTextures[player.texturePath]);
		playerSprite.setTextureRect(sf::IntRect(textureX, textureY, invert*charSize, 64));
		playerSprite.setPosition(player.x,player.y);
		this->window->draw(playerSprite);
	}

	this->window->popGLStates();
	//THIS IS NOW DRAWING THE PARTICLES
	for(int i = 0; i < toDraw.size(); i++) {
		if(toDraw[i].get()->life == 0) {
			toDraw.erase(toDraw.begin()+i);
		} else {
			toDraw[i].get()->Draw();
		}
	}
}

void GUI::resetMapSprites() {
	std::vector<Texture> textures = this->client->world.currentMap.textures;
	std::vector<std::string> alreadyLoaded;
	for(int i = 0; i < textures.size(); i++) {
		int textureIndex = 0;
		std::vector<std::string>::iterator foundString;
		foundString = std::find(alreadyLoaded.begin(), alreadyLoaded.end(), textures.at(i).name);
		if (foundString == alreadyLoaded.end()) {
			sf::Texture texture;
			FILE_LOG(logDEBUG) << "images/tiles/" + textures.at(i).name + ".png";
			texture.loadFromFile("images/tiles/" + textures.at(i).name + ".png");
			this->mapTextures.push_back(texture);
			alreadyLoaded.push_back(textures.at(i).name);
		}
		if(textureIndex == 0) { textureIndex = alreadyLoaded.size() - 1; }
		this->mapTexturesIndex.push_back(textureIndex);
	}
	//TEXTURES LOADED FROM MAP
	//LOOP AAAALLL THE TILES!
	int i = 0;
	std::vector<std::vector<Tile> > *tiles = &this->client->world.currentMap.tiles;
	std::vector<std::vector<Tile> >::iterator tileItr;
	std::vector<Tile>::iterator tileYItr;
	for(tileItr = tiles->begin(); tileItr != tiles->end(); tileItr++) {
		for(tileYItr = tileItr->begin(); tileYItr != tileItr->end(); tileYItr++) {
			Tile *tile = &(*tileYItr);
			tile->setSprite(i);
			int textureX = (*tileYItr).textureX;
			int textureY = (*tileYItr).textureY;
			int mapTextureIndex = this->mapTexturesIndex.at((*tileYItr).textureType);
			this->mapSprites.push_back(Sprite(this, mapTextureIndex, textureX, textureY));
			i++;
		}
	}
}

void GUI::handleCamera() {
	//CHANGE CAMERA
	int windowLength = this->client->settings.windowWidth;
	int viewCoordX = this->client->world.players[this->client->clientPlayerID].x-windowLength*0.5;
	if (viewCoordX < 0) { viewCoordX = 0; }
	int mapWidth = this->client->world.currentMap.width;
	int tileSize = this->client->world.settings.TILESIZE;
	if (viewCoordX > (mapWidth*tileSize-windowLength)) { viewCoordX = mapWidth*tileSize-windowLength; }
	this->view.reset(sf::FloatRect(viewCoordX, 0, window->getSize().x, window->getSize().y));
	window->setView(view);
}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

