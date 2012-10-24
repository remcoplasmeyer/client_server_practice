/*
 * Particle.h
 *
 *  Created on: Oct 16, 2012
 *      Author: Remco
 */

#ifndef PARTICLE_H_
#define PARTICLE_H_
#include "Drawable.h"
#include <string>

/*class of one 'particle' or a bitmap of one particle
 * too lazy for getters/setters right now
 * NOTE: this class does not contain the 'randomness' of a particle.
 * Once a particle has been generated, it lives on it's own. The Draw() method can also be seen as a 'Update' method
 * in this case.
 *
 * TODO:
 * color changing
 * moving in a traject rather than linear
 * change of speed by easing
 */

class GUI;
class Effect;

enum particleType { LIGHTPARTICLE };		//different types of animations/particles

class Particle : public Drawable {
public:
	int type;	//location, velocity, type(effectType) and angle of the particle
	float x, y, size;
	double angle, vel;
	Effect *effect;
	std::string texturePath;

	Particle();
	Particle(int x, int y, int vel, int angle, int type, Effect *effect);
	~Particle();

	void Draw();
};

#endif /* PARTICLE_H_ */
