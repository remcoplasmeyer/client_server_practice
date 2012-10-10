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
#include <GL/glu.h>

GUI::GUI(Client * client) {
	this->client = client;
	//get window settings

	std::cout << client->settings.windowHeight << std::endl;

	sf::Window window(sf::VideoMode(client->settings.windowWidth, client->settings.windowHeight), "Client");

	// Limit the framerate to 60 frames per second
	window.setFramerateLimit(60);

	// Set color and depth clear value
	    glClearDepth(1.f);
	    glClearColor(0.f, 0.f, 0.f, 0.f);

	    // Enable Z-buffer read and write
	    glEnable(GL_DEPTH_TEST);
	    glDepthMask(GL_TRUE);

	    // Setup a perspective projection
	    glMatrixMode(GL_PROJECTION);
	    glLoadIdentity();
	    gluPerspective(90.f, 1.f, 1.f, 500.f);

	// The main loop - ends as soon as the window is closed
	while (window.isOpen()) {
		sf::Event event;

		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

		//activate window, for rendering
		window.setActive();

		//OpenGL drawing commands go here...
		 // Draw a cube
		// Clear color and depth buffer
		        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

		// Apply some transformations
		glMatrixMode(GL_MODELVIEW);
		glLoadIdentity();
		glTranslatef(0.f, 0.f, -200.f);
		glBegin(GL_QUADS);

			glVertex3f(-50.f, -50.f, -50.f);
			glVertex3f(-50.f,  50.f, -50.f);
			glVertex3f( 50.f,  50.f, -50.f);
			glVertex3f( 50.f, -50.f, -50.f);

			glVertex3f(-50.f, -50.f, 50.f);
			glVertex3f(-50.f,  50.f, 50.f);
			glVertex3f( 50.f,  50.f, 50.f);
			glVertex3f( 50.f, -50.f, 50.f);

			glVertex3f(-50.f, -50.f, -50.f);
			glVertex3f(-50.f,  50.f, -50.f);
			glVertex3f(-50.f,  50.f,  50.f);
			glVertex3f(-50.f, -50.f,  50.f);

			glVertex3f(50.f, -50.f, -50.f);
			glVertex3f(50.f,  50.f, -50.f);
			glVertex3f(50.f,  50.f,  50.f);
			glVertex3f(50.f, -50.f,  50.f);

			glVertex3f(-50.f, -50.f,  50.f);
			glVertex3f(-50.f, -50.f, -50.f);
			glVertex3f( 50.f, -50.f, -50.f);
			glVertex3f( 50.f, -50.f,  50.f);

			glVertex3f(-50.f, 50.f,  50.f);
			glVertex3f(-50.f, 50.f, -50.f);
			glVertex3f( 50.f, 50.f, -50.f);
			glVertex3f( 50.f, 50.f,  50.f);

		glEnd();


		//display 'new' window
		window.display();
	}
}

GUI::~GUI() {
	// TODO Auto-generated destructor stub
}

