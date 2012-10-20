/*
 * Particle.cpp
 *
 *  Created on: Oct 16, 2012
 *      Author: Remco
 */

#include "Particle.h"
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
	Drawable::life = 180;					//3 seconds
}

Particle::~Particle() {
	// TODO Auto-generated destructor stub
}


//this function is called every game loop
void Particle::Draw() {
	x = float(x+cos(angle)*vel);
	y = float(y+sin(angle)*vel);

	// Apply some transformations
	glMatrixMode(GL_MODELVIEW);
	glLoadIdentity();
	glTranslatef(float(x), float(y), -200.f);
	glBindTexture(GL_TEXTURE_2D, this->effect->gui->textures[0]);
	glTexParameteri(GL_TEXTURE_2D,GL_TEXTURE_MAG_FILTER,GL_LINEAR);
	float alpha = (float(life)+1)/160;
	float random = float(generate_random_number(0, 100))/100;
	glColor4f(0.5f, 0.f, 0.f, alpha);
	//start drawing
	glBegin(GL_QUADS);

		glTexCoord2f(0.f,0.f);
		glVertex2f(0.f, 0.f);

		glTexCoord2f(0.f,1.f);
		glVertex2f(0.f, 10.f);

		glTexCoord2f(1.f,1.f);
		glVertex2f(10.f, 10.f);

		glTexCoord2f(1.f,0.f);
		glVertex2f(10.f, 0.f);

	glEnd();

	this->life--;
}
