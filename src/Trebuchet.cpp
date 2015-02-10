/*
 * Trebuchet.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: Zachary Ash
 */

#include "Trebuchet.h"

void Trebuchet::build(void*) {
	long_beam.build_with_params(1 * FOOT, 10 * FOOT, 1 * FOOT);
	short_beam.build_with_params(1 * FOOT, 1 * FOOT, 3 * FOOT);
	mass.build_with_params(2 * FOOT, .5 * FOOT, .5 * FOOT, 2 * FOOT, 2 * FOOT, 30);
	arm.build_cylinder(5*FOOT, .5 * FOOT, 30);
}

void Trebuchet::render(bool launching) const {
	//render structure
	glColor3ub(102, 51, 0);

	//render base
	glPushMatrix();
	glTranslatef(0,1.5*FOOT,0.5*FOOT);
	long_beam.render(false);
	glTranslatef(0,-3*FOOT,0.5*FOOT);
	long_beam.render(false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(3*FOOT,0,0.5*FOOT);
	short_beam.render(false);
	glTranslatef(-6*FOOT,0,0);
	short_beam.render(false);
	glPopMatrix();

	//render upright (angled) beams
	glPushMatrix();
	glTranslatef(-2.5*FOOT, 1.5*FOOT, 4.33 * FOOT);
	glRotatef(60,0,1,0);
	long_beam.render(false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(-2.5*FOOT, -1.5*FOOT,4.33*FOOT);
	glRotatef(60,0,1,0);
	long_beam.render(false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5*FOOT, 1.5*FOOT, 4.33 * FOOT);
	glRotatef(-60,0,1,0);
	long_beam.render(false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(2.5*FOOT,-1.5*FOOT,4.33*FOOT);
	glRotatef(-60,0,1,0);
	long_beam.render(false);
	glPopMatrix();

	//render beam at top (fulcrum)
	glPushMatrix();
	glTranslatef(0,0,8.66 * FOOT);
	short_beam.render(false);
	glPopMatrix();

	//render throwing mechanism
	if(launching) {
		glColor3ub(82, 41, 0);
		glPushMatrix();
		glTranslatef(-1.50*FOOT, 0,  11.25* FOOT);
		glRotatef(-60,0,1,0);
		arm.render(false);
		glPopMatrix();

		glColor3ub(57, 52, 47);
		glPushMatrix();
		glTranslatef(1.00 *FOOT, 0,  6.93* FOOT);
		mass.render(false);
		glPopMatrix();
	}
	else {
		glColor3ub(82, 41, 0);
		glPushMatrix();
		glTranslatef(-2.30*FOOT, 0,  6.73* FOOT);
		glRotatef(40,0,1,0);
		arm.render(false);
		glPopMatrix();

		glColor3ub(57, 52, 47);
		glPushMatrix();
		glTranslatef(1.53*FOOT, 0,  9.95* FOOT);
		mass.render(false);
		glPopMatrix();
	}
}
