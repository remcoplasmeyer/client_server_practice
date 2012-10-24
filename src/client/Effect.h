/*
 * Particle.h
 *
 *  Created on: Oct 14, 2012
 *      Author: Remco
 */

#ifndef EFFECT_H_
#define EFFECT_H_
#include "Particle.h"

class GUI;

//Particle class, contains different types of animations, particle-like
//NOTE: Particles are only client sided, they may contain a server-sided hitbox though

enum effectType { SINGLE, SPLATTER };		//different types of effects

class Effect {
public:
	float x, y;
	int type;						//base location of effect and type
	GUI *gui;

	Effect();
	Effect(float x, float y, int type, GUI *gui);
	~Effect();
};

#endif /* EFFECT_H_ */
