/*
 * GUI.cpp

 *
 *  Created on: Oct 10, 2012
 *      Author: Remco
 */

#include "GUI.h"
#include "Client.h"
#include <SFML/Window.hpp>
#include <SFML/Graphics.hpp>
#include <iostream>
#include <vector>
#include <string>
#include <GL/glu.h>
#include "Particle.h"

//preload all textures to video card, so we can use them with glBindTextures
void GUI::loadTextures() {
	//list of textures, hardcoded for now
	std::string textureFiles[] = { "images/effects/particle_splatter.bmp" };
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
	this->client = client;
	this->loadTextures();
	//get window settings

	std::cout << client->settings.windowHeight << std::endl;

	sf::RenderWindow window(
			sf::VideoMode(client->settings.windowWidth,
					client->settings.windowHeight), "Client");
	window.setFramerateLimit(60);

	// Set color and depth clear value
	glClearDepth(1.f);
	glClearColor(0.f, 0.f, 0.f, 0.f);

	glDisable(GL_DEPTH_TEST);
	glEnable(GL_BLEND);
	glEnable(GL_TEXTURE_2D);
	glBlendFunc(GL_SRC_ALPHA,GL_ONE);
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
		int mouseX = mouseVector.x;
		int mouseY = mouseVector.y;
		//left click
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
			// Clear color and depth buffer
			Particle particle(50, 50, SINGLE, this);
		}

		//activate window, for rendering
		window.setActive();
		//display 'new' window
		window.display();
	}
}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

