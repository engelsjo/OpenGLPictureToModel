/*
 * Castle.cpp
 *
 *  Created on: Feb 7, 2015
 *      Author: Zachary Ash
 */

#include "Castle.h"

void Castle::build(void*) {
	castle.build_with_params(60 * FOOT, 40 * FOOT, 40 * FOOT, 75, 75, 75);
	tower.build_cylinder(5 * FOOT,  4* FOOT, 30, 200, 200, 200);
	roof.build_with_params(6 * FOOT, 10 * FOOT, 30, 102, 0, 0);
	bigTower.build_cylinder(10 * FOOT, 9 * FOOT, 30, 255, 255, 255);
	bigRoof.build_with_params(12 * FOOT, 20 * FOOT, 30, 255, 0, 0);
}

void Castle::render(bool) const {

	//render castle building

	glPushMatrix();
	glTranslatef(0, 0, 30 * FOOT);
	castle.render(false);
	glPopMatrix();

	//render towers

	glPushMatrix();
	glTranslatef(17 * FOOT, 17 * FOOT, 65 * FOOT);
	tower.render(false);

	glTranslatef(-34 * FOOT, 0, 0);
	tower.render(false);

	glTranslatef(0, -34 * FOOT, 0);
	tower.render(false);

	glTranslatef(34 * FOOT, 0, 0);
	tower.render(false);

	glTranslatef(0, 0, 5* FOOT);
	roof.render(false);

	glTranslatef(-34 * FOOT, 0, 0);
	roof.render(false);

	glTranslatef(0, 34 * FOOT, 0);
	roof.render(false);

	glTranslatef(34 * FOOT, 0, 0);
	roof.render(false);
	glPopMatrix();

	glPushMatrix();
	glTranslatef(0,0, 70 * FOOT);
	bigTower.render(false);

	glTranslatef(0, 0, 10 * FOOT);
	bigRoof.render(false);
	glPopMatrix();
}
