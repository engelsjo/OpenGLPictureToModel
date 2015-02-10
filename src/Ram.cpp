/*
 * Ram.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: Zachary Ash
 */

#include "Ram.h"

void Ram::build(void*) {
	cylinder.build_cylinder(3 * FOOT,.9 * FOOT, 30, 64, 64, 64);
	cube.build_with_params(5 * FOOT, 9 * FOOT, 6 * FOOT, 70, 40, 10);
	roof.build_with_params(3 * FOOT, 9 * FOOT, 3 * FOOT);
}

void Ram::render(bool outline) const {
	//TODO: add color
	//render wheels

	glColor3ub(64, 64, 64);
	glPushMatrix();
    glTranslatef(-3.5 * FOOT, 0, .9 * FOOT);
    glRotatef(90, 1, 0, 0);
	cylinder.render(outline);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-1.2 * FOOT, 0, .9 * FOOT);
    glRotatef(90, 1, 0, 0);
    cylinder.render(outline);
    glPopMatrix();
    
    glPushMatrix();
    glTranslatef(1.2 * FOOT, 0, .9 * FOOT);
    glRotatef(90, 1, 0, 0);
    cylinder.render(outline);
    glPopMatrix();

    glPushMatrix();
    glTranslatef(3.5 * FOOT, 0, .9 * FOOT);
    glRotatef(90, 1, 0, 0);
	cylinder.render(outline);
	glPopMatrix();

	//render body

	glColor3ub(70, 40, 10);
	glPushMatrix();
	glTranslatef(0, 0, 4 * FOOT);
	cube.render(false);
	glPopMatrix();

	//render ram

	glColor3ub(255, 255, 255);
	glPushMatrix();
    glTranslatef(3 * FOOT,0,4 * FOOT);
    glRotatef(90, 0, 1, 0);
    cylinder.render(false);
	glPopMatrix();

	//render roof

	glColor3ub(64, 64, 64);
	glPushMatrix();
	glTranslatef(4.5 * FOOT,-3 * FOOT, 6.5 * FOOT);
    glRotatef(90, 0, 0, 1);
	roof.render(false);
	glPopMatrix();
    
    glPushMatrix();
    glTranslatef(-4.5 * FOOT,3 * FOOT, 6.5 * FOOT);
    glRotatef(270,0,0,1);
    roof.render(false);
    glPopMatrix();

	//TODO: needs a proper shape yet
}
