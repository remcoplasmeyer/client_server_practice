/*
 * Particle.cpp
 *
 *  Created on: Oct 14, 2012
 *      Author: Remco
 */

#include "Effect.h"
#include "gl/gl.h"
#include <iostream>
#include "GUI.h"
#include "Particle.h"
#include "Client.h"
#include <boost/shared_ptr.hpp>

Effect::Effect() {
	// TODO Auto-generated constructor stub
}

Effect::Effect(float x, float y, int type, GUI *gui) {
	this->gui = gui;
	this->x = x;
	this->y = y;
	this->type = type;

	if(type == SPLATTER) {
		int random = generate_random_number(4, 8);
		for(int i = 0;i < random; ++i) {
			int randomAngle = generate_random_number(0, 180);
			int randomSpeed = generate_random_number(2, 5);
			typedef boost::shared_ptr<Drawable> todraw_ptr;
			todraw_ptr particlePtr(new Particle(x, y, randomSpeed, randomAngle, LIGHTPARTICLE, this));
			gui->toDraw.push_back(particlePtr);
		}
	}
}

Effect::~Effect() {
	// TODO Auto-generated destructor stub
}

