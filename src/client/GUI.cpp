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

#include <boost/foreach.hpp>

//preload all textures to video card, so we can use them with glBindTextures
void GUI::loadTextures() {
	//list of textures, hardcoded for now
	std::string textureFiles[] = { "images/effects/particle_splatter.png" };
	for(unsigned int i = 0; i < (sizeof(textureFiles) / sizeof(textureFiles[0])); ++i) {
		sf::Image texture;
		if(texture.loadFromFile(textureFiles[i])) {
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
			textures.push_back(texture_handler);
		}
	}
}

GUI::GUI(Client * client) {
	state = NOGUI;

	this->client = client;
	this->loadTextures();
	this->resetMapSprites();
	//get window settings

	sf::RenderWindow window(sf::VideoMode(800, 600), "Client", sf::Style::Default, sf::ContextSettings(32));
	state = GUILOADINGMAINSCREEN;
	window.setFramerateLimit(60);
	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	glViewport(0, 0, window.getSize().x, window.getSize().y);
	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glDepthMask(GL_TRUE);
	glHint(GL_PERSPECTIVE_CORRECTION_HINT,GL_NICEST);	// Really Nice Perspective Calculations
	glHint(GL_POINT_SMOOTH_HINT,GL_NICEST);				// Really Nice Point Smoothing

	// Setup a perspective projection
	glMatrixMode(GL_PROJECTION);
	glLoadIdentity();
	gluPerspective(90.f, 1.f, 1.f, 500.f);
	glShadeModel(GL_SMOOTH);

	// The main loop - ends as soon as the window is closed
	while (window.isOpen()) {

		sf::Event event;
		while (window.pollEvent(event)) {
			//we fetch all window events in this loop
			if (event.type == sf::Event::Closed) {
				window.close();
			}
		}

		//we fetch all other inputs here
		//get mouse coordinates first
		sf::Vector2i mouseVector = sf::Mouse::getPosition(window);
		int mouseX = mouseVector.x - (window.getSize().x / 2);
		int mouseY = mouseVector.y - (window.getSize().y / 2);
		//left click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			// Clear color and depth buffer
			Effect effect(mouseX, mouseY*-1, SPLATTER, this);		//opengl and sfml have inverted y-coordinates compared
		}

		drawAllObjects();

		//activate window, for rendering
		window.setActive();
		//display 'new' window
//		window.pushGLStates();
//		window.popGLStates();
		window.display();
	}
}

//draw all objects in toDraw and copies toDrawNext to toDraw
void GUI::drawAllObjects() {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);			//clear window
	//LOOP AAAALLL THE TILES!
	int i = 0;
	std::vector<std::vector<Tile> > tiles = this->client->world.currentMap.tiles;
	std::vector<std::vector<Tile> >::iterator tileItr;
	std::vector<Tile>::iterator tileYItr;
	for(tileItr = tiles.begin(); tileItr != tiles.end(); tileItr++) {
		for(tileYItr = tileItr->begin(); tileYItr != tileItr->end(); tileYItr++) {
			Tile tile = *tileYItr;
			float x = float(tile.x);
			float y = float(tile.y);
			this->mapSprites.at(tile.textureType).sprite.setPosition(400,400);
			this->mapSprites.at(tile.textureType).sprite.setColor(sf::Color(255, 255, 255, 200));
			this->window.draw(this->mapSprites.at(tile.textureType).sprite);
		}
	}

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
			FILE_LOG(logDEBUG) << texture.getSize().x;
			alreadyLoaded.push_back(textures.at(i).name);
		}
		if(textureIndex == 0) { textureIndex = alreadyLoaded.size() - 1; }
		this->mapTexturesIndex.push_back(textureIndex);
	}
	//TEXTURES LOADED FROM MAP
	//LOOP AAAALLL THE TILES!
	int i = 0;
	std::vector<std::vector<Tile> > tiles = this->client->world.currentMap.tiles;
	std::vector<std::vector<Tile> >::iterator tileItr;
	std::vector<Tile>::iterator tileYItr;
	for(tileItr = tiles.begin(); tileItr != tiles.end(); tileItr++) {
		for(tileYItr = tileItr->begin(); tileYItr != tileItr->end(); tileYItr++) {
			Tile tile = *tileYItr;
			tile.setSprite(i);
			int textureX = tile.textureX;
			int textureY = tile.textureY;
			int mapTextureIndex = this->mapTexturesIndex.at(tile.textureType);
			this->mapSprites.push_back(Sprite(this, mapTextureIndex, textureX, textureY));
			i++;
		}
	}
}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

