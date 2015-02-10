/*
 * Gate.cpp
 *
 *  Created on: Feb 9, 2015
 *      Author: Zachary Ash
 */

#include "Gate.h"

void Gate::build(void*) {
	side.build_with_params(15 * FOOT, 10 * FOOT, 5 * FOOT);
	top.build_with_params(5 * FOOT, 10 * FOOT, 5 * FOOT);
	gate.build_cylinder(5 * FOOT, .25 * FOOT, 30);
}

void Gate::render(bool) const {

	//render wall/frame of gate
	glColor3ub(96, 96, 96);
	glPushMatrix();
	glTranslatef(10 * FOOT, 0, 7.5 * FOOT);
	side.render(false);
	glTranslatef(-20 * FOOT, 0, 0);
	side.render(false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0, 12.5 * FOOT);
	top.render(false);
	glPopMatrix();

	//render portcullis
	
	glColor3ub(64, 64, 64);
	glPushMatrix();
	glTranslatef(-4 * FOOT, 0, 5 * FOOT);
	gate.render(false);
	for(int i = 0; i < 9; i++) {
		glTranslatef(1 * FOOT, 0, 0);
		gate.render(false);
	}
	glPopMatrix();

        for(int i = 0; i < 10; i++) {
        	glPushMatrix();
        	glTranslatef(0,0, (i+1) * FOOT);
        	glRotatef(90, 0, 1, 0);
        	gate.render(false);
        	glPopMatrix();
   	}
}
