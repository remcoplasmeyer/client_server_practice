/*
 * Particle.h
 *
 *  Created on: Oct 14, 2012
 *      Author: Remco
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_

class GUI;

//Particle class, contains different types of animations, particle-like
//NOTE: Particles are only client sided, they may contain a server-sided hitbox though

enum particleType { SINGLE, SPLATTER };		//different types of animations/particles

class Particle {
public:
	int x, y, type;						//base location and type

	Particle();
	Particle(int x, int y, int type, GUI *gui);
	~Particle();
};

#endif /* PARTICLE_H_ */
