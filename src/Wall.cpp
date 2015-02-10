/*
 * Wall.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: Zachary Ash
 */

#include "Wall.h"

void Wall::build(void*) {
	wall.build_with_params(10 * FOOT, 10 * FOOT, 5 * FOOT, 64, 64, 64);
}

void Wall::render(bool) const{
	glColor3ub(96, 96, 96);
	glPushMatrix();
	glTranslatef(0,0,5 * FOOT);
	wall.render(false);
	glPopMatrix();
}
