/*
 * Particle.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: Remco
 */

#include "Particle.h"
#include "gl/gl.h"
#include <iostream>
#include "GUI.h"

Particle::Particle() {
	// TODO Auto-generated constructor stub
}

Particle::Particle(int x, int y, int type, GUI *gui) {
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(0.f, 0.f, -200.f);
	std::cout << type;
	glBindTexture(GL_TEXTURE_2D, gui->textures[type]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	glBegin(GL_QUADS);

		glTexCoord2d(1,1); glVertex2i(0, 0);
		glTexCoord2d(0,1);  glVertex2i(0, 150);
		glTexCoord2d(1,0); glVertex2i(50, 50);
		glTexCoord2d(0,0); glVertex2i(50, 0);

	glEnd();
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}

