/*
 * Particle.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: Remco
 */

#include "Particle.h"
#include "../Log.h"
#include <GL/glu.h>
#include "GUI.h"
#include "Effect.h"
#include <iostream>
#include <cmath>
#include "Client.h"

Particle::Particle() {
	// TODO Auto-generated constructor stub

}

Particle::Particle(int x, int y, int vel, int angle, int type, Effect *effect) {
	this->x = x;
	this->y = y;
	this->vel = double(vel);
	this->type = type;
	this->angle = angle*(3.14/180);		//convert to radian
	this->effect = effect;
	this->life = 180;
	size = float(generate_random_number(0, 25));			//TODO: PUT THIS AS PARAMETER
	this->texturePath = "images/effects/particle_splatter.png";
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}


//this function is called every game loop
void Particle::Draw() {
	x = float(x-cos(angle)*vel);
	y = float(y-sin(angle)*vel);
	float x2 = float(x + size);
	float y2 = float(y + size);


	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glEnable(GL_TEXTURE_2D);
	glBindTexture(GL_TEXTURE_2D, this->effect->gui->textures[this->texturePath]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	//start drawing
	float alpha = (float(this->life)+1)/160;
//	float random = float(generate_random_number(0, 100))/100;
	glColor4f(0.5f, 0.f, 0.f, alpha);
	glBegin(GL_QUADS);

		glTexCoord2f(0.f,0.f);
		glVertex2f(x, y);

		glTexCoord2f(0.f,1.f);
		glVertex2f(x, y2);

		glTexCoord2f(1.f,1.f);
		glVertex2f(x2, y2);

		glTexCoord2f(1.f,0.f);
		glVertex2f(x2, y);

	glEnd();


	this->life--;
}
