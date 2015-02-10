/*
 * Wall.h
 *
 *  Created on: Feb 7, 2015
 *      Author: Zachary Ash
 */

#ifndef WALL_H_
#define WALL_H_

#include "BufferObject.h"
#include "Cube.h"

class Wall : public BufferObject {
private:
	Cube wall;

public:
	void build(void*);
	void render(bool) const;
};

#endif /* WALL_H_ */
