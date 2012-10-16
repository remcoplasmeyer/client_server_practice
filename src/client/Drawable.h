/*
 * Drawable.h
 *
 *  Created on: Oct 16, 2012
 *      Author: Remco
 */

#ifndef DRAWABLE_H_
#define DRAWABLE_H_

class Drawable {
public:
	unsigned int life;						//to live in number of frames (at 60fps)

	Drawable();
	virtual ~Drawable();

	virtual void Draw();
};

#endif /* DRAWABLE_H_ */
